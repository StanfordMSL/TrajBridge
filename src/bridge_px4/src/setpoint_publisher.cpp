#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~hz_out", hz_out);
    ros::param::get("~checkup_hz", checkup_hz);
    ros::param::get("~checkup_hz_min", checkup_hz_min);
    ros::param::get("~hz_in_min", hz_in_min);
    ros::param::get("~dt_fs", dt_fs);
    ros::param::get("~dt_rs",dt_rs);
    ros::param::get("~z_fs",z_fs);

    // ROS Initialization
    pose_sp_sub = nh.subscribe("setpoint/pose",1,&SetpointPublisher::pose_sp_cb,this);
    vels_sp_sub = nh.subscribe("setpoint/velocity",1,&SetpointPublisher::vels_sp_cb,this);
    accs_sp_sub = nh.subscribe("setpoint/acceleration",1,&SetpointPublisher::accs_sp_cb,this);
    
    pose_cr_sub = nh.subscribe("mavros/vision_pose/pose",10,&SetpointPublisher::pose_cr_cb,this);
    mavs_cr_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mavs_cr_cb,this);

    poseT_sp_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    attdT_sp_pub = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);

    setpointLoop = nh.createTimer(ros::Duration(1.0/sp_out_hz),&SetpointPublisher::setpoint_cb, this);
    checkupLoop  = nh.createTimer(ros::Duration(1.0/checkup_hz),&SetpointPublisher::checkup_cb, this);

    land_client = nh.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");

    ROS_INFO("ROS Components Initialized");

    // State Machine Initialization
    sp_pub_state    = STARTUP;
    mc_stream_state = MC_INIT;
    ob_mode_state   = OB_INIT;
    ac_mode_state   = AC_INIT;
    ROS_INFO("State Machines Initialized.");
    ROS_INFO("SP_PUB_STATE: STARTUP");

    // Constants Initialized
    quat_forward.w = 1;
    quat_forward.x = 0;
    quat_forward.y = 0;
    quat_forward.z = 0;

    n_rs = ceil(dt_rs*sp_out_hz);

    // Stream Timer Checks
    pose_dt_max = ros::Duration(1.0/pose_hz_min);
    vels_dt_max = ros::Duration(1.0/vels_hz_min);
    accs_dt_max = ros::Duration(1.0/accs_hz_min);
    checkup_dt_max  = ros::Duration(1.0/checkup_hz_min);
    dt_max = pose_dt_max;
    dt_max_vect(0,0) = pose_dt_max.toSec();
    dt_max_vect(1,0) = vels_dt_max.toSec();
    dt_max_vect(2,0) = accs_dt_max.toSec();

    ROS_INFO("Timers Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

void SetpointPublisher::pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_sp = *msg;
}

void SetpointPublisher::vels_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
    vels_sp = *msg;
}

void SetpointPublisher::accs_sp_cb(const geometry_msgs::AccelStamped::ConstPtr& msg){
    accs_sp = *msg;
}

void SetpointPublisher::pose_cr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_cr = *msg;
}

void SetpointPublisher::mavs_cr_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_cr = *msg;

    if (mode_cr.mode == "OFFBOARD") {
        ob_mode_state = OB_ON;
    } else if ( (mode_cr.mode == "POSCTL") || (mode_cr.mode == "STABILIZED") || (mode_cr.mode == "ALTCTL") )
    {
        ob_mode_state = OB_OFF;
    }

}

void SetpointPublisher::pub_sp_pose() {
    pose_compute();
    
    poseT_sp.header.stamp = ros::Time::now();
    poseT_sp.header.seq   = k_main;
    poseT_sp.header.frame_id = "map";

    poseT_sp_pub.publish(poseT_sp);

    //std::cout << "Publishing Pos: " << k_main << std::endl;
}

void SetpointPublisher::pub_sp_attd() {
    attD_compute();

    attdT_sp.header.stamp = ros::Time::now();
    attdT_sp.header.seq   = k_main;
    attdT_sp.header.frame_id = "map";
    attdT_sp.type_mask = attdT_sp.IGNORE_ATTITUDE;

    attdT_sp_pub.publish(attdT_sp);

    //std::cout << "Publishing BR " << k_main << std::endl;
    //std::cout <<  att_sp_out.thrust << std::endl;
}

void SetpointPublisher::pub_sp_active() {
    switch (sp_type_state)
    {
    case TP_NONE:
    {
        ac_mode_state = AC_OFF;
        ROS_INFO("Trajectory Complete/Stopped");
    }
    break;
    case TP_POS:
    {
        pub_sp_pose();
    }
    break;
    case TP_ATT:
    {
        pub_sp_attd();
        //cout <<  att_sp_in.thrust << std::endl;
    }
    break;
    default:
    {
        ac_mode_state = AC_OFF;
        ROS_INFO("STREAM TYPE UNKNOWN");
    }
    }
}

void SetpointPublisher::setpoint_cb(const ros::TimerEvent& event)
{
    switch (sp_pub_state)
    {
    case STARTUP:
    {
        // Do State Tasks
        ROS_DEBUG("STARTUP");

        pose_sp.pose = pose_sa;
        pose_sp_out.pose.position.z = 0.0f;

        pub_sp_pos();

        // State Transition
        if ((mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF))
        {
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ((mc_stream_state == MC_ON) && (ob_mode_state != OB_OFF))
        {
            ROS_DEBUG("OFFBOARD switch is not off. Blocking state transform from STARTUP to LINKED.");
        } else
        {
            // Stay in State
        }

    }
    break;
    case LINKED:
    {
        // Do State Tasks
        ROS_DEBUG("LINKED");

        pose_sa.position = pose_curr.pose.position;
        pose_sa.orientation = quat_forward;

        pose_sp_out.pose = pose_sa;
        pose_sp_out.pose.position.z = 0.0f;

        pub_sp_pos();

        // State Transition
        if (mc_stream_state == MC_OFF)
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) )
        {
            pose_sa.position.z = z_fs;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_ON) )
        {
            ROS_DEBUG("BOTH OB and SP are ON. Blocking state transform from LINKED to HOVER.");
        } else
        {
            // Stay in State
        }
    }
    break;
    case HOVER:
    {
        // Do State Tasks
        ROS_DEBUG("HOVER");

        pose_sp_out.pose = pose_sa;

        pub_sp_pos();

        // State Transition
        if (mc_stream_state == MC_OFF)
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF)  ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_ON) )
        {
            sp_pub_state = ACTIVE;
            ROS_INFO("SP_PUB_STATE: ACTIVE");
        } else {
            // Stay in State
        }
    }
    break;
    case ACTIVE:
    {
        // Do State Tasks
        ROS_DEBUG("ACTIVE");

        pub_sp_active();

        //pose_sa.position = pose_curr.pose.position;
        //pose_sa.orientation = quat_forward;
        pose_sa = pose_curr.pose;

        // State Transition
        if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) )
        {
//            pose_sa.position.z = 1.0;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        } else if (mc_stream_state == MC_OFF)
        {
            pose_sa.position = pose_curr.pose.position;
            pose_sa.position.z = pose_sa.position.z-0.2;

            t_fs = ros::Time::now();
            k_rs = 0;

            sp_pub_state = FAILSAFE;
            ROS_INFO("SP_PUB_STATE: FAILSAFE");
        } else {
            // Stay in State
        }
        //std::cout <<  att_sp_in.thrust << std::endl;

    }
    break;
    case FAILSAFE:
    {
        // Do State Tasks
        ROS_DEBUG("FAILSAFE");

        pose_sp_out.pose = pose_sa;

        pub_sp_pos();

        // State Transition
        ros::Time t_now = ros::Time::now();
        if ( (t_now - t_fs) >= ros::Duration(dt_fs) ) {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (mc_stream_state == MC_OFF) && (ob_mode_state == OB_OFF) ) {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) )
        {
            k_rs += 1;
            if  ( (k_rs >= n_rs)  && (sp_stream_state == SP_OFF) ) {
                pose_sa.position.z = z_fs;

                sp_pub_state = HOVER;
                ROS_INFO("SP_PUB_STATE: HOVER");
            } else if ( (k_rs >= n_rs)  && (sp_stream_state == SP_ON) ) {
                sp_pub_state = ACTIVE;
                ROS_INFO("SP_PUB_STATE: ACTIVE");
            } else {
                // Stay in failsafe mode.
            }
        }
    }
    break;
    default:
    {
        ROS_DEBUG("default (should not be here)");

        land();
        pose_sp_out.pose = pose_curr.pose;
        pose_sp_out.pose.position.z = 0.0f;

        pub_sp_pos();
    }
    }

    //std::cout << "Z Height Is: " << pose_sa.position.z << std::endl;

    k_main++;
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {

    sp_type_assign();
    if (t_last > dt_max) {
        if (sp_stream_state == SP_ON) {
            ROS_INFO("Setpoint Stream Stopped");
        }

        ROS_DEBUG("Setpoint Stream Off");

        sp_stream_state = SP_OFF;
    } else
    {
        ROS_DEBUG("Setpoint Stream On");

        sp_stream_state = SP_ON;
    }

    ros::Time t_now = ros::Time::now();
    if ((t_now - pose_curr.header.stamp) > checkup_dt_max) {
        if (mc_stream_state == MC_ON) {
            ROS_INFO("MoCap Stream Broken. Last vision_pose message came in at: %f", pose_curr.header.stamp.toSec());
        }
        ROS_DEBUG("MoCap Stream Off");

        mc_stream_state = MC_OFF;
    } else
    {
        ROS_DEBUG("MoCap Stream On");

        mc_stream_state = MC_ON;
    }
}

void SetpointPublisher::land() {
    mavros_msgs::CommandTOL srv_land;
    if (land_client.call(srv_land) && srv_land.response.success)
    {
        ROS_INFO("Land Successful");
    } else {
        ROS_WARN("Land Failed");
    }
}

void SetpointPublisher::pose_compute() {
    poseT_sp.pose = pose_sp.pose;
}

void SetpointPublisher::attD_compute() {
    attdT_sp.thrust = 0.0;
    attdT_sp.body_rate.x = 0.0;
    attdT_sp.body_rate.y = 0.0;
    attdT_sp.body_rate.z = 0.0;
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

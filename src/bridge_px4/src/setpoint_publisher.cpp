#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~sp_out_hz", sp_out_hz);
    ros::param::get("~checkup_hz", checkup_hz);
    ros::param::get("~z_fs",z_fs);

    // ROS Initialization
    pose_sp_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    vel_sp_pub  = nh.advertise<geometry_msgs::Twist>("mavros/setpoint_velocity/cmd_vel_unstamped",1);
    att_sp_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);

    pos_sp_sub = nh.subscribe("setpoint/position",1,&SetpointPublisher::pose_sp_cb,this);
    vel_sp_sub  = nh.subscribe("setpoint/velocity",1,&SetpointPublisher::vel_sp_cb,this);
    att_sp_sub  = nh.subscribe("setpoint/attitude",1,&SetpointPublisher::att_sp_cb,this);

    pose_curr_sub = nh.subscribe("mavros/local_position/pose",10,&SetpointPublisher::pose_curr_cb,this);
    mav_state_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mav_state_cb,this);

    land_client = nh.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");

    setpointLoop = nh.createTimer(ros::Duration(1.0/sp_out_hz),&SetpointPublisher::setpoint_cb, this);
    checkupLoop  = nh.createTimer(ros::Duration(1.0/checkup_hz),&SetpointPublisher::checkup_cb, this);

    ROS_INFO("ROS Components Initialized");

    // State Machine Initialization
    sp_pub_state    = STARTUP;
    mc_stream_state = MC_INIT;
    ob_mode_state   = OB_INIT;
    sp_stream_state = SP_INIT;
    sp_type_state   = TP_NONE;
    ROS_INFO("State Machines Initialized.");
    ROS_INFO("SP_PUB_STATE: STARTUP");

    // Constants Initialized
    quat_forward.w = 1;
    quat_forward.x = 0;
    quat_forward.y = 0;
    quat_forward.z = 0;

    // Stream Timer Checks
    ROS_INFO("Timers Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

void SetpointPublisher::pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_sp_in = *msg;
}

void SetpointPublisher::vel_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
    vel_sp_in = *msg;
}

void SetpointPublisher::att_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg){
    att_sp_in = *msg;
}

void SetpointPublisher::pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_curr = *msg;
}

void SetpointPublisher::mav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_cr = *msg;

    if (mode_cr.mode == "OFFBOARD") {
        ob_mode_state = OB_ON;
    } else {
        ob_mode_state = OB_OFF;
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

        pose_sp_out.pose = pose_sa;
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
    ros::Time t_now = ros::Time::now();

    // Check if Target States are Publishing


    // Check if Mocap Stream is Publishing


    // Check if Drone is in Safe Ball
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

void SetpointPublisher::pub_sp() {
    // pose_sp_out.header.stamp = ros::Time::now();
    // pose_sp_out.header.seq   = k_main;
    // pose_sp_out.header.frame_id = "map";

    // Pose is always published
    pose_sp_pub.publish(pose_sp_out);
    vel_sp_pub.publish(vel_sp_out);
    att_sp_pub.publish(att_sp_out);

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~sp_out_hz", sp_out_hz);
    ros::param::get("~checkup_hz", checkup_hz);    
    ros::param::get("~sp_gcs_hz_min", sp_gcs_hz_min);
    ros::param::get("~checkup_hz_min", checkup_hz_min);
    ros::param::get("~dt_fs", dt_fs);
    ros::param::get("~dt_rs",dt_rs);

    // ROS Initialization
    pose_sp_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    pose_sp_sub = nh.subscribe("gcs/setpoint/pose",1,&SetpointPublisher::pose_sp_cb,this);    
    pose_curr_sub = nh.subscribe("mavros/vision_pose/pose",1,&SetpointPublisher::pose_curr_cb,this);
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
    ROS_INFO("State Machines Initialized.");
    ROS_INFO("SP_PUB_STATE: STARTUP");

    // Constants Initialized
    quat_forward.w = 1;
    quat_forward.x = 0;
    quat_forward.y = 0;
    quat_forward.z = 0;

    n_rs = ceil(dt_rs*sp_out_hz);

    // Stream Timer Checks
    setpoint_dt_max = ros::Duration(1.0/sp_gcs_hz_min);
    checkup_dt_max  = ros::Duration(1.0/checkup_hz_min);

    ROS_INFO("Timers Initialized.");
}
SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

void SetpointPublisher::pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_t_sp_gcs = *msg;
}

void SetpointPublisher::pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_t_curr = *msg;
}

void SetpointPublisher::mav_state_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_cr = *msg;

    if (mode_cr.mode == "OFFBOARD") {
        ob_mode_state = OB_ON;
    } else if ( (mode_cr.mode == "POSCTL") || (mode_cr.mode == "STABILIZED") || (mode_cr.mode == "ALTCTL") )
    {
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

        pose_t_sp_out.pose = pose_sa;
        pose_t_sp_out.pose.position.z = 0.0f;
        
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

        pose_sa.position = pose_t_curr.pose.position;
        pose_sa.orientation = quat_forward;

        pose_t_sp_out.pose = pose_sa;
        pose_t_sp_out.pose.position.z = 0.0f;

        // State Transition
        if (mc_stream_state == MC_OFF)
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) ) 
        {
            pose_sa.position.z = 1.0;

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

        pose_t_sp_out.pose = pose_sa;

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

        pose_t_sp_out.pose = pose_t_sp_gcs.pose;

        pose_sa.position = pose_t_curr.pose.position;
        pose_sa.orientation = quat_forward;

        // State Transition
        if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) )
        {
            pose_sa.position.z = 1.0;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        } else if (mc_stream_state == MC_OFF) 
        {
            pose_sa.position = pose_t_curr.pose.position;
            pose_sa.position.z = pose_sa.position.z-0.2;

            t_fs = ros::Time::now();
            k_rs = 0;

            sp_pub_state = FAILSAFE;
            ROS_INFO("SP_PUB_STATE: FAILSAFE");
        } else {
            // Stay in State            
        }
    }
    break;
    case FAILSAFE:
    {
        // Do State Tasks
        ROS_DEBUG("FAILSAFE");

        pose_t_sp_out.pose = pose_sa;

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
                pose_sa.position.z = 1.0;

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
        pose_t_sp_out.pose = pose_t_curr.pose;
        pose_t_sp_out.pose.position.z = 0.0f;
    }
    }

    pose_t_sp_out.header.stamp = ros::Time::now();
    pose_t_sp_out.header.seq   = k_main;
    pose_t_sp_out.header.frame_id = "world";
    k_main++;

    pose_sp_pub.publish(pose_t_sp_out);
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {

    ros::Time t_now = ros::Time::now();
    
    if ((t_now - pose_t_sp_gcs.header.stamp) > setpoint_dt_max) {
        if (sp_stream_state == SP_ON) {
            ROS_INFO("Setpoint Stream Broken");
        }
        ROS_DEBUG("Setpoint Stream Off");

        sp_stream_state = SP_OFF;
    } else
    {
        ROS_DEBUG("Setpoint Stream On");

        sp_stream_state = SP_ON;
    }

    if ((t_now - pose_t_curr.header.stamp) > checkup_dt_max) {
        if (mc_stream_state == MC_ON) {
            ROS_INFO("MoCap Stream Broken");
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

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~sp_out_hz", sp_out_hz);
    ros::param::get("~checkup_hz", checkup_hz);
    ros::param::get("~z_fs",z_fs);
    ros::param::get("~r_fs",r_fs);
    ros::param::get("~sp_toff",sp_toff);
    ros::param::get("~land_fs",land_fs);

    // ROS Initialization
    pos_sp_sub  = nh.subscribe("setpoint/position",1,&SetpointPublisher::pos_sp_cb,this);
    att_sp_sub  = nh.subscribe("setpoint/attitude",1,&SetpointPublisher::att_sp_cb,this);

    pose_sp_pub  = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);

    pose_curr_sub = nh.subscribe("mavros/local_position/pose",10,&SetpointPublisher::pose_curr_cb,this);
    mav_state_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mav_state_cb,this);

    setpointLoop = nh.createTimer(ros::Duration(1.0/sp_out_hz),&SetpointPublisher::setpoint_cb, this);
    checkupLoop  = nh.createTimer(ros::Duration(1.0/checkup_hz),&SetpointPublisher::checkup_cb, this);

    toff_client = nh.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/takeoff");
    land_client = nh.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");

    ROS_INFO("ROS Components Initialized");

    // State Machine Initialization
    sp_pub_state    = STARTUP;
    ep_stream_state = EP_INIT;
    ob_mode_state   = OB_INIT;
    sp_stream_state = SP_INIT;
    ROS_INFO("State Machines Initialized.");
    ROS_INFO("SP_PUB_STATE: STARTUP");

    // Constants and Counters Initialized
    k_main = 0;
    dt_max = ros::Duration(1.0/checkup_hz);
    quat_forward.w = 1.0;
    quat_forward.x = 0.0;
    quat_forward.y = 0.0;
    quat_forward.z = 0.0;
    pos_check = false;
    att_check = false;

    // Stream Timer Checks
    ROS_INFO("Timers Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating SetpointPublisher");
}

void SetpointPublisher::pos_sp_cb(const geometry_msgs::PointStamped::ConstPtr& msg){
    sp_stream_state = SP_ON;
    pos_check = true;    
    pos_sp_in = *msg;
}

void SetpointPublisher::att_sp_cb(const geometry_msgs::QuaternionStamped::ConstPtr& msg){
    sp_stream_state = SP_ON;
    att_check = true;
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

        pose_sa = pose_curr.pose;
        pose_sa.position.z = 0.0f;

        pose_sp_out.pose = pose_sa;
        pub_sp();

        // State Transition
        if ((ep_stream_state == EP_ON) && (ob_mode_state == OB_OFF))
        {
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ((ep_stream_state == EP_ON) && (ob_mode_state != OB_OFF))
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

        pose_sa = pose_curr.pose;
        pose_sa.position.z = 0.0f;

        pose_sp_out.pose = pose_sa;
        pub_sp();

        // State Transition
        if (ep_stream_state == EP_OFF)
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) )
        {
            pose_st = pose_sa;
            toff();

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        } else if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_ON) )
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

        pose_sa.position.z = z_fs;
        
        pose_sp_out.pose = pose_sa;
        pub_sp();

        // State Transition
        if (ep_stream_state == EP_OFF)
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        } else if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_OFF)  ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_ON) )
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

        pose_sa = pose_curr.pose;
        
        pose_sp_out.pose.position = pos_sp_in.point;
        pose_sp_out.pose.orientation = att_sp_in.quaternion;
        pub_sp();

        // State Transition
        if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_OFF) ) {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        } else if ( (ep_stream_state == EP_ON) && (ob_mode_state == OB_ON) && (sp_stream_state == SP_OFF) )
        {
//            pose_sa.position.z = 1.0;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        } else if (ep_stream_state == EP_OFF) {
            land();

            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: INIT");
        } else {
            // Stay in State
        }
        //std::cout <<  att_sp_in.thrust << std::endl;

    }
    break;
    default:
    {
        ROS_DEBUG("default (should not be here)");
        land();
    }
    }

    //std::cout << "Z Height Is: " << pose_sa.position.z << std::endl;

    k_main++;
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {
    // Current Time
    ros::Time t_now = ros::Time::now();

    // Check if Target States are Publishing
    pos_check = ((t_now - pos_sp_in.header.stamp) < dt_max) ? true : false;
    att_check = ((t_now - att_sp_in.header.stamp) < dt_max) ? true : false;

    if ((pos_check == false) && (att_check == false)) {
        sp_stream_state = SP_OFF;
    }
    
    // Check if Target States are Publishing
    if ((t_now - pose_curr.header.stamp) < dt_max) {
        ep_stream_state = EP_ON;
    } else {
        ep_stream_state = EP_OFF;
    }

    // Check if Drone is in Safe Ball
    Eigen::Vector3f err_pos;
    err_pos <<  pose_curr.pose.position.x - pose_sp_out.pose.position.x,
                pose_curr.pose.position.y - pose_sp_out.pose.position.y,
                pose_curr.pose.position.z - pose_sp_out.pose.position.z;

    if (err_pos.norm() > r_fs) {
        land();

        sp_pub_state = STARTUP;
        ROS_INFO("SP_PUB_STATE: INIT");
    }
}

void SetpointPublisher::toff() {
    if (sp_toff == false) {
        mavros_msgs::CommandTOL srv_toff;
        srv_toff.request.altitude = z_fs;
        srv_toff.request.min_pitch = 0.0;

        if (land_client.call(srv_toff) && srv_toff.response.success)
        {
            ROS_INFO("Takeoff Successful");
        } else {
            ROS_WARN("Takeoff Failed");
        }
    } else {
        // Carry On
    }
}

void SetpointPublisher::land() {
    if (land_fs == true) {
        mavros_msgs::CommandTOL srv_land;
        if (land_client.call(srv_land) && srv_land.response.success)
        {
            ROS_INFO("Land Successful");
        } else {
            ROS_WARN("Land Failed");
        }
    } else {
        // Carry On
    }

}

void SetpointPublisher::pub_sp() {
    ros::Time t_now = ros::Time::now();

    pose_sp_out.header.stamp = t_now;
    pose_sp_out.header.seq   = k_main;

    pose_sp_pub.publish(pose_sp_out);

}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

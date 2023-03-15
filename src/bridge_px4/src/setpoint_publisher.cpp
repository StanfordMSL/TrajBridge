#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~sp_out_hz", sp_out_hz);
    ros::param::get("~checkup_hz", checkup_hz);
    ros::param::get("~z_fs",z_fs);
    ros::param::get("~r_fs",r_fs);

    // ROS Initialization
    pos_sp_sub  = nh.subscribe("setpoint/position",1,&SetpointPublisher::pos_sp_cb,this);
    vel_sp_sub  = nh.subscribe("setpoint/velocity",1,&SetpointPublisher::vel_sp_cb,this);
    att_sp_sub  = nh.subscribe("setpoint/attitude",1,&SetpointPublisher::att_sp_cb,this);
    rat_sp_sub  = nh.subscribe("setpoint/bodyrate",1,&SetpointPublisher::rat_sp_cb,this);
    thr_sp_sub  = nh.subscribe("setpoint/throttle",1,&SetpointPublisher::thr_sp_cb,this);

    posT_sp_pub  = nh.advertise<mavros_msgs::PositionTarget>("mavros/setpoint_raw/local",1);
    attT_sp_pub  = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);

    pose_curr_sub = nh.subscribe("mavros/local_position/pose",10,&SetpointPublisher::pose_curr_cb,this);
    mav_state_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mav_state_cb,this);

    setpointLoop = nh.createTimer(ros::Duration(1.0/sp_out_hz),&SetpointPublisher::setpoint_cb, this);
    checkupLoop  = nh.createTimer(ros::Duration(1.0/checkup_hz),&SetpointPublisher::checkup_cb, this);

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
    vel_check = false;
    att_check = false;
    rat_check = false;

    posT_sp_out.header.frame_id = "map";
    posT_sp_out.coordinate_frame = posT_sp_out.FRAME_LOCAL_NED;
    posT_sp_out.type_mask = 4095;               // PositionTarget: none=4095,pos=4088,vel=4039,posvel=4032

    attT_sp_out.header.frame_id = "map";
    attT_sp_out.type_mask = 255;                // AttitudeTarget: none=255,th+rat=128,rat=192,th+att=7,att=71,th+att+rat=0,att+rat=64,th=135

    // Stream Timer Checks
    ROS_INFO("Timers Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

void SetpointPublisher::pos_sp_cb(const geometry_msgs::PointStamped::ConstPtr& msg){
    pos_sp_in = *msg;
}

void SetpointPublisher::vel_sp_cb(const geometry_msgs::Vector3Stamped::ConstPtr& msg){
    vel_sp_in = *msg;
}

void SetpointPublisher::att_sp_cb(const geometry_msgs::QuaternionStamped::ConstPtr& msg){
    att_sp_in = *msg;
}

void SetpointPublisher::rat_sp_cb(const geometry_msgs::Vector3Stamped::ConstPtr& msg){
    rat_sp_in = *msg;
}

void SetpointPublisher::thr_sp_cb(const mavros_msgs::Thrust::ConstPtr& msg){
    thr_sp_in = *msg;
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

        pose_sa.position.z = 0.0f;

        posT_sp_out.position = pose_sa.position;
        
        posT_sp_out.type_mask = 4088; 
        attT_sp_out.type_mask = 255;

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

        pose_sa.position = pose_curr.pose.position;
        pose_sa.orientation = pose_curr.pose.orientation;
        pose_sa.position.z = 0.0f;

        posT_sp_out.position = pose_sa.position;
        attT_sp_out.orientation = pose_sa.orientation;

        posT_sp_out.type_mask = 4088; 
        attT_sp_out.type_mask = 71;

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

        posT_sp_out.position = pose_sa.position;

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

        posT_sp_out.position = pos_sp_in.point;
        posT_sp_out.velocity = vel_sp_in.vector;
        attT_sp_out.orientation = att_sp_in.quaternion;
        attT_sp_out.body_rate = rat_sp_in.vector;
        attT_sp_out.thrust = thr_sp_in.thrust;

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
        posT_sp_out.position = pose_sa.position;
        posT_sp_out.position.z = 0.0f;

        pub_sp();
    }
    }

    //std::cout << "Z Height Is: " << pose_sa.position.z << std::endl;

    k_main++;
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {
    ros::Time t_now = ros::Time::now();

    // TODO: bitwise form would be more elegant

    // Check if Target States are Publishing
    pos_check = ((t_now - pos_sp_in.header.stamp) < dt_max) ? true : false;
    vel_check = ((t_now - vel_sp_in.header.stamp) < dt_max) ? true : false;
    att_check = ((t_now - att_sp_in.header.stamp) < dt_max) ? true : false;
    rat_check = ((t_now - rat_sp_in.header.stamp) < dt_max) ? true : false;
    thr_check = ((t_now - thr_sp_in.header.stamp) < dt_max) ? true : false;

    if (sp_pub_state == ACTIVE) {
        if ((pos_check == true) && (vel_check == true)) {
            posT_sp_out.type_mask = 4032;
        } else if ((pos_check == true) && (vel_check == false)) {
            posT_sp_out.type_mask = 4088;
        } else if ((pos_check == false) && (vel_check == true)) {
            posT_sp_out.type_mask = 4039;
        } else if ((pos_check == false) && (vel_check == false)) {
            posT_sp_out.type_mask = 4095;
        }
        // PositionTarget: none=4095,pos=4088,vel=4039,posvel=4032

        if ((att_check == true) && (rat_check == true) && (thr_check == true)) {
            attT_sp_out.type_mask = 0;
        } else if ((att_check == true) && (rat_check == false) && (thr_check == true)) {
            attT_sp_out.type_mask = 7;
        } else if ((att_check == false) && (rat_check == true) && (thr_check == true)) {
            attT_sp_out.type_mask = 128;
        } else if ((att_check == false) && (rat_check == false) && (thr_check == true)) {
            attT_sp_out.type_mask = 135;
        } else if ((att_check == true) && (rat_check == true) && (thr_check == false)) {
            attT_sp_out.type_mask = 64;
        } else if ((att_check == true) && (rat_check == false) && (thr_check == false)) {
            attT_sp_out.type_mask = 71;
        } else if ((att_check == false) && (rat_check == true) && (thr_check == false)) {
            attT_sp_out.type_mask = 192;
        } else if ((att_check == false) && (rat_check == false) && (thr_check == false)) {
            attT_sp_out.type_mask = 255;
        }   
        // AttitudeTarget: none=255,th+rat=128,rat=192,th+att=7,att=71,th+att+rat=0,att+rat=64,th=135
    }
    
    // Check if Drone is in Safe Ball
    Eigen::Vector3f err_pos;
    err_pos <<  pose_curr.pose.position.x - posT_sp_out.position.x,
                pose_curr.pose.position.y - posT_sp_out.position.y,
                pose_curr.pose.position.z - posT_sp_out.position.z;

    if (err_pos.norm() > r_fs) {
        land();

        sp_pub_state = STARTUP;
        ROS_INFO("SP_PUB_STATE: INIT");
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

void SetpointPublisher::pub_sp() {
    ros::Time t_now = ros::Time::now();

    posT_sp_out.header.stamp = t_now;
    posT_sp_out.header.seq   = k_main;

    attT_sp_out.header.stamp = t_now;
    attT_sp_out.header.seq   = k_main;

    // Pose is always published
    posT_sp_pub.publish(posT_sp_out);
    attT_sp_pub.publish(attT_sp_out);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

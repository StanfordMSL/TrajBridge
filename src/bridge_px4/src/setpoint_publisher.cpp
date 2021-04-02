#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    ros::param::get("~sp_out_hz", sp_out_hz);
    ros::param::get("~checkup_hz", checkup_hz);    
    ros::param::get("~sp_gcs_hz_min", sp_gcs_hz_min);
    ros::param::get("~checkup_hz_min", checkup_hz_min);

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
    sp_stream_state = SP_STREAM_OFF;
    mc_stream_state = MC_STREAM_OFF;
    ROS_INFO("State Machines Initialized.");
    ROS_INFO("SP_PUB_STATE: STARTUP");

    // Constants Initialized
    quat_forward.w = 1;
    quat_forward.x = 0;
    quat_forward.y = 0;
    quat_forward.z = 0;

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
}

void SetpointPublisher::setpoint_cb(const ros::TimerEvent& event)
{       
    switch (sp_pub_state)
    {
    case STARTUP:
    {
        ROS_DEBUG("STARTUP");

        pose_t_sp_out.pose.position.x = 0.0f;
        pose_t_sp_out.pose.position.y = 0.0f;
        pose_t_sp_out.pose.position.z = 0.0f;

        pose_t_sp_out.pose.orientation = quat_forward;
        
        if (mc_stream_state == MC_STREAM_ON)
        {
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        }
    }
    break;
    case LINKED:
    {
        ROS_DEBUG("LINKED");

        pose_sa.position = pose_t_curr.pose.position;
        pose_sa.orientation = quat_forward;

        pose_t_sp_out.pose = pose_sa;
        pose_t_sp_out.pose.position.z = 0.0f;

        if ( (mode_cr.mode == "OFFBOARD") && (sp_stream_state == SP_STREAM_OFF) )
        {
            pose_sa.position.z = 1.0;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        }

        if (mc_stream_state == MC_STREAM_OFF) 
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        }
    }
    break;
    case HOVER:
    {
        ROS_DEBUG("HOVER");

        pose_t_sp_out.pose = pose_sa;

        if (sp_stream_state == SP_STREAM_ON)
        {
            sp_pub_state = ACTIVE;
            ROS_INFO("SP_PUB_STATE: ACTIVE");
        }

        if (mc_stream_state == MC_STREAM_OFF) 
        {
            land();
            sp_pub_state = STARTUP;
            ROS_INFO("SP_PUB_STATE: STARTUP");
        }

        if (mode_cr.mode != "OFFBOARD")
        {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        }
    }
    break;
    case ACTIVE:
    {
        ROS_DEBUG("ACTIVE");

        pose_t_sp_out.pose = pose_t_sp_gcs.pose;

        if (sp_stream_state == SP_STREAM_OFF && mc_stream_state == MC_STREAM_ON)
        {
            pose_sa.position = pose_t_curr.pose.position;
            pose_sa.position.z = 1.0;
            pose_sa.orientation = quat_forward;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");           
        }

        if (mc_stream_state == MC_STREAM_OFF) 
        {
            pose_sa.position.z = pose_sa.position.z-0.1;
            sp_pub_state = FAILSAFE;
            ROS_INFO("SP_PUB_STATE: FAILSAFE");
        }
        
        if (mode_cr.mode != "OFFBOARD")
        {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        }
    }
    break;
    case FAILSAFE:
    {
        ROS_DEBUG("FAILSAFE");

        pose_t_sp_out.pose = pose_sa;

        if (sp_stream_state == SP_STREAM_ON && mc_stream_state == MC_STREAM_ON)
        {
            sp_pub_state = ACTIVE;
        } else if (sp_stream_state == SP_STREAM_OFF && mc_stream_state == MC_STREAM_ON)
        {
            pose_sa.position = pose_t_curr.pose.position;
            pose_sa.position.z = 1.0;
            pose_sa.orientation = quat_forward;

            sp_pub_state = HOVER;
            ROS_INFO("SP_PUB_STATE: HOVER");
        }     

        if (mode_cr.mode != "OFFBOARD")
        {
            land();
            sp_pub_state = LINKED;
            ROS_INFO("SP_PUB_STATE: LINKED");
        }
    }
    break;
    default:
    {
        ROS_DEBUG("default (should not be here)");

        pose_t_sp_out.pose = pose_t_curr.pose;
        pose_t_sp_out.pose.position.z = 0.0f;
    }
    }

    pose_t_sp_out.header.stamp = ros::Time::now();
    pose_t_sp_out.header.seq   = count_main;
    pose_t_sp_out.header.frame_id = "world";
    count_main++;

    pose_sp_pub.publish(pose_t_sp_out);
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {
    /*
    Vector3d err_pos;
    err_pos(0) = pose_t_curr.pose.position.x - pose_sa.position.x;
    err_pos(1) = pose_t_curr.pose.position.y - pose_sa.position.y;
    err_pos(2) = pose_t_curr.pose.position.z - pose_sa.position.z;

    double err_norm = err_pos.norm();

    if ( (err_norm >= 0.2) && (mc_stream_state == MC_STREAM_ON) ) {
        pose_sa.position = pose_t_curr.pose.position;
        pose_sa.orientation = quat_forward;
    }
    */

    ros::Time t_now = ros::Time::now();
    if ((t_now - pose_t_sp_gcs.header.stamp) > setpoint_dt_max) {
        if (sp_stream_state == SP_STREAM_ON) {
            ROS_INFO("Setpoint Stream Broken");
        }
        ROS_DEBUG("Setpoint Stream Off");

        sp_stream_state = SP_STREAM_OFF;
    } else
    {
        ROS_DEBUG("Setpoint Stream On");

        sp_stream_state = SP_STREAM_ON;
    }

    if ((t_now - pose_t_curr.header.stamp) > checkup_dt_max) {
        if (mc_stream_state == MC_STREAM_ON) {
            ROS_INFO("MoCap Stream Broken");
        }
        ROS_DEBUG("MoCap Stream Off");

        mc_stream_state = MC_STREAM_OFF;
    } else
    {
        ROS_DEBUG("MoCap Stream On");

        mc_stream_state = MC_STREAM_ON;
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

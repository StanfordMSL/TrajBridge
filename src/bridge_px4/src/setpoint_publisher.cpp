#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    // Load Node Parameters
    ros::param::get("~spo_hz", spo_hz);
    ros::param::get("~cup_hz", cup_hz);
    ros::param::get("~spi_hz_min", spi_hz_min);
    ros::param::get("~mci_hz_min", mci_hz_min);
    ros::param::get("~sa_z",sa_z);
    ros::param::get("~x_min",map_lim(0,0));
    ros::param::get("~x_max",map_lim(0,1));
    ros::param::get("~y_min",map_lim(1,0));
    ros::param::get("~y_max",map_lim(1,1));
    ros::param::get("~z_min",map_lim(2,0));
    ros::param::get("~z_max",map_lim(2,1));
    
    ROS_INFO("Node Parameters Loaded");

    // ROS Subscribers
    pose_sp_sub = nh.subscribe("setpoint/pose",1,&SetpointPublisher::pose_sp_cb,this);
    bora_sp_sub = nh.subscribe("setpoint/bora",1,&SetpointPublisher::bora_sp_cb,this);
    atop_sp_sub = nh.subscribe("setpoint/atop",1,&SetpointPublisher::atop_sp_cb,this);
    
    pose_cr_sub = nh.subscribe("mavros/vision_pose/pose",10,&SetpointPublisher::pose_cr_cb,this);
    mavs_cr_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mavs_cr_cb,this);

    // ROS Publishers
    pose_sp_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    bora_sp_pub = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);
    atop_sp_pub = nh.advertise<mavros_msgs::ActuatorControl>("mavros/actuator_control",1);

    // Timer Loops
    setpointLoop = nh.createTimer(ros::Duration(1.0/spo_hz),&SetpointPublisher::setpoint_cb, this);
    checkupLoop  = nh.createTimer(ros::Duration(1.0/cup_hz),&SetpointPublisher::checkup_cb, this);

    // ROS Services
    ac_mode_service = nh.advertiseService("act_ac_mode",&SetpointPublisher::actACmode,this);
    sp_mode_service = nh.advertiseService("set_sp_mode",&SetpointPublisher::setSPmode,this);

    // ROS Clients
    land_client = nh.serviceClient<mavros_msgs::CommandTOL>("mavros/cmd/land");

    ROS_INFO("ROS Components Initialized");

    // Initialize State Machine
    sp_pub_state    = INIT;
    mc_stream_state = MC_INIT;
    ob_mode_state   = OB_INIT;
    ac_mode_state   = AC_INIT;
    sp_mode_state  = SP_POSE;

    ROS_INFO("State Machines Initialized");
    ROS_INFO("SP_MODE_STATE: SP_NONE");

    // Initialize some useful variables
    q_fw.w=1.0, q_fw.x=0.0, q_fw.y=0.0, q_fw.z=0.0;
    pose_sa.pose.position.x=0.0,pose_sa.pose.position.y=0.0,pose_sa.pose.position.z=0.0,
    pose_sa.pose.orientation.w=1.0,pose_sa.pose.orientation.x=0.0,pose_sa.pose.orientation.y=0.0,pose_sa.pose.orientation.z=0.0;
    spi_dt_max = 1/spi_hz_min;
    mci_dt_max = 1/mci_hz_min;

    ROS_INFO("Node Fully Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

bool SetpointPublisher::setSPmode(bridge_px4::SetSPMode::Request& req, bridge_px4::SetSPMode::Response& res) {
    // Change Mode
    if (req.mode == "SP_POSE") {
        sp_mode_state = SP_POSE;
        ROS_INFO("SP_MODE_STATE: SP_POSE");
    } else if (req.mode == "SP_BORA") {
        sp_mode_state = SP_BORA;
        ROS_INFO("SP_MODE_STATE: SP_BORA");
    } else if (req.mode == "SP_ATOP") {
        sp_mode_state = SP_ATOP;
        ROS_INFO("SP_MODE_STATE: SP_ATOP");
    } else {
        sp_mode_state = SP_POSE;
        ROS_INFO("Unknown mode requested. Reverting to SP_POTW");
        ROS_INFO("SP_MODE_STATE: SP_POSE");
    }

    // Return checksum for verification (not completed/verified, still TODO)
    res.success = true;
    res.result = req.mode;

    return true;
}

bool SetpointPublisher::actACmode(bridge_px4::ActACMode::Request& req, bridge_px4::ActACMode::Response& res) {
    // Change Mode
    if (req.arm == true) {
        ac_mode_state = AC_ON;
        ROS_INFO("AC_MODE_STATE: AC_ON");
    } else {
        ac_mode_state = AC_OFF;
        ROS_INFO("Unknown mode requested. AC not activated");
        ROS_INFO("AC_MODE_STATE: AC_OFF");
    }

    // Return checksum for verification (not completed/verified, still TODO)
    res.success = true;
    res.result = req.arm;

    return true;
}
void SetpointPublisher::pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_sp = *msg;
}

void SetpointPublisher::bora_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg){
    bora_sp = *msg;
}

void SetpointPublisher::atop_sp_cb(const mavros_msgs::ActuatorControl::ConstPtr& msg){
    atop_sp = *msg;
}

void SetpointPublisher::pose_cr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_cr = *msg;
}

void SetpointPublisher::mavs_cr_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_cr = *msg;

    if (mode_cr.mode == "OFFBOARD") {
        ob_mode_state = OB_ON;
    } else if ( (mode_cr.mode == "POSCTL") || (mode_cr.mode == "STABILIZED") || (mode_cr.mode == "ALTCTL") ) {
        ob_mode_state = OB_OFF;
    } else {
        ob_mode_state = OB_OFF;
        ROS_INFO("[SP PUB] MAV state not recognized.");
    }
}

void SetpointPublisher::pub_pos() {    
    pose_sa.header.stamp = ros::Time::now();
    pose_sa.header.seq   = k_main;
    pose_sa.header.frame_id = "map";

    pose_sp_pub.publish(pose_sa);
}

void SetpointPublisher::pub_sp() {
    if (sp_mode_state == SP_POSE) {
        pose_sp.header.stamp = ros::Time::now();
        pose_sp.header.seq   = k_main;
        pose_sp.header.frame_id = "map";

        pose_sp_pub.publish(pose_sp);
    } else if (sp_mode_state == SP_BORA) {
        bora_sp.header.stamp = ros::Time::now();
        bora_sp.header.seq   = k_main;
        bora_sp.header.frame_id = "map";
        // bora_sp.type_mask = bora_tg.IGNORE_ATTITUDE
        
        bora_sp_pub.publish(bora_sp);
    } else if (sp_mode_state == SP_ATOP) {
        atop_sp.header.stamp = ros::Time::now();
        atop_sp.header.seq   = k_main;
        atop_sp.header.frame_id = "map";
        
        atop_sp_pub.publish(atop_sp);
    } else {
        ROS_INFO("[SP PUB] SP Mode not recognized. Aborting trajectory");
        ac_mode_state = AC_OFF;
    }
}


void SetpointPublisher::setpoint_cb(const ros::TimerEvent& event) {    
    switch (sp_pub_state) {
        case INIT: {
            // ROS_INFO("[SP PUB] INIT");
            // State Transition
            if ((mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF)) {
                sp_pub_state = LINKED;
                ROS_INFO("[SP PUB] SP_PUB_STATE: LINKED");
            } else {
            // State Action
                pose_sa.pose.position = pose_cr.pose.position;
                pose_sa.pose.position.z=0.0;
                pub_pos();
            }
        } break;
        case LINKED: {
            // ROS_INFO("[SP PUB] LINKED");
            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                sp_pub_state = INIT;
                ROS_INFO("[SP PUB] SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_OFF) ) {
                sp_pub_state = HOVER;
                ROS_INFO("[SP PUB] SP_PUB_STATE: HOVER");
            } else {
            // State Action
                pose_sa.pose.position = pose_cr.pose.position;
                pose_sa.pose.position.z=0.0;
                pub_pos();
            }
        } break;
        case HOVER: {
            // ROS_INFO("[SP PUB] HOVER");
            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = INIT;
                ROS_INFO("[SP PUB] SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = LINKED;
                ROS_INFO("[SP PUB] SP_PUB_STATE: LINKED");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_ON) ) {
                sp_pub_state = ACTIVE;
                ROS_INFO("[SP PUB] SP_PUB_STATE: ACTIVE");
            } else {
            // State Action
                pose_sa.pose.position.z=sa_z;
                pub_pos();
            }
        } break;
        case ACTIVE: {
            // ROS_INFO("[SP PUB] ACTIVE");
            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = INIT;
                ROS_INFO("[SP PUB] SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = LINKED;
                ROS_INFO("[SP PUB] SP_PUB_STATE: LINKED");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_OFF) ) {
                ac_mode_state = AC_OFF;
                sp_pub_state = HOVER;
                ROS_INFO("[SP PUB] SP_PUB_STATE: HOVER");
            } else {
                pose_sa.pose.position = pose_cr.pose.position;
                pose_sa.pose.position.z=sa_z;
                pub_sp();
            }
        } break;
        default: {
            ROS_DEBUG("default (should not be here)");
            land();
            ac_mode_state = AC_OFF;
        }
    }        
    k_main++;
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {
    float t_now = ros::Time::now().toSec();
    
    // Get time since last setpoint and mocap data
    float spi_dt = 999.0;
    if (sp_mode_state == SP_POSE) {
        spi_dt = t_now-pose_sp.header.stamp.toSec();
    } else if (sp_mode_state == SP_BORA) {
        spi_dt = t_now-bora_sp.header.stamp.toSec();
    } else if (sp_mode_state == SP_ATOP) {
        spi_dt = t_now-atop_sp.header.stamp.toSec();
    } else {
        ROS_INFO("SP Mode not recognized. Aborting trajectory");
        ac_mode_state = AC_OFF;
    }
    float mci_dt = t_now-pose_cr.header.stamp.toSec();

    // Setpoint Time Failsafe
    if (spi_dt > spi_dt_max) {
        if (ac_mode_state == AC_ON) {
            ROS_INFO("Setpoint Stream Stopped");
        }
        ac_mode_state = AC_OFF;
    }

    // Mocap Time Failsafe
    if (mci_dt > mci_dt_max) {
        if (mc_stream_state == MC_ON) {
            ROS_INFO("MoCap Stream Stopped");
        }
        mc_stream_state = MC_OFF;
    } else {
        mc_stream_state = MC_ON;    
    }

    // Map Limit Failsafe
    if (pose_cr.pose.position.x < map_lim(0,0) ||
        pose_cr.pose.position.x > map_lim(0,1) ||
        pose_cr.pose.position.y > map_lim(1,0) ||
        pose_cr.pose.position.y > map_lim(1,1) ||
        pose_cr.pose.position.z > map_lim(2,0) ||
        pose_cr.pose.position.z > map_lim(2,1)) {
        if (ac_mode_state == AC_ON) {
            ROS_INFO("Drone Out of Bounds");
        }
        ac_mode_state = AC_OFF;
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

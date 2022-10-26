#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
    // Load Node Parameters
    ros::param::get("~spo_hz", spo_hz);
    ros::param::get("~cup_hz", cup_hz);
    ros::param::get("~spi_hz_min", spi_hz_min);
    ros::param::get("~mci_hz_min", mci_hz_min);
    ros::param::get("~fs_th", fs_th);
    ros::param::get("~rs_th",rs_th);
    ros::param::get("~fs_hov_z",fs_hov_z);
    ros::param::get("~eps_p_th", eps_p_th);
    
    ROS_INFO("Node Parameters Loaded");

    // ROS Subscribers
    pose_sp_sub = nh.subscribe("setpoint/pose",1,&SetpointPublisher::pose_sp_cb,this);
    vels_sp_sub = nh.subscribe("setpoint/velocity",1,&SetpointPublisher::vels_sp_cb,this);
    accs_sp_sub = nh.subscribe("setpoint/acceleration",1,&SetpointPublisher::accs_sp_cb,this);
    
    pose_cr_sub = nh.subscribe("mavros/vision_pose/pose",10,&SetpointPublisher::pose_cr_cb,this);
    mavs_cr_sub = nh.subscribe("mavros/state",1,&SetpointPublisher::mavs_cr_cb,this);

    // ROS Publishers
    pose_tg_pub = nh.advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    bora_tg_pub = nh.advertise<mavros_msgs::AttitudeTarget>("mavros/setpoint_raw/attitude",1);
    nowr_tg_pub = nh.advertise<mavros_msgs::ActuatorControl>("mavros/actuator_control",1);

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

    ROS_INFO("State Machines Initialized");
    ROS_INFO("SP_MODE_STATE: SP_NONE");

    // Initialize some useful variables
    q_fw.w=1.0, q_fw.x=0.0, q_fw.y=0.0, q_fw.z=0.0;
    pose_sa.position.x=0.0,pose_sa.position.y=0.0,pose_sa.position.z=0.0,
    pose_sa.orientation.w=1.0,pose_sa.orientation.x=0.0,pose_sa.orientation.y=0.0,pose_sa.orientation.z=0.0;
    spi_dt_max = 1/spi_hz_min;
    mci_dt_max = 1/mci_hz_min;

    ROS_INFO("Node Fully Initialized.");
}

SetpointPublisher::~SetpointPublisher() {
  ROS_WARN("Terminating Publisher");
}

bool SetpointPublisher::setSPmode(bridge_px4::SetSPMode::Request& req, bridge_px4::SetSPMode::Response& res) {
    // Change Mode
    if (req.mode == "SP_POTW") {
        sp_mode_state = SP_POTW;
        ROS_INFO("SP_MODE_STATE: SP_POTW");
    } else if (req.mode == "SP_BORA") {
        sp_mode_state = SP_BORA;
        ROS_INFO("SP_MODE_STATE: SP_BORA");
    } else if (req.mode == "SP_NOWR") {
        sp_mode_state = SP_NOWR;
        ROS_INFO("SP_MODE_STATE: SP_NOWR");
    } else {
        sp_mode_state = SP_POTW;
        ROS_INFO("Unknown mode requested. Reverting to SP_POTW");
        ROS_INFO("SP_MODE_STATE: SP_POTW");
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
    } else if ( (mode_cr.mode == "POSCTL") || (mode_cr.mode == "STABILIZED") || (mode_cr.mode == "ALTCTL") ) {
        ob_mode_state = OB_OFF;
    } else {
        ob_mode_state = OB_OFF;
        ROS_INFO("MAV state not configured correctly.");
    }
}

void SetpointPublisher::pub_sp_pose() {
    pose_compute();
    
    pose_tg.header.stamp = ros::Time::now();
    pose_tg.header.seq   = k_main;
    pose_tg.header.frame_id = "map";

    pose_tg_pub.publish(pose_tg);

    //std::cout << "Publishing Pos: " << k_main << std::endl;
}

void SetpointPublisher::pub_sp_bora() {
    bora_compute();

    bora_tg.header.stamp = ros::Time::now();
    bora_tg.header.seq   = k_main;
    bora_tg.header.frame_id = "map";
    bora_tg.type_mask = bora_tg.IGNORE_ATTITUDE;

    bora_tg_pub.publish(bora_tg);

    //std::cout << "Publishing BR " << k_main << std::endl;
    //std::cout <<  att_sp_out.thrust << std::endl;
}

void SetpointPublisher::pub_sp_nowr() {
    nowr_compute();

    nowr_tg.header.stamp = ros::Time::now();
    nowr_tg.header.seq   = k_main;
    nowr_tg.header.frame_id = "map";

    nowr_tg_pub.publish(nowr_tg);

    //std::cout << "Publishing BR " << k_main << std::endl;
    //std::cout <<  att_sp_out.thrust << std::endl;
}

void SetpointPublisher::setpoint_cb(const ros::TimerEvent& event) {
    switch (sp_pub_state) {
        case INIT: {
            // Do State Tasks
            ROS_DEBUG("INIT");

            pose_sp.pose = pose_sa;
            pose_sp.pose.position.z = 0.0f;

            pub_sp_pose();

            // State Transition
            if ((mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF)) {
                sp_pub_state = LINKED;
                ROS_INFO("SP_PUB_STATE: LINKED");
            } else {
                // Stay in State
            }
        } break;
        case LINKED: {
            // Do State Tasks
            ROS_DEBUG("LINKED");

            pose_sa.position = pose_cr.pose.position;
            pose_sa.orientation = q_fw;
            pose_sp.pose = pose_sa;
            pose_sp.pose.position.z = 0.0f;

            pub_sp_pose();

            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                sp_pub_state = INIT;
                ROS_INFO("SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_OFF) ) {
                pose_sa.position.z = fs_hov_z;

                sp_pub_state = HOVER;
                ROS_INFO("SP_PUB_STATE: HOVER");
            } else {
                // Stay in State
            }
        } break;
        case HOVER: {
            // Do State Tasks
            ROS_DEBUG("HOVER");

            pose_sp.pose = pose_sa;

            pub_sp_pose();

            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = INIT;
                ROS_INFO("SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = LINKED;
                ROS_INFO("SP_PUB_STATE: LINKED");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_ON) ) {
                sp_pub_state = ACTIVE;
                ROS_INFO("SP_PUB_STATE: ACTIVE");
            } else {
                // Stay in State
            }
        } break;
        case ACTIVE: {
            // Do State Tasks
            ROS_DEBUG("ACTIVE");

            pose_sa = pose_cr.pose;

            pub_sp_pose();

            // State Transition
            if (mc_stream_state == MC_OFF) {
                land();
                ac_mode_state = AC_OFF;
                sp_pub_state = INIT;
                ROS_INFO("SP_PUB_STATE: INIT");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_OFF) ) {
                ac_mode_state = AC_OFF;
                sp_pub_state = LINKED;
                ROS_INFO("SP_PUB_STATE: LINKED");
            } else if ( (mc_stream_state == MC_ON) && (ob_mode_state == OB_ON) && (ac_mode_state == AC_OFF) ) {
                ac_mode_state = AC_OFF;
                sp_pub_state = HOVER;
                ROS_INFO("SP_PUB_STATE: HOVER");
            } else {
                // Stay in State
            }
            //std::cout <<  att_sp_in.thrust << std::endl;
        } break;
        default: {
            ROS_DEBUG("default (should not be here)");

            land();
            ac_mode_state = AC_OFF;

            pose_sp.pose = pose_cr.pose;
            pose_sp.pose.position.z = 0.0f;

            pub_sp_pose();
        }
    }
        
    //std::cout << "Z Height Is: " << pose_sa.position.z << std::endl;

    k_main++;
}

void SetpointPublisher::checkup_cb(const ros::TimerEvent& event) {
    float t_now = ros::Time::now().toSec();
    float t_spi = pose_sp.header.stamp.toSec();
    float t_mci = pose_cr.header.stamp.toSec();

    float spi_dt = t_now-t_spi;
    float mci_dt = t_now-t_mci;

    if (spi_dt > spi_dt_max) {
        if (ac_mode_state == AC_ON) {
            ROS_INFO("Setpoint Stream Stopped");
        }

        ROS_DEBUG("Setpoint Stream Off");
        ac_mode_state = AC_OFF;
    } else {
        ROS_DEBUG("Setpoint Stream On");
        ac_mode_state = AC_ON;
    }

    if (mci_dt > mci_dt_max) {
        if (mc_stream_state == MC_ON) {
            cout << t_mci << t_now << endl;
            ROS_INFO("MoCap Stream Broken. Last vision_pose message came in at: %f", pose_cr.header.stamp.toSec());
        }

        ROS_DEBUG("MoCap Stream Off");
        mc_stream_state = MC_OFF;
    } else {
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
    pose_tg.pose = pose_sp.pose;
}

void SetpointPublisher::bora_compute() {
    bora_tg.thrust = 0.0;
    bora_tg.body_rate.x = 0.0;
    bora_tg.body_rate.y = 0.0;
    bora_tg.body_rate.z = 0.0;
}

void SetpointPublisher::nowr_compute() {
    nowr_tg.controls = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0};
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");

    SetpointPublisher sp;

    ros::spin();
    return 0;
}

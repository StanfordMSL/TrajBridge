#include <bridge_px4/auto_rc.h>

Auto_RC::Auto_RC()
{
    // Load Node Parameters
    ros::param::get("~sp_mode", sp_mode_val);

    // Setup ROS Subscribers
    state_sub = nh.subscribe("/drone1/mavros/state",1,&Auto_RC::state_cb,this);

    // Setup ROS Services
    arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/drone1/mavros/cmd/arming");
    px4_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/drone1/mavros/set_mode");
    sp_mode_client = nh.serviceClient<bridge_px4::SetSPMode>("/drone1/set_sp_mode");
}

Auto_RC::~Auto_RC()
{
  ROS_WARN("Terminating auto_rc");
}

void Auto_RC::state_cb(const mavros_msgs::State::ConstPtr& msg){
    state = msg->mode;
}

void Auto_RC::rc_takeoff()
{
    mavros_msgs::SetMode px4_mode;
    mavros_msgs::CommandBool arm_cmd;
    bridge_px4::SetSPMode sp_mode;

    px4_mode.request.custom_mode = "POSCTL";
    if (px4_mode_client.call(px4_mode) && px4_mode.response.mode_sent)
    {
        ROS_INFO("Drone Switched to POSCTL.");
    } 
    ros::Duration(1.0).sleep();

    px4_mode.request.custom_mode = "OFFBOARD";
    if (px4_mode_client.call(px4_mode) && px4_mode.response.mode_sent)
    {
        ROS_INFO("Drone Switched to OFFBOARD.");

    }
    ros::Duration(1.0).sleep();
    
    arm_cmd.request.value = true;
    if (arming_client.call(arm_cmd) && arm_cmd.response.success)
    {
        ROS_INFO("Drone Armed. Taking Off.");
    }
    ros::Duration(1.0).sleep();

    sp_mode.request.mode = sp_mode_val;
    if (sp_mode_client.call(sp_mode) && sp_mode.response.success)
    {
        ROS_INFO("Drone SP mode set to %s.",sp_mode_val.c_str());
    }
    ros::Duration(1.0).sleep();

    ros::shutdown();
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    Auto_RC a_rc;

    ros::Rate rate(100);
    while(ros::ok()){
        // Take off when ready
        if (a_rc.state.substr(0,4) == "AUTO") {
            a_rc.rc_takeoff();
        } else {
            // Carry on
        }
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
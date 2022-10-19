#include <bridge_px4/auto_rc.h>

Auto_RC::Auto_RC()
{
    // Setup ROS Subscribers
    state_sub = nh.subscribe("/drone1/mavros/state",1,&Auto_RC::state_cb,this);

    // Setup ROS Services
    arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/drone1/mavros/cmd/arming");
    set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/drone1/mavros/set_mode");
}

Auto_RC::~Auto_RC()
{
  ROS_WARN("Terminating auto_rc");
}

void Auto_RC::state_cb(const mavros_msgs::State::ConstPtr& msg){
    state = msg->mode;
}

void Auto_RC::rc_takeoff_sequence()
{
    mavros_msgs::SetMode set_mode;
    mavros_msgs::CommandBool arm_cmd;

    set_mode.request.custom_mode = "POSCTL";
    if (set_mode_client.call(set_mode) && set_mode.response.mode_sent)
    {
        ROS_INFO("Drone Switched to POSCTL.");
    } 
    ros::Duration(1.0).sleep();

    set_mode.request.custom_mode = "OFFBOARD";
    if (set_mode_client.call(set_mode) && set_mode.response.mode_sent)
    {
        ROS_INFO("Drone Switched to OFFBOARD.");

    }
    ros::Duration(1.0).sleep();
    
    arm_cmd.request.value = true;
    if (arming_client.call(arm_cmd) && arm_cmd.response.success)
    {
        ROS_INFO("Drone Armed. Taking Off.");
    }
    ros::Duration(5.0).sleep();

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
            a_rc.rc_takeoff_sequence();
        } else {
            // Carry on
        }
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
#include <bridge_px4/auto_rc.h>

Auto_RC::Auto_RC()
{
    // Setup ROS Subscribers
    pose_sp_sub = nh.subscribe("setpoint/position",1,&Auto_RC::pose_sp_cb,this);
    vel_sp_sub  = nh.subscribe("setpoint/velocity",1,&Auto_RC::vel_sp_cb,this);
    att_sp_sub  = nh.subscribe("setpoint/attitude",1,&Auto_RC::att_sp_cb,this);

    // Setup ROS Services
    arming_client = nh.serviceClient<mavros_msgs::CommandBool>("/drone1/mavros/cmd/arming");
    set_mode_client = nh.serviceClient<mavros_msgs::SetMode>("/drone1/mavros/set_mode");
    
    // Take Off
    rc_takeoff_sequence();
}

Auto_RC::~Auto_RC()
{
  ROS_WARN("Terminating auto_rc");
}

void Auto_RC::pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_sp_in = *msg;
}

void Auto_RC::vel_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg){
    vel_sp_in = *msg;
}

void Auto_RC::att_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg){
    att_sp_in = *msg;
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
}

void Auto_RC::rc_rtl_sequence()
{
    mavros_msgs::SetMode set_mode;

    set_mode.request.custom_mode = "AUTO.RTL";
    if (set_mode_client.call(set_mode) && set_mode.response.mode_sent)
    {
        ROS_INFO(" Trajectory Complete. Triggering RTL.");
    }
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "gcs_node");

    Auto_RC a_rc;

    ros::Rate rate(100);
    while(ros::ok()){
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

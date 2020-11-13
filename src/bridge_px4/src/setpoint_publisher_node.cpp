#include <bridge_px4/setpoint_publisher_node.h>

using namespace Eigen;

SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh)
{
    state = SP_DISARMED;

    pos_sp_pub      = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub       = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub        = nh->subscribe("/mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
    gcs_service     = nh->advertiseService("/gcs_commander",&SetpointPublisher::gcs_commander,this);
    arming_client   = nh->serviceClient<mavros_msgs::CommandBool>("mavros/cmd/arming");
    set_mode_client = nh->serviceClient<mavros_msgs::SetMode>("mavros/set_mode");
    
    ros::Rate rate(20);
    while(ros::ok() && !curr_state.connected){
        ROS_INFO("Waiting for Connection to PX4.");
        ros::spinOnce();
        rate.sleep();
    }

    pos_sp    = init_pose;
}

void SetpointPublisher::state_cb(const mavros_msgs::State::ConstPtr& msg){
    curr_state = *msg;
}

void SetpointPublisher::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    curr_pose = *msg;
}
bool SetpointPublisher::gcs_commander(bridge_px4::GcsCmd::Request &req,
                      bridge_px4::GcsCmd::Response &res)
{
    if (req.trigger == 1) {
        state = SP_ARMED;
        last_request = ros::Time::now();

	init_pose = curr_pose;
	targ_pose = init_pose;
	targ_pose.pose.position.z = init_pose.pose.position.z + 1.0;
	pos_sp = targ_pose;

        offb_set_mode.request.custom_mode = "OFFBOARD";
        arm_cmd.request.value = true;

        ROS_INFO("System Armed. Streaming Trajectory");
    } else {
        state = SP_DISARMED;
        ROS_INFO("System Disarmed. Landing Immediately.");
    }
      
     return true;
}   

void SetpointPublisher::offb_trigger()
{
    //std::cout << curr_state.mode << std::endl;

    if (state == SP_ARMED) {
        if ( !curr_state.armed && (ros::Time::now() - last_request > ros::Duration(5.0))) {
            if (arming_client.call(arm_cmd) && arm_cmd.response.success){
                    ROS_INFO("Vehicle Armed");
                }
            last_request = ros::Time::now();
        } else {
            if ( curr_state.mode != "OFFBOARD" && (ros::Time::now() - last_request > ros::Duration(5.0)) ) {
                if (set_mode_client.call(offb_set_mode) && offb_set_mode.response.mode_sent) {
                ROS_INFO("Offboard enabled");
            }
                last_request = ros::Time::now();
            }
        }
    }
}
void SetpointPublisher::update_setpoint()
{   
    VectorXf s_error(3);
    
    s_error <<  curr_pose.pose.position.x-targ_pose.pose.position.x,
                curr_pose.pose.position.y-targ_pose.pose.position.y,
                curr_pose.pose.position.z-targ_pose.pose.position.z;
    

    if (state == SP_ARMED) {
        if (s_error.norm() > 0.1 ) {        
            pos_sp = targ_pose;
        } else {        
            pos_sp = init_pose;
        }
    } else {
        pos_sp = init_pose;
    }
    pos_sp.pose.position.z = targ_pose.pose.position.z + 0.5;
}
   
void SetpointPublisher::publish_setpoint()
{
    pos_sp_pub.publish(pos_sp);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");
    ros::NodeHandle nh;

    ROS_INFO("main: Instantiating Setpoint Publisher Node");
    SetpointPublisher sp = SetpointPublisher(&nh);

    ros::Rate rate(20);
    while(ros::ok()){
        sp.offb_trigger();
        sp.update_setpoint();
        sp.publish_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

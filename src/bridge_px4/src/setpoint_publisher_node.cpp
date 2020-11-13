#include <bridge_px4/setpoint_publisher_node.h>

using namespace Eigen;

SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh)
{
    state = SP_DISARMED;

    pos_sp_pub  = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub   = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub    = nh->subscribe("/mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
    gcs_service = nh->advertiseService("/gcs_commander",&SetpointPublisher::gcs_commander,this);

    ros::Rate rate(20);
    while(ros::ok() && !curr_state.connected){
        ROS_INFO("Waiting for Connection to PX4.");
        ros::spinOnce();
        rate.sleep();
    }
    
    ROS_INFO("Connection Established. Setting initial position and setpoint position to current position.");
    init_pose = curr_pose;
    
    targ_pose = init_pose;
    targ_pose.pose.position.z = init_pose.pose.position.z + 0.5;

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
        t_start = ros::Time::now() + ros::Duration(3.0);
        state = SP_ARMED;
        ROS_INFO("Setpoint Publisher Armed. Streaming Trajectory in 3s.");
    } else {
        state = SP_DISARMED;
        ROS_INFO("Setpoint Publisher Disarmed. Reverting Trajectory to Hover Immediately.");
    }
      
     return true;
}   

void SetpointPublisher::update_setpoint()
{   
    VectorXf s_error(3);
    
    s_error <<  curr_pose.pose.position.x-targ_pose.pose.position.x,
                curr_pose.pose.position.y-targ_pose.pose.position.y,
                curr_pose.pose.position.z-targ_pose.pose.position.z;
    

    if (state == SP_ARMED) {
        if ( (ros::Time::now() > t_start) && (s_error.norm() > 0.1) ) {        
            pos_sp = targ_pose;
        } else {        
            pos_sp = init_pose;
        }
    } else {
        pos_sp = init_pose;
    }
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
        sp.update_setpoint();
        sp.publish_setpoint();
            
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}
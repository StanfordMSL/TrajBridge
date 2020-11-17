#include <bridge_px4/setpoint_publisher_node.h>


SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh)
{
    // ROS Initialization
    pose_sp_pub = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub   = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub    = nh->subscribe("/mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
       
    ROS_INFO("ROS Components Initialized");

    // Trajectory Initialization
    MatrixXf m(4,6);
    m << 5.0, 15.0, 20.0, 30.0, 35.0, 40.0,
         0.0,  6.0,  6.0,  0.0,  0.0,  0.0,
         0.0,  0.0,  3.0,  3.0,  0.0,  0.0,
         1.0,  1.0,  1.0,  1.0,  1.0,  0.0;

    traj.block<4,6>(0,0) = m;
    N_traj = 6;

    // Setpoint Stream Initialization
    sp_status = SP_STREAM_READY;

    // Counter and Time Initialization
    count_main = 0;
    count_traj  = 0;
    ROS_INFO("Counters Initialized.");
}

void SetpointPublisher::state_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_curr = *msg;

    if ((mode_curr.mode == "OFFBOARD") && sp_status == SP_STREAM_READY) {
        t_start = ros::Time::now();
        sp_status = SP_STREAM_ACTIVE;
    } else if (mode_curr.mode != "OFFBOARD") {
        // Reset sp stream.
        sp_status = SP_STREAM_READY;
    }
}

void SetpointPublisher::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_curr = *msg;
}

void SetpointPublisher::update_setpoint()
{   
    ros::Time t_now = ros::Time::now();

    if (sp_status == SP_STREAM_ACTIVE) {
        float t_check = traj(0,count_traj);
        if ( (count_traj < N_traj) &&
             (ros::Time::now() - t_start > ros::Duration(t_check)) ) {
            pose_sp.pose.position.x = traj(1,count_traj);
            pose_sp.pose.position.y = traj(2,count_traj);
            pose_sp.pose.position.z = traj(3,count_traj);
            
            count_traj++;
        } else if (count_traj >= N_traj) {
            ROS_INFO("Trajectory Complete.");
            sp_status == SP_STREAM_COMPLETE;
        }
    } else {
        pose_sp.pose.position.x = 0.0f;
        pose_sp.pose.position.y = 0.0f;
        pose_sp.pose.position.z = 0.0f;

        count_traj = 0;
    }

    pose_sp.pose.orientation.w = 1.0f;
    pose_sp.pose.orientation.x = 0.0f;
    pose_sp.pose.orientation.y = 0.0f;
    pose_sp.pose.orientation.z = 0.0f;

    pose_sp.header.stamp = ros::Time::now();
    pose_sp.header.seq   = count_main;
    pose_sp.header.frame_id = 1;
    count_main++;

    pose_sp_pub.publish(pose_sp);
}
   
int main(int argc, char **argv)
{
    ros::init(argc, argv, "setpoint_publisher_node");
    ros::NodeHandle nh;

    SetpointPublisher sp = SetpointPublisher(&nh);

    ros::Rate rate(20);
    while(ros::ok()){
        sp.update_setpoint();
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

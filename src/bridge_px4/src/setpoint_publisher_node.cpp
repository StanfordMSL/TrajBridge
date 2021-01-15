#include <bridge_px4/setpoint_publisher_node.h>


SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh)
{
    // ROS Initialization
    pose_sp_pub = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub   = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub    = nh->subscribe("/mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
       
    ROS_INFO("ROS Components Initialized");

    // Trajectory Initialization

    //===============================================================================================
    /*
    N_traj = 3;

    MatrixXf m_pose(5,3);
    m_pose << 5.0,  10.0,  15.0,
              0.0,   3.0,   3.0,
              0.0,   0.0,   0.0,
              1.0,   1.0,   0.0,
              0.0,   0.0,   0.0;

    traj.block<5,3>(0,0) = m_pose;
    */
    //===============================================================================================
    /*
    N_traj = 6;

    MatrixXf m_pose(5,6);
    m_pose << 5.0,  10.0,  15.0,  20.0,  25.0,  30.0,
              0.0,   3.0,   3.0,   0.0,   0.0,   0.0,
              0.0,   0.0,   3.0,   3.0,   0.0,   0.0,
              1.0,   1.0,   1.0,   1.0,   1.0,   0.0,
              0.0,   0.0,   0.0,   0.0,   0.0,   0.0;

    traj.block<5,6>(0,0) = m_pose;
    */
    //===============================================================================================
    
    N_traj = 13;

    MatrixXf m_pose(5,13);
    m_pose <<  3,7,8.1,9.2,10.3,11.4,12.5,13.6,14.7,15.8,16.9,18,21,
               0,-0.5,-0.214,0.536,1.46,2.21,2.5,2.21,1.46,0.536,-0.214,-0.5,-0.5,
               0,1,0.118,-0.427,-0.427,0.118,1,1.88,2.43,2.43,1.88,1,1,
               1,1,1,1,1,1,1,1,1,1,1,1,0,
               0,0,0.628,1.26,1.88,2.51,3.14,3.77,4.4,5.03,5.65,6.28,6.28;

    traj.block<5,13>(0,0) = m_pose;

    //===============================================================================================

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
            
            double roll  = 0.0f;
            double pitch = 0.0f;
            double yaw   = traj(4,count_traj);
            
            double cy = cos(yaw * 0.5);
            double sy = sin(yaw * 0.5);
            double cp = cos(pitch * 0.5);
            double sp = sin(pitch * 0.5);
            double cr = cos(roll * 0.5);
            double sr = sin(roll * 0.5);
            
            pose_sp.pose.orientation.w = cr * cp * cy + sr * sp * sy;
            pose_sp.pose.orientation.x = sr * cp * cy - cr * sp * sy;
            pose_sp.pose.orientation.y = cr * sp * cy + sr * cp * sy;
            pose_sp.pose.orientation.z = cr * cp * sy - sr * sp * cy;

            count_traj++;
        } else if (count_traj >= N_traj) {
            ROS_INFO("Trajectory Complete.");
            sp_status == SP_STREAM_COMPLETE;
        }
    } else {
        pose_sp.pose.position.x = 0.0f;
        pose_sp.pose.position.y = 0.0f;
        pose_sp.pose.position.z = 0.0f;

        pose_sp.pose.orientation.w = 1.0f;
        pose_sp.pose.orientation.x = 0.0f;
        pose_sp.pose.orientation.y = 0.0f;
        pose_sp.pose.orientation.z = 0.0f;

        count_traj = 0;
    }

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

#include <bridge_px4/setpoint_publisher_node.h>


SetpointPublisher::SetpointPublisher(ros::NodeHandle *nh)
{
    // ROS Initialization
    pose_sp_pub = nh->advertise<geometry_msgs::PoseStamped>("mavros/setpoint_position/local",1);
    state_sub   = nh->subscribe("mavros/state",1,&SetpointPublisher::state_cb,this);
    pose_sub    = nh->subscribe("/mavros/local_position/pose",1,&SetpointPublisher::pose_cb,this);
       
    ROS_INFO("ROS Components Initialized");

    // Trajectory Initialization
    MatrixXf m(4,3);
    m << 0.0, 3.0, 6.0,
         0.0, 0.0, 0.0,
         0.0, 0.0, 0.0,
         0.0, 1.0, 0.0;

    traj.block<4,3>(0,0) = m;

    // Quad Connection Initialization
    ros::Rate rate(1);
    while(ros::ok() && !mode_curr.connected){
        ROS_INFO("Waiting for Connection to PX4.");
        ros::spinOnce();
        rate.sleep();
    }
    ROS_INFO("Quad Connection Established. Quad believes it as at: %f, %f, %f.",
            pose_curr.pose.position.x,
            pose_curr.pose.position.y,
            pose_curr.pose.position.z);

    // Setpoint Value Initialization
    sp_status = SP_STREAM_OFF;
    pose_sp = pose_curr;
    ROS_INFO("Quad Setpoint Initialized at: %f, %f, %f.",
            pose_sp.pose.position.x,
            pose_sp.pose.position.y,
            pose_sp.pose.position.z);

    // Counter and Time Initialization
    count_total = 0;
    count_traj  = 0;
    ROS_INFO("Counters Initialized.");
}

bool SetpointPublisher::last_req_check() {
    ros::Time t_now = ros::Time::now();
    ros::Duration t_delta = ros::Duration(5.0);

    if (t_now - last_request > t_delta) {
        last_request = t_now;
        return true;
    } else {
        return false;
    }
}

void SetpointPublisher::state_cb(const mavros_msgs::State::ConstPtr& msg){
    mode_curr = *msg;

    ros::Time t_now = ros::Time::now();
    if ((mode_curr.mode == "OFFBOARD") && last_req_check()) {
        t_start_ns = t_now.nsec;
        sp_status = SP_STREAM_ON;
    } else {
        sp_status = SP_STREAM_OFF;
    }
}

void SetpointPublisher::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_curr = *msg;
}

void SetpointPublisher::update_setpoint()
{   
    ros::Time t_now = ros::Time::now();

    if (sp_status == SP_STREAM_ON) {
        uint32_t t_check = (uint32_t)traj(0,count_traj) * pow(10,9);
        if ( (t_now.nsec - t_start_ns) > t_check ) {
            pose_sp.pose.position.x = traj(1,count_traj);
            pose_sp.pose.position.y = traj(2,count_traj);
            pose_sp.pose.position.z = traj(3,count_traj);
            
            count_traj++;
        } else {
            // Carry on
        }
    } else {
        pose_sp = pose_curr;
        pose_sp.pose.position.z = 0;

        count_traj = 0;
    }

    pose_sp.header.stamp = ros::Time::now();
    pose_sp.header.seq   = count_total;
    pose_sp.header.frame_id = 1;
    count_total++;

    pose_sp_pub.publish(pose_sp);
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
        
        ros::spinOnce();
        rate.sleep();
    }

    return 0;
}

#include <bridge_px4/mocap_vel.h>

MocapVel::MocapVel()
{
    ros::param::get("~alpha", alpha);

    // Subscribe to mavros/vision_pose/pose
    pose_curr_sub = nh.subscribe("mavros/vision_pose/pose",1,&MocapVel::pose_cb,this);

    // Publish to /mavros/odometry/out
    odom_curr_pub = nh.advertise<nav_msgs::Odometry>("mavros/odometry/out",1);
}

MocapVel::~MocapVel()
{
  ROS_WARN("Terminating MocapVel");
}

void MocapVel::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    // Load new data
    odom_curr.header = msg->header;
    odom_curr.pose.pose = msg->pose;

    // Calculate raw velocity value
    dt = odom_curr.header.stamp.toSec() - pose_prev.header.stamp.toSec();

    vel_raw.x = (odom_curr.pose.pose.position.x-pose_prev.pose.position.x)/dt;
    vel_raw.y = (odom_curr.pose.pose.position.y-pose_prev.pose.position.y)/dt;
    vel_raw.z = (odom_curr.pose.pose.position.z-pose_prev.pose.position.z)/dt;
    
    // Low-Pass Filter
    vel_curr.x = vel_curr.x + alpha*(vel_raw.x-vel_curr.x);
    vel_curr.y = vel_curr.y + alpha*(vel_raw.y-vel_curr.y);
    vel_curr.z = vel_curr.z + alpha*(vel_raw.z-vel_curr.z);

    // Send values to actual message
    odom_curr.twist.twist.linear.x = vel_curr.x;
    odom_curr.twist.twist.linear.y = vel_curr.z;
    odom_curr.twist.twist.linear.z = vel_curr.z;

    // Prepare for next callback
    pose_prev.header = odom_curr.header;
    pose_prev.pose = odom_curr.pose.pose;

    odom_curr_pub.publish(odom_curr);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_node");

    MocapVel od;

    ros::spin();
    return 0;
}

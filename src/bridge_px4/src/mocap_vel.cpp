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
  ROS_WARN("Terminating Publisher");
}

void MocapVel::pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg){
    pose_prev.header = odom_curr.header;
    pose_prev.pose = odom_curr.pose.pose;

    odom_curr.header = msg->header;
    odom_curr.pose.pose = msg->pose;

    float dt = odom_curr.header.stamp.sec-pose_prev.header.stamp.sec;

    float vel_x = (odom_curr.pose.pose.position.x-pose_prev.pose.position.x)/dt;
    float vel_y = (odom_curr.pose.pose.position.y-pose_prev.pose.position.y)/dt;
    float vel_z = (odom_curr.pose.pose.position.z-pose_prev.pose.position.z)/dt;

    vel_curr.x = vel_curr.x + alpha*(vel_x-vel_curr.x);
    vel_curr.y = vel_curr.y + alpha*(vel_y-vel_curr.y);
    vel_curr.z = vel_curr.z + alpha*(vel_z-vel_curr.z);

    odom_curr.twist.twist.linear.x = vel_curr.x;
    odom_curr.twist.twist.linear.y = vel_curr.z;
    odom_curr.twist.twist.linear.y = vel_curr.z;

    odom_curr_pub.publish(odom_curr);
}

int main(int argc, char **argv)
{
    ros::init(argc, argv, "odom_node");

    MocapVel od;

    ros::spin();
    return 0;
}

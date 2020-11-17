#include <ros/ros.h>
#include <geometry_msgs/PoseStamped.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "offb_node");
    ros::NodeHandle nh;

    ros::Publisher local_pos_pub = nh.advertise<geometry_msgs::PoseStamped>
            ("mavros/setpoint_position/local", 10);

    //the setpoint publishing rate MUST be faster than 2Hz
    ros::Rate rate(100.0);

    geometry_msgs::PoseStamped pose;
    int count = 1;
    while(ros::ok()){
        pose.header.stamp = ros::Time::now();
        pose.header.seq   = count;
        pose.header.frame_id = 1;

        pose.pose.position.x = 0;
        pose.pose.position.y = 0;
        pose.pose.position.z = 0;

        pose.pose.orientation.w = 1;
        pose.pose.orientation.x = 0;
        pose.pose.orientation.y = 0;
        pose.pose.orientation.z = 0;

        local_pos_pub.publish(pose);

        ros::spinOnce();
        count++;
        rate.sleep();
    }

    return 0;
}
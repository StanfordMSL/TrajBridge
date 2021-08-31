
#ifndef __MOCAP_VEL_NODE_H__
#define __MOCAP_VEL_NODE_H__

#include "ros/ros.h"

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Vector3.h>
#include <nav_msgs/Odometry.h>

using namespace std;

class MocapVel
{
public:
  // Constructor
  MocapVel();
  virtual ~MocapVel();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Subscriber  pose_curr_sub;
  ros::Publisher   odom_curr_pub;

  geometry_msgs::PoseStamped pose_prev;
  geometry_msgs::Vector3 vel_raw;
  geometry_msgs::Vector3 vel_curr;

  nav_msgs::Odometry odom_curr;

  // Filter Gain
  double alpha;

  // Time
  double dt;
  
  // Functions
  void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);

};

#endif

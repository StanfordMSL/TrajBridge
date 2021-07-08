
#ifndef __MOCAP_GEN_NODE_H__
#define __MOCAP_GEN_NODE_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>
#include <mavros_msgs/State.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class MocapGen
{
public:
  // Constructor
  MocapGen();
  virtual ~MocapGen();

  // Setpoint Function(s)
  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Publisher   pose_curr_pub;
  ros::Subscriber  pose_curr_sub;

  geometry_msgs::PoseStamped pose_curr_in;
  geometry_msgs::PoseStamped pose_curr_out;

  uint32_t k_main;

  // Functions
  void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
};

#endif

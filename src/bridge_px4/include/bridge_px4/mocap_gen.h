#ifndef __MOCAP_GEN_NODE_H__
#define __MOCAP_GEN_NODE_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <gazebo_msgs/ModelStates.h>
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
  ros::Subscriber  pose_curr_sub;
  ros::Publisher   pose_curr_pub;

  geometry_msgs::Pose pose_curr_in;
  geometry_msgs::PoseStamped pose_curr_out;

  uint32_t k_main;

  // Functions
  void pose_cb(const gazebo_msgs::ModelStates::ConstPtr& msg);
};

#endif
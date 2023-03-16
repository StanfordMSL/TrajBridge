
#ifndef __MOCAP_GPS_NODE_H__
#define __MOCAP_GPS_NODE_H__

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

class MocapGPS
{
public:
  // Constructor
  MocapGPS();
  virtual ~MocapGPS();

protected:
  ros::NodeHandle nh;

private:
  string drone_name;
  float x_init;
  float y_init;
  // ROS variables
  ros::Subscriber  pose_curr_sub;
  ros::Publisher   pose_curr_pub;

  geometry_msgs::PoseStamped pose_curr_out;

  uint32_t k_main;

  // Functions
  void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
};

#endif

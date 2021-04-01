/**************************************************************************
  File Name    : visualizer.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Mar 31, 2021.
  Description  : Converts the posestamped msgs to path msgs for rviz
**************************************************************************/

#ifndef __VISUALIZER_H__
#define __VISUALIZER_H__

#include "ros/ros.h"

#include <string>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

#include "ros/ros.h"

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class Visualizer
{
public:
  // Constructor
  Visualizer();
  virtual ~Visualizer();

  // Setpoint Function(s)
  void update_path();

protected:
  ros::NodeHandle nh;

private:
  int n_dr;
  double dt;
  double t_hist;
  int n_fr;
  
  // ROS variables  
  geometry_msgs::PoseStamped pose_des[10];
  geometry_msgs::PoseStamped pose_act[10];
  nav_msgs::Path path_des[10];
  nav_msgs::Path path_act[10];

  ros::Subscriber drone_des_sub[10];
  ros::Subscriber drone_act_sub[10];
  ros::Publisher  path_des_pub[10];
  ros::Publisher  path_act_pub[10];

  ros::Timer updateLoop;   // setpoint update timer

  void des_cb(const geometry_msgs::PoseStamped::ConstPtr& msg, const int idx);
  void act_cb(const geometry_msgs::PoseStamped::ConstPtr& msg, const int idx);

  void update_cb(const ros::TimerEvent& event);
};

#endif

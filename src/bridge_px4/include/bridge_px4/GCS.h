
/**************************************************************************
  File Name    : gcs_node.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Jan 27, 2020.
  Description  : Publisher to Handle Setpoint by Error Over Mavlink
**************************************************************************/

#ifndef __GCS_H__
#define __GCS_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <geometry_msgs/PoseStamped.h>

#include <Eigen/Dense>
#include <map>

using namespace Eigen;
using namespace std;

class GCS
{
public:
  // Constructor
  GCS();
  virtual ~GCS();

  // Setpoint Function(s)
  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Publisher pose_sp_pub[10];

  // Trajectory Variables
  string traj_id;
  vector<vector<vector<double>>> traj;
  int n_dr;
  int n_fr;

  // Time Variables
  ros::Time t_start;
  float t_final;

  geometry_msgs::PoseStamped pose_sp;

  // Counters and Time Variables
  int count_main;
  int count_traj;
  int count_loop;
  int N_traj;

  // Functions
  vector<vector<vector<double>>>  load_trajectory(const string &input);
};

#endif

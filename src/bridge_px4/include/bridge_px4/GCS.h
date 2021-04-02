
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

using namespace Eigen;
using namespace std;

using OneD = vector<double>;
using TwoD = vector<vector<double>>;
using ThreeD = vector<vector<vector<double>>>;

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
  int n_dr;
  int n_fr;
  string  traj_id;
  OneD    t_traj;
  ThreeD  st_traj;

  // Time Variables
  double      t_end;      // end of  single trajectory
  double      t_final;    //  end of total trajectory
  ros::Time   t_start;    // Start time using world clock

  geometry_msgs::PoseStamped pose_sp[10];

  // Counters and Time Variables
  int k_main;
  int k_traj;
  int k_loop;

  // Functions
  void load_trajectory(const string &input);
};

#endif

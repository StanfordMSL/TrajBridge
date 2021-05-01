
/**************************************************************************
  File Name    : GCSVelTraj.h
  Author       : Keiko Nagami
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : knagami@stanford.edu
  Create Time  : Apr 28, 2020.
  Description  : Based on GCS. Publish trajectory waypoints. 
**************************************************************************/

#ifndef __GCSVelTraj_H__
#define __GCSVelTraj_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class GCSVelTraj
{
public:
  // Constructor
  GCSVelTraj();
  virtual ~GCSVelTraj();

  // Setpoint Function(s)
  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Publisher     pose_sp_pub;
  ros::Publisher     vel_sp_pub;

  // Trajectory Variables
  int                 n_fr;
  string              traj_id;
  vector<double>             t_traj;
  vector< vector<double> >   st_traj;

  // Time Variables
  double          t_end;      // end of single trajectory
  double          t_final;    // end of total trajectory
  ros::Time       t_start;    // Start time using world clock

  geometry_msgs::TwistStamped  vel_sp;
  geometry_msgs::PoseStamped   pose_sp;

  // Counters and Time Variables
  int k_main;
  int k_traj;
  int k_loop;

  // Functions
  void load_trajectory(const string &input);
};

#endif

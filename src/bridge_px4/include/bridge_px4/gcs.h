
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

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <mavros_msgs/Thrust.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class GCS
{
public:
  // Constructor
  GCS();
  virtual ~GCS();

  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  string drone_id;                              // Drone Name
  ros::Publisher    pos_sp_pub;                  // Setpoint (In) Position
  ros::Publisher    vel_sp_pub;                  // Setpoint (In) Linear Velocity
  ros::Publisher    att_sp_pub;                  // Setpoint (In) Attitude
  ros::Publisher    rat_sp_pub;                  // Setpoint (In) Angular Rate
  ros::Publisher    thr_sp_pub;                  // Setpoint (In) Throttle

  geometry_msgs::PointStamped       pos_sp;    // Setpoint (In) Position
  geometry_msgs::Vector3Stamped     vel_sp;    // Setpoint (In) Linear Velocity
  geometry_msgs::QuaternionStamped  att_sp;    // Setpoint (In) Attitude
  geometry_msgs::Vector3Stamped     rat_sp;    // Setpoint (In) Angular Rate
  mavros_msgs::Thrust               thr_sp;    // Setpoint (In) Throttle

  int k_main; // Counter
};

#endif

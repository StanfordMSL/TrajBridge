#ifndef __GCSVel_H__
#define __GCSVel_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class GCSVel
{
public:
  // Constructor
  GCSVel();
  virtual ~GCSVel();

  // Setpoint Function(s)
  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Publisher     velocity_sp_pub[10];
  ros::Subscriber    pose_curr_sub[10];

  // Gains
  double kp;
  double ki;
  double kd;

  double integral_term;
  int n_dr;

  // Desired Hover Position
  double hover_x;
  double hover_y;
  double hover_z;

  // Time Variables
  double      t_final;    //  end of total trajectory
  ros::Time   t_start;    // Start time using world clock
  ros::Time   t_prev;     // Previous time

  geometry_msgs::Twist     vel_sp[10];
  geometry_msgs::Vector3   vel_angular;

  // Counters and Time Variables
  int k_main;

  // Functions
  void compute_integral(double &integral_term, double prev_val, double curr_val, double dt_secs);
};

#endif

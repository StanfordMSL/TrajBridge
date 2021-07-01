
/**************************************************************************
  File Name    : auto_rc.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Jul 01, 2021.
  Description  : RC Simulator
**************************************************************************/

#ifndef __AUTO_RC_H__
#define __AUTO_RC_H__

#include "ros/ros.h"

#include <string>

#include <mavros_msgs/CommandBool.h>
#include <mavros_msgs/SetMode.h>

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/Thrust.h>
#include <mavros_msgs/AttitudeTarget.h>

using namespace std;

class Auto_RC
{
public:
  // Constructor
  Auto_RC();
  virtual ~Auto_RC();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Subscriber    pose_sp_sub;
  ros::Subscriber    vel_sp_sub;
  ros::Subscriber    att_sp_sub;

  ros::ServiceClient arming_client;
  ros::ServiceClient set_mode_client;

  geometry_msgs::PoseStamped  pose_sp_in;      // Setpoint Position In
  geometry_msgs::PoseStamped  pose_sp_out;     // Setpoint Position Out

  geometry_msgs::TwistStamped vel_sp_in;       // Setpoint Velocity In
  geometry_msgs::Twist        vel_sp_out;      // Setpoint Velocity Out

  mavros_msgs::AttitudeTarget att_sp_in;       // Setpoint Attitude (body rate, orientation, thrust) In 
  mavros_msgs::AttitudeTarget att_sp_out;      // Setpoint Attitude (body rate, orientation, thrust) Out

  // Setpoint Callbacks
  void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void vel_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
  void att_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg);

  // Functions
  void rc_takeoff_sequence();
  void rc_rtl_sequence();
};

#endif

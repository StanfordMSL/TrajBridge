
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
#include <mavros_msgs/State.h>
#include <bridge_px4/SetSPMode.h>

using namespace std;

class Auto_RC
{
public:
  // Constructor
  Auto_RC();
  virtual ~Auto_RC();

  // Node Variables
  string state;
  string sp_mode_val;
  void rc_takeoff();
  void setSPmode();

protected:
  ros::NodeHandle nh;

private:
  // ROS variables
  ros::Subscriber    state_sub;
  ros::ServiceClient arming_client;
  ros::ServiceClient px4_mode_client;
  ros::ServiceClient sp_mode_client;

  // Functions
  void state_cb(const mavros_msgs::State::ConstPtr& msg);
};

#endif
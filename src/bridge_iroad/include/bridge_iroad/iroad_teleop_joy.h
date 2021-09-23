
#ifndef __IROAD_TELEOP_JOY_H__
#define __IROAD_TELEOP_JOY_H__

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
  
using namespace std;

class Teleop_IRoad
{
public:
  Teleop_IRoad();

protected:
  ros::NodeHandle nh;

private:
  // ROS Publishers/Subscribers
  ros::Subscriber joy_sub_;

  // ROS Timers
  ros::Timer udpLoop;

  // Joystick IDs
  int accel_id;
  int steer_id;
  int ct_input_id;
  int PRNDL_vr_id;
  int PRNDL_ct_id;
  int pk_brake_id;

  // Joystick Data
  float accel;     // ud_l_stick
  float steer;     // lr_l_stick
  float ct_input;  // l_trig
  float PRNDL_vr;  // circle
  float PRNDL_ct;  // square
  float pk_brake;  // cross

  // Offset/Scaling Variables
  float steer_scale;

  // Functions
  void joy_cb(const sensor_msgs::Joy::ConstPtr& joy);
  void udp_cb(const ros::TimerEvent& event);
};


#endif
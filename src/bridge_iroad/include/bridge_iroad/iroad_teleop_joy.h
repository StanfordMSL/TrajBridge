
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

#define PORT 25000

using namespace std;

class Teleop_IRoad
{
public:
  Teleop_IRoad();

protected:
  ros::NodeHandle nh;

private:
  // UDP
  int socket_desc;
  struct sockaddr_in server_addr,client_addr;

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
  struct iroad_cmd { 
    float cmd_0;
    float steer;
    float cmd_2; 
    float ct_input;
    float cmd_4;
    float cmd_5; 
    float accel;
    float cmd_7;
    float cmd_8;
    float pk_brake; 
    float PRNDL_vr;
    float cmd_11; 
    float PRNDL_ct;
    float cmd_13;
    float cmd_14;
    float cmd_15;
    float cmd_16;
    float cmd_17;
    float cmd_18;
    float cmd_19;
    float cmd_20;
    float cmd_21;
    float cmd_22;
    };
  struct iroad_cmd cmd_struct;

  // Offset/Scaling Variables
  float steer_scale;

  // Functions
  void joy_cb(const sensor_msgs::Joy::ConstPtr& joy);
  void udp_cb(const ros::TimerEvent& event);
};


#endif
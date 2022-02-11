
#ifndef __IROAD_CLOSEDLOOP_H__
#define __IROAD_CLOSEDLOOP_H__

#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <sensor_msgs/Imu.h>
#include <sensor_msgs/NavSatFix.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <Eigen/Dense>
#include <numeric>

#define PORT 25000

using namespace std;
using namespace Eigen;

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
  ros::Subscriber imu_sub_;
  ros::Subscriber gps_sub_;

  // ROS Timers
  ros::Timer udpLoop;

  // Joystick IDs
  int accel_id;
  int steer_id;
  int ct_input_id;
  int PRNDL_vr_id;
  int PRNDL_ct_id;
  int pk_brake_id;
  int cl_activation_id; //button to activate closed-loop control
  bool cl_act_chk;

  // Origin location (latitude and longitude)
  float origin_lat;
  float origin_lon;
  float origin_alt;

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
  struct iroad_cmd cmd_in;
  struct iroad_cmd cmd_out;

  // Variables for describing IMU orientation
  Matrix<double,3,1> vHx;
  Matrix<double,3,1> vHxp;
  Matrix<double,3,1> vHy;
  Matrix<double,3,1> vHyp;
  Matrix<double,1,4> psi;
  
  // Variables for describing GNSS localization
  Matrix<double,3,1> xCurr;
  Matrix<double,3,1> xGoal;
  Matrix<double,3,1> xOrig;
  double distance;
  double dist_thres;

  // Offset/Scaling Variables
  float steer_scale;
  
  // Constants
  double r2d;
  double R;

  // Functions
  void joy_cb(const sensor_msgs::Joy::ConstPtr& joy);
  void udp_cb(const ros::TimerEvent& event);
  void imu_cb(const sensor_msgs::Imu::ConstPtr& imu);
  void gps_cb(const sensor_msgs::NavSatFix::ConstPtr& gps);
};


#endif

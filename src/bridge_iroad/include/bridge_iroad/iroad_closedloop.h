
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
  double udp_hz;
  ros::Timer udpLoop;

  // Coordinate Transform Variables
  Matrix<double,3,3> Re2e;    // Transformation matrix from ecef to enu

  // State Variables and Parameters
  Matrix<double,7,1> pose;    // Vehicle Pose in World Frame
  Matrix<double,3,1> p0;      // Origin Position in ECEF
  Matrix<double,3,1> pt;      // Target Position in ECEF
  double ptx;                 // Launch File Input for Target Position in World Frame (x)
  double pty;                 // Launch File Input for Target Position in World Frame (y)
  double lat0;                // Latitude of Origin Point
  double lon0;                // Longitude of Origin Point
  double phi0;
  double lam0;
  double dthres;              // Radius of Goal

  // Input Variables and Parameters
  float steer_scale;
  double accel;
  double steer;

  double v_const;             // Placeholder for CAN feedback: controller assumes vehicle is moving at this velocity (m/s)
  //float ctrl_k1;              // Gain for Feedback Controller (velocity and steering)
  float ctrl_k2;              // Gain for Feedback Controller (steering)
  //float ctrl_k3;            // Gain for Feedback Controller (steering to align with target direction)
  float whlbase;              // Vehicle Wheelbase (longitudinal distance between wheel axes) (m)
  float max_steer;            // Maximum Steering Mechanism Angle (deg)

  // Joystick Data and Parameters
  int  accel_id;
  int  steer_id;
  int  ct_input_id;
  int  PRNDL_vr_id;
  int  PRNDL_ct_id;
  int  pk_brake_id;
  int  cl_act_id; //button to activate closed-loop control
  bool cl_act_chk;

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
  struct iroad_cmd cmd_joy;
  struct iroad_cmd cmd_out;

  // Functions
  void joy_cb(const sensor_msgs::Joy::ConstPtr& joy);
  void udp_cb(const ros::TimerEvent& event);
  void imu_cb(const sensor_msgs::Imu::ConstPtr& imu);
  void gps_cb(const sensor_msgs::NavSatFix::ConstPtr& gps);
  double deg2rad(const double theta_d);
  double rad2deg(const double theta_r);
  Matrix<double,3,1> quatrot(const Vector3d& v);
  Matrix<double,3,1> gcs2ecef(const double lat,const double lon);
  Matrix<double,3,3> Re2e_gen(const double lat,const double lon);
};


#endif

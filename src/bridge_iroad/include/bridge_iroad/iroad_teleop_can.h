
#ifndef __IROAD_TELEOP_CAN_H__
#define __IROAD_TELEOP_CAN_H__

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

#define PORT 25002

using namespace std;

class Teleop_Can
{
public:
  Teleop_Can();

  // Variables for transmitting feedback from vehicle
  geometry_msgs::Twist can_twist; //Contains the vehicle movement indicated by CAN feedback
  //geometry_msgs::Twist can_acgyr; //Contains the signals from vehicle accelerometer and gyroscope
  bool can_seatb; //Contains datum on whether seat belt is engaged
  bool can_doors; //Contains datum on whether either door is open
  bool can_brake; //Contains datum on whether brake pedal is engaged

  // ROS Publishers/Subscribers
  ros::Publisher can_pub_; //Publisher of current vehicle maneuver deduced from CAN feedback (linear: m/s, angular: rad/s)
  ros::Publisher sft_pub_; //PRNDL publisher
  ros::Publisher str_pub_; //Steering publisher
  ros::Publisher acl_pub_; //Accelerator publisher
  ros::Publisher brk_pub_; //Brake pedal publisher
  ros::Publisher hzd_pub_; //Intermittent lights publisher
  ros::Publisher dct_pub_; //Door status publisher
  ros::Publisher sbt_pub_; //Seat belt publisher
  ros::Publisher len_pub_; //Lean angle publisher
  //ros::Publisher gsn_pub_; //Publisher of signals received from internal vehicle accelerometer and gyroscope

  // CAN feedback datagram structure
  struct iroad_feedback {
    u_int32_t can_clck; //clock signal from CAN feedback (value steadily increases, by one at each time step, at 1Hz)
    u_int32_t can_sftps;  //PRNDL setting (0: Neutral, 1: Drive, 2: Reverse)
    int32_t can_steer;  //vehicle steering angle ([-480,480], with negative numbers representing right turns and 0 representing no turn)
    u_int32_t can_accel;  //accelerator setting ([0,96], with the maximum value corresponding to Wide Open Throttle)
    u_int32_t can_brkpd;  //break pedal engagement (0: mechanical brake deactivated, 1: brake pedal engaged)
    int32_t can_vspd;   //vehicle speed (km/h)
    int32_t can_lean;   //vehicle lean angle (degrees)
    u_int32_t can_hzdl;   //turn or hazard light engagement (0: intermittent lights off, 1: right turn indicated, 2: left turn indicated, 3: hazard lights indicated)
    u_int32_t can_dcty;   //door open (0: both doors are closed, 1: left door is open OR right door is open)
    u_int32_t can_stbt;   //seat belt engagement (0: seat belt not engaged, 1: seat belt secured)
    u_int32_t can_pkon;   //parking break engagement (on, {0,1})
    u_int32_t can_pkoff;  //parking break engagement (off, {0,1})
    /*int32_t can_gsenx;  //linear acceleration signals (x,y,z)
    int32_t can_gseny;
    int32_t can_gsenz;
    int32_t can_gyrox;  //gyroscopic signals (x,y,z)
    int32_t can_gyroy;
    int32_t can_gyroz;*/
  };
  struct iroad_feedback can_feedback;

  char buffer[sizeof(can_feedback)]; //buffer to contain data received from vehicle CAN

  // Offset/Scaling Variables
  double st_conv; //Factor for conversion from steering setting to angle of steering mechanism (radians)
  double sp_conv; //Factor for conversion from vehicle speed signal
  //double ln_conv; //Factor for conversion from vehicle lean signal
  /*double ac_conv; //Factor for conversion from internal accelerometer signal
  double gy_conv;*/ //Factor for conversion from internal gyroscope signal
  float whlbase; //Vehicle wheelbase, in meters

  // UDP
  int socket_desc;
  struct sockaddr_in server_addr,client_addr;

protected:
  ros::NodeHandle n;
  
private:

  // ROS Timers
  ros::Timer printLoop;

  // Functions
  void print_cb(const ros::TimerEvent& event);

};


#endif
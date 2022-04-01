
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

  // Variables for transmitting devices
  geometry_msgs::Twist can_twist; //Contains the vehicle movement indicated by CAN feedback

  // ROS Publishers/Subscribers
  ros::Publisher can_pub_;

  // CAN feedback datagram structure
  struct iroad_feedback {
    u_int32_t can_clck; //clock signal from CAN feedback
    u_int32_t can_sftps;  //PRNDL setting
    int32_t can_steer;  //vehicle steering angle
    u_int32_t can_accel;  //accelerator setting
    u_int32_t can_brkpd;  //brake pedal engagement
    int32_t can_vspd;   //vehicle speed
    int32_t can_lean;   //vehicle lean angle
    u_int32_t can_hzdl;   //turn or hazard light engagement
    u_int32_t can_dcty;   //door open
    u_int32_t can_stbt;   //seat belt engagement
    u_int32_t can_pkon;   //parking break engagement (on)
    u_int32_t can_pkoff;  //parking break engagement (off)
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
  float whlbase; //Vehicle wheelbase, in meters

  //int debug_ctr; //counter for debugging 

//private:
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

#ifndef __UDP_SERVER_H__
#define __UDP_SERVER_H__

#include <ros/ros.h>

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT    25000
#define MAXLINE 92
using namespace std;

class UDP_Server
{
public:
  UDP_Server();
protected:
  ros::NodeHandle nh;
private:
  struct iroad_cmd { 
    float steer; 
    float ct_input; 
    float accel;
    float pk_brake; 
    float PRNDL_vr; 
    float PRNDL_ct;
    };
};


#endif
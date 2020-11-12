
/**************************************************************************
  File Name    : setpoint_publisher_node.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Nov 11, 2020.
  Description  : Publisher to Handle Various Setpoint Methods Over Mavlink
**************************************************************************/

#ifndef __SETPOINT_PUBLISHER_NODE_H__
#define __SETPOINT_PUBLISHER_NODE_H__

#include "ros/ros.h"

class SetPointPublisher {
 public:
    SetPointPublisher();
    ~SetPointPublisher();

 private:
    ros::NodeHandle nh;
    ros::Publisher pos_pub;
    ros::Subscriber 

};

#endif
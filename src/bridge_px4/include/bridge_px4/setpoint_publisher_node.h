
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
#include <geometry_msgs/PoseStamped.h>
#include <mavros_msgs/State.h>
#include <bridge_px4/GcsCmd.h>

#include <Eigen/Dense>

enum sp_state
{
   SP_DISARMED,
   SP_ARMED
};

class SetpointPublisher {
private:
   ros::Publisher pos_sp_pub;
   ros::Subscriber state_sub;
   ros::Subscriber pose_sub;
   ros::ServiceServer gcs_service;

   mavros_msgs::State         curr_state;
   geometry_msgs::PoseStamped init_pose;
   geometry_msgs::PoseStamped curr_pose;
   geometry_msgs::PoseStamped targ_pose;
   geometry_msgs::PoseStamped pos_sp;

public:
   SetpointPublisher(ros::NodeHandle *nh);

   sp_state state;
   ros::Time t_start;

   void state_cb(const mavros_msgs::State::ConstPtr& msg);
   void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);

   bool gcs_commander(bridge_px4::GcsCmd::Request &req,bridge_px4::GcsCmd::Response &res);
   
   void update_setpoint();
   void publish_setpoint();
};

#endif
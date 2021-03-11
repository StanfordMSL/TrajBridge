
/**************************************************************************
  File Name    : sp_pos_t_node.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Jan 27, 2020.
  Description  : Publisher to Handle Setpoint by Error Over Mavlink
**************************************************************************/

#ifndef __SETPOINT_POS_T_NODE_H__
#define __SETPOINT_POS_T_NODE_H__

#include "ros/ros.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <geometry_msgs/PoseStamped.h>
#include <std_msgs/Time.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/ParamSet.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class SetpointPublisher {
private:
   // ROS variables
   ros::Publisher     pose_sp_pub;
   ros::Publisher     t_start_pub;
   ros::Subscriber    state_sub;
   ros::Subscriber    pose_sub;
   ros::ServiceClient land_client;
   ros::ServiceClient tune_client;
   
   // Trajectory Variables
   MatrixXd    traj = MatrixXd::Zero(5,2000);
   
   // Quad State/Parameter Variables
   mavros_msgs::State         mode_curr;
   geometry_msgs::PoseStamped pose_curr;
   geometry_msgs::PoseStamped pose_0;
   float                      t_fs;
   float                      err_tol;

   // Setpoint Variables
   enum sp_stream_status {
      SP_STREAM_READY,
      SP_STREAM_ACTIVE,
      SP_STREAM_COMPLETE,
      SP_STREAM_FAILSAFE,
   } sp_status;
   geometry_msgs::PoseStamped pose_sp;

   // Counters and Time Variables
   int count_main;
   int count_traj;
   int count_loop;
   int N_traj;

   std_msgs::Time t_start_out;
   ros::Time   t_start; 
   ros::Time   t_traj;

public:
   // Constructor
   SetpointPublisher(ros::NodeHandle *nh, const std::string& traj_name, const float& t_fs_i, const float& err_tol_i);

   // Last Request Check
   bool last_req_check();

   // Telemetry Function(s)
   void state_cb(const mavros_msgs::State::ConstPtr& msg);
   void pose_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);

   // Setpoint Function(s)
   void update_setpoint();

   // Param Update
   void param_update();
   MatrixXd load_trajectory(const std::string& input);

};

#endif

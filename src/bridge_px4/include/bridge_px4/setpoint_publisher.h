
/**************************************************************************
  File Name    : setpoint_publisher.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Mar 16, 2021.
  Description  : Publisher to Handle Setpoint by Error Over Mavlink
**************************************************************************/

#ifndef __SETPOINT_PUBLISHER_NODE_H__
#define __SETPOINT_PUBLISHER_NODE_H__

#include "ros/ros.h"

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <mavros_msgs/Thrust.h>
#include <mavros_msgs/AttitudeTarget.h>

#include <geometry_msgs/Quaternion.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandCode.h>

#include <Eigen/Dense>

using namespace Eigen;
using namespace std;

class SetpointPublisher {
public:
   // Constructor
   SetpointPublisher();
   virtual ~SetpointPublisher();
protected:
  ros::NodeHandle nh;
private:
   // State Machines
   enum sp_pub_state_machine {
      STARTUP,
      LINKED,
      HOVER,
      ACTIVE,
      FAILSAFE,
   } sp_pub_state;

   enum mc_stream_state_machine {
      MC_INIT,
      MC_ON,
      MC_OFF,
   } mc_stream_state;

   enum ob_mode_state_machine {
      OB_INIT,
      OB_ON,
      OB_OFF,
   } ob_mode_state;

   enum sp_stream_state_machine {
      SP_INIT,
      SP_ON,
      SP_OFF,
   } sp_stream_state;

   enum sp_type_state_machine {
      TP_NONE,
      TP_POS,
      TP_VEL,
      TP_ATT,
   } sp_type_state;

   // Input Params
   string drone_id;
   float sp_out_hz;
   float checkup_hz;
   float sp_gcs_hz_min;
   float checkup_hz_min;
   float dt_fs;
   float dt_rs;

   // Position Publishers/Subscribers
   ros::Publisher     pose_sp_pub;
   ros::Subscriber    pose_sp_sub;

   // Velocity Publishers/Subscribers
   ros::Publisher     vel_sp_pub;
   ros::Subscriber    vel_sp_sub;

   // Attitude Publishers/Subscribers
   ros::Publisher     att_sp_pub;
   ros::Subscriber    att_sp_sub;

   // Drone State/Status Subscribers
   ros::Subscriber    pose_curr_sub;
   ros::Subscriber    mav_state_sub;

   // ROS Timers
   ros::Timer setpointLoop;      // setpoint update timer
   ros::Timer checkupLoop;       // savepoint update timer
   
   // ROS Services
   ros::ServiceClient land_client;
   
   // Quad Setpoints
   geometry_msgs::PoseStamped  pose_sp_in;      // Setpoint Position In
   geometry_msgs::PoseStamped  pose_sp_out;     // Setpoint Position Out

   geometry_msgs::TwistStamped vel_sp_in;       // Setpoint Velocity In
   geometry_msgs::Twist        vel_sp_out;      // Setpoint Velocity Out

   mavros_msgs::AttitudeTarget att_sp_in;       // Setpoint Attitude (body rate, orientation, thrust) In 
   mavros_msgs::AttitudeTarget att_sp_out;      // Setpoint Attitude (body rate, orientation, thrust) Out

   // Quad Parameters
   geometry_msgs::PoseStamped  pose_curr;       // Current Pose
   geometry_msgs::Pose         pose_st;         // Starting Pose
   geometry_msgs::Pose         pose_sa;         // Savepoint Pose (for failsafes and active hover)
   mavros_msgs::State          mode_cr;         // Current Mavros Mode

   // Counters and Time Variables
   int k_main;                  // Main loop counter
   int k_rs;                    // Restore Counter
   int n_rs;                    // Total Restore Counter
   ros::Duration  t_last;
   ros::Duration  setpoint_dt_max;
   ros::Duration  checkup_dt_max;
   ros::Time      t_fs;

   // Constants
   geometry_msgs::Quaternion quat_forward;

   // Telemetry Function(s)
   void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void vel_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
   void att_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg);

   void pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void mav_state_cb(const mavros_msgs::State::ConstPtr& msg);

   void setpoint_cb(const ros::TimerEvent& event);
   void checkup_cb(const ros::TimerEvent& event);

   // Functions
   void land();

   void sp_type_assign();
   void pub_sp_pos();
   void pub_sp_vel();
   void pub_sp_att();
   void pub_sp_active();
};

#endif

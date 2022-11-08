
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
#include "bridge_px4/SetSPMode.h"
#include "bridge_px4/ActACMode.h"

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/AccelStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/ActuatorControl.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandCode.h>

#include <eigen3/Eigen/Dense>

// #include <mavros_msgs/Thrust.h>
// #include <geometry_msgs/Twist.h>

using namespace Eigen;
using namespace std;

class SetpointPublisher {
public:
   // Constructor
   SetpointPublisher();
   virtual ~SetpointPublisher();

   bool setSPmode(bridge_px4::SetSPMode::Request& req, bridge_px4::SetSPMode::Response& res);
   bool actACmode(bridge_px4::ActACMode::Request& req, bridge_px4::ActACMode::Response& res);

protected:
  ros::NodeHandle nh;
private:
   // State Machines
   enum sp_pub_state_machine {            // Setpoint publisher states
      INIT,
      LINKED,
      HOVER,
      ACTIVE
   } sp_pub_state;

   enum mc_stream_state_machine {         // Mocap stream states
      MC_INIT,
      MC_ON,
      MC_OFF,
   } mc_stream_state;

   enum ob_mode_state_machine {           // Offboard mode states
      OB_INIT,
      OB_ON,
      OB_OFF,
   } ob_mode_state;

   enum ac_mode_state_machine {           // Autonomous control mode states
      AC_INIT,
      AC_ON,
      AC_OFF,
   } ac_mode_state;

   enum sp_mode_state_machine {           // Setpoint mode states
      SP_POSE,                            // Send pose setpoints
      SP_BORA,                            // Send body rate setpoints
      SP_ATOP,                            // Send actuator output setpoints
   } sp_mode_state;

   // Node Parameters
   float spo_hz;                          // Setpoint publisher output frequency
   float cup_hz;                          // CheckUp callback frequency
   float spi_hz_min;                      // Setpoint input minimum frequency
   float mci_hz_min;                      // Mocap input minimum frequency
   float sa_z;                        // Failsafe hover height

   // ROS Subscribers
   ros::Subscriber    pose_sp_sub;                 // Position and Orientation (setpoint)
   ros::Subscriber    bora_sp_sub;                 // Attitude (setpoint)
   ros::Subscriber    atop_sp_sub;                 // Thrust,Roll,Pitch,Yaw (setpoint) 
   
   ros::Subscriber    pose_cr_sub;                 // Pose (current)
   ros::Subscriber    mavs_cr_sub;                 // MAV state (current)

   // ROS Publishers
   ros::Publisher     pose_sp_pub;                  // Pose Setpoint
   ros::Publisher     bora_sp_pub;                  // Attitude Setpoint
   ros::Publisher     atop_sp_pub;                  // Wrench Setpoint

   // Timer Loops
   ros::Timer setpointLoop;                        // setpoint update timer
   ros::Timer checkupLoop;                         // savepoint update timer

   // ROS Services
   ros::ServiceServer ac_mode_service;             // AC Mode Service
   ros::ServiceServer sp_mode_service;             // SP Mode Service

   // ROS Clients
   ros::ServiceClient land_client;                 // Landing client

   // Variables
   geometry_msgs::PoseStamped   pose_sp;            // Pose (setpoint)
   mavros_msgs::AttitudeTarget  bora_sp;            // Twist (setpoint) (lin+alg)
   mavros_msgs::ActuatorControl atop_sp;            // Accelerations (setpoint) (lin+alg)
   
   geometry_msgs::PoseStamped   pose_cr;            // Current Pose
   mavros_msgs::State           mode_cr;            // Current Mavros Mode

   geometry_msgs::PoseStamped   pose_sa;            // Savepoint Pose (for failsafes and active hover)
   Vector3f    eps_p;                                // Position Error
   
   // Counters and Time Variables
   int k_main;                                        // Main loop counter
   float  spi_dt_max;                                 // Max time without setpoint data
   float  mci_dt_max;                                 // Max time without mocap data
   Matrix<double,3,2> map_lim;                 

   // Constants
   geometry_msgs::Quaternion q_fw;                // Quaternion Default Forward Direction (along x-axis)

   // Functions
   void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void bora_sp_cb(const mavros_msgs::AttitudeTarget::ConstPtr& msg);
   void atop_sp_cb(const mavros_msgs::ActuatorControl::ConstPtr& msg);
   
   void pose_cr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void mavs_cr_cb(const mavros_msgs::State::ConstPtr& msg);

   void pub_pos();
   void pub_sp();

   void setpoint_cb(const ros::TimerEvent& event);
   void checkup_cb(const ros::TimerEvent& event);

   void land();
};

#endif

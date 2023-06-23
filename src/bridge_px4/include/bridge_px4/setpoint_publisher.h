
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

#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/Vector3Stamped.h>
#include <geometry_msgs/QuaternionStamped.h>
#include <mavros_msgs/Thrust.h>

#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/Twist.h>

#include <mavros_msgs/PositionTarget.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandCode.h>

#include <Eigen/Dense>
#include <cmath>

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
   enum sp_pub_state_machine {                     // Setpoint Publisher (in)
      STARTUP,
      LINKED,
      HOVER,
      ACTIVE,
   } sp_pub_state;

   enum ep_stream_state_machine {                  // External Pose Stream (MoCap/GPS)
      EP_INIT,
      EP_ON,
      EP_OFF,
   } ep_stream_state;

   enum ob_mode_state_machine {                    // Offboard Mode
      OB_INIT,
      OB_ON,
      OB_OFF,
   } ob_mode_state;

   enum sp_stream_state_machine {                  // Setpoint Stream (out)
      SP_INIT,
      SP_ON,
      SP_OFF,
   } sp_stream_state;

   enum sp_type_state_machine {                  // Setpoint Stream (out)
      TP_NONE,
      TP_POSE,
      TP_TWST,
   } sp_type_state;

   // Constants
   geometry_msgs::Quaternion quat_forward;         // Front Facing Attitude

   // Node Input Params
   string drone_id;                                // Drone Name
   float sp_out_hz;                                // Setpoint Output Rate
   float checkup_hz;                               // Checkup Rate
   float z_fs;                                     // Failsafe Altitude
   float r_fs;                                     // Failsafe Ball Radius

   // Setpoint Subscribers
   ros::Subscriber    pos_sp_sub;                  // Setpoint (In) Position
   ros::Subscriber    att_sp_sub;                  // Setpoint (In) Attitude
   ros::Subscriber    vel_sp_sub;                  // Setpoint (In) Velocity
   ros::Subscriber    bdr_sp_sub;                  // Setpoint (In) BodyRate
   
   // Setpoint Publishers
   ros::Publisher     pose_sp_pub;                 // Position Target (position, velocity, acceleration)
   ros::Publisher     twst_sp_pub;                 // Velocity Target

   // Drone State/Status Subscribers
   ros::Subscriber    pose_curr_sub;               // Drone's Current Pose 
   ros::Subscriber    mav_state_sub;               // Drone's Current Flight State (mav state)

   // ROS Timers
   ros::Timer setpointLoop;                        // Setpoint update timer
   ros::Timer checkupLoop;                         // Savepoint update timer

   // ROS Services
   ros::ServiceClient land_client;                 // Client to Trigger Landing

   // Quad Setpoints (In)
   geometry_msgs::PointStamped       pos_sp_in;    // Setpoint (In) Position
   geometry_msgs::QuaternionStamped  att_sp_in;    // Setpoint (In) Attitude
   geometry_msgs::Vector3Stamped     vel_sp_in;    // Setpoint (In) Velocity
   geometry_msgs::Vector3Stamped     bdr_sp_in;    // Setpoint (In) BodyRate

   // Quad Setpoints (Out)
   geometry_msgs::PoseStamped pose_sp_out;        // Setpoint Attitude (body rate, orientation, thrust) In
   geometry_msgs::Twist       twst_sp_out;        // Setpoint Velocity 

   // Quad Parameters
   geometry_msgs::PoseStamped  pose_curr;          // Current Pose
   geometry_msgs::Pose         pose_st;            // Starting Pose
   geometry_msgs::Pose         pose_sa;            // Savepoint Pose (for failsafes and active hover)
   mavros_msgs::State          mode_cr;            // Current Mavros Mode

   // Counters
   int k_main;                                     // Main loop counter

   // Checkup Variables
   ros::Duration dt_max;                           // Maximum time without without target setpoints 
   bool pos_check;                                 // Checker for Setpoint (In) Position Topic
   bool att_check;                                 // Checker for Setpoint (In) Linear Velocity Topic
   bool vel_check;                                 // Checker for Setpoint (In) Linear Velocity Topic
   bool bdr_check;                                 // Checker for Setpoint (In) Angular Velocity Topic

   // Input Functions
   void pos_sp_cb(const geometry_msgs::PointStamped::ConstPtr& msg);           // Update Setpoint Position
   void att_sp_cb(const geometry_msgs::QuaternionStamped::ConstPtr& msg);      // Update Setpoint Attitude
   void vel_sp_cb(const geometry_msgs::Vector3Stamped::ConstPtr& msg);         // Update Setpoint Velocity
   void bdr_sp_cb(const geometry_msgs::Vector3Stamped::ConstPtr& msg);         // Update Setpoint BodyRate

   // Node State Functions
   void pose_curr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);  // Update Current Position
   void mav_state_cb(const mavros_msgs::State::ConstPtr& msg);          // Update Current mav state
   void checkup_cb(const ros::TimerEvent& event);                       // Checkup Loop

   // Output Functions
   void setpoint_cb(const ros::TimerEvent& event);                      // State Machine Loop
   void pub_sp_active();
   void pub_sp_pose();
   void pub_sp_twst();                                                       // Publish Setpoint
   void sp_type_assign();

   // Service Function
   void land();                                                         // Landing
};

#endif

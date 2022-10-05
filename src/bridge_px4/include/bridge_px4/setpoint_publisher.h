
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
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/AccelStamped.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <geometry_msgs/Quaternion.h>

#include <mavros_msgs/State.h>
#include <mavros_msgs/CommandTOL.h>
#include <mavros_msgs/CommandCode.h>

#include <Eigen/Dense>

// #include <mavros_msgs/Thrust.h>
// #include <geometry_msgs/Twist.h>

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

   enum ac_mode_state_machine {
      AC_INIT,
      AC_ON,
      AC_OFF,
   } ac_mode_state;

   enum sp_type_state_machine {
      TP_NONE,
      TP_POS,
      TP_ATT,
   } sp_type_state;

   // Input Params
   string drone_id;
   float sp_out_hz;
   float checkup_hz;
   float sp_hz_min;
   float checkup_hz_min;
   float dt_fs;
   float dt_rs;
   float z_fs;

   // Subscribers
   ros::Subscriber    pose_sp_sub;                 // Pose (setpoint)
   ros::Subscriber    vels_sp_sub;                 // Velocities (setpoint) (lin+ang) 
   ros::Subscriber    accs_sp_sub;                 // Accelerations (setpoint) (lin+ang) 
   
   ros::Subscriber    pose_cr_sub;                 // Pose (current)
   ros::Subscriber    mavs_cr_sub;                 // MAV state (current)

   // Publishers
   ros::Publisher     poseT_sp_pub;                // Position Setpoint
   ros::Publisher     attdT_sp_pub;                // Attitude Setpoint

   // Variables
   geometry_msgs::PoseStamped  pose_sp;            // Pose (setpoint)
   geometry_msgs::TwistStamped vels_sp;            // Velocities (setpoint) (lin+alg)
   geometry_msgs::AccelStamped accs_sp;            // Accelerations (setpoint) (lin+alg)
   geometry_msgs::PoseStamped  poseT_sp;           // Pose Target Setpoint
   mavros_msgs::AttitudeTarget attdT_sp;           // Attitude Target Setpoint
   geometry_msgs::PoseStamped  pose_cr;            // Current Pose
   geometry_msgs::Pose         pose_st;            // Starting Pose
   geometry_msgs::Pose         pose_sa;            // Savepoint Pose (for failsafes and active hover)
   mavros_msgs::State          mode_cr;            // Current Mavros Mode

   // ROS Services
   ros::ServiceClient land_client;                 // Landing client

   // Counters and Time Variables
   int k_main;                                     // Main loop counter
   int k_rs;                                       // Current Restore Counter
   int n_rs;                                       // Total Restore Counter
   Matrix<double,3,1> dt_max_vect;                 
   ros::Timer setpointLoop;                        // setpoint update timer
   ros::Timer checkupLoop;                         // savepoint update timer
   ros::Time      t_fs;
   ros::Duration  t_last;
   ros::Duration  pose_dt_max;
   ros::Duration  vels_dt_max;
   ros::Duration  accs_dt_max;
   ros::Duration  dt_max;
   ros::Duration  checkup_dt_max;

   // Constants
   geometry_msgs::Quaternion quat_forward;

   // Functions
   void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void vels_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
   void accs_sp_cb(const geometry_msgs::AccelStamped::ConstPtr& msg);
   
   void pose_cr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void mavs_cr_cb(const mavros_msgs::State::ConstPtr& msg);

   void pub_sp_pose();
   void pub_sp_attd();
   void pub_sp_active();

   void setpoint_cb(const ros::TimerEvent& event);
   void checkup_cb(const ros::TimerEvent& event);

   void land();

   void pose_compute();
   void attD_compute();
};

#endif

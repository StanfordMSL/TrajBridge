
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
#include "bridge_px4/SetACMode.h"

#include <geometry_msgs/Pose.h>
#include <geometry_msgs/PoseStamped.h>
#include <geometry_msgs/TwistStamped.h>
#include <geometry_msgs/AccelStamped.h>
#include <mavros_msgs/AttitudeTarget.h>
#include <mavros_msgs/ManualControl.h>
#include <geometry_msgs/Quaternion.h>

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

   bool setACmode(bridge_px4::SetACMode::Request& req, bridge_px4::SetACMode::Response& res);

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
      SP_NONE,                            // No setpoints allowed
      SP_POSE,                            // Send pose setpoints
      SP_BORA,                            // Send body rate setpoints (thrust normalized)
      SP_WRCH,                            // Send wrench setpoints (all normalized 1x[0 1],3x[-1 1])
   } sp_mode_state;

   // Node Parameters
   float spo_hz;                          // Setpoint publisher output frequency
   float cup_hz;                          // CheckUp callback frequency
   float spi_hz_min;                      // Setpoint input minimum frequency
   float mci_hz_min;                      // Mocap input minimum frequency
   float fs_th;                           // Failsafe landing trigger threshold (s)
   float rs_th;                           // Resume trigger threshold (s)
   float fs_hov_z;                        // Failsafe hover height
   float eps_p_th;                        // Position error threshold

   // ROS Subscribers
   ros::Subscriber    pose_sp_sub;                 // Pose (setpoint)
   ros::Subscriber    vels_sp_sub;                 // Velocities (setpoint) (lin+ang) 
   ros::Subscriber    accs_sp_sub;                 // Accelerations (setpoint) (lin+ang) 
   
   ros::Subscriber    pose_cr_sub;                 // Pose (current)
   ros::Subscriber    mavs_cr_sub;                 // MAV state (current)

   // ROS Publishers
   ros::Publisher     pose_tg_pub;                 // Position Setpoint
   ros::Publisher     bora_tg_pub;                 // Attitude Setpoint
   ros::Publisher     wrch_tg_pub;                 // Attitude Setpoint

   // Timer Loops
   ros::Timer setpointLoop;                        // setpoint update timer
   ros::Timer checkupLoop;                         // savepoint update timer

   // ROS Clients
   ros::ServiceClient land_client;                 // Landing client

   // Variables
   geometry_msgs::PoseStamped  pose_sp;            // Pose (setpoint)
   geometry_msgs::TwistStamped vels_sp;            // Velocities (setpoint) (lin+alg)
   geometry_msgs::AccelStamped accs_sp;            // Accelerations (setpoint) (lin+alg)

   geometry_msgs::PoseStamped  pose_cr;            // Current Pose
   mavros_msgs::State          mode_cr;            // Current Mavros Mode

   geometry_msgs::PoseStamped  pose_tg;            // Pose Target 
   mavros_msgs::AttitudeTarget bora_tg;            // Body Rate Target 
   mavros_msgs::ManualControl  wrch_tg;            // Wrench Target
   
   geometry_msgs::Pose         pose_sa;            // Savepoint Pose (for failsafes and active hover)
   Vector3f    eps_p;                                 // Position Error
   // Counters and Time Variables
   int k_main;                                     // Main loop counter
   ros::Time      t_fs0;                           // Failsafe start time
   ros::Duration  t_rs;                            // Reset time counter
   // int k_rs;                                       // Current Restore Counter
   // int n_rs;                                       // Total Restore Counter
   // Matrix<double,3,1> dt_max_vect;                 
   // ros::Duration  pose_dt_max;
   // ros::Duration  vels_dt_max;
   // ros::Duration  accs_dt_max;
   float  spi_dt_max;
   float  mci_dt_max;

   // Constants
   geometry_msgs::Quaternion q_fw;                // Quaternion Default Forward Direction (along x-axis)

   // Functions
   void pose_sp_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void vels_sp_cb(const geometry_msgs::TwistStamped::ConstPtr& msg);
   void accs_sp_cb(const geometry_msgs::AccelStamped::ConstPtr& msg);
   
   void pose_cr_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
   void mavs_cr_cb(const mavros_msgs::State::ConstPtr& msg);

   void pub_sp_pose();
   void pub_sp_bora();
   void pub_sp_wrch();

   void setpoint_cb(const ros::TimerEvent& event);
   void checkup_cb(const ros::TimerEvent& event);

   void land();

   void pose_compute();
   void bora_compute();
   void wrch_compute();
};

#endif

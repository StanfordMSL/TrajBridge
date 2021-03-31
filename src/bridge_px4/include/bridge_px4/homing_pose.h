
/**************************************************************************
  File Name    : homing_pose_node.h
  Author       : JunEn Low
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : jelow@stanford.edu
  Create Time  : Mar 30, 2021.
  Description  : Publisher to Handle Setpoint by Error Over Mavlink
**************************************************************************/

#ifndef __HOMING_POSE_H__
#define __HOMING_POSE_H__

#include "ros/ros.h"

#include <geometry_msgs/PoseStamped.h>

#include <tf/tf.h>
#include <Eigen/Dense>

using namespace Eigen;
using namespace std;
using namespace tf;

class HomingPose
{
public:
  // Constructor
  HomingPose();
  virtual ~HomingPose();
  
  // Setpoint Function(s)
  void update_setpoint();

protected:
  ros::NodeHandle nh;

private:
  // ROS Publishers and Subscribers
  ros::Publisher  pose_sp_pub;
  ros::Subscriber pose_gquad_sub;
  ros::Subscriber pose_targ_sub;
  
  // ROS State Variables
  geometry_msgs::PoseStamped pose_t_gquad;      // Current GQuad Pose
  geometry_msgs::PoseStamped pose_t_grasp;      // Current GQuad Pose
  geometry_msgs::PoseStamped pose_t_targ;       // Current Target Pose
  geometry_msgs::PoseStamped pose_t_sp_out;     // Output setpoint.
  geometry_msgs::Pose pose_sa;                 // Savepoint Pose (for failsafes and active hover)
  geometry_msgs::Pose pose_pitbull;                 // Savepoint Pose (for failsafes and active hover)

  // ROS Timers
  ros::Timer checkupLoop;

  // State Machine
  enum gquad_state_machine {
      PRELOCK,
      TRACKING,
      PITBULL,
      COMPLETE,
   } gquad_state;

  // Grasp-Quad Variables
  int gquad_id;
  geometry_msgs::Pose tf_grasper;

  // Homing Variables
  double l2_tracking;
  double l2_pitbull;
  double dt_pitbull;
  double pos_offset;

  // Counters and Time Variables
  int k_main;
  ros::Time t_pitbull;

  // Constants
   geometry_msgs::Quaternion quat_forward;

  // Functions
  void pose_gquad_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void pose_targ_cb(const geometry_msgs::PoseStamped::ConstPtr& msg);
  void checkup_cb(const ros::TimerEvent& event);
  Vector3d pos_rel_calc(geometry_msgs::Point a,geometry_msgs::Point b);

};

#endif

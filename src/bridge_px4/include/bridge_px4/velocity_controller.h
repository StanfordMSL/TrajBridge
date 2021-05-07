/* copyright[2020] <msl> <kunal shah>
**************************************************************************
  File Name    : velocityController.h
  Author       : Kunal Shah
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : k2shah@stanford.edu
  Create Time  : Aug 18, 2020.
  Description  : generic pid feedforward velocity controller
**************************************************************************/

#ifndef __velocity_controller_H__
#define __velocity_controller_H__

#include <string>

#include "ros/ros.h"
#include "geometry_msgs/PoseStamped.h"
#include "geometry_msgs/TwistStamped.h"

#include "pid.h"

template <typename T>
void recepitCallback(const T& msg, T& receipt){
    receipt = msg;
}

class Controller
{
public:
    Controller();
    ~Controller();
    // topic name: outgoing twist
    std::string setpointTwist_topic;
    // topic names: incoming pose and twist
    std::string targetPose_topic;
    std::string targetTwist_topic;
    std::string currentPose_topic;

private:
    // ros
    ros::NodeHandle _nh;
    // controller implementation
    ros::Time _publishTime;
    PID4d _controller;
    void setParameters();

    // messages
    geometry_msgs::TwistStamped _setpointTwistSp;

    // ros subs
    // current pose
    geometry_msgs::PoseStamped _currentPoseSp;
    ros::Subscriber _currentPose_sub;
    void currentPoseCB(const geometry_msgs::PoseStamped& msg);
    // target pose
    geometry_msgs::PoseStamped _targetPoseSp;
    ros::Subscriber _targetPose_sub;
    void targetPoseCB(const geometry_msgs::PoseStamped& msg);

    // target vel
    geometry_msgs::TwistStamped _targetTwistSp;
    ros::Subscriber _targetTwist_sub;
    void targetTwistCB(const geometry_msgs::TwistStamped& msg);

    // yaw
    float _currentYaw;
    float _targetYaw;
    float getYawAngle(const geometry_msgs::PoseStamped& msg);

    // ros pubs
    ros::Publisher _setpointTwist_pub;

    double setpointFreq_;
    ros::Timer setpointTimer_;
    void setpointLoopCB(const ros::TimerEvent& event);
};

#endif

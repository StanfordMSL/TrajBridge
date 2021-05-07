/* copyright[2020] <msl> <kunal shah>
**************************************************************************
  File Name    : velocityController.h
  Author       : Kunal Shah
                 Multi-Robot Systems Lab (MSL), Stanford University
  Contact      : k2shah@stanford.edu
  Create Time  : Aug 18, 2020.
  Description  : generic pid feedforward velocity controller
**************************************************************************/

#include "bridge_px4/velocity_controller.h"

Controller::Controller(){
// retrieve ROS parameter
  // topic names
  ros::param::param<std::string>(
    "~targetPose_topic", targetPose_topic, "command/pose");

  ros::param::param<std::string>(
    "~targetTwist_topic", targetTwist_topic, "command/twist");

  ros::param::param<std::string>(
    "~setpointTwist_topic", setpointTwist_topic, "setpoint/velocity");

    ros::param::param<std::string>(
      "~currentPose_topic", currentPose_topic, "mavros/vision_pose/pose");

  // timer frequenceies
  ros::param::param<double>(
    "~setpointFreq", setpointFreq_, 100.0);

  // pid paramters
  setParameters();

  // ROS subs
  _currentPose_sub = _nh.subscribe(
    currentPose_topic, 1,
    &Controller::currentPoseCB, this);

  _targetPose_sub = _nh.subscribe(
    targetPose_topic,1,
    &Controller::targetPoseCB, this);

  _targetTwist_sub = _nh.subscribe(
    targetTwist_topic,1,
    &Controller::targetTwistCB, this);


  //ROS pubs
  _setpointTwist_pub = _nh.advertise<geometry_msgs::TwistStamped>(
      setpointTwist_topic, 1);


  // wait for initial
  while (ros::ok() && _targetPoseSp.header.seq < 10) {
      std::cout << "waiting for initial command." << std::endl;
      ros::spinOnce();
      ros::Duration(1.0).sleep();
  }
  _publishTime = ros::Time::now();

  // start timers
  setpointTimer_ = _nh.createTimer(
    ros::Duration(1.0/setpointFreq_),
    &Controller::setpointLoopCB, this);

}
Controller::~Controller(){

}

void Controller::setParameters(){
  float kp, ki, kd, integralLimit;
    // pid paramters
  ros::param::param<float>(
    "~kp", kp, 1.0f);
  ros::param::param<float>(
    "~ki", ki, 0.0f);
  ros::param::param<float>(
    "~kf", kd, 0.0f);
  ros::param::param<float>(
    "~integralLimit", integralLimit, 0.0f);

  _controller.setGains(kp, ki, kd);
  _controller.setIntegralLimit(integralLimit);

}

void Controller::currentPoseCB(const geometry_msgs::PoseStamped& msg){
  _currentPoseSp = msg;
}

void Controller::targetPoseCB(const geometry_msgs::PoseStamped& msg){
  _targetPoseSp = msg;
}

void Controller::targetTwistCB(const geometry_msgs::TwistStamped& msg){
  _targetTwistSp = msg;
}

void Controller::setpointLoopCB(const ros::TimerEvent& event){
  float dt = ros::Time::now().toSec() - _publishTime.toSec();
  _publishTime = ros::Time::now();

  // run pid and update setpoints
  // x
  _setpointTwistSp.twist.linear.x = _controller.x.effort(
    _currentPoseSp.pose.position.x,
    _targetPoseSp.pose.position.x,
    dt,
    _targetTwistSp.twist.linear.x);
  // y
  _setpointTwistSp.twist.linear.y = _controller.y.effort(
    _currentPoseSp.pose.position.y,
    _targetPoseSp.pose.position.y,
    dt,
    _targetTwistSp.twist.linear.y);
    // z
  _setpointTwistSp.twist.linear.z = _controller.z.effort(
    _currentPoseSp.pose.position.z,
    _targetPoseSp.pose.position.z,
    dt,
    _targetTwistSp.twist.linear.z);
  // yaw
  _currentYaw = getYawAngle(_currentPoseSp);
  _targetYaw  = getYawAngle(_targetPoseSp);

  _setpointTwistSp.twist.angular.z = _controller.yaw.effort(
    _currentYaw,
    _targetYaw,
    dt,
    _targetTwistSp.twist.angular.z);

  _setpointTwistSp.header.stamp = _publishTime;
  _setpointTwistSp.header.frame_id = "map";
  _setpointTwist_pub.publish(_setpointTwistSp);

}

float Controller::getYawAngle(const geometry_msgs::PoseStamped& msg){
    const float qw = msg.pose.orientation.w;
    const float qx = msg.pose.orientation.x;
    const float qy = msg.pose.orientation.y;
    const float qz = msg.pose.orientation.z;
    return atan2(2*(qw*qz + qx*qy), 1 - 2*(qy*qy + qz*qz));
}

int main(int argc, char **argv) {
    ros::init(argc, argv, "controller");
    ROS_INFO_STREAM("Controller Initiated");
    Controller controller;
    while(ros::ok()){
      ros::spin();
    }
    return 0;
  }

// MIT License
//
// Copyright (c) 2022 Alvin Sun
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "vrpn_mocap/tracker.hpp"

#include <eigen3/Eigen/Geometry>
#include <chrono>
#include <functional>
#include <memory>
#include <regex>
#include <string>
#include <math.h>

namespace vrpn_mocap
{

using px4_msgs::msg::VehicleOdometry;
using namespace std::chrono_literals;

std::string Tracker::ValidNodeName(const std::string & tracker_name)
{
  // replace non alphanum characters with _
  const std::string alnum_name = std::regex_replace(tracker_name, std::regex("[^a-zA-Z0-9_]"), "_");
  // strip consecutive underscores
  const std::string node_name = std::regex_replace(alnum_name, std::regex("_+"), "_");

  return node_name;
}

Tracker::Tracker(const std::string & tracker_name)
: Node(ValidNodeName(tracker_name)),
  name_(tracker_name),
  multi_sensor_(declare_parameter("multi_sensor", false)),
  frame_id_(declare_parameter("frame_id", "world")),
  vrpn_tracker_(name_.c_str())
{
  Init();

  // start main loop when instantiated as a standalone node
  const double update_freq = this->declare_parameter("update_freq", 100.);
  timer_ = this->create_wall_timer(1s / update_freq, std::bind(&Tracker::MainLoop, this));
}

Tracker::Tracker(
  const rclcpp::Node & base_node, const std::string & tracker_name,
  const std::shared_ptr<vrpn_Connection> & connection)
: Node(base_node, ValidNodeName(tracker_name)),
  name_(tracker_name),
  multi_sensor_(base_node.get_parameter("multi_sensor").as_bool()),
  frame_id_(base_node.get_parameter("frame_id").as_string()),
  vrpn_tracker_(name_.c_str(), connection.get())
{
  Init();
}

Tracker::~Tracker()
{
  vrpn_tracker_.unregister_change_handler(this, &Tracker::HandlePose);
  vrpn_tracker_.unregister_change_handler(this, &Tracker::HandleTwist);

  RCLCPP_INFO_STREAM(this->get_logger(), "Destroyed new tracker " << name_);
}

void Tracker::Init()
{
  vrpn_tracker_.register_change_handler(this, &Tracker::HandlePose);
  vrpn_tracker_.register_change_handler(this, &Tracker::HandleTwist);
  vrpn_tracker_.shutup = true;

  RCLCPP_INFO_STREAM(this->get_logger(), "Created new tracker " << name_);
}

void Tracker::MainLoop() {vrpn_tracker_.mainloop();}

void VRPN_CALLBACK Tracker::HandlePose(void * data, const vrpn_TRACKERCB tracker_pose)
{
  Tracker * tracker = static_cast<Tracker *>(data);

  // lazy initialization of publisher
  auto pub = tracker->GetOrCreatePublisher<VehicleOdometry>(
    static_cast<size_t>(tracker_pose.sensor), "vodom", &tracker->odom_pubs_);

  // populate message
  px4_msgs::msg::VehicleOdometry msg;

  msg.timestamp = tracker->get_clock()->now().seconds();
  
  msg.pose_frame = msg.POSE_FRAME_NED;
  msg.position[0] = tracker_pose.pos[0];
  msg.position[1] = tracker_pose.pos[1];
  msg.position[2] = tracker_pose.pos[2];

  msg.q[0] = tracker_pose.quat[0];
  msg.q[1] = tracker_pose.quat[1];
  msg.q[2] = tracker_pose.quat[2];
  msg.q[3] = tracker_pose.quat[3];

  msg.velocity_frame = msg.VELOCITY_FRAME_UNKNOWN;
  msg.velocity = {NAN,NAN,NAN};
  msg.angular_velocity = {NAN,NAN,NAN};

  msg.position_variance = {NAN,NAN,NAN};
  msg.orientation_variance = {NAN,NAN,NAN};
  msg.velocity_variance = {NAN,NAN,NAN};
  
  pub->publish(msg);
}

void VRPN_CALLBACK Tracker::HandleTwist(void * data, const vrpn_TRACKERVELCB tracker_twist)
{
  Tracker * tracker = static_cast<Tracker *>(data);

  // Some math
  const Eigen::Quaterniond quat(
    tracker_twist.vel_quat[3], tracker_twist.vel_quat[0], tracker_twist.vel_quat[1],
    tracker_twist.vel_quat[2]);
  const Eigen::AngleAxisd axis_ang(quat);
  const Eigen::Vector3d rot_vel = axis_ang.axis() * axis_ang.angle() / tracker_twist.vel_quat_dt;

  // lazy initialization of publisher
  auto pub = tracker->GetOrCreatePublisher<VehicleOdometry>(
    static_cast<size_t>(tracker_twist.sensor), "vodom", &tracker->odom_pubs_);

  // populate message
  px4_msgs::msg::VehicleOdometry msg;

  msg.timestamp = tracker->get_clock()->now().seconds();

  msg.pose_frame = msg.POSE_FRAME_NED;
  msg.position = {NAN,NAN,NAN};
  msg.q = {NAN,NAN,NAN,NAN};

  msg.velocity_frame = msg.VELOCITY_FRAME_UNKNOWN;
  msg.velocity[0] = tracker_twist.vel[0];
  msg.velocity[1] = tracker_twist.vel[1];
  msg.velocity[2] = tracker_twist.vel[2];

  msg.angular_velocity[0] = rot_vel.x();
  msg.angular_velocity[1] = rot_vel.y();
  msg.angular_velocity[2] = rot_vel.z();

  msg.position_variance = {NAN,NAN,NAN};
  msg.orientation_variance = {NAN,NAN,NAN};
  msg.velocity_variance = {NAN,NAN,NAN};
  
  pub->publish(msg);

}


}  // namespace vrpn_mocap

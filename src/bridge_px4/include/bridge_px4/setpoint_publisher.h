/**
 * @brief Setpoint Publisher Header
 * @file setpoint_publisher.h
 * @addtogroup bridge_px4
 * @author JunEn Low <jelow@stanford.edu>
 *
 */

// #ifndef SETPOINT_PUBLISHER_H
// #define SETPOINT_PUBLISHER_H


#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <rclcpp/rclcpp.hpp>
#include <stdint.h>

#include <chrono>
#include <iostream>

using namespace std::chrono;
using namespace std::chrono_literals;
using namespace px4_msgs::msg;

// class SetpointPublisher : public rclcpp::Node 
// { 
// public:
//    // Constructor
//    SetpointPublisher() : Node("setpoint_publisher") {}
// private:
//    rclcpp::TimerBase::SharedPtr timer_;

//    void timerCallback();
// };


// #endif // FRAME_TRANSFORMS_H

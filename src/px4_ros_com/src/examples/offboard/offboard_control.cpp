/****************************************************************************
 *
 * Copyright 2020 PX4 Development Team. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its contributors
 * may be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ****************************************************************************/

/**
 * @brief Offboard control example
 * @file offboard_control.cpp
 * @addtogroup examples
 * @author Mickey Cowden <info@cowden.tech>
 * @author Nuno Marques <nuno.marques@dronesolutions.io>
 */

#include <px4_msgs/msg/offboard_control_mode.hpp>
#include <px4_msgs/msg/trajectory_setpoint.hpp>
#include <px4_msgs/msg/vehicle_command.hpp>
#include <px4_msgs/msg/vehicle_control_mode.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>
#include <rclcpp/rclcpp.hpp>
#include <stdint.h>
#include <eigen3/Eigen/Dense>

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;
using namespace std::chrono_literals;
using namespace px4_msgs::msg;
using namespace Eigen;


class OffboardControl : public rclcpp::Node
{
public:
	OffboardControl() : Node("offboard_control")
	{
		// Parameters
		declare_parameter("pos_ref",vector<double>{0.0,0.0,0.0});
		declare_parameter("safe_lim", 1.0);
		declare_parameter("test_lim", 0.1);

		vector<double> vect_pos_ref; 
		get_parameter("pos_ref",vect_pos_ref);
		get_parameter("safe_lim",lim_safe);
		get_parameter("test_lim",lim_test);
		pos_ref << vect_pos_ref[0],vect_pos_ref[1],vect_pos_ref[2];

		// Checkers
		in_safe = true;
		in_test = false;

		// Publishers
		offboard_control_mode_publisher_ = this->create_publisher<OffboardControlMode>("/fmu/in/offboard_control_mode", 10);
		trajectory_setpoint_publisher_ = this->create_publisher<TrajectorySetpoint>("/fmu/in/trajectory_setpoint", 10);
		vehicle_command_publisher_ = this->create_publisher<VehicleCommand>("/fmu/in/vehicle_command", 10);
      	
		// Subscribers
		rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
		auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);

		vehicle_odometry_subscriber_ = this->create_subscription<px4_msgs::msg::VehicleOdometry>("/fmu/out/vehicle_odometry", qos,
		[this](const px4_msgs::msg::VehicleOdometry::UniquePtr msg) {
			Vector3f pos_now;
			pos_now << msg->position[0], msg->position[1], msg->position[2];

			float dist = (pos_now-pos_ref).norm();

			if (dist > lim_safe) {
				OffboardControl::in_safe = false;
				OffboardControl::in_test = false;
			} else {
				if (dist < lim_test) {
					OffboardControl::in_test = true;
				}
			}

			
		});

		offboard_setpoint_counter_ = 0;
		offboard_out_zone_counter_ = 0;

		auto timer_callback = [this]() -> void {
			
			if (offboard_setpoint_counter_ == 10) {
				// Change to Offboard mode after 10 setpoints
				this->publish_vehicle_command(VehicleCommand::VEHICLE_CMD_DO_SET_MODE, 1, 6);

				// Arm the vehicle
				this->arm();
			}

			if (OffboardControl::in_safe == false) {			
				if (offboard_out_zone_counter_ < 11) {
					this->publish_vehicle_command(VehicleCommand::VEHICLE_CMD_NAV_LAND);
					offboard_out_zone_counter_++;
				}
			} else {
				if (OffboardControl::in_test == true) {
					this->publish_offboard_control("sfti");
				} else {
					this->publish_offboard_control("taxi");
				}
				
			}

			// stop the counter after reaching 11
			if (offboard_setpoint_counter_ < 11) {
				offboard_setpoint_counter_++;
			}
		};
		timer_ = this->create_wall_timer(100ms, timer_callback);
	}

	void arm();
	void disarm();

private:
	rclcpp::TimerBase::SharedPtr timer_;

	rclcpp::Publisher<OffboardControlMode>::SharedPtr offboard_control_mode_publisher_;
	rclcpp::Publisher<TrajectorySetpoint>::SharedPtr trajectory_setpoint_publisher_;
	rclcpp::Publisher<VehicleCommand>::SharedPtr vehicle_command_publisher_;
    rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr vehicle_odometry_subscriber_;

	std::atomic<uint64_t> timestamp_;   //!< common synced timestamped

	uint64_t offboard_setpoint_counter_;   //!< counter for the number of setpoints sent
	uint64_t offboard_out_zone_counter_;   //!< counter for the number of setpoints sent
	Vector3f pos_ref;
	bool in_safe, in_test;
	float lim_safe,lim_test;	

	void publish_offboard_control(std::string mode);
	void publish_vehicle_command(uint16_t command, float param1 = 0.0, float param2 = 0.0);
	void vehicle_odometry_callback(const px4_msgs::msg::VehicleOdometry msg);
};

/**
 * @brief Send a command to Arm the vehicle
 */
void OffboardControl::arm()
{
	publish_vehicle_command(VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM, 1.0);

	RCLCPP_INFO(this->get_logger(), "Arm command send");
}

/**
 * @brief Send a command to Disarm the vehicle
 */
void OffboardControl::disarm()
{
	publish_vehicle_command(VehicleCommand::VEHICLE_CMD_COMPONENT_ARM_DISARM, 0.0);

	RCLCPP_INFO(this->get_logger(), "Disarm command send");
}

/**
 * @brief Publish the offboard control mode.
 *        For this example, only position and altitude controls are active.
 */
void OffboardControl::publish_offboard_control(std::string mode)
{
	// Output Variables
	OffboardControlMode msg_ocm{};
	TrajectorySetpoint msg_tsp{};

	// Mode Variables
	if (mode == "taxi") {
		msg_ocm.position = true;
		msg_ocm.actuator  = false;

		msg_tsp.position = {0.0, 0.0, -3.0};
	} else if (mode == "sfti") {
		msg_ocm.position = true;
		msg_ocm.actuator  = false;

		msg_tsp.position = {0.0, 0.0, -1.0};
	} else {
		msg_ocm.position = false;
		msg_ocm.actuator  = false;

		msg_tsp.position = {0.0, 0.0, 0.0};
	}

	// Mode Constants
	msg_ocm.velocity = false;
	msg_ocm.acceleration = false;
	msg_ocm.attitude = false;
	msg_ocm.body_rate = false;

	msg_tsp.yaw = 0.0; // [-PI:PI]

	msg_ocm.timestamp = msg_tsp.timestamp = this->get_clock()->now().nanoseconds() / 1000;

	// Publish
	trajectory_setpoint_publisher_->publish(msg_tsp);
	offboard_control_mode_publisher_->publish(msg_ocm);

}

/**
 * @brief Publish vehicle commands
 * @param command   Command code (matches VehicleCommand and MAVLink MAV_CMD codes)
 * @param param1    Command parameter 1
 * @param param2    Command parameter 2
 */
void OffboardControl::publish_vehicle_command(uint16_t command, float param1, float param2)
{
	VehicleCommand msg{};
	msg.param1 = param1;
	msg.param2 = param2;
	msg.command = command;
	msg.target_system = 1;
	msg.target_component = 1;
	msg.source_system = 1;
	msg.source_component = 1;
	msg.from_external = true;
	msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
	vehicle_command_publisher_->publish(msg);
}

int main(int argc, char *argv[])
{
	std::cout << "Starting offboard control node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<OffboardControl>());

	rclcpp::shutdown();
	return 0;
}

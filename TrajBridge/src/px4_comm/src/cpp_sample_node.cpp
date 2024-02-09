#include <px4_comm/cpp_sample_node.hpp>
#include <rclcpp/rclcpp.hpp>
#include <px4_msgs/msg/vehicle_odometry.hpp>

/**
 * @brief Intel node that updates a single variable using callbacks on various topics. This
 * variable can then be queried by the neural network at whatever rate of our choice.
 */
class Intel : public rclcpp::Node
{
public:
	explicit Intel() : Node("intel")
	{
		rmw_qos_profile_t qos_profile = rmw_qos_profile_sensor_data;
		auto qos = rclcpp::QoS(rclcpp::QoSInitialization(qos_profile.history, 5), qos_profile);
		
		subscription_ = this->create_subscription<px4_msgs::msg::VehicleOdometry>("/fmu/out/vehicle_odometry", qos,
		[this](const px4_msgs::msg::VehicleOdometry::UniquePtr msg) {
			std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
			std::cout << "RECEIVED SENSOR COMBINED DATA"   << std::endl;
			std::cout << "============================="   << std::endl;
			std::cout << "ts: "          << msg->timestamp    << std::endl;
			std::cout << "position[0]: " << msg->position[0]  << std::endl;
			std::cout << "position[1]: " << msg->position[1]  << std::endl;
			std::cout << "position[2]: " << msg->position[2]  << std::endl;
			std::cout << "velocity[0]: " << msg->position[0]  << std::endl;
			std::cout << "velocity[1]: " << msg->position[1]  << std::endl;
			std::cout << "velocity[2]: " << msg->velocity[2]  << std::endl;
			std::cout << "quaternion[0]: " << msg->q[0]  << std::endl;
			std::cout << "quaternion[1]: " << msg->q[1]  << std::endl;
			std::cout << "quaternion[2]: " << msg->q[2]  << std::endl;
			std::cout << "quaternion[3]: " << msg->q[2]  << std::endl;
			std::cout << "angular_velocity[0]: " << msg->angular_velocity[0]  << std::endl;
			std::cout << "angular_velocity[1]: " << msg->angular_velocity[1]  << std::endl;
			std::cout << "angular_velocity[2]: " << msg->angular_velocity[2]  << std::endl;
		});
	}

private:
	rclcpp::Subscription<px4_msgs::msg::VehicleOdometry>::SharedPtr subscription_;

};

int main(int argc, char *argv[])
{
	std::cout << "Starting intel node..." << std::endl;
	setvbuf(stdout, NULL, _IONBF, BUFSIZ);
	rclcpp::init(argc, argv);
	rclcpp::spin(std::make_shared<Intel>());

	rclcpp::shutdown();
	return 0;
}
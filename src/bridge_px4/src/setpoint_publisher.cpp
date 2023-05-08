#include <bridge_px4/setpoint_publisher.h>


class SetpointPublisher : public rclcpp::Node
{
public:
    SetpointPublisher() : Node("setpoint_publisher")
    {
		actuator_setpoint_publisher_ = this->create_publisher<ActuatorMotors>("/fmu/in/offboard_actuator_motors", 1);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(5),
            std::bind(&SetpointPublisher::publish_actuator_setpoint, this));
    }
private:
	rclcpp::Publisher<ActuatorMotors>::SharedPtr actuator_setpoint_publisher_;

	void publish_actuator_setpoint();

    rclcpp::TimerBase::SharedPtr timer_;
};

void SetpointPublisher::publish_actuator_setpoint()
{
	ActuatorMotors msg{};
	msg.control = {	0.1, 0.1, 0.1, 0.1,
					0.0, 0.0, 0.0, 0.0,
					0.0, 0.0, 0.0, 0.0};
	msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
	actuator_setpoint_publisher_->publish(msg);
}

int main(int argc, char **argv)
{
	std::cout << "Starting Setpoint Publisher Node." << std::endl;

  	rclcpp::init(argc, argv);
  	auto node = std::make_shared<SetpointPublisher>();
  	rclcpp::spin(node);
	rclcpp::shutdown();
	
	return 0;
}


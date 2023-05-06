#include <bridge_px4/setpoint_publisher.h>


class SetpointPublisher : public rclcpp::Node
{
public:
    SetpointPublisher() : Node("setpoint_publisher")
    {
		trajectory_setpoint_publisher_ = this->create_publisher<TrajectorySetpoint>("/fmu/in/test_in", 1);

        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(5),
            std::bind(&SetpointPublisher::publish_trajectory_setpoint, this));
    }
private:
	rclcpp::Publisher<TrajectorySetpoint>::SharedPtr trajectory_setpoint_publisher_;

	void publish_trajectory_setpoint();

    rclcpp::TimerBase::SharedPtr timer_;
};

void SetpointPublisher::publish_trajectory_setpoint()
{
	TrajectorySetpoint msg{};
	msg.position = {0.0, 0.0, -5.0};
	msg.yaw = -3.14; // [-PI:PI]
	msg.timestamp = this->get_clock()->now().nanoseconds() / 1000;
	trajectory_setpoint_publisher_->publish(msg);}

int main(int argc, char **argv)
{
	std::cout << "Starting Setpoint Publisher Node." << std::endl;

  rclcpp::init(argc, argv);
  auto node = std::make_shared<SetpointPublisher>();
  rclcpp::spin(node);
	rclcpp::shutdown();
	return 0;
}


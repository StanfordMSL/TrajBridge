#include <bridge_px4/setpoint_publisher.h>

SetpointPublisher::SetpointPublisher()
{
		timer_ = this->create_wall_timer(100ms, timer_callback);

    
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

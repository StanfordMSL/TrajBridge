#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

using namespace std;

class Teleop_IRoad
{
public:
  Teleop_IRoad();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Subscriber joy_sub_;
};


Teleop_IRoad::Teleop_IRoad():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);

  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &Teleop_IRoad::joyCallback, this);
  
}

void Teleop_IRoad::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];

  cout << twist.linear.x << endl;
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "Teleop_IRoad");
  Teleop_IRoad teleop_iRoad;

  ros::spin();
}
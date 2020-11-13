#include "ros/ros.h"
#include <bridge_px4/GcsCmd.h>
#include <cstdlib>

int main(int argc, char **argv)
{
  ros::init(argc, argv, "gcs_node");
  if (argc != 3)
  {
    ROS_INFO("usage: trigger a launch [mode] [trigger]");
    return 1;
  }

  ros::NodeHandle n;
  ros::ServiceClient client = n.serviceClient<bridge_px4::GcsCmd>("gcs_commander");
  bridge_px4::GcsCmd srv;
  srv.request.mode = atoll(argv[1]);
  srv.request.trigger = atoll(argv[2]);
  if (client.call(srv))
  {
    ROS_INFO("Triggered with Initial Position: %f, %f, %f",
     srv.response.pose_init[0],
     srv.response.pose_init[1],
     srv.response.pose_init[2]);
  }
  else
  {
    ROS_ERROR("Failed to call service gcs_commander");
    return 1;
  }

  return 0;
}
#! /bin/bash
### Add this to /etc/ros/ directory to be called every time the drone boots
export HOSTNAME
export ROS_HOSTNAME=$(hostname).local
export ROS_MASTER_URI=http://node2.local:11311
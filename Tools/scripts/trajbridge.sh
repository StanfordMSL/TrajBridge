#!/usr/bin/env bash
bash -c "export HOSTNAME && export ROS_HOSTNAME=drone5.local && export ROS_MASTER_URI=http://relay.local:11311/ && source /home/carl/StanfordMSL/Trajbridge/devel/setup.bash && roslaunch bridge_px4 drone.launch"

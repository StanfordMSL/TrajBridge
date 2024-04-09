# TrajBridge
TrajBridge is a package that bridges PX4 to ROS2 for easy testing of trajectory following algorithms within a motion capture environment. It is set up such that a user need only to package their controller and call it within TrajBridge. The package provides easily editable nodes that expose the drone state and allow the user to publish to key layers of the PX4 controller [position,velocity,vehicle attitude and actuator motors]. The package takes care of the rest through a tunable state machine. We provide an example controller packages to aid the user:
1) SimpleController: a simple package that converts a spline to desired Trajectory Setpoints

Check out the [wiki page](https://github.com/StanfordMSL/TrajBridge/wiki) to get started.

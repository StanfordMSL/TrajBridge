# TrajBridge
TrajBridge is a package that bridges PX4 to ROS2 for easy testing of trajectory following algorithms within a motion capture environment. It is set up such that a user need only to package their controller and call it within TrajBridge. The package provides easily editable nodes that expose the drone state and allow the user to publish to key layers of the PX4 controller [position,velocity,vehicle attitude and actuator motors]. The package takes care of the rest through a tunable state machine. We provide two example controller packages to aid the user:
1) SplineController: a simple package that converts a spline to desired Trajectory Setpoints
2) MLPController: given the current proclivity for learning based control, a controller that essentially exposes PX4 to Pytorch.

Check out the [wiki page](https://github.com/StanfordMSL/TrajBridge/wiki/Getting-Started) to get started.

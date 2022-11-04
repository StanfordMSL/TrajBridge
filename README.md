# TrajBridge
The goal of TrajBridge is to enable quick and safe testing of trajectory planning pipeliness and novel trajectory control policies on multirotor hardware. This is done through a set of ROS(1) nodes that interact with PX4 over mavros. There exists a bunch of excellent code bases out there that do something similiar in simulation. This repo differs from these by the following aspects:
1) Provides a step-by-step guide for an actual hardware implementation in the wiki.
2) Provides a comprehensive and easy to modify set of failsafe mechanisms for safe hardware implementation.
3) Enables access to the Synthesized Adaptive Controller (SAC), a neural-network based controller that is being designed to work across a variety of multirotor platforms that are also under additional dynamics (aerial grasping, tugging, perching)

The controllers in this repository has the following input->output structure:
1) Pose Commands -> Pose Commands
2) Pose Commands -> Normalized Thrust and Body Rate Commands
3) Full State Reference Trajectory -> Motor Comands

The controller is slaved to a state machine that checks for the following failsafes:
1) Motion Capture Stream -> Auto Land
2) L2-norm position error -> Auto Land
3) L2-norm velocity error -> Auto Land
4) Flight area bounding box -> Auto Land
5) Transmitter Soft Kill -> Auto Land
6) Transmitter Hard Kill -> Motor Cut

The goal of this code base is to provide a bridge between ROS(1) and PX4 with easy and robust access to low-level control for multiple robots.

# Key Objectives
* Have a Ground Control Station (GCS) that outputs a desired state (pose,twist) at 10Hz
* Have a Companion Computer that can switch between three different types of input into the flight controller (200Hz):
    * \[High Level (HiLe)\]: Pose,Twist 
    * \[Body Rates (BoRa)\]: Normalized Thrust + Body Rate 
    * \[Low Level (LoLe)\] Normalized Thrust + Torques
* Able to safely abort/land robots when algorithm fails or communication is compromised.
* A Setup that is able to seamlessly switch between simulation and actual experiments.

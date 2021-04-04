======================
Instructions for Tools
======================

This document contains some notes and instructions for using the Tools
directory. Tools include two main directories:

- **Drone**: Contains files that are directly representative of the drone's
  filesystem.
- **scripts**: Some random scripts that can be useful for interacting with the
  drones.

Installing the Drone files
==========================

The Drones directory contains several files needed to setup the drone when
powered on. These files contain system level services and some configurations
needed for the drone to run correctly. If there files under this directory have
been updated since you last used the drone or this is the first time setting up
the drone, you will need to run the following commands.

- `sudo visudo`
  - Add the line `carl ALL=(ALL) NOPASSWD: ALL` after the `%sudo ALL=(ALL:ALL) ALL
- `sudo rsync -rvulD ~/StanfordMSL/TrajBridge-PX4/Tools/Drone/* /.`
  - You can add `-n` to the end of this command to verify the copy.
- 'sudo systemctl daemon-reload`
- `sudo systemctl enable aether-1.service`
- `sudo systemctl enable aether-2.service`
- `sudo systemctl enable roslaunch_drone.service`
- `sudo 

What do these commands do?
--------------------------

The first updates the sudoer file to include "carl" as a sudoer without the need
of a password. This is needed for running some of the startup scripts.

This `rsync` command will copy all of the files under the "Drone" directory to
their appropriate locations on the drone's filesystem. This command will need to
be run anytime the files inside the Drone directory are updated.

The `systemctl` commands all interact with the operating system. Specifically,
reloading and enabling our scripts to run at startup. The `daemon-reload` needs
to be run anytime the service files have changed. The next three updates the
system to enable these service on startup. In other words, these service will
start as soon as the drone is booted, allowing our drone to start flying when
powered on.


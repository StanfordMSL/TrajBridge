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

The Drone directory contains several files needed to setup the drone when
powered on. These files contain system level services and some configurations
needed for the drone to run correctly. If the files under this directory have
been updated since you last used the drone or this is the first time setting up
the drone, you will need to run the following commands.

- :code:`sudo visudo`
  
  - Add the line :code:`carl ALL=(ALL) NOPASSWD: ALL` after the 
    :code:`%sudo ALL=(ALL:ALL) ALL`
  
- :code:`sudo rsync -rvulD ~/StanfordMSL/TrajBridge-PX4/Tools/Drone/* /.`

  - You can add :code:`-n` to the end of this command to verify the copy.

- :code:`sudo systemctl daemon-reload`
- :code:`sudo systemctl enable aether-1.service`
- :code:`sudo systemctl enable aether-2.service`
- :code:`sudo systemctl enable roslaunch_drone.service`
- :code:`sudo vim /etc/hosts`

  - Update the 'drone4' and 'drone4.local' to match the specific hostname of the
    drone. E.g. drone1 if you're updating these files on drone 1.

If you are updating a drone that already has these services from a previous
version of the code, you should run a `sudo systemctl restart service` on
each of the above services. If this is the first time, replace `restart` with
`start`.

To verify the services are running correctly, please run
:code:`sudo systemctl status service`. You should see a status of "success" if
things are running as expected.

.. note::
   
   You can also try running :code:`journalctl -u service -b` to look at the full
   log from the service. This will show you all logs from the specified service
   for your current boot.

After all of this has been updated, you should power cycle the drone. This can
be done by running :code:`sudo shutdown now`, then replacing the battery.

What do these commands do?
--------------------------

The first updates the sudoer file to include "carl" as a sudoer without the need
of a password. This is needed for running some of the startup scripts.

This :code:`rsync` command will copy all of the files under the "Drone"
directory to their appropriate locations on the drone's filesystem. This command
will need to be run anytime the files inside the Drone directory are updated.

The :code:`systemctl` commands all interact with the operating system.
Specifically, reloading and enabling our scripts to run at startup. The
:code:`daemon-reload` needs to be run anytime the service files have changed.
The next three update the system to enable these service on startup. In other
words, these service will start as soon as the drone is booted, allowing our
drone to start flying when powered on.

Other scripts
=============

Here we discuss the other scripts within our Tools/scripts directory in the
repository.

shutdown_drones.sh
------------------

This script will ssh into each drone and run the `sudo shutdown now` command.
This is a quick way to poweroff the drones without having to go into each drone
individually. It will inform you if the drone is unreachable and will let you
know if the drone has closed its connection (shutdown.)

restart_drone_services.sh
-------------------------

This is similar to the showdown script, in that it will ssh into each drone and
restart our roslaunch_drone script for each drone. This has generally been
needed when the VRPN client has been restarted on the ROS Core machine.
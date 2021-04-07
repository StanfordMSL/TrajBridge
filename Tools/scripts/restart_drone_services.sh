#!/bin/bash
for i in {1..6}
do
    if nc -z drone$i.local 22 -w 1 2>/dev/null; then
        echo -e "Restarting the roslaunch_drone.service for drone$i"
        ssh carl@drone$i.local 'sudo systemctl restart roslaunch_drone.service'
    else
        echo -e "drone$i is not reachable"
    fi
done
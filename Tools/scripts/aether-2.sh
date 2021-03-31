#!/bin/bash
while true
do
        while ! ping -c 1 -n -w 1 node2.local &> /dev/null
        do
                echo gw is not accessible
        done
        export ROS_HOSTNAME=$(hostname).local
        python /usr/local/bin/client.py
        sleep 1
done
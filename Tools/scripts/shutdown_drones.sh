#!/bin/bash
for i in {1..6}
do
    if nc -z drone$i.local 22 -w 1 2>/dev/null; then
        echo -e "Shutting down drone$i"
        ssh carl@drone$i.local 'sudo shutdown now'
    else
        echo -e "drone$i is not reachable"
    fi
done
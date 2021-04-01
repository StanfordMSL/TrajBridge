#/bin/bash
sudo service avahi-daemon stop
sudo systemctl disable avahi-daemon.service
sudo perl -p -i -e "s:127.0.0.53:10.67.128.12:g" /etc/resolv.conf
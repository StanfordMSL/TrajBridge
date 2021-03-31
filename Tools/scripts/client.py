import argparse, socket, os
from datetime import datetime

sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
print os.environ['ROS_HOSTNAME']
text = os.environ['ROS_HOSTNAME']
data = text.encode('ascii')
sock.sendto(data, ('node2.local', 58080))
print('The OS assigned me the address {}'.format(sock.getsockname()))
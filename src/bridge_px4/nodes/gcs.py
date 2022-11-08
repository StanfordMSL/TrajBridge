#!/usr/bin/env python3

# license removed for brevity
import rospy
import json
import numpy as np
from bridge_px4.srv import ActACMode
from geometry_msgs.msg import PoseStamped

### Configuration ===========================================

# Trajectory
file = "traj999.json"
# file = "traj_good.json"

# Time Step
dt = 0.5

### =========================================================

# Load Data
with open("../trajectories/"+file) as json_file:
    data = json.load(json_file)

# Process Data (into position)
P = np.zeros((3,0))
for datum in data["traj"]:
    x = np.array(datum)
    p = x[0:3].reshape((3,1))
    P = np.hstack((P,p))
N = P.shape[1]

# Generate Time Tracker
T = np.arange(0.0,N*dt,dt)

# Initialize ROS Node
pub = rospy.Publisher("drone1/setpoint/pose", PoseStamped, queue_size=1)
act_ac = rospy.ServiceProxy("drone1/act_ac_mode",ActACMode)

rospy.init_node('gcs_node', anonymous=True)
rate = rospy.Rate(50)

# Initialize ROS Variables
pose = PoseStamped()
pose.pose.orientation.w = 1.0
pose.pose.orientation.x = 0.0
pose.pose.orientation.y = 0.0
pose.pose.orientation.z = 0.0
pose.header.frame_id = "map"

# Wait a bit
rospy.sleep(1.0)

# Activate Autonomous mode
resp1 = act_ac(1)

# Initialize Counter Variables
t_start = rospy.Time.now()
k = 0
t_end = T[-1]+3.0

while True:
    # Generate and send waypoint
    t_now = rospy.Time.now()
    p_now = P[:,k]

    pose.header.stamp = t_now
    pose.header.seq = k
    pose.pose.position.x = p_now[0]
    pose.pose.position.y = p_now[1]
    pose.pose.position.z = p_now[2]
    pub.publish(pose)

    # Counter Updates
    tk = (t_now-t_start).to_sec()
    if ((tk > T[k]) and (k < N-1)):
        k+=1
    elif tk > t_end:
        break
    else:
        pass
    rate.sleep()
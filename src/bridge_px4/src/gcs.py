#!/usr/bin/env python3

import rospy
from typing import Tuple
import numpy as np
from geometry_msgs.msg import PointStamped
from geometry_msgs.msg import QuaternionStamped
import os 

class GCS:
    def __init__(self):
        # Input Params
        drone_id  = rospy.get_param("gcs/drone_id")
        traj_name = rospy.get_param("gcs/traj_name")
        laps = rospy.get_param("gcs/laps")

        # Trajectory Variables
        self.drone_id = drone_id
        self.T,self.X = self.traj_load(traj_name)
        self.dt = self.T[1]-self.T[0]
        self.N = self.T.shape[0]
        self.laps = laps

        self.k = 0
        self.lap = 0

        # Publishers
        self.pos_pub = rospy.Publisher(drone_id+"/setpoint/position",PointStamped,queue_size=1)
        self.att_pub = rospy.Publisher(drone_id+"/setpoint/attitude",QuaternionStamped,queue_size=1)

    def traj_load(self,traj_name) -> Tuple[np.ndarray,np.ndarray]:
        # Get Address of Trajectory
        dir_path = os.path.dirname(os.path.realpath(__file__))
        address = dir_path+"/../trajectories/"+traj_name
        data = np.genfromtxt(address,delimiter=',')
        
        # Extract Data
        T = data[0,:]
        X = data[1:14,:]
        print("Starting at:",X[0:3,0])

        return T,X
            
    def traj_out(self, event=None):
        # Unpack some stuff
        k = self.k
        t_now = rospy.Time.now()

        # Variables to publish
        pos_msg = PointStamped()
        att_msg = QuaternionStamped()

        # Position
        pos_msg.header.stamp = t_now
        pos_msg.header.seq = k
        pos_msg.header.frame_id = "map"

        pos_msg.point.x = self.X[0,k]
        pos_msg.point.y = self.X[1,k]
        pos_msg.point.z = self.X[2,k]

        # Attitude
        att_msg.header.stamp = t_now
        att_msg.header.seq = k
        att_msg.header.frame_id = "map"
        
        att_msg.quaternion.w = self.X[6,k]
        att_msg.quaternion.x = self.X[7,k]
        att_msg.quaternion.y = self.X[8,k]
        att_msg.quaternion.z = self.X[9,k]

        # Publish
        self.pos_pub.publish(pos_msg)
        self.att_pub.publish(att_msg)

        # Update Counter
        self.k += 1

        if self.k >= self.N:
            if self.lap <= self.laps:
                self.k = 0
                self.lap += 1
                print("Completed Lap:",self.lap,"of",self.laps)
            else:
                rospy.signal_shutdown("GCS Send Complete")

if __name__ == '__main__':
    rospy.init_node('gcs_node',disable_signals=True)
    gcs = GCS()

    rospy.Timer(rospy.Duration(gcs.dt), gcs.traj_out)
    rospy.spin()


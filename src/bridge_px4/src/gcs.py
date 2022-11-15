# #!/usr/bin/env python3

import rospy
import json
import numpy as np
from bridge_px4.srv import *
from geometry_msgs.msg import PoseStamped
import os 
from enum import Enum,auto

class mSP(Enum):    # Setpoint mode
    SP_POSE = 0
    SP_BORA = 1
    SP_ATOP = 2

class GCS:
    def __init__(self):
        # Input Params
        sp_mode = rospy.get_param("gcs/sp_mode")
        traj_name = rospy.get_param("gcs/traj_name")

        # Trajectory Variables
        self.sp_mode = sp_mode
        self.X,self.U,self.dt = self.traj_load(traj_name)
        self.check = sum(sum(self.X))+sum(sum(self.U))

        # ROS Variables
        self.sendXU_clt = rospy.ServiceProxy("drone1/sendXU",SendXU)

        # Send Trajectory
        res = self.traj_send()


    def traj_load(self,traj_name):
        # Get Address of Trajectory
        dir_path = os.path.dirname(os.path.realpath(__file__))
        address = dir_path+"/../trajectories/"+traj_name
        data = np.genfromtxt(address,delimiter=',')
        
        # Extract Data
        X = data[1:14,1:]
        U = data[14:18,1:]
        dt = data[0,2]-data[0,1]

        return X,U,dt
    
    def traj_send(self):
        req = SendXURequest()

        req.sp_mode = mSP[self.sp_mode].value
        req.xr,req.ur,req.dt = list(self.X.flatten('F')),list(self.U.flatten('F')),self.dt       
        req.check = self.check

        return self.sendXU_clt(req)

if __name__ == '__main__':
    rospy.init_node('gcs_node',disable_signals=True)
    GCS()
    rospy.signal_shutdown("GCS Send Complete")
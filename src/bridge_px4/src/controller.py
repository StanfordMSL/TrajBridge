# #!/usr/bin/env python3

import rospy
import json
import numpy as np
from bridge_px4.srv import *
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from mavros_msgs.msg import AttitudeTarget
from mavros_msgs.msg import ActuatorControl

import os 
from enum import Enum,auto

class mAC(Enum):    # Setpoint mode
    AC_INIT = 0
    AC_ON = 1
    AC_OFF = 2

class mSP(Enum):    # Setpoint mode
    SP_POSE = 0
    SP_BORA = 1
    SP_ATOP = 2

class Controller:
    def __init__(self):
        # Controller Mode
        self.ac_sp = mSP.SP_POSE
        self.state = 0
        self.kt   = 0
        self.ks   = 0

        # Variables
        self.Xk = np.zeros((13,))
        self.pose_sp = PoseStamped()
        self.bora_sp = AttitudeTarget()
        self.atop_sp = ActuatorControl()

        # Reference Trajectory
        self.Tr = np.zeros((1,0))
        self.Xr = np.zeros((13,0))
        self.Ur = np.zeros((4,0))
        
        # Actual Trajectory
        self.Ta = np.zeros((1,0))
        self.Xa = np.zeros((13,0))
        self.Ua = np.zeros((4,0))

        # ROS Variables
        self.pose_cr_sub = rospy.Subscriber("mavros/local_position/pose",PoseStamped,self.pose_cr_cb);
        self.vel_cr_sub = rospy.Subscriber("mavros/local_position/velocity",TwistStamped,self.vel_cr_cb);

        self.pose_pub = rospy.Publisher("setpoint/pose", PoseStamped, queue_size=1)
        self.bora_pub = rospy.Publisher("setpoint/bora", AttitudeTarget, queue_size=1)
        self.atop_pub = rospy.Publisher("setpoint/atop", ActuatorControl, queue_size=1)

        self.txtraj_service = rospy.Service("tx_traj",TxTraj,self.callback_tx_traj)
        self.act_ac = rospy.ServiceProxy("act_ac_mode",ActACMode)
        self.set_sp = rospy.ServiceProxy("set_sp_mode",SetSPMode)

    def pose_cr_cb(self,msg):
        self.Xk[0] = msg.pose.position.x
        self.Xk[1] = msg.pose.position.y
        self.Xk[2] = msg.pose.position.z
        self.Xk[6] = msg.pose.orientation.w
        self.Xk[7] = msg.pose.orientation.x
        self.Xk[8] = msg.pose.orientation.y
        self.Xk[9] = msg.pose.orientation.z

    def vel_cr_cb(self,msg):
        self.Xk[3] = msg.twist.linear.x
        self.Xk[4] = msg.twist.linear.y
        self.Xk[5] = msg.twist.linear.z
        self.Xk[10] = msg.twist.angular.x
        self.Xk[11] = msg.twist.angular.y
        self.Xk[12] = msg.twist.angular.z

    def callback_tx_traj(self,req):
        Xr = np.array(req.xr).reshape((13,-1),order='F')
        check = sum(sum(Xr))

        res = TxTrajResponse()
        if check == req.check:
            self.Xr = Xr
            self.dt = req.dt
            res = True

            self.N = Xr.shape[1]
            self.state = 1
            self.act_ac(mAC['AC_ON'].value)
            self.kt = 0
            self.ks = 0
        else:
            res = False

            self.flag = False

        return res

    def controller(self):
        tk = rospy.Time.now().to_sec()

        if ( (tk > self.Tr[self.kt]) and (self.kt < self.N-1) ):
            self.kt += 1
        elif self.kt >= self.N-1:
            ctl.flag = 0
        
        if self.ac_sp is mSP.SP_POSE:
            self.pose_con(self.Xr[:,self.kt])
        elif self.ac_sp is mSP.SP_BORA:
            self.bora_con()
        elif self.ac_sp is mSP.SP_ATOP:
            self.atop_con()

    def pose_con(self,X):
        self.pose_sp.header.stamp = rospy.Time.now()
        self.pose_sp.header.seq = self.ks
        self.pose_sp.header.frame_id = "map"

        self.pose_sp.pose.position.x = X[0]
        self.pose_sp.pose.position.y = X[1]
        self.pose_sp.pose.position.z = X[2]
        self.pose_sp.pose.orientation.w = X[6]
        self.pose_sp.pose.orientation.x = X[7]
        self.pose_sp.pose.orientation.y = X[8]
        self.pose_sp.pose.orientation.z = X[9]
        
        self.pose_pub.publish(self.pose_sp)
        self.ks += 1

    def bora_con(self,X):
        self.pose_sp.header.stamp = rospy.Time.now()
        self.pose_sp.header.seq = self.ks
        self.pose_sp.header.frame_id = "map"

        self.bora_sp.type_mask = self.bora_sp.IGNORE_ATTITUDE
        self.bora_sp.thrust = 0.5
        self.bora_sp.body_rate.x = 0.0
        self.bora_sp.body_rate.y = 0.0
        self.bora_sp.body_rate.z = 0.0

        self.bora_pub.publish(self.bora_sp)
        self.ks += 1

    def atop_con(self,X):
        print(X[0:3,self.k])

if __name__ == '__main__':
    rospy.init_node('controller_node')
    ctl = Controller()

    rate = rospy.Rate(100)

    while not rospy.is_shutdown():
        if ctl.state == 0:
            pass
        elif ctl.state == 1:
            ctl.pose_con(ctl.Xr[:,0])
            if np.linalg.norm(ctl.Xr[0:6,0]-ctl.Xk[0:6]) < 0.1:
                ctl.Tr = np.arange(0,ctl.N)*ctl.dt+rospy.Time.now().to_sec()
                ctl.state = 2
        elif ctl.state == 2:
            ctl.controller()

        rate.sleep()
# ### Configuration ===========================================

# # Trajectory
# file = "traj999.json"
# # file = "traj_good.json"

# # Time Step
# dt = 0.5

# # ### =========================================================

# # Load Data
# with open() as json_file:
#     data = json.load(json_file)

# # Process Data (into position)
# P = np.zeros((3,0))
# for datum in data["traj"]:
#     x = np.array(datum)
#     p = x[0:3].reshape((3,1))
#     P = np.hstack((P,p))
# N = P.shape[1]

# # Generate Time Tracker
# T = np.arange(0.0,N*dt,dt)

# # Initialize ROS Node
# pub = rospy.Publisher("drone1/setpoint/pose", PoseStamped, queue_size=1)
# act_ac = rospy.ServiceProxy("drone1/act_ac_mode",ActACMode)

# rospy.init_node('gcs_node', anonymous=True)
# rate = rospy.Rate(50)

# # Initialize ROS Variables
# pose = PoseStamped()
# pose.pose.orientation.w = 1.0
# pose.pose.orientation.x = 0.0
# pose.pose.orientation.y = 0.0
# pose.pose.orientation.z = 0.0
# pose.header.frame_id = "map"

# # Wait a bit
# rospy.sleep(1.0)

# # Activate Autonomous mode
# resp1 = act_ac(1)

# # Initialize Counter Variables
# t_start = rospy.Time.now()
# k = 0
# t_end = T[-1]+3.0

# while True:
#     # Generate and send waypoint
#     t_now = rospy.Time.now()
#     p_now = P[:,k]

#     pose.header.stamp = t_now
#     pose.header.seq = k
#     pose.pose.position.x = p_now[0]
#     pose.pose.position.y = p_now[1]
#     pose.pose.position.z = p_now[2]
#     pub.publish(pose)

#     # Counter Updates
#     tk = (t_now-t_start).to_sec()
#     if ((tk > T[k]) and (k < N-1)):
#         k+=1
#     elif tk > t_end:
#         break
#     else:
#         pass
#     rate.sleep()
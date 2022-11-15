#!/usr/bin/env python3

import rospy
import json
import numpy as np
from bridge_px4.srv import *
from geometry_msgs.msg import PoseStamped
from geometry_msgs.msg import TwistStamped
from mavros_msgs.msg import AttitudeTarget
from mavros_msgs.msg import ActuatorControl

import torch
import torch.nn.functional as F
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

class mCT(Enum):    # Controller mode
    CT_TAXI = 0
    CT_ON = 1
    CT_OFF = 2

class Controller:
    def __init__(self):
        # Controller Mode
        self.sp_mode  = mSP.SP_POSE

        self.ct_state = mCT.CT_OFF
        self.kt    = 0
        self.ks    = 0

        self.ac_flag  = False

        # DNN Policies
        self.Nhtr = 5
        self.Nhrz = 30
        # use_cuda = torch.cuda.is_available()
        use_cuda = False                    
        self.device = torch.device("cuda:0" if use_cuda else "cpu") 
        dir_path = os.path.dirname(os.path.realpath(__file__))
        add_polNN = dir_path+"/dnn/polNN_5htr30hrz_p1_1000eps.pth"

        self.polNN = torch.load(add_polNN,map_location=self.device)
        self.polNN.eval()

        # Constants
        self.uhov = np.array([0.5,0.0,0.0,0.0]).reshape((4,1))
        self.Nfr = 30

        # SP Variables
        self.pose_sp = PoseStamped()
        self.bora_sp = AttitudeTarget()
        self.atop_sp = ActuatorControl()

        # Reference Trajectory
        self.dt = 0.0
        self.Tr = np.zeros((1,self.Nfr))
        self.Xr = np.zeros((13,self.Nfr))
        self.Ur = np.zeros((4,self.Nfr))

        self.N = self.Nfr

        # Actual Trajectory
        self.xk = np.zeros((13))
        self.Uhtr = np.tile(self.uhov,(1,self.Nfr))
        self.Xhrz = np.zeros((4,self.Nfr))
        
        Nupol = 13+self.Nhtr*4+self.Nhrz*13
        self.upol = torch.zeros([Nupol],dtype=torch.float32)
        self.umot = self.polNN(self.upol).cpu().detach().numpy()
        self.uout = np.zeros((4))

        # ROS Variables
        self.pose_cr_sub = rospy.Subscriber("mavros/local_position/pose",PoseStamped,self.pose_cr_cb);
        self.vel_cr_sub = rospy.Subscriber("mavros/local_position/velocity",TwistStamped,self.vel_cr_cb);
        self.vel_cr_sub = rospy.Subscriber("mavros/local_position/velocity",TwistStamped,self.vel_cr_cb);

        self.pose_pub = rospy.Publisher("setpoint/pose", PoseStamped, queue_size=1)
        self.bora_pub = rospy.Publisher("setpoint/bora", AttitudeTarget, queue_size=1)
        self.atop_pub = rospy.Publisher("setpoint/atop", ActuatorControl, queue_size=1)

        self.sendXU_srv = rospy.Service("sendXU",SendXU,self.sendXU_cb)
        self.trigAC_clt = rospy.ServiceProxy("trigAC",TrigAC)

        # PX4 Secret Sauce
        sqnorm = lambda x: np.inner(x,x)        
        ct,km = 6.5,0.05
        lx,ly = 0.15,0.15

        G = np.array([  [-ly*ct, ly*ct, ly*ct,-ly*ct],
                        [-lx*ct, lx*ct,-lx*ct, lx*ct],
                        [ km*ct, km*ct,-km*ct,-km*ct],
                        [    ct,    ct,    ct,    ct]])
        E = np.linalg.pinv(G)
        C = np.zeros((4,4))
        C[0,0] = np.sqrt(sqnorm(E[:,0])/2)
        C[1,1] = np.sqrt(sqnorm(E[:,1])/2)
        C[2,2] = np.max(E[:,2])
        C[3,3] = sum(abs(E[:,3]))/4

        a = 0.7

        self.a,self.G,self.C = a,G,C

    def pose_cr_cb(self,msg):
        self.xk[0] = msg.pose.position.x
        self.xk[1] = msg.pose.position.y
        self.xk[2] = msg.pose.position.z
        self.xk[6] = -msg.pose.orientation.w
        self.xk[7] = -msg.pose.orientation.x
        self.xk[8] = -msg.pose.orientation.y
        self.xk[9] = -msg.pose.orientation.z

    def vel_cr_cb(self,msg):
        self.xk[3] = msg.twist.linear.x
        self.xk[4] = msg.twist.linear.y
        self.xk[5] = msg.twist.linear.z
        self.xk[10] = msg.twist.angular.x
        self.xk[11] = msg.twist.angular.y
        self.xk[12] = msg.twist.angular.z

    def sendXU_cb(self,req):
        Xr = np.array(req.xr).reshape((13,-1),order='F')
        Ur = np.array(req.ur).reshape((4,-1),order='F')
        check = sum(sum(Xr))+sum(sum(Ur))

        res = SendXUResponse()
        if check == req.check:
            self.sp_mode = mSP(req.sp_mode)
            self.dt = req.dt
            self.Xr = Xr
            self.Ur = Ur
            res = True

            self.N = Xr.shape[1]
            self.ct_state = mCT.CT_TAXI
            self.kt = 0
            self.ks = 0
            self.Uhtr = np.tile(self.uhov,(1,self.Nfr))
        else:
            res = False

            self.flag = False

        return res

    def state_machine(self,event=None):
        if self.ct_state == mCT.CT_OFF:
            pass
        elif self.ct_state == mCT.CT_TAXI:
            self.pose_con(self.Xr[:,0])

            if self.ac_flag == False:
                self.ac_flag = self.trigAC_clt(mAC['AC_ON'].value).success
            elif np.linalg.norm(self.Xr[0:6,0]-self.xk[0:6]) < 0.1:
                self.Tr = np.arange(0,self.N+1)*self.dt+rospy.Time.now().to_sec()
                self.ct_state = mCT.CT_ON
        elif self.ct_state == mCT.CT_ON:
            self.controller()
        
    def updater(self,event=None):
        kt = self.kt
        N = self.N
        Nfr = self.Nfr
        
        if self.ct_state == mCT.CT_ON:
            self.Uhtr = np.hstack((self.umot.reshape((4,1)),self.Uhtr[:,:-1]))
            
            if kt <= N-Nfr:
                self.Xhrz = self.Xr[:,kt:kt+Nfr]
            else:
                xrk = self.Xr[:,kt:]
                xrb = np.tile(self.Xr[:,-1].reshape((13,1)),(1,Nfr-N+kt))
                self.Xhrz = np.hstack((xrk,xrb))

            idx1 = 13 + (self.Nhtr*4)
            
            self.upol[0:13] = torch.from_numpy(self.xk)
            self.upol[13:idx1] = torch.from_numpy(self.Uhtr[:,0:self.Nhtr].flatten('F'))
            self.upol[idx1:] = torch.from_numpy(self.Xhrz[:,0:self.Nhrz].flatten('F'))
        # print(self.Uhtr[:,0])

    def controller(self):
        tk = rospy.Time.now().to_sec()

        if ( (tk > self.Tr[self.kt]) and (tk <= self.Tr[-1]) ):
            self.kt += 1
        elif (tk > self.Tr[-1]):
            self.ac_flag = self.trigAC_clt(mAC['AC_OFF'].value).success
            self.ct_state = mCT.CT_OFF
        
        if self.sp_mode is mSP.SP_POSE:
            self.pose_con(self.Xr[:,self.kt])
        elif self.sp_mode is mSP.SP_BORA:
            self.bora_con(self.Xr[:,self.kt])
        elif self.sp_mode is mSP.SP_ATOP:
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
        self.bora_sp.header.stamp = rospy.Time.now()
        self.bora_sp.header.seq = self.ks
        self.bora_sp.header.frame_id = "map"

        self.bora_sp.type_mask = self.bora_sp.IGNORE_ATTITUDE
        self.bora_sp.thrust = 0.5
        self.bora_sp.body_rate.x = 0.0
        self.bora_sp.body_rate.y = 0.0
        self.bora_sp.body_rate.z = 0.0

        self.bora_pub.publish(self.bora_sp)
        self.ks += 1

    def atop_con(self):
        # umo = self.Ur[:,self.kt]
        self.umot = self.polNN(self.upol).cpu().detach().numpy()

        uact = (self.a)*(self.umot**2)+(1-self.a)*self.umot 
        uact  = self.C@self.G@uact

        tk = rospy.Time.now().to_sec()
        print(tk,uact)

        # self.pose_sp.header.stamp = rospy.Time.now()
        # self.pose_sp.header.seq = self.ks
        # self.pose_sp.header.frame_id = "map"

        # X = self.Xhrz[:,0]
        # self.pose_sp.pose.position.x = X[0]
        # self.pose_sp.pose.position.y = X[1]
        # self.pose_sp.pose.position.z = X[2]
        # self.pose_sp.pose.orientation.w = X[6]
        # self.pose_sp.pose.orientation.x = X[7]
        # self.pose_sp.pose.orientation.y = X[8]
        # self.pose_sp.pose.orientation.z = X[9]

        # self.pose_pub.publish(self.pose_sp)
        # self.ks += 1

        self.atop_sp.header.stamp = rospy.Time.now()
        self.atop_sp.header.seq = self.ks
        self.atop_sp.header.frame_id = "map"
        self.atop_sp.group_mix = self.atop_sp.PX4_MIX_FLIGHT_CONTROL

        self.atop_sp.controls[0] = 0.1*uact[0]
        self.atop_sp.controls[1] = 0.1*uact[1]
        self.atop_sp.controls[2] = 0.1*uact[2]
        self.atop_sp.controls[3] = uact[3]

        self.atop_pub.publish(self.atop_sp)
        self.ks += 1

if __name__ == '__main__':
    rospy.init_node('controller_node')
    ctl = Controller()

    rospy.Timer(rospy.Duration(1.0/10.0), ctl.state_machine)
    rospy.Timer(rospy.Duration(1.0/10.0), ctl.updater)
    rospy.spin()

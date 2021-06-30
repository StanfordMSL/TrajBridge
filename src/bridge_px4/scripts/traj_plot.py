#!/usr/bin/env python

import matplotlib.pyplot as plt
import rospy
from geometry_msgs.msg import PoseStamped
import numpy as np
from matplotlib.animation import FuncAnimation

class plot_node():
    def __init__(self):       
        self.fig, self.ax = plt.subplots()
        self.ln = plt.plot([], [], 'ro')
        
        self.t_start = rospy.get_time()
        self.t_now = 0.0
        self.data_act = np.zeros(shape=(3,1))
        self.data_des = np.zeros(shape=(3,1))

        self.t_act = np.zeros(10)
        self.x_act = np.zeros(shape=(3,10))
        self.x_des = np.zeros((3,10))


        self.act_sub = rospy.Subscriber("/drone1/mavros/local_position/pose", PoseStamped, self.act_cb)
        self.des_sub = rospy.Subscriber("/drone1/gcs/setpoint/pose", PoseStamped, self.des_cb)
    
        self.timer = rospy.Timer(rospy.Duration(1), self.plot_update)

    def act_cb(self,data):
        self.t_now = rospy.get_time() - self.t_start
        self.data_act = np.array([[data.pose.position.x],[data.pose.position.y],[data.pose.position.z]])

    def des_cb(self,data):
        self.data_des = np.array([[data.pose.position.x],[data.pose.position.y],[data.pose.position.z]])

    def plot_update(self,timer):
        print(self.x_act[:,1:])
        print(self.data_act)

        self.t_act = np.concatenate((self.t_act[1:],[self.t_now]))
        self.x_act = np.hstack((self.x_act[:,1:],self.data_act))
        
 


if __name__ == '__main__':
    rospy.init_node('plot_node')

    try:
        plot_node()
        rospy.spin()
    except rospy.ROSInterruptException:
        pass
#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PointStamped
from geometry_msgs.msg import QuaternionStamped

from geometry_msgs.msg import Point
from geometry_msgs.msg import Quaternion
from std_msgs.msg import Header

from copy import deepcopy

class Rogue:
    def __init__(self):
        # Input Params
        self.drone_id = rospy.get_param("rogue/drone_targ")
        self.x_off = rospy.get_param("rogue/x_off")
        self.y_off = rospy.get_param("rogue/y_off")
        self.z_abs = rospy.get_param("rogue/z_abs")
        self.dt    = 1.0/rospy.get_param("rogue/hz")

        # Trajectory Variables
        self.attack = False
        self.kf = 0
        self.pos = Point()
        self.att = Quaternion()

        # Publishers
        self.pos_sub = rospy.Subscriber("/gcs/setpoint/position",PointStamped,self.pos_cb)
        self.att_sub = rospy.Subscriber("/gcs/setpoint/attitude",QuaternionStamped,self.att_cb)

        self.pos_pub = rospy.Publisher("/"+self.drone_id+"/setpoint/position",PointStamped,queue_size=1)
        self.att_pub = rospy.Publisher("/"+self.drone_id+"/setpoint/attitude",QuaternionStamped,queue_size=1)

    def pos_cb(self,msg:PointStamped):
        self.attack = True

        self.pos.x = msg.point.x + self.x_off
        self.pos.y = msg.point.y + self.y_off
        self.pos.z = self.z_abs

        # self.pos_pub.publish(msg)

    def att_cb(self,msg:QuaternionStamped):
        self.att = msg.quaternion
        # self.att_pub.publish(msg)
    
    def traj_out(self, event=None):
        # Unpack some stuff
        t_now = rospy.Time.now()

        # Header
        header = Header()
        header.stamp = t_now
        header.seq = self.kf
        header.frame_id = "map"

        pos_msg = PointStamped()
        att_msg = QuaternionStamped()

        pos_msg.header = header
        att_msg.header = header

        # Setpoints
        pos_msg.point = self.pos
        att_msg.quaternion = self.att

        # Publish
        if self.attack is True:
            self.pos_pub.publish(pos_msg)
            self.att_pub.publish(att_msg)

        # Update Counter
        self.kf += 1

if __name__ == '__main__':
    rospy.init_node('rogue_transform_node',disable_signals=True)
    rog = Rogue()

    rospy.Timer(rospy.Duration(rog.dt), rog.traj_out)
    rospy.spin()


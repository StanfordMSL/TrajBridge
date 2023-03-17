#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PointStamped
from geometry_msgs.msg import QuaternionStamped

from geometry_msgs.msg import Point
from copy import deepcopy

class SetpointTransform:
    def __init__(self):
        # Input Params
        self.drone_id = rospy.get_param("setpoint_transform/drone_id")
        self.x_off = rospy.get_param("setpoint_transform/x_off")
        self.y_off = rospy.get_param("setpoint_transform/y_off")
        self.z_off = rospy.get_param("setpoint_transform/z_off")

        # Trajectory Variables
        self.k = 0
        self.dt =  1.0/20.0
        self.point = Point()

        # Publishers
        self.pos_sub = rospy.Subscriber("/gcs/setpoint/position",PointStamped,self.pos_cb)
        self.att_sub = rospy.Subscriber("/gcs/setpoint/attitude",QuaternionStamped,self.att_cb)

        self.pos_pub = rospy.Publisher("/"+self.drone_id+"/setpoint/position",PointStamped,queue_size=1)
        self.att_pub = rospy.Publisher("/"+self.drone_id+"/setpoint/attitude",QuaternionStamped,queue_size=1)

    def pos_cb(self,msg:PointStamped):
        msg.point.x += self.x_off
        msg.point.y += self.y_off
        msg.point.z += self.z_off

        self.pos_pub.publish(msg)

    def att_cb(self,msg:QuaternionStamped):
        self.att_pub.publish(msg)
    
if __name__ == '__main__':
    rospy.init_node('setpoint_transform_node',disable_signals=True)
    st = SetpointTransform()

    rospy.spin()


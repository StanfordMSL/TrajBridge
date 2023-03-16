#!/usr/bin/env python3

import rospy
from geometry_msgs.msg import PointStamped
from geometry_msgs.msg import Point
from copy import deepcopy
class GCSRogue:
    def __init__(self):
        # Input Params
        drone_id  = rospy.get_param("gcs_rogue/drone_id")

        # Trajectory Variables
        self.k = 0
        self.drone_id = drone_id
        self.dt =  1.0/20.0
        self.point = Point()

        # Publishers
        self.pose_sub = rospy.Subscriber(drone_id+"/setpoint/position",PointStamped,self.pose_cb)
        self.pose_pub = rospy.Publisher(drone_id+"/setpoint/position",PointStamped,queue_size=1)

    def pose_cb(self,msg:PointStamped):
        self.point = msg.point
        self.point.z = 0.5

    def traj_out(self, event=None):
        t_now = rospy.Time.now()
        k = self.k

        pos_msg = PointStamped()

        pos_msg.header.stamp = t_now
        pos_msg.header.seq = k
        pos_msg.header.frame_id = "map"
        pos_msg.point = self.point
    
        self.pose_pub.publish(pos_msg)

if __name__ == '__main__':
    rospy.init_node('gcs_rogue_node',disable_signals=True)
    gcs = GCSRogue()
    rospy.Timer(rospy.Duration(gcs.dt), gcs.traj_out)

    rospy.spin()


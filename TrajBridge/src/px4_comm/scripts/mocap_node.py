#!/usr/bin/env python3

import numpy as np

import rclpy
from rclpy.node import Node
import rclpy.publisher
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
from functools import partial
from geometry_msgs.msg import (
    PoseStamped
)

from px4_msgs.msg import (
    VehicleOdometry,
)
import rclpy.subscription

class Mocap(Node):
    """Node for sending pose data from mocap to drone."""

    def __init__(self) -> None:
        super().__init__('mocap_node')

        # Configure QoS profile for publishing and subscribing
        self.qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Create timer that looks for vrpn_mocap topics
        self.searchLoop = self.create_timer(0.2, self.search_callback)
        self.assets = []
        self.subs = []
        self.pubs = []

    def search_callback(self) -> None:
        topic_list = self.get_topic_names_and_types()

        for topic in topic_list:
            text = topic[0].split('/')

            if text[1] == 'vrpn_mocap':
                if text[2] not in self.assets:
                    if len(self.assets) > 5:
                        # Limit to 5 mocap topics
                        print("Warning: More than 5 mocap topics found. Not adding more")
                    else:
                        # Add new mocap topic
                        self.assets.append(text[2])
                        print("Found mocap topic:", text[2])

                        # Create subscriber for new mocap topic
                        self.subs.append(
                            self.create_subscription(
                                PoseStamped,topic[0],
                                self.make_callback(len(self.assets)-1), 
                                self.qos_profile))
                        
                        # Create publisher for new mocap topic
                        self.pubs.append(
                            self.create_publisher(
                                VehicleOdometry,text[2]+"/in/vehicle_visual_odometry", 
                                self.qos_profile)
                        )

    def make_callback(self, idx:int):
        def vehicle_attitude_callback(msg:PoseStamped) -> None:
            vo = VehicleOdometry()

            vo.timestamp = int(self.get_clock().now().nanoseconds / 1000)
            vo.timestamp_sample = int(msg.header.stamp.sec * 1e6 + msg.header.stamp.nanosec / 1e3)
            
            vo.pose_frame = VehicleOdometry.POSE_FRAME_FRD
            vo.position = [ msg.pose.position.x,
                        -msg.pose.position.y,
                        -msg.pose.position.z]
            
            vo.q = [ msg.pose.orientation.w,
                    msg.pose.orientation.x,
                    -msg.pose.orientation.y,
                    -msg.pose.orientation.z]

            vo.velocity_frame = VehicleOdometry.VELOCITY_FRAME_UNKNOWN
            vo.velocity = np.array([None,None,None]).astype(np.float32)
            vo.angular_velocity = np.array([None,None,None]).astype(np.float32)

            self.pubs[idx].publish(vo)

        return vehicle_attitude_callback
    

def main(args=None) -> None:
    print('Starting mocap node...')
    rclpy.init(args=args)
    mocap = Mocap()
    rclpy.spin(mocap)
    mocap.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

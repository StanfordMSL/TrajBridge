#!/usr/bin/env python3

import numpy as np
from typing import List

import rclpy
from rclpy.node import Node
import rclpy.publisher
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy
from rclpy.subscription import Subscription
from rclpy.publisher import Publisher

from geometry_msgs.msg import (
    PoseStamped
)

from px4_msgs.msg import (
    VehicleOdometry,
)

class Mocap(Node):
    """Node for sending pose data from mocap to drone."""

    def __init__(self) -> None:
        super().__init__('mocap_node')

        # Required Parameters
        self.declare_parameter('asset_limit',rclpy.Parameter.Type.INTEGER)        
        self.declare_parameter('hz_topic_search',rclpy.Parameter.Type.DOUBLE)   

        N_as = self.get_parameter('asset_limit').value
        hz_ts = self.get_parameter('hz_topic_search').value

        # Configure QoS profile for publishing and subscribing
        self.qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Node variables
        self.N_as = N_as
        self.assets = []
        self.subs: List[Subscription]  = []
        self.pubs: List[Publisher] = []
        self.searchLoop = self.create_timer(hz_ts, self.topic_search_callback)

        # Print outs
        print("--------------------------------------------------------------------------")
        print("Mocap Node Parameters:")
        print("Asset Limit:", self.N_as)
        print("Topic Search Rate:", hz_ts)
        print("--------------------------------------------------------------------------")
        
    def topic_search_callback(self) -> None:
        """Search for mocap topics and if a new one is found, create a subscriber and publisher for it."""

        # Get list of all topics
        topic_list = self.get_topic_names_and_types()

        # Search for mocap topics
        for topic in topic_list:
            text = topic[0].split('/')

            # Check if topic is from mocap
            if text[1] == 'vrpn_mocap':
                # Check if mocap topic is already being used
                if text[2] not in self.assets:
                    # Limit to N_as mocap topics
                    if len(self.assets) > self.N_as:
                        print("Warning: More than ", self.N_as, " mocap topics found. Ignoring additional topics.")
                        print("--------------------------------------------------------------------------")
                    else:
                        # Add new mocap topic
                        self.assets.append(text[2])
                        print("Found Mocap Topic:", text[2])
                        print("Current MoCap Topics:", self.assets)
                        print("--------------------------------------------------------------------------")
                        
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
        """Create a callback function for a specific mocap topic."""

        # Callback function template for mocap topic
        def vehicle_attitude_callback(msg:PoseStamped) -> None:
            vo = VehicleOdometry()

            # Set timestamp using current ROS time and message time
            vo.timestamp = int(self.get_clock().now().nanoseconds / 1000)
            vo.timestamp_sample = int(msg.header.stamp.sec * 1e6 + msg.header.stamp.nanosec / 1e3)
            
            # Set mocap pose data (FLU to FRD conversion)
            vo.pose_frame = VehicleOdometry.POSE_FRAME_FRD
            vo.position = [ 
                 msg.pose.position.x,
                -msg.pose.position.y,
                -msg.pose.position.z
                ]
            
            vo.q = [
                 msg.pose.orientation.w,
                 msg.pose.orientation.x,
                -msg.pose.orientation.y,
                -msg.pose.orientation.z
                ]

            # Blank out velocity data
            vo.velocity_frame = VehicleOdometry.VELOCITY_FRAME_UNKNOWN
            vo.velocity = np.array([None,None,None]).astype(np.float32)
            vo.angular_velocity = np.array([None,None,None]).astype(np.float32)

            # Publish message
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

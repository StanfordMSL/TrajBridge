#!/usr/bin/env python3

import numpy as np

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from geometry_msgs.msg import (
    PoseStamped
)

from px4_msgs.msg import (
    VehicleOdometry,
)

class Mocap(Node):
    """Node for controlling a vehicle using an SFTI pilot."""

    def __init__(self) -> None:
        super().__init__('state_machine_node')

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.VOLATILE,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Create subscribers
        self.mocap_pose_subscriber = self.create_subscription(
            PoseStamped, '/vrpn_mocap/fmu/pose', self.vehicle_attitude_callback, qos_profile)
        self.vision_pose_publisher = self.create_publisher(
            VehicleOdometry,'/fmu/in/vehicle_visual_odometry', qos_profile)
        
    def vehicle_attitude_callback(self, msg:PoseStamped) -> None:
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

        self.vision_pose_publisher.publish(vo)

def main(args=None) -> None:
    print('Starting state_machine node...')
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

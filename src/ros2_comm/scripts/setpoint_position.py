#!/usr/bin/env python3

import numpy as np

import synthesize.generate_data as gd
import synthesize.trajectory_helper as th


import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    TrajectorySetpoint,
)

class SetpointPosition(Node):
    """Node for publishing setpoints."""

    def __init__(self) -> None:
        super().__init__('setpoint_node')

        # Required Parameters
        self.declare_parameter('mission_name','tutorial')        

        # Optional Parameters
        self.declare_parameter('control_frequency',200)

        # Get Parameters
        ms_name = self.get_parameter('mission_name').value
        hz_ctl = self.get_parameter('control_frequency').value

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Some Useful Intermediate Variables
        tf,CPs,_ = gd.generate_control_points(ms_name,rng_seed=1)                                                      # Load Mission
        CP = CPs[0]
        print(CP)
        fo_0 = th.ts_to_fo(0,tf,CP)

        # Class Variables
        self.tf,self.CP = tf,CP
        self.ts_ds = TrajectorySetpoint(
            position=fo_0[0:3,0],
            velocity=fo_0[0:3,1],
            acceleration=fo_0[0:3,2],
            jerk=fo_0[0:3,3],
            yaw=fo_0[3,0],
            yawspeed=fo_0[3,1]
        )

        # Create publishers
        self.trajectory_setpoint_publisher = self.create_publisher(
            TrajectorySetpoint, '/setpoint_control/position_with_ff', qos_profile)
        
        # Create a timer to publish control commands
        self.cmdLoop = self.create_timer(1/hz_ctl, self.cmd_callback)

        # Start the start time
        self.t0 = self.get_clock().now().nanoseconds / 1e9


    def cmd_callback(self) -> None:
        # Looping Callback Actions
        tk = self.get_clock().now().nanoseconds / 1e9

        fo = th.ts_to_fo(tk-self.t0,self.tf,self.CP)

        self.ts_ds.position = fo[0:3,0].astype(np.float32)
        self.ts_ds.velocity = fo[0:3,1].astype(np.float32)
        self.ts_ds.acceleration = fo[0:3,2].astype(np.float32)
        self.ts_ds.jerk = fo[0:3,3].astype(np.float32)
        self.ts_ds.yaw = float(fo[3,0])
        self.ts_ds.yawspeed = float(fo[3,1])

        tf_hn = self.tf-(tk-self.t0)

        self.ts_ds.timestamp = int(self.get_clock().now().nanoseconds / 1000)

        self.trajectory_setpoint_publisher.publish(self.ts_ds)

        if tf_hn <= 0:
            print('Finished mission.')
            exit(0)

def main(args=None) -> None:
    print('Starting setpoint node...')
    rclpy.init(args=args)
    setpoint_position = SetpointPosition()
    rclpy.spin(setpoint_position)
    setpoint_position.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

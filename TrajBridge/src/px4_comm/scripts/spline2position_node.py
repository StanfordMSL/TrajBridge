#!/usr/bin/env python3

import numpy as np
import json
import os

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    TrajectorySetpoint
)

import generate_min_snap as gms
import trajectory_helper as th

class Spline2Position(Node):
    """Node for generating position (with feed-forward) commands from spline."""

    def __init__(self) -> None:
        super().__init__('spline2position_node')
        
        # Optional Parameters
        self.declare_parameter('control_frequency',200)
        
        # Get Parameters
        hz_ctl = self.get_parameter('control_frequency').value
        
        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        trajectory_name = "line"

        # Unpack trajectories
        trajectories_path = os.path.join(os.path.dirname(os.path.dirname(gms.__file__)), "trajectories")       
        trajectory_path   = os.path.join(trajectories_path,trajectory_name+".json")    

        with open(trajectory_path) as json_file:
            config = json.load(json_file)

        tf = config["flight_time"]
        fo0 = np.array(config["flat_outputs"]["initial"])
        f01 = np.array(config["flat_outputs"]["final"])

        # Some Useful Intermediate Variables
        self.tf = tf
        self.CP = gms.solve_min_snap(tf,fo0,f01)

        self.pos_sp = TrajectorySetpoint()                              # position with ff setpoint command

        # Create subscribers
        self.sp_position_with_ff_publisher = self.create_publisher(
            TrajectorySetpoint,'/setpoint_control/position_with_ff', qos_profile)

        # Create a timer to publish control commands
        self.cmdLoop = self.create_timer(1/hz_ctl, self.controller)

        # Current Time
        self.t0 = self.get_clock().now().nanoseconds / 1e9

    def controller(self) -> None:
        tk = self.get_clock().now().nanoseconds / 1e9 - self.t0

        if tk <= self.tf:
            fo = th.ts_to_fo(tk,self.tf,self.CP)
            
            self.pos_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

            self.pos_sp.position = fo[0:3,0].astype(np.float32)
            self.pos_sp.velocity = fo[0:3,1].astype(np.float32)
            self.pos_sp.acceleration = fo[0:3,2].astype(np.float32)
            self.pos_sp.jerk = fo[0:3,3].astype(np.float32)

            self.pos_sp.yaw = float(fo[3,0])
            self.pos_sp.yawspeed = float(fo[3,1])

            self.sp_position_with_ff_publisher.publish(self.pos_sp)
        else:
            exit()

def main(args=None) -> None:
    print('Starting spline2position node...')
    rclpy.init(args=args)
    controller = Spline2Position()
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

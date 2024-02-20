#!/usr/bin/env python3

import sys
import numpy as np

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    TrajectorySetpoint
)

import generate_min_snap as gms
import trajectory_helper as th

class Spline2Velocity(Node):
    """Node for generating velocity (with feed-forward) commands from spline."""

    def __init__(self,trajectory_name:str,control_frequency:int=200) -> None:
        super().__init__('spline2velocity_node')

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Unpack trajectories
        output = gms.solve_min_snap(trajectory_name)
        if output is not False:
            Tkf, CP = output
        else:
            raise ValueError("Trajectory not feasible. Aborting.")

        # Initialize class variables
        self.Tkf,self.CP = Tkf,CP
        self.ksm,self.Nsm = 0, len(Tkf)-1
        self.vel_sp = TrajectorySetpoint()                              # velocity with ff setpoint command

        # Create subscribers
        self.sp_velocity_with_ff_publisher = self.create_publisher(
            TrajectorySetpoint,'/setpoint_control/velocity_with_ff', qos_profile)

        # Create a timer to publish control commands
        self.cmdLoop = self.create_timer(1/control_frequency, self.controller)

        # Current Time
        self.t0 = self.get_clock().now().nanoseconds / 1e9

        print('=========================================')
        print('Trajectory Name:',trajectory_name)
        print('Control Frequency:',control_frequency)
        print('=========================================')
        print('Trajectory Started.')
        
    def controller(self) -> None:
        tk = self.get_clock().now().nanoseconds / 1e9 - self.t0

        if tk <= self.Tkf[-1]:
            if tk > self.Tkf[self.ksm+1]:
                self.ksm += 1

            tf_sm = self.Tkf[self.ksm+1]-self.Tkf[self.ksm]
            tk_sm = tk-self.Tkf[self.ksm]
            CP_sm = self.CP[self.ksm,:,:]
            fo = th.ts_to_fo(tk_sm,tf_sm,CP_sm)
            
            self.vel_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

            self.vel_sp.position = np.array([None,None,None]).astype(np.float32)
            self.vel_sp.velocity = fo[0:3,1].astype(np.float32)
            self.vel_sp.acceleration = fo[0:3,2].astype(np.float32)
            self.vel_sp.jerk = fo[0:3,3].astype(np.float32)

            self.vel_sp.yaw = float(fo[3,0])
            self.vel_sp.yawspeed = float(fo[3,1])

            self.sp_velocity_with_ff_publisher.publish(self.vel_sp)
        else:
            print('Trajectory Finished.')
            print('=========================================')
            exit()

def main(args) -> None:
    print('Starting spline2velocity node...')
    if len(args) == 0:
        print('No arguments provided.')
        print('Using default trajectory (line) and control frequency (200hz).')
        trajectory_name = 'line'
        control_frequency = 200
    elif len(args) == 1:
        print('No frequency provided.')
        print('Using default control frequency (200hz).')
        trajectory_name = args[0]
        control_frequency = 200
    elif len(args) == 2:
        trajectory_name = args[0]
        control_frequency = int(args[1])
    else:
        raise ValueError('Invalid number of arguments.')
    
    rclpy.init()
    controller = Spline2Velocity(trajectory_name,control_frequency)
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main(sys.argv[1:])
    except Exception as e:
        print(e)


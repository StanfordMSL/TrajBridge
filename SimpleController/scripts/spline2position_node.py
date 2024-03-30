#!/usr/bin/env python3

import sys
import numpy as np
import json
import os
import argparse
from tabulate import tabulate

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    VehicleOdometry,
    TrajectorySetpoint
)

import min_snap as ms
import trajectory_helper as th
import plot_trajectory as pt

class Spline2Position(Node):
    """Node for generating position (with feed-forward) commands from spline."""

    def __init__(self,trajectory_name:str,control_frequency:int=200) -> None:
        super().__init__('spline2position_node')

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Generate some useful paths
        workspace_path = os.path.dirname(os.path.dirname(__file__))
        trajectory_path = os.path.join(workspace_path,"trajectories",trajectory_name+".json")

        # Load Configs
        with open(trajectory_path) as json_file:
            course_config = json.load(json_file)

        # Unpack trajectories
        Tpi,CPi = ms.solve(course_config)
        
        # Initialize class variables
        N = int(Tpi[-1]*control_frequency) + 100

        self.Tp,self.CP = Tpi,CPi
        self.ksm,self.Nsm = 0, len(Tpi)-1
        self.pos_sp = TrajectorySetpoint()                              # position with ff setpoint command
        
        self.vo_cr = VehicleOdometry()                                  # current vehicle odometry
        self.tXi = np.zeros((14,N))                                     # ideal trajectory
        self.tXa = np.zeros((14,N))                                    # actual trajectory
        self.k = 0                                                       # trajectory index

        # Create publishers
        self.sp_position_with_ff_publisher = self.create_publisher(
            TrajectorySetpoint,'/setpoint_control/position_with_ff', qos_profile)

        # Create subscribers
        self.vehicle_odometry_subscriber = self.create_subscription(
            VehicleOdometry, '/fmu/out/vehicle_odometry', self.vehicle_odometry_callback, qos_profile)
        
        # Create a timer to publish control commands
        self.cmdLoop = self.create_timer(1/control_frequency, self.controller)

        # Diagnostics
        table = []
        for idx,item in enumerate(course_config.values()):
            FOkf = np.array(item['fo'],dtype=float)
            data = np.hstack((self.Tp[idx],FOkf[:,0]))
            table.append(data)

        print('================================================')
        print('Trajectory Name:',trajectory_name)
        print('Control Frequency:',control_frequency)
        print('================================================')

        print('Trajectory Information:')
        print('Number of Segments:',self.Nsm)
        print('Trajectory Duration:',self.Tp[-1],'s')
        print('------------------------------------------------')
        print('Keyframes:')
        print(tabulate(table, headers=["Time","x (m)", "y (m)", "z (m)", "yaw (rad)"]))
        print('------------------------------------------------')
        print('================================================')

        pt.CP_to_3D([self.Tp],[self.CP],n=50)
        input("Press Enter to start trajectory...")
    
        print('================================================')

        print('Trajectory Started.')
        print('In Segment:',self.ksm+1,'/',self.Nsm)

        # Current Time
        self.t0 = self.get_clock().now().nanoseconds / 1e9

    def vehicle_odometry_callback(self, vehicle_odometry:VehicleOdometry):
        """Callback function for vehicle_odometry topic subscriber."""
        self.vo_cr = vehicle_odometry

    def controller(self) -> None:
        tk = self.get_clock().now().nanoseconds / 1e9 - self.t0

        if tk <= self.Tp[-1]:
            # Check if we are in a new segment
            if tk > self.Tp[self.ksm+1]:
                self.ksm += 1
                print('In Segment:',self.ksm+1,'/',self.Nsm)

            # Compute the feed-forward trajectory
            tf_sm = self.Tp[self.ksm+1]-self.Tp[self.ksm]
            tk_sm = tk-self.Tp[self.ksm]
            CP_sm = self.CP[self.ksm,:,:]
            fo = th.ts_to_fo(tk_sm,tf_sm,CP_sm)
            
            # Publish the feed-forward trajectory
            self.pos_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

            self.pos_sp.position = fo[0:3,0].astype(np.float32)
            self.pos_sp.velocity = fo[0:3,1].astype(np.float32)
            self.pos_sp.acceleration = fo[0:3,2].astype(np.float32)
            self.pos_sp.jerk = fo[0:3,3].astype(np.float32)

            self.pos_sp.yaw = float(fo[3,0])
            self.pos_sp.yawspeed = float(fo[3,1])

            self.sp_position_with_ff_publisher.publish(self.pos_sp)

            # Logging
            xi_cr = th.fo_to_xu(fo)[0:13]
            xa_cr = np.hstack((self.vo_cr.position,self.vo_cr.velocity,self.vo_cr.q,self.vo_cr.angular_velocity))

            xi_cr[6:10] += np.array([1e-6,0,0,0])
            xa_cr[6:10] += np.array([1e-6,0,0,0])
            xi_cr[6:10] = xi_cr[6:10] / np.linalg.norm(xi_cr[6:10])
            xa_cr[6:10] = xa_cr[6:10] / np.linalg.norm(xa_cr[6:10])

            self.tXi[0,self.k] = self.tXa[0,self.k] = tk
            self.tXi[1:,self.k] = xi_cr
            self.tXa[1:,self.k] = xa_cr
            self.k += 1

        else:
            print('Trajectory Finished.')
            print('=========================================')
            
            # Trim the trajectories
            self.tXa = self.tXa[:,0:self.k]
            self.tXi = self.tXi[:,0:self.k]

            # Plot the trajectories
            pt.tXU_to_3D([self.tXi,self.tXa])

            exit()

def main() -> None:
    print('Starting spline2position node...')

    # Create ArgumentParser object
    parser = argparse.ArgumentParser(description="Spline2Position Node.")

    # Add arguments
    parser.add_argument('--traj', type=str, help='Trajectory Name')
    parser.add_argument('--freq', type=int, help='Control Frequency', default=200)

    # Parse the command line arguments
    args = parser.parse_args()
    
    rclpy.init()
    controller = Spline2Position(args.traj,args.freq)
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)
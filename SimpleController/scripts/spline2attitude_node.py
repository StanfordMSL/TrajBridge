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
from geometry_msgs.msg import (
    Wrench
)

import min_snap as ms
import trajectory_helper as th
import plot_trajectory as pt

class Spline2Position(Node):
    """Node for generating position (with feed-forward) commands from spline."""

    def __init__(self,trajectory_name:str,drone_name:str,Fdes:float,control_frequency:int) -> None:
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
        
        # Some useful intermediate variables
        dr_pf = '/'+drone_name if drone_name != 'fmu' else ''
        N = int(Tpi[-1]*control_frequency) + 100

        # Initialize class variables
        self.node_start = False                                 # Node start flag
        self.node_status_informed = False                       # Node status informed flag
        self.Tp,self.CP = Tpi,CPi
        self.ksm,self.Nsm = 0, len(Tpi)-1
        self.pos_sp = TrajectorySetpoint()                              # position with ff setpoint command
        
        self.vo_cr = VehicleOdometry()                                  # current vehicle odometry
        self.tXi = np.zeros((14,N))                                     # ideal trajectory
        self.tXa = np.zeros((14,N))                                    # actual trajectory
        self.k = 0                                                       # trajectory index
        self.t0 = None
        self.tf = Tpi[-1]

        # FT Reading Stuff
        self.Fdes = Fdes
        self.pdes = np.array([0.0,0.0,0.0],dtype=np.float32)
        self.Kp = 0.350
        self.Ki = 0.000
        self.Kd = 0.100
        self.Tst = 5.0
        self.alpha = 0.0
        self.prev_error = 0.0
        self.integral = 0.0
        self.lim_int = 0.1
        self.ft_state = False
        self.ft_reading = Wrench()

        # Create publishers
        self.sp_position_with_ff_publisher = self.create_publisher(
            TrajectorySetpoint,dr_pf+'/fmu/setpoint_control/position_with_ff', qos_profile)

        # Create subscribers
        self.vehicle_odometry_subscriber = self.create_subscription(
            VehicleOdometry, dr_pf+'/fmu/out/vehicle_odometry', self.vehicle_odometry_callback, qos_profile)
        self.ft_reading_subscriber = self.create_subscription(
            Wrench, '/FTReading', self.ft_reading_callback, 10)

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
        print("Drone Name:",drone_name)
        print('Control Frequency:',control_frequency)
        print('================================================')

        print('Trajectory Information:')
        print('Desired Force in Z :',self.Fdes)
        print('PID Gains:',self.Kp,self.Ki,self.Kd)
        print('alpha val:',self.alpha)
        print('Step Time:',self.Tst)
        print('Number of Segments :',self.Nsm)
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

    def vehicle_odometry_callback(self, vehicle_odometry:VehicleOdometry):
        """Callback function for vehicle_odometry topic subscriber."""
        self.vo_cr = vehicle_odometry

    def ft_reading_callback(self, ft_reading:Wrench):
        """Callback function for ft_reading topic subscriber."""

        self.ft_reading = ft_reading

    def node_check(self) -> bool:
        """Check if node is ready to start. We are waiting for state and control input messages."""

        if self.node_start == False:
            if self.node_status_informed == False:
                print('---------------------------------------------------------------------')
                print('Node is not ready. Waiting for state and control input messages.')

                self.node_status_informed = True 
            
            if self.vo_cr.timestamp <= 0:
                return False
            else:
                self.node_start = True
                self.t0 = self.get_clock().now().nanoseconds / 1e9
                self.node_status_informed = False
                return False
            
        else:
            if self.node_status_informed == False:
                print('---------------------------------------------------------------------')
                print('Node is ready. Starting trajectory.')
                print('---------------------------------------------------------------------')
                print('=====================================================================')
                print('Trajectory Started.')
                print('In Segment:',self.ksm+1,'/',self.Nsm)

                self.node_status_informed = True 

            return True
        
    def controller(self) -> None:
        if self.node_check():
            tk = self.get_clock().now().nanoseconds / 1e9 - self.t0

            if tk <= self.tf:
                # Check if we are in a new segment
                if tk > self.Tp[self.ksm+1]:
                    self.ksm += 1
                    print('In Segment:',self.ksm+1,'/',self.Nsm)

                # Compute the feed-forward trajectory
                tf_sm = self.Tp[self.ksm+1]-self.Tp[self.ksm]
                tk_sm = tk-self.Tp[self.ksm]
                CP_sm = self.CP[self.ksm,:,:]
                fo = th.ts_to_fo(tk_sm,tf_sm,CP_sm).astype(np.float32)
                
                # Publish the feed-forward trajectory
                self.pos_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

                # =============================================================
                # Simple FT Feedback ==========================================

                # Simple State Machine
                if self.ft_state == False:
                    # Carry on with the trajectory
                    self.pos_sp.position = fo[0:3,0]
                    self.pos_sp.velocity = fo[0:3,1]
                    self.pos_sp.acceleration = fo[0:3,2]
                    self.pos_sp.jerk = fo[0:3,3]
                    self.pos_sp.yaw = float(fo[3,0])
                    self.pos_sp.yawspeed = float(fo[3,1])

                    # Check if the force is greater than the threshold
                    if self.ft_reading.force.z > self.Fdes:
                        self.ft_state = True
                        self.pdes = self.alpha*self.vo_cr.position + (1.0-self.alpha)*fo[0:3,0]
                        self.tf = tk + self.Tst
                        print("Locking Position at:",self.pdes)
                    else:
                        pass
                elif self.ft_state == True:
                    # Lock the setpoint
                    v0,s0 = np.array([0.0,0.0,0.0],dtype=np.float32),float(0.0)

                    self.pos_sp.position[0:2]= self.pdes[0:2]
                    self.pos_sp.velocity = self.pos_sp.acceleration = self.pos_sp.jerk = v0
                    self.pos_sp.yaw = self.pos_sp.yawspeed = s0

                    # PID controller on z     
                    error = (self.Fdes-self.ft_reading.force.z)
                    self.integral += error
                    output = -self.Kp*error - self.Ki*self.integral - self.Kd*(error-self.prev_error)
                    
                    output = np.clip(output,-0.3, 0.3)

                    self.prev_error = error
                    self.integral = np.clip(self.integral,-self.lim_int,self.lim_int)

                    self.pos_sp.position[2] = self.pdes[2] + output


                # =============================================================
                # =============================================================

                self.sp_position_with_ff_publisher.publish(self.pos_sp)

                # Logging
                xi_cr = th.fo_to_xu(fo)[0:13]
                xa_cr = np.hstack((self.vo_cr.position,
                                   self.vo_cr.velocity,
                                   self.vo_cr.q[1:4],
                                   self.vo_cr.q[0],
                                   self.vo_cr.angular_velocity))

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
                self.tXa = self.tXa[:,10:self.k]
                self.tXi = self.tXi[:,10:self.k]
                # Plot the trajectories
                pt.tXU_to_3D([self.tXi,self.tXa])

                exit()
        else:
            pass

def main() -> None:
    print('Starting spline2position node...')

    # Create ArgumentParser object
    parser = argparse.ArgumentParser(description="Spline2Position Node.")

    # Add arguments
    parser.add_argument('--traj', type=str, help='Trajectory Name')
    parser.add_argument('--drone', type=str, help='Drone Name')
    parser.add_argument('--Fdes', type=float, help='Desired Force', default=1.0)
    parser.add_argument('--freq', type=int, help='Control Frequency', default=200)

    # Parse the command line arguments
    args = parser.parse_args()
    
    rclpy.init()
    controller = Spline2Position(args.traj,args.drone,args.Fdes,args.freq)
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

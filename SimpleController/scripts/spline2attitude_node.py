#!/usr/bin/env python3

import sys
import numpy as np
import json
import os
import argparse
from tabulate import tabulate
from scipy.spatial.transform import Rotation as R

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    VehicleOdometry,
    VehicleAttitudeSetpoint
)
from geometry_msgs.msg import (
    Wrench
)

import min_snap as ms
import trajectory_helper as th
import plot_trajectory as pt

class Spline2Attitude(Node):
    """Node for generating attitude commands from spline."""

    def __init__(self,trajectory_name:str,drone_name:str,Fdes:float,control_frequency:int) -> None:
        super().__init__('spline2attitude_node')

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
        self.att_sp = VehicleAttitudeSetpoint()                 # attitude setpoint command
        
        self.vo_cr = VehicleOdometry()                          # current vehicle odometry
        self.tXi = np.zeros((14,N))                             # ideal trajectory
        self.tXa = np.zeros((14,N))                             # actual trajectory
        self.k = 0                                              # trajectory index
        self.t0 = None
        self.tf = Tpi[-1]

        # FT Reading Stuff
        self.Kp = np.diag([3.0,3.0,5.0])
        self.Kv = np.diag([3.0,3.0,3.0])
        self.tn = 4.0*6.90
        self.m  = 1.0
        self.ft_reading = Wrench()

        # Create publishers
        self.sp_attitude_publisher = self.create_publisher(
            VehicleAttitudeSetpoint,dr_pf+'/fmu/setpoint_control/vehicle_attitude', qos_profile)

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
        print('PID Gains:',self.Kp,self.Kv)
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

    def vo2xv(self,vo:VehicleOdometry) -> np.ndarray:
        """Convert VehicleOdometry to state vector."""

        xv = np.array([vo.position[0],vo.position[1],vo.position[2],
                       vo.velocity[0],vo.velocity[1],vo.velocity[2],
                       vo.q[1],vo.q[2],vo.q[3],vo.q[0],
                       vo.angular_velocity[0],vo.angular_velocity[1],vo.angular_velocity[2]])
        
        xv[6:10] += np.array([0.0,0.0,0.0,1e-9])
        xv[6:10] = xv[6:10]/np.linalg.norm(xv[6:10])

        return xv
            
    def controller(self) -> None:
        if self.node_check():
            tk = self.get_clock().now().nanoseconds / 1e9 - self.t0
            xv_cr = self.vo2xv(self.vo_cr)

            if tk <= self.tf:
                # Check if we are in a new segment
                if tk > self.Tp[self.ksm+1]:
                    self.ksm += 1
                    print('In Segment:',self.ksm+1,'/',self.Nsm)

                # Compute the feed-forward trajectory
                tf_sm = self.Tp[self.ksm+1]-self.Tp[self.ksm]
                tk_sm = tk-self.Tp[self.ksm]
                CP_sm = self.CP[self.ksm,:,:]
                xv_ds = th.ts_to_xu(tk_sm,tf_sm,CP_sm,None,None,None)[0:10]

                # Publish the feed-forward trajectory
                self.att_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

                # =============================================================
                # Simple FT Feedback ==========================================

                # Some useful intermediate variables
                del_p = xv_ds[0:3]-xv_cr[0:3]
                del_v = xv_ds[3:6]-xv_cr[3:6]
 
                R_ds = R.from_quat(xv_ds[6:10]).as_matrix()
                R_cr = R.from_quat(xv_cr[6:10]).as_matrix()
                z_cr = R_cr[:,2]

                Fdes = -self.Kp@del_p - self.Kv@del_v + self.m*np.array([0,0,9.81])

                # Generate z_cmd vector
                z_cmd = Fdes/np.linalg.norm(Fdes)
                y_cmd = np.cross(z_cmd,R_ds[:,0])/np.linalg.norm(np.cross(z_cmd,R_ds[:,0]))
                x_cmd = np.cross(y_cmd,z_cmd)

                R_cmd = np.hstack((x_cmd.reshape(-1,1),y_cmd.reshape(-1,1),z_cmd.reshape(-1,1)))

                # Generate Thrust Command
                thrust = -np.dot(Fdes,z_cr)
                n_thrust = float(thrust/self.tn)

                # Generate Quaternion Command
                q_cmd = R.from_matrix(R_cmd).as_quat().astype(np.float32)

                self.att_sp.q_d = np.array([q_cmd[3],q_cmd[0],q_cmd[1],q_cmd[2]]).astype(np.float32)
                self.att_sp.thrust_body = np.array([0.0, 0.0, n_thrust]).astype(np.float32)
                # =============================================================
                # =============================================================

                self.sp_attitude_publisher.publish(self.att_sp)

            else:
                print('Trajectory Finished.')
                print('=========================================')
                
                # # Trim the trajectories
                # self.tXa = self.tXa[:,10:self.k]
                # self.tXi = self.tXi[:,10:self.k]
                # # Plot the trajectories
                # pt.tXU_to_3D([self.tXi,self.tXa])

                exit()
        else:
            pass

def main() -> None:
    print('Starting spline2attitude node...')

    # Create ArgumentParser object
    parser = argparse.ArgumentParser(description="Spline2Attitude Node.")

    # Add arguments
    parser.add_argument('--traj', type=str, help='Trajectory Name')
    parser.add_argument('--drone', type=str, help='Drone Name')
    parser.add_argument('--Fdes', type=float, help='Desired Force', default=1.0)
    parser.add_argument('--freq', type=int, help='Control Frequency', default=200)

    # Parse the command line arguments
    args = parser.parse_args()
    
    rclpy.init()
    controller = Spline2Attitude(args.traj,args.drone,args.Fdes,args.freq)
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

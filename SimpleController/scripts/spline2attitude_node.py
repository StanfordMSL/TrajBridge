#!/usr/bin/env python3

import numpy as np
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

from enum import Enum

class StateMachine(Enum):
    """Enum class for pilot state."""
    FREE_STARTUP = 0
    FREE_SEARCH = 1
    FREE_DISENGAGE = 2
    CONTACT_SEARCH = 3
    CONTACT_HOLD = 4
    
class Spline2Attitude(Node):
    """Node for generating attitude commands from spline."""

    def __init__(self,trajectory_name:str,drone_name:str,control_frequency:int) -> None:
        super().__init__('spline2attitude_node')

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        
        # Some useful intermediate variables
        dr_pf = '/'+drone_name if drone_name != 'fmu' else ''

        # Initialize state machine variables
        self.drone_state = StateMachine.FREE_STARTUP            # Drone state
        self.att_sp = VehicleAttitudeSetpoint()                 # attitude setpoint command
        self.vo_cr  = VehicleOdometry()                         # current vehicle odometry
        self.wr_sn = Wrench()                                   # wrench sensor reading
        self.t0 = 0.0                                           # State machine start time variable
        self.fv_ds:np.ndarray = np.zeros(3)                     # State machine desired force vector
        self.xv_0:np.ndarray  = np.eye(10)[9]                   # State machine starting full state variable
        self.xv_ds:np.ndarray = np.eye(10)[9]                   # State machine desired full state variable
        
        # Initialize state machine constants
        self.idx_st = 0                                         # State machine stair index
        self.dt_st = 5.0                                        # State machine stair time  
        self.Ftgt = np.array([1.0,2.0,3.0])                     # State machine stair forces
        self.Fthh = 0.5                                         # State machine search threshold
        self.dp_z = 0.1                                         # z-position search rate
        self.df_z = 0.01                                        # z-force search rate
        self.pz_max = -1.5                                      # State machine stair max height
        self.fz_max = np.max(self.Ftgt)+1.0                     # State machine stair max force

        # Controller
        self.Kp = np.diag([3.0,3.0,5.0])                        # VAS Pos Gain
        self.Kv = np.diag([3.0,3.0,3.0])                        # VAS Vel Gain
        self.tn = 4.0*6.90                                      # Thurt Gain
        self.m  = 1.0                                           # Mass
        self.Kfp = 0.005                                          # Force Feedback P-Gain

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

        print('================================================')
        print('Trajectory Name:',trajectory_name)
        print("Drone Name:",drone_name)
        print('Control Frequency:',control_frequency)
        print('================================================')

        print('Trajectory Information:')
        print('PD Gains:',np.diag(self.Kp),np.diag(self.Kv))
        input("Press Enter to start trajectory...")
    
        print('================================================')

        print('Trajectory Started.')

    def vehicle_odometry_callback(self, vehicle_odometry:VehicleOdometry):
        """Callback function for vehicle_odometry topic subscriber."""
        self.vo_cr = vehicle_odometry

    def ft_reading_callback(self, ft_reading:Wrench):
        """Callback function for ft_reading topic subscriber."""

        self.wr_sn = ft_reading

    def vo2xv(self,vo:VehicleOdometry) -> np.ndarray:
        """Convert VehicleOdometry to state vector."""

        xv = np.array([vo.position[0],vo.position[1],vo.position[2],
                       vo.velocity[0],vo.velocity[1],vo.velocity[2],
                       vo.q[1],vo.q[2],vo.q[3],vo.q[0],
                       vo.angular_velocity[0],vo.angular_velocity[1],vo.angular_velocity[2]])
        
        xv[6:10] += np.array([0.0,0.0,0.0,1e-9])
        xv[6:10] = xv[6:10]/np.linalg.norm(xv[6:10])

        return xv
    
    def vas_controller(self,xv_ds:np.ndarray,xv_cr:np.ndarray,fv_ds:np.ndarray=False) -> tuple:
        del_p = xv_ds[0:3]-xv_cr[0:3]
        del_v = xv_ds[3:6]-xv_cr[3:6]

        R_ds = R.from_quat(xv_ds[6:10]).as_matrix()
        R_cr = R.from_quat(xv_cr[6:10]).as_matrix()
        z_cr = R_cr[:,2]

        if fv_ds is False:
            Fdes = -self.Kp@del_p - self.Kv@del_v + self.m*np.array([0,0,9.81])

            z_cmd = Fdes/np.linalg.norm(Fdes)
            y_cmd = np.cross(z_cmd,R_ds[:,0])/np.linalg.norm(np.cross(z_cmd,R_ds[:,0]))
            x_cmd = np.cross(y_cmd,z_cmd)

            R_cmd = np.hstack((x_cmd.reshape(-1,1),y_cmd.reshape(-1,1),z_cmd.reshape(-1,1)))

            # Generate Thrust Command
            thrust = -np.dot(Fdes,z_cr)

            # Generate Quaternion Command
            q_cmd = R.from_matrix(R_cmd).as_quat().astype(np.float32)

            nt_cmd = float(thrust/self.tn)
        else:
            Fdes = -(0.3*(self.Kp@del_p)) - (0.3*(self.Kv@del_v)) + self.m*np.array([0,0,9.81])

            z_cmd = Fdes/np.linalg.norm(Fdes)
            y_cmd = np.cross(z_cmd,R_ds[:,0])/np.linalg.norm(np.cross(z_cmd,R_ds[:,0]))
            x_cmd = np.cross(y_cmd,z_cmd)

            R_cmd = np.hstack((x_cmd.reshape(-1,1),y_cmd.reshape(-1,1),z_cmd.reshape(-1,1)))

            # Generate Thrust Command
            thrust = -np.dot(Fdes,z_cr)

            # Generate Quaternion Command
            q_cmd = R.from_matrix(R_cmd).as_quat().astype(np.float32)

            if self.drone_state == StateMachine.CONTACT_SEARCH:
                nt_cmd = fv_ds[2]
            elif self.drone_state == StateMachine.CONTACT_HOLD:
                fz_tgt = self.Ftgt[self.idx_st]
                fz_act = self.wr_sn.force.z
                nt_cmd = fv_ds[2] - self.Kfp*(fz_tgt-fz_act)
                
        # print(self.drone_state,nt_cmd)

        thrust_body = np.array([0.0, 0.0, nt_cmd]).astype(np.float32)
        q_d = np.array([q_cmd[3],q_cmd[0],q_cmd[1],q_cmd[2]]).astype(np.float32)

        return thrust_body,q_d
            
    def controller(self) -> None:
        # Looping Controlle Actions
        tk = self.get_clock().now().nanoseconds / 1e9
        xv_cr = self.vo2xv(self.vo_cr)

        # Drone State Machine
        if self.drone_state == StateMachine.FREE_STARTUP:
            # Looping State Actions

            # State Transition Actions
            if self.vo_cr.timestamp >    0:
                self.t0,self.x0 = tk,xv_cr
                self.drone_state = StateMachine.FREE_SEARCH
                print("State Machine: FREE_SEARCH")

        elif self.drone_state == StateMachine.FREE_SEARCH:
            # Looping State Actions
            xv_ds = self.xv_0.copy()
            xv_ds[2] -= self.dp_z*(tk-self.t0)

            # State Transition Actions
            if xv_cr[2] < self.pz_max:
                self.drone_state = StateMachine.FREE_DISENGAGE
                print("Failsafe Triggered at:",xv_ds[2])
                print("State Machine: FREE_DISENGAGE")
            elif self.wr_sn.force.z > self.Fthh:
                self.t0,self.xd,self.fv_ds = tk,xv_ds,self.att_sp.thrust_body
                self.drone_state = StateMachine.CONTACT_SEARCH
                print("State Machine: CONTACT_SEARCH")
            # Looping State Actions
            else:
                self.att_sp.thrust_body,self.att_sp.q_d = self.vas_controller(xv_ds,xv_cr)
                self.att_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)
                self.sp_attitude_publisher.publish(self.att_sp)

        elif self.drone_state == StateMachine.CONTACT_SEARCH:
            # Looping State Actions
            xv_ds = self.xv_ds
            fv_ds = self.fv_ds.copy()
            sgn_ds = np.sign(self.Ftgt[self.idx_st]-self.wr_sn.force.z)

            fv_ds[2] -= sgn_ds*self.df_z*(tk-self.t0)

            # State Transition Actions
            if (xv_cr[2] < self.pz_max) or (self.wr_sn.force.z > self.fz_max):
                self.drone_state = StateMachine.FREE_DISENGAGE
                print("Failsafe Triggered.")
                print("Z Height:",xv_cr[2])
                print("Z Force:",self.wr_sn.force.z)
                print("State Machine: FREE_DISENGAGE")
            elif self.wr_sn.force.z > self.Ftgt[self.idx_st]:
                self.t0,self.fv_ds = tk,self.att_sp.thrust_body

                self.drone_state = StateMachine.CONTACT_HOLD
                print("State Machine: CONTACT_HOLD")
            # Looping State Actions
            else:
                self.att_sp.thrust_body,self.att_sp.q_d = self.vas_controller(xv_ds,xv_cr,fv_ds)
                self.att_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)
                self.sp_attitude_publisher.publish(self.att_sp)

        elif self.drone_state == StateMachine.CONTACT_HOLD:
            # Looping State Actions
            xv_ds = self.xv_ds
            fv_ds = self.fv_ds

            # State Transition Actions
            if (xv_cr[2] < self.pz_max) or (self.wr_sn.force.z > self.fz_max):
                self.drone_state = StateMachine.FREE_DISENGAGE
                print("Failsafe Triggered.")
                print("State Machine: FREE_DISENGAGE")
            elif tk > self.t0 + self.dt_st:
                self.idx_st += 1
                if self.idx_st < len(self.Ftgt):
                    self.t0,self.fv_ds = tk,self.att_sp.thrust_body

                    self.drone_state = StateMachine.CONTACT_SEARCH
                    print("State Machine: CONTACT_SEARCH")
                else:
                    self.drone_state = StateMachine.FREE_DISENGAGE
                    self.t0 = tk
                    print("State Machine: FREE_DISENGAGE")
            # Looping State Actions
            else:
                self.att_sp.thrust_body,self.att_sp.q_d = self.vas_controller(xv_ds,xv_cr,fv_ds)
                self.att_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)
                self.sp_attitude_publisher.publish(self.att_sp)

        elif self.drone_state == StateMachine.FREE_DISENGAGE:
            xv_ds = self.xv_0.copy()
            xv_ds[2] = -0.8

            self.att_sp.thrust_body,self.att_sp.q_d = self.vas_controller(xv_ds,xv_cr)
            self.att_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)
            self.sp_attitude_publisher.publish(self.att_sp)
            
            if tk > self.t0 + 1.0:
                exit()

def main() -> None:
    print('Starting spline2attitude node...')

    # Create ArgumentParser object
    parser = argparse.ArgumentParser(description="Spline2Attitude Node.")

    # Add arguments
    parser.add_argument('--traj', type=str, help='Trajectory Name')
    parser.add_argument('--drone', type=str, help='Drone Name')
    parser.add_argument('--freq', type=int, help='Control Frequency', default=200)

    # Parse the command line arguments
    args = parser.parse_args()
    
    rclpy.init()
    controller = Spline2Attitude(args.traj,args.drone,args.freq)
    rclpy.spin(controller)
    controller.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

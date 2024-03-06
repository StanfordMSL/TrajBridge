#!/usr/bin/env python3

import numpy as np

import px4_comm.ball_timer as bt
import px4_comm.offboard_controller as oc
import px4_comm.states_modes as sm

import rclpy
from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

from px4_msgs.msg import (
    VehicleOdometry,
    VehicleStatus,
    TrajectorySetpoint,
    VehicleAttitudeSetpoint,
    ActuatorMotors
)

class StateMachine(Node):
    """Node for controlling a vehicle using an SFTI pilot."""

    def __init__(self) -> None:
        super().__init__('state_machine_node')

        # Required Parameters
        self.declare_parameter('auto_start',rclpy.Parameter.Type.BOOL)        
        self.declare_parameter('auto_land',rclpy.Parameter.Type.BOOL)        
        self.declare_parameter('wp_ready',rclpy.Parameter.Type.DOUBLE_ARRAY)        
        
        # Optional Parameters
        self.declare_parameter('control_frequency',200)
        self.declare_parameter('hover_height',-1.0)
        self.declare_parameter('timer_time_tolerance', 3.0)
        self.declare_parameter('timer_distance_tolerance', 0.2)
        self.declare_parameter('gcs_time_tolerance', 0.5)

        # Get Parameters
        at_st = self.get_parameter('auto_start').value
        at_ld = self.get_parameter('auto_land').value
        wp_rdy = self.get_parameter('wp_ready').value
        hz_ctl = self.get_parameter('control_frequency').value
        z_hvr  = self.get_parameter('hover_height').value
        tmr_t_tol = self.get_parameter('timer_time_tolerance').value
        tmr_s_tol = self.get_parameter('timer_distance_tolerance').value
        gcs_t_tol = self.get_parameter('gcs_time_tolerance').value

        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )

        # Create subscribers
        self.vehicle_status_subscriber = self.create_subscription(
            VehicleStatus, '/fmu/out/vehicle_status', self.vehicle_status_callback, qos_profile)
        self.vehicle_odometry_subscriber = self.create_subscription(
            VehicleOdometry, '/fmu/out/vehicle_odometry', self.vehicle_odometry_callback, qos_profile)
        self.sp_position_with_ff_subscriber = self.create_subscription(
            TrajectorySetpoint, '/setpoint_control/position_with_ff', self.position_with_ff_callback, qos_profile)
        self.sp_velocity_with_ff_subscriber = self.create_subscription(
            TrajectorySetpoint, '/setpoint_control/velocity_with_ff', self.velocity_with_ff_callback, qos_profile)
        self.sp_vehicle_attitude_subscriber = self.create_subscription(
            VehicleAttitudeSetpoint, '/setpoint_control/vehicle_attitude', self.vehicle_attitude_callback, qos_profile)
        self.sp_actuator_motors_subscriber = self.create_subscription(
            ActuatorMotors, '/setpoint_control/actuator_motors', self.actuator_motors_callback, qos_profile)

        # Create publishers
        self.offboard_controller = oc.OffboardController(self)
        
        # Subscriber variables
        self.vs_cr = VehicleStatus()                                    # current vehicle status
        self.vo_cr = VehicleOdometry()                                  # current state vector
        self.uf_cr = ActuatorMotors()                                   # current actuator motors input
        self.pos_sp = TrajectorySetpoint()                              # position with ff setpoint command
        self.vel_sp = TrajectorySetpoint()                              # velocity with ff setpoint command
        self.vas_sp = VehicleAttitudeSetpoint()                         # vehicle attitude setpoint command
        self.ams_sp = ActuatorMotors()                                  # actuator motors setpoint command
        
        # Initialize state machine variables        
        self.publisher_mode = sm.PublisherMode.STATE_MACHINE_WP         # publisher mode
        self.smp_sp = TrajectorySetpoint()                              # state machine position setpoint command
        self.wp_rdy = np.array(wp_rdy)                                  # state machine ready waypoint
        self.z_hvr  = z_hvr                                             # hover height
        self.sm_tmr = bt.BallTimer(0.0,0.0,tmr_t_tol,tmr_s_tol)         # timer for state machine transitions
        self.gcs_t_tol = gcs_t_tol                                      # time tolerance for gcs messages
        self.at_ld = at_ld                                              # auto land flag
        
        if at_st == True:
            self.drone_state = sm.StateMachine.STARTUP_AUTO

            # Print outs
            print("State Machine: STARTUP (AUTO)")
        else:
            self.drone_state = sm.StateMachine.STARTUP_USER
            
            # Print outs
            print("State Machine: STARTUP (USER)")
        
        # Create a timer to publish control commands
        self.cmdLoop = self.create_timer(1/hz_ctl, self.cmd_callback)

    def get_publisher_mode(self):
        """Get the current publisher mode."""
        # Check if time since last message received exceeds threshold
        t_now = self.get_clock().now().nanoseconds / 1e9
        
        pos_elapsed = t_now - self.pos_sp.timestamp / 1e6
        vel_elapsed = t_now - self.vel_sp.timestamp / 1e6
        vas_elapsed = t_now - self.vas_sp.timestamp / 1e6
        ams_elapsed = t_now - self.ams_sp.timestamp / 1e6

        idx_mode =  np.argmin([self.gcs_t_tol, pos_elapsed, vel_elapsed, vas_elapsed, ams_elapsed])

        if idx_mode == 0:
            return sm.PublisherMode.STATE_MACHINE_WP
        elif idx_mode == 1:
            return sm.PublisherMode.POSITION_WITH_FF
        elif idx_mode == 2:
            return sm.PublisherMode.VELOCITY_WITH_FF
        elif idx_mode == 3:
            return sm.PublisherMode.VEHICLE_ATTITUDE
        elif idx_mode == 4:
            return sm.PublisherMode.ACTUATOR_MOTORS
        else:
            raise ValueError('Invalid Publisher Mode')
        
    def vehicle_status_callback(self, vehicle_status:VehicleStatus):
        """Callback function for vehicle_status topic subscriber."""
        self.vs_cr = vehicle_status

    def vehicle_odometry_callback(self, vehicle_odometry:VehicleOdometry):
        """Callback function for vehicle_odometry topic subscriber."""
        self.vo_cr = vehicle_odometry

    def position_with_ff_callback(self, position_with_ff:TrajectorySetpoint):
        """Callback function for position_with_ff topic subscriber."""
        self.pos_sp = position_with_ff

    def velocity_with_ff_callback(self, velocity_with_ff:TrajectorySetpoint):
        """Callback function for velocity_with_ff topic subscriber."""
        self.vel_sp = velocity_with_ff

    def vehicle_attitude_callback(self, vehicle_attitude:VehicleAttitudeSetpoint):
        """Callback function for vehicle_attitude topic subscriber."""
        self.vas_sp = vehicle_attitude

    def actuator_motors_callback(self, actuator_motors:ActuatorMotors):
        """Callback function for actuator_motors topic subscriber."""
        self.ams_sp = actuator_motors

    def cmd_callback(self) -> None:
        # Looping Variables
        t_cr = self.get_clock().now().nanoseconds / 1e9
        xv_cr = self.vo2xv(self.vo_cr)
        pub_mode = self.get_publisher_mode()

        # Looping Callback Actions
        self.offboard_controller.set_offboard_control_mode(pub_mode)

        # Safety Check
        if ((self.vs_cr.nav_state is not VehicleStatus.NAVIGATION_STATE_OFFBOARD) and 
            (self.drone_state is not sm.StateMachine.STARTUP_AUTO) and
            (self.drone_state is not sm.StateMachine.STARTUP_USER)):
            self.offboard_controller.land()
            exit(0)

        # Drone State Machine
        if self.drone_state == sm.StateMachine.STARTUP_AUTO:
            # Looping State Actions
            self.update_smp_sp(np.array([xv_cr[0],xv_cr[1],0.0,0.0]))               # Set waypoint to current xy-position (grounded altitude)
            self.offboard_controller.set_trajectory_setpoint(self.smp_sp)           # Publish desired position  

            if self.vs_cr.pre_flight_checks_pass is True:
                # State Transition Actions
                self.update_smp_sp(np.array([xv_cr[0],xv_cr[1],self.z_hvr,0.0]))    # Set waypoint to current xy-position (hover altitude)
                self.offboard_controller.set_trajectory_setpoint(self.smp_sp)       # Publish desired position  
                
                self.offboard_controller.engage_offboard_mode()                     # Switch drone to offboard mode
                self.offboard_controller.arm()                                      # Arm drone
                self.sm_tmr.reset(t_cr,self.smp_sp.position)                        # Reset state machine timer for takeoff

                # State Transition  
                self.drone_state = sm.StateMachine.TAKEOFF                          # Transition to takeoff
                
                # Print outs
                print("-------------------------------------------------------------------------------")
                print("State Machine: TAKEOFF")

        elif self.drone_state == sm.StateMachine.STARTUP_USER:
            if self.vs_cr.nav_state is VehicleStatus.NAVIGATION_STATE_OFFBOARD:
                # State Transition Actions
                self.update_smp_sp(self.wp_rdy)                                     # Send to ready waypoint
                self.sm_tmr.reset(t_cr,self.smp_sp.position)                        # Reset state machine timer for takeoff

                # State Transition  
                self.drone_state = sm.StateMachine.WAYPOINT                         # Transition to takeoff

                # Print outs
                print("-------------------------------------------------------------------------------")
                print("State Machine: WAYPOINT")
        elif self.drone_state == sm.StateMachine.TAKEOFF:
            # Looping State Actions
            self.update_smp_sp()                                                    # Update waypoint command (time only)
            self.offboard_controller.set_trajectory_setpoint(self.smp_sp)           # Publish desired position  

            if self.sm_tmr.check(t_cr,xv_cr[0:3]):
                # State Transition Actions
                self.update_smp_sp(self.wp_rdy)                                     # Send to ready waypoint

                self.sm_tmr.reset(t_cr,self.smp_sp.position)                        # Reset state machine timer for waypoint

                # State Transition  
                self.drone_state = sm.StateMachine.WAYPOINT                         # Transition to waypoint

                # Print outs
                print("-------------------------------------------------------------------------------")
                print("State Machine: WAYPOINT")                                  

        elif self.drone_state == sm.StateMachine.WAYPOINT:
            # Looping State Actions
            self.update_smp_sp()                                                    # Update waypoint command (time only)
            self.offboard_controller.set_trajectory_setpoint(self.smp_sp)           # Publish desired position  
            
            if self.sm_tmr.check(t_cr,xv_cr[0:3]):
                # State Transition Actions

                # State Transition  
                self.drone_state = sm.StateMachine.READY                            # Transition to active

                # Print outs
                print("-------------------------------------------------------------------------------")
                print("State Machine: READY")
                
        elif self.drone_state == sm.StateMachine.READY:
            # Looping State Actions
            self.update_smp_sp()                                                    # Update waypoint command (time only)
            self.offboard_controller.set_trajectory_setpoint(self.smp_sp)           # Publish desired position  

            if pub_mode is not sm.PublisherMode.STATE_MACHINE_WP:
                # State Transition Actions

                # State Transition  
                self.drone_state = sm.StateMachine.ACTIVE                           # Transition to active

                # Print outs
                print("-------------------------------------------------------------------------------")
                print("State Machine: ACTIVE")
                
        elif self.drone_state == sm.StateMachine.ACTIVE:
            # Looping State Actions
            if pub_mode is sm.PublisherMode.POSITION_WITH_FF:
                self.offboard_controller.set_trajectory_setpoint(self.pos_sp)
            elif pub_mode is sm.PublisherMode.VELOCITY_WITH_FF:
                self.offboard_controller.set_trajectory_setpoint(self.vel_sp)
            elif pub_mode is sm.PublisherMode.VEHICLE_ATTITUDE:
                self.offboard_controller.set_vehicle_attitude_setpoint(self.vas_sp)
            elif pub_mode is sm.PublisherMode.ACTUATOR_MOTORS:
                self.offboard_controller.set_actuator_motors(self.ams_sp)
            else:
                # State Transition Actions
                self.update_smp_sp(self.wp_rdy)                                     # Send to ready waypoint
                self.sm_tmr.reset(t_cr,self.smp_sp.position)                        # Reset state machine timer for takeoff
                
                if self.at_ld == True:
                    # State Transition  
                    self.drone_state = sm.StateMachine.LAND                         # Transition to land

                    # Print outs
                    print("-------------------------------------------------------------------------------")
                    print("State Machine: LAND")
                else:
                    # State Transition  
                    self.drone_state = sm.StateMachine.WAYPOINT                     # Transition to waypoint

                    # Print outs
                    print("-------------------------------------------------------------------------------")
                    print("State Machine: WAYPOINT")
                
        elif self.drone_state == sm.StateMachine.LAND:
            # Terminal State Actions
            self.offboard_controller.land()
            exit(0)
        else:
            # Terminal State Actions
            self.offboard_controller.land()
            exit(0)

    def update_smp_sp(self,wp:np.ndarray=None):
        """Update the waypoint setpoint command."""
        if wp is not None:
            self.smp_sp.position = wp[0:3].astype(np.float32)
            self.smp_sp.yaw = float(wp[3])

        self.smp_sp.timestamp = int(self.get_clock().now().nanoseconds / 1000)

    def vo2xv(self,vo:VehicleOdometry):
        """Convert odometry message to numpy array."""
        xv_cr = np.zeros(13)

        xv_cr[0:3] = vo.position
        xv_cr[3:6] = vo.velocity
        xv_cr[6:9] = vo.q[1:4]
        xv_cr[9]   = vo.q[0]
        xv_cr[10:] = vo.angular_velocity
    
        return xv_cr
    
def main(args=None) -> None:
    print('Starting state_machine node...')
    rclpy.init(args=args)
    state_machine = StateMachine()
    rclpy.spin(state_machine)
    state_machine.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    try:
        main()
    except Exception as e:
        print(e)

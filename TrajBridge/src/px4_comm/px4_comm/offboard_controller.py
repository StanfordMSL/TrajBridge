from px4_msgs.msg import (
    VehicleCommand,
    OffboardControlMode,
    TrajectorySetpoint,
    VehicleAttitudeSetpoint,
    VehicleRatesSetpoint,
    ActuatorMotors
)

from rclpy.node import Node
from rclpy.qos import QoSProfile, ReliabilityPolicy, HistoryPolicy, DurabilityPolicy

import px4_comm.states_modes as sm

class OffboardController():
    '''
    Common vehicle commands
    '''
    def __init__(self,node:Node,dr_pf:str):
        # Configure QoS profile for publishing and subscribing
        qos_profile = QoSProfile(
            reliability=ReliabilityPolicy.BEST_EFFORT,
            durability=DurabilityPolicy.TRANSIENT_LOCAL,
            history=HistoryPolicy.KEEP_LAST,
            depth=1
        )
        
        # Parent Node
        self.node = node
        
        # Create Publishers
        self.vehicle_command_publisher = self.node.create_publisher(
            VehicleCommand,dr_pf+'/fmu/in/vehicle_command', qos_profile)
        self.offboard_control_mode_publisher = self.node.create_publisher(
            OffboardControlMode,dr_pf+'/fmu/in/offboard_control_mode', qos_profile)
        self.trajectory_setpoint_publisher = self.node.create_publisher(
            TrajectorySetpoint,dr_pf+'/fmu/in/trajectory_setpoint', qos_profile)
        self.vehicle_attitude_setpoint_publisher = self.node.create_publisher(
            VehicleAttitudeSetpoint,dr_pf+'/fmu/in/vehicle_attitude_setpoint', qos_profile)
        self.vehicle_rates_setpoint_publisher = self.node.create_publisher(
            VehicleRatesSetpoint,dr_pf+'/fmu/in/vehicle_rates_setpoint', qos_profile)
        self.actuator_motors_publisher = self.node.create_publisher(
            ActuatorMotors,dr_pf+'/fmu/in/actuator_motors', qos_profile)

        # Create Controller Variables
        self.vehicle_command = VehicleCommand(
            param1=0.0,param2=0.0,param3=0.0,param4=0.0,param5=0.0,
            param6=0.0,param7=0.0,target_system=1,target_component=1,
            source_system=1,source_component=1,from_external=True,
            timestamp=0
        )
        self.offboard_control_mode = OffboardControlMode(
            position=True,velocity=False,acceleration=False,
            attitude=False,body_rate=False,actuator=False,
            timestamp=0
        )

    def arm(self) -> None:
        """Send an arm command to the vehicle."""
        self.vehicle_command.command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
        self.vehicle_command.param1 = 1.0
        self.vehicle_command.param2 = 0.0

        self.vehicle_command.timestamp = int(self.node.get_clock().now().nanoseconds / 1000)
        self.vehicle_command_publisher.publish(self.vehicle_command)

    def disarm(self) -> None:
        """Send a disarm command to the vehicle."""
        self.vehicle_command.command = VehicleCommand.VEHICLE_CMD_COMPONENT_ARM_DISARM
        self.vehicle_command.param1 = 0.0
        self.vehicle_command.param2 = 0.0

        self.vehicle_command.timestamp = int(self.node.get_clock().now().nanoseconds / 1000)
        self.vehicle_command_publisher.publish(self.vehicle_command)

    def engage_offboard_mode(self) -> None:
        """Switch to offboard mode."""
        self.vehicle_command.command = VehicleCommand.VEHICLE_CMD_DO_SET_MODE
        self.vehicle_command.param1 = 1.0
        self.vehicle_command.param2 = 6.0

        self.vehicle_command.timestamp = int(self.node.get_clock().now().nanoseconds / 1000)
        self.vehicle_command_publisher.publish(self.vehicle_command)

    def land(self) -> None:
        """Switch to land mode."""
        self.vehicle_command.command = VehicleCommand.VEHICLE_CMD_NAV_LAND
        self.vehicle_command.param1 = 0.0
        self.vehicle_command.param2 = 0.0

        self.vehicle_command.timestamp = int(self.node.get_clock().now().nanoseconds / 1000)
        self.vehicle_command_publisher.publish(self.vehicle_command)

    def set_offboard_control_mode(self,pub_mode:sm.PublisherMode) -> None:
        """Publish the offboard control mode."""
        self.offboard_control_mode.position = False
        self.offboard_control_mode.velocity = False
        self.offboard_control_mode.acceleration = False
        self.offboard_control_mode.attitude = False
        self.offboard_control_mode.body_rate = False
        self.offboard_control_mode.actuator = False

        if (pub_mode is sm.PublisherMode.STATE_MACHINE_WP):
            self.offboard_control_mode.position = True
        elif (pub_mode is sm.PublisherMode.POSITION_WITH_FF):
            self.offboard_control_mode.position = True
        elif (pub_mode is sm.PublisherMode.VELOCITY_WITH_FF):
            self.offboard_control_mode.position = True
        elif (pub_mode is sm.PublisherMode.VEHICLE_ATTITUDE):
            self.offboard_control_mode.attitude = True
        elif (pub_mode is sm.PublisherMode.VEHICLE_RATES):
            self.offboard_control_mode.body_rate = True
        elif (pub_mode is sm.PublisherMode.ACTUATOR_MOTORS):
            self.offboard_control_mode.actuator = True
        else:
            raise ValueError('Invalid Publisher Mode')
        
        self.offboard_control_mode.timestamp = int(self.node.get_clock().now().nanoseconds / 1000)
        self.offboard_control_mode_publisher.publish(self.offboard_control_mode)

    def set_trajectory_setpoint(self,ts:TrajectorySetpoint) -> None:
        """Publish the trajectory setpoint."""
        self.trajectory_setpoint_publisher.publish(ts)

    def set_vehicle_attitude_setpoint(self,vas:VehicleAttitudeSetpoint) -> None:
        """Publish the vehicle attitude setpoint."""
        self.vehicle_attitude_setpoint_publisher.publish(vas)

    def set_vehicle_rates_setpoint(self,vrs:VehicleRatesSetpoint) -> None:
        """Publish the vehicle rates setpoint."""
        self.vehicle_rates_setpoint_publisher.publish(vrs)

    def set_actuator_motors(self,am:ActuatorMotors) -> None:
        """Publish the actuator motors."""
        self.actuator_motors_publisher.publish(am)
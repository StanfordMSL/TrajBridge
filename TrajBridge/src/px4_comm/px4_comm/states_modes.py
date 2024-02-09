from enum import Enum

class StateMachine(Enum):
    """Enum class for pilot state."""
    STARTUP = 0
    TAKEOFF = 1
    WAYPOINT = 2
    READY = 3
    ACTIVE = 4
    HOVER = 5
    LAND = 6

class PublisherMode(Enum):
    """Enum class for publisher mode."""
    STATE_MACHINE_WP = 0
    POSITION_WITH_FF = 1
    VELOCITY_WITH_FF = 2
    VEHICLE_ATTITUDE = 3
    ACTUATOR_MOTORS = 4
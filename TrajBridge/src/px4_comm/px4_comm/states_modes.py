from enum import Enum

class StateMachine(Enum):
    """Enum class for pilot state."""
    STARTUP_AUTO = 0
    STARTUP_USER = 1
    TAKEOFF = 2
    WAYPOINT = 3
    READY = 4
    ACTIVE = 5
    LAND = 6

class PublisherMode(Enum):
    """Enum class for publisher mode."""
    STATE_MACHINE_WP = 0
    POSITION_WITH_FF = 1
    VELOCITY_WITH_FF = 2
    VEHICLE_ATTITUDE = 3
    VEHICLE_RATES = 4
    ACTUATOR_MOTORS = 5
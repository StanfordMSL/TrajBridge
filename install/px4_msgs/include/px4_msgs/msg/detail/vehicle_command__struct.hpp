// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/VehicleCommand.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__VehicleCommand __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__VehicleCommand __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleCommand_
{
  using Type = VehicleCommand_<ContainerAllocator>;

  explicit VehicleCommand_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->param1 = 0.0f;
      this->param2 = 0.0f;
      this->param3 = 0.0f;
      this->param4 = 0.0f;
      this->param5 = 0.0;
      this->param6 = 0.0;
      this->param7 = 0.0f;
      this->command = 0ul;
      this->target_system = 0;
      this->target_component = 0;
      this->source_system = 0;
      this->source_component = 0;
      this->confirmation = 0;
      this->from_external = false;
    }
  }

  explicit VehicleCommand_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->param1 = 0.0f;
      this->param2 = 0.0f;
      this->param3 = 0.0f;
      this->param4 = 0.0f;
      this->param5 = 0.0;
      this->param6 = 0.0;
      this->param7 = 0.0f;
      this->command = 0ul;
      this->target_system = 0;
      this->target_component = 0;
      this->source_system = 0;
      this->source_component = 0;
      this->confirmation = 0;
      this->from_external = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _param1_type =
    float;
  _param1_type param1;
  using _param2_type =
    float;
  _param2_type param2;
  using _param3_type =
    float;
  _param3_type param3;
  using _param4_type =
    float;
  _param4_type param4;
  using _param5_type =
    double;
  _param5_type param5;
  using _param6_type =
    double;
  _param6_type param6;
  using _param7_type =
    float;
  _param7_type param7;
  using _command_type =
    uint32_t;
  _command_type command;
  using _target_system_type =
    uint8_t;
  _target_system_type target_system;
  using _target_component_type =
    uint8_t;
  _target_component_type target_component;
  using _source_system_type =
    uint8_t;
  _source_system_type source_system;
  using _source_component_type =
    uint8_t;
  _source_component_type source_component;
  using _confirmation_type =
    uint8_t;
  _confirmation_type confirmation;
  using _from_external_type =
    bool;
  _from_external_type from_external;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__param1(
    const float & _arg)
  {
    this->param1 = _arg;
    return *this;
  }
  Type & set__param2(
    const float & _arg)
  {
    this->param2 = _arg;
    return *this;
  }
  Type & set__param3(
    const float & _arg)
  {
    this->param3 = _arg;
    return *this;
  }
  Type & set__param4(
    const float & _arg)
  {
    this->param4 = _arg;
    return *this;
  }
  Type & set__param5(
    const double & _arg)
  {
    this->param5 = _arg;
    return *this;
  }
  Type & set__param6(
    const double & _arg)
  {
    this->param6 = _arg;
    return *this;
  }
  Type & set__param7(
    const float & _arg)
  {
    this->param7 = _arg;
    return *this;
  }
  Type & set__command(
    const uint32_t & _arg)
  {
    this->command = _arg;
    return *this;
  }
  Type & set__target_system(
    const uint8_t & _arg)
  {
    this->target_system = _arg;
    return *this;
  }
  Type & set__target_component(
    const uint8_t & _arg)
  {
    this->target_component = _arg;
    return *this;
  }
  Type & set__source_system(
    const uint8_t & _arg)
  {
    this->source_system = _arg;
    return *this;
  }
  Type & set__source_component(
    const uint8_t & _arg)
  {
    this->source_component = _arg;
    return *this;
  }
  Type & set__confirmation(
    const uint8_t & _arg)
  {
    this->confirmation = _arg;
    return *this;
  }
  Type & set__from_external(
    const bool & _arg)
  {
    this->from_external = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint16_t VEHICLE_CMD_CUSTOM_0 =
    0u;
  static constexpr uint16_t VEHICLE_CMD_CUSTOM_1 =
    1u;
  static constexpr uint16_t VEHICLE_CMD_CUSTOM_2 =
    2u;
  static constexpr uint16_t VEHICLE_CMD_NAV_WAYPOINT =
    16u;
  static constexpr uint16_t VEHICLE_CMD_NAV_LOITER_UNLIM =
    17u;
  static constexpr uint16_t VEHICLE_CMD_NAV_LOITER_TURNS =
    18u;
  static constexpr uint16_t VEHICLE_CMD_NAV_LOITER_TIME =
    19u;
  static constexpr uint16_t VEHICLE_CMD_NAV_RETURN_TO_LAUNCH =
    20u;
  static constexpr uint16_t VEHICLE_CMD_NAV_LAND =
    21u;
  static constexpr uint16_t VEHICLE_CMD_NAV_TAKEOFF =
    22u;
  static constexpr uint16_t VEHICLE_CMD_NAV_PRECLAND =
    23u;
  static constexpr uint16_t VEHICLE_CMD_DO_ORBIT =
    34u;
  static constexpr uint16_t VEHICLE_CMD_NAV_ROI =
    80u;
  static constexpr uint16_t VEHICLE_CMD_NAV_PATHPLANNING =
    81u;
  static constexpr uint16_t VEHICLE_CMD_NAV_VTOL_TAKEOFF =
    84u;
  static constexpr uint16_t VEHICLE_CMD_NAV_VTOL_LAND =
    85u;
  static constexpr uint16_t VEHICLE_CMD_NAV_GUIDED_LIMITS =
    90u;
  static constexpr uint16_t VEHICLE_CMD_NAV_GUIDED_MASTER =
    91u;
  static constexpr uint16_t VEHICLE_CMD_NAV_DELAY =
    93u;
  static constexpr uint16_t VEHICLE_CMD_NAV_LAST =
    95u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_DELAY =
    112u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_CHANGE_ALT =
    113u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_DISTANCE =
    114u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_YAW =
    115u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_LAST =
    159u;
  static constexpr uint16_t VEHICLE_CMD_CONDITION_GATE =
    4501u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_MODE =
    176u;
  static constexpr uint16_t VEHICLE_CMD_DO_JUMP =
    177u;
  static constexpr uint16_t VEHICLE_CMD_DO_CHANGE_SPEED =
    178u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_HOME =
    179u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_PARAMETER =
    180u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_RELAY =
    181u;
  static constexpr uint16_t VEHICLE_CMD_DO_REPEAT_RELAY =
    182u;
  static constexpr uint16_t VEHICLE_CMD_DO_REPEAT_SERVO =
    184u;
  static constexpr uint16_t VEHICLE_CMD_DO_FLIGHTTERMINATION =
    185u;
  static constexpr uint16_t VEHICLE_CMD_DO_CHANGE_ALTITUDE =
    186u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_ACTUATOR =
    187u;
  static constexpr uint16_t VEHICLE_CMD_DO_LAND_START =
    189u;
  static constexpr uint16_t VEHICLE_CMD_DO_GO_AROUND =
    191u;
  static constexpr uint16_t VEHICLE_CMD_DO_REPOSITION =
    192u;
  static constexpr uint16_t VEHICLE_CMD_DO_PAUSE_CONTINUE =
    193u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_ROI_LOCATION =
    195u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_ROI_WPNEXT_OFFSET =
    196u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_ROI_NONE =
    197u;
  static constexpr uint16_t VEHICLE_CMD_DO_CONTROL_VIDEO =
    200u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_ROI =
    201u;
  static constexpr uint16_t VEHICLE_CMD_DO_DIGICAM_CONTROL =
    203u;
  static constexpr uint16_t VEHICLE_CMD_DO_MOUNT_CONFIGURE =
    204u;
  static constexpr uint16_t VEHICLE_CMD_DO_MOUNT_CONTROL =
    205u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_CAM_TRIGG_DIST =
    206u;
  static constexpr uint16_t VEHICLE_CMD_DO_FENCE_ENABLE =
    207u;
  static constexpr uint16_t VEHICLE_CMD_DO_PARACHUTE =
    208u;
  static constexpr uint16_t VEHICLE_CMD_DO_MOTOR_TEST =
    209u;
  static constexpr uint16_t VEHICLE_CMD_DO_INVERTED_FLIGHT =
    210u;
  static constexpr uint16_t VEHICLE_CMD_DO_GRIPPER =
    211u;
  static constexpr uint16_t VEHICLE_CMD_DO_SET_CAM_TRIGG_INTERVAL =
    214u;
  static constexpr uint16_t VEHICLE_CMD_DO_MOUNT_CONTROL_QUAT =
    220u;
  static constexpr uint16_t VEHICLE_CMD_DO_GUIDED_MASTER =
    221u;
  static constexpr uint16_t VEHICLE_CMD_DO_GUIDED_LIMITS =
    222u;
  static constexpr uint16_t VEHICLE_CMD_DO_LAST =
    240u;
  static constexpr uint16_t VEHICLE_CMD_PREFLIGHT_CALIBRATION =
    241u;
  static constexpr uint16_t PREFLIGHT_CALIBRATION_TEMPERATURE_CALIBRATION =
    3u;
  static constexpr uint16_t VEHICLE_CMD_PREFLIGHT_SET_SENSOR_OFFSETS =
    242u;
  static constexpr uint16_t VEHICLE_CMD_PREFLIGHT_UAVCAN =
    243u;
  static constexpr uint16_t VEHICLE_CMD_PREFLIGHT_STORAGE =
    245u;
  static constexpr uint16_t VEHICLE_CMD_PREFLIGHT_REBOOT_SHUTDOWN =
    246u;
  static constexpr uint16_t VEHICLE_CMD_OBLIQUE_SURVEY =
    260u;
  static constexpr uint16_t VEHICLE_CMD_GIMBAL_DEVICE_INFORMATION =
    283u;
  static constexpr uint16_t VEHICLE_CMD_MISSION_START =
    300u;
  static constexpr uint16_t VEHICLE_CMD_ACTUATOR_TEST =
    310u;
  static constexpr uint16_t VEHICLE_CMD_CONFIGURE_ACTUATOR =
    311u;
  static constexpr uint16_t VEHICLE_CMD_COMPONENT_ARM_DISARM =
    400u;
  static constexpr uint16_t VEHICLE_CMD_RUN_PREARM_CHECKS =
    401u;
  static constexpr uint16_t VEHICLE_CMD_INJECT_FAILURE =
    420u;
  static constexpr uint16_t VEHICLE_CMD_START_RX_PAIR =
    500u;
  static constexpr uint16_t VEHICLE_CMD_REQUEST_MESSAGE =
    512u;
  static constexpr uint16_t VEHICLE_CMD_SET_CAMERA_MODE =
    530u;
  static constexpr uint16_t VEHICLE_CMD_SET_CAMERA_ZOOM =
    531u;
  static constexpr uint16_t VEHICLE_CMD_SET_CAMERA_FOCUS =
    532u;
  static constexpr uint16_t VEHICLE_CMD_DO_GIMBAL_MANAGER_PITCHYAW =
    1000u;
  static constexpr uint16_t VEHICLE_CMD_DO_GIMBAL_MANAGER_CONFIGURE =
    1001u;
  static constexpr uint16_t VEHICLE_CMD_IMAGE_START_CAPTURE =
    2000u;
  static constexpr uint16_t VEHICLE_CMD_DO_TRIGGER_CONTROL =
    2003u;
  static constexpr uint16_t VEHICLE_CMD_VIDEO_START_CAPTURE =
    2500u;
  static constexpr uint16_t VEHICLE_CMD_VIDEO_STOP_CAPTURE =
    2501u;
  static constexpr uint16_t VEHICLE_CMD_LOGGING_START =
    2510u;
  static constexpr uint16_t VEHICLE_CMD_LOGGING_STOP =
    2511u;
  static constexpr uint16_t VEHICLE_CMD_CONTROL_HIGH_LATENCY =
    2600u;
  static constexpr uint16_t VEHICLE_CMD_DO_VTOL_TRANSITION =
    3000u;
  static constexpr uint16_t VEHICLE_CMD_ARM_AUTHORIZATION_REQUEST =
    3001u;
  static constexpr uint16_t VEHICLE_CMD_PAYLOAD_PREPARE_DEPLOY =
    30001u;
  static constexpr uint16_t VEHICLE_CMD_PAYLOAD_CONTROL_DEPLOY =
    30002u;
  static constexpr uint16_t VEHICLE_CMD_FIXED_MAG_CAL_YAW =
    42006u;
  static constexpr uint16_t VEHICLE_CMD_DO_WINCH =
    42600u;
  static constexpr uint32_t VEHICLE_CMD_PX4_INTERNAL_START =
    65537u;
  static constexpr uint32_t VEHICLE_CMD_SET_GPS_GLOBAL_ORIGIN =
    100000u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_RETRACT =
    0u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_NEUTRAL =
    1u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_MAVLINK_TARGETING =
    2u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_RC_TARGETING =
    3u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_GPS_POINT =
    4u;
  static constexpr uint8_t VEHICLE_MOUNT_MODE_ENUM_END =
    5u;
  static constexpr uint8_t VEHICLE_ROI_NONE =
    0u;
  static constexpr uint8_t VEHICLE_ROI_WPNEXT =
    1u;
  static constexpr uint8_t VEHICLE_ROI_WPINDEX =
    2u;
  static constexpr uint8_t VEHICLE_ROI_LOCATION =
    3u;
  static constexpr uint8_t VEHICLE_ROI_TARGET =
    4u;
  static constexpr uint8_t VEHICLE_ROI_ENUM_END =
    5u;
  static constexpr uint8_t PARACHUTE_ACTION_DISABLE =
    0u;
  static constexpr uint8_t PARACHUTE_ACTION_ENABLE =
    1u;
  static constexpr uint8_t PARACHUTE_ACTION_RELEASE =
    2u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_GYRO =
    0u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_ACCEL =
    1u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_MAG =
    2u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_BARO =
    3u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_GPS =
    4u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_OPTICAL_FLOW =
    5u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_VIO =
    6u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_DISTANCE_SENSOR =
    7u;
  static constexpr uint8_t FAILURE_UNIT_SENSOR_AIRSPEED =
    8u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_BATTERY =
    100u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_MOTOR =
    101u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_SERVO =
    102u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_AVOIDANCE =
    103u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_RC_SIGNAL =
    104u;
  static constexpr uint8_t FAILURE_UNIT_SYSTEM_MAVLINK_SIGNAL =
    105u;
  static constexpr uint8_t FAILURE_TYPE_OK =
    0u;
  static constexpr uint8_t FAILURE_TYPE_OFF =
    1u;
  static constexpr uint8_t FAILURE_TYPE_STUCK =
    2u;
  static constexpr uint8_t FAILURE_TYPE_GARBAGE =
    3u;
  static constexpr uint8_t FAILURE_TYPE_WRONG =
    4u;
  static constexpr uint8_t FAILURE_TYPE_SLOW =
    5u;
  static constexpr uint8_t FAILURE_TYPE_DELAYED =
    6u;
  static constexpr uint8_t FAILURE_TYPE_INTERMITTENT =
    7u;
  static constexpr uint8_t SPEED_TYPE_AIRSPEED =
    0u;
  static constexpr uint8_t SPEED_TYPE_GROUNDSPEED =
    1u;
  static constexpr uint8_t SPEED_TYPE_CLIMB_SPEED =
    2u;
  static constexpr uint8_t SPEED_TYPE_DESCEND_SPEED =
    3u;
  static constexpr int8_t ARMING_ACTION_DISARM =
    0;
  static constexpr int8_t ARMING_ACTION_ARM =
    1;
  static constexpr uint8_t GRIPPER_ACTION_RELEASE =
    0u;
  static constexpr uint8_t GRIPPER_ACTION_GRAB =
    1u;
  static constexpr uint8_t ORB_QUEUE_LENGTH =
    8u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::VehicleCommand_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::VehicleCommand_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleCommand_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleCommand_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__VehicleCommand
    std::shared_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__VehicleCommand
    std::shared_ptr<px4_msgs::msg::VehicleCommand_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleCommand_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->param1 != other.param1) {
      return false;
    }
    if (this->param2 != other.param2) {
      return false;
    }
    if (this->param3 != other.param3) {
      return false;
    }
    if (this->param4 != other.param4) {
      return false;
    }
    if (this->param5 != other.param5) {
      return false;
    }
    if (this->param6 != other.param6) {
      return false;
    }
    if (this->param7 != other.param7) {
      return false;
    }
    if (this->command != other.command) {
      return false;
    }
    if (this->target_system != other.target_system) {
      return false;
    }
    if (this->target_component != other.target_component) {
      return false;
    }
    if (this->source_system != other.source_system) {
      return false;
    }
    if (this->source_component != other.source_component) {
      return false;
    }
    if (this->confirmation != other.confirmation) {
      return false;
    }
    if (this->from_external != other.from_external) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleCommand_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleCommand_

// alias to use template instance with default allocator
using VehicleCommand =
  px4_msgs::msg::VehicleCommand_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CUSTOM_0;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CUSTOM_1;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CUSTOM_2;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_WAYPOINT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_LOITER_UNLIM;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_LOITER_TURNS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_LOITER_TIME;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_RETURN_TO_LAUNCH;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_LAND;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_TAKEOFF;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_PRECLAND;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_ORBIT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_ROI;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_PATHPLANNING;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_VTOL_TAKEOFF;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_VTOL_LAND;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_GUIDED_LIMITS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_GUIDED_MASTER;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_DELAY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_NAV_LAST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_DELAY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_CHANGE_ALT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_DISTANCE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_YAW;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_LAST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONDITION_GATE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_MODE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_JUMP;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_CHANGE_SPEED;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_HOME;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_PARAMETER;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_RELAY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_REPEAT_RELAY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_REPEAT_SERVO;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_FLIGHTTERMINATION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_CHANGE_ALTITUDE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_ACTUATOR;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_LAND_START;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GO_AROUND;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_REPOSITION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_PAUSE_CONTINUE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_ROI_LOCATION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_ROI_WPNEXT_OFFSET;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_ROI_NONE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_CONTROL_VIDEO;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_ROI;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_DIGICAM_CONTROL;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_MOUNT_CONFIGURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_MOUNT_CONTROL;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_CAM_TRIGG_DIST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_FENCE_ENABLE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_PARACHUTE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_MOTOR_TEST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_INVERTED_FLIGHT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GRIPPER;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_SET_CAM_TRIGG_INTERVAL;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_MOUNT_CONTROL_QUAT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GUIDED_MASTER;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GUIDED_LIMITS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_LAST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PREFLIGHT_CALIBRATION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::PREFLIGHT_CALIBRATION_TEMPERATURE_CALIBRATION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PREFLIGHT_SET_SENSOR_OFFSETS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PREFLIGHT_UAVCAN;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PREFLIGHT_STORAGE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PREFLIGHT_REBOOT_SHUTDOWN;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_OBLIQUE_SURVEY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_GIMBAL_DEVICE_INFORMATION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_MISSION_START;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_ACTUATOR_TEST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONFIGURE_ACTUATOR;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_COMPONENT_ARM_DISARM;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_RUN_PREARM_CHECKS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_INJECT_FAILURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_START_RX_PAIR;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_REQUEST_MESSAGE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_SET_CAMERA_MODE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_SET_CAMERA_ZOOM;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_SET_CAMERA_FOCUS;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GIMBAL_MANAGER_PITCHYAW;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_GIMBAL_MANAGER_CONFIGURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_IMAGE_START_CAPTURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_TRIGGER_CONTROL;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_VIDEO_START_CAPTURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_VIDEO_STOP_CAPTURE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_LOGGING_START;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_LOGGING_STOP;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_CONTROL_HIGH_LATENCY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_VTOL_TRANSITION;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_ARM_AUTHORIZATION_REQUEST;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PAYLOAD_PREPARE_DEPLOY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PAYLOAD_CONTROL_DEPLOY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_FIXED_MAG_CAL_YAW;
template<typename ContainerAllocator>
constexpr uint16_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_DO_WINCH;
template<typename ContainerAllocator>
constexpr uint32_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_PX4_INTERNAL_START;
template<typename ContainerAllocator>
constexpr uint32_t VehicleCommand_<ContainerAllocator>::VEHICLE_CMD_SET_GPS_GLOBAL_ORIGIN;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_RETRACT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_NEUTRAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_MAVLINK_TARGETING;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_RC_TARGETING;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_GPS_POINT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_MOUNT_MODE_ENUM_END;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_NONE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_WPNEXT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_WPINDEX;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_LOCATION;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_TARGET;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::VEHICLE_ROI_ENUM_END;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::PARACHUTE_ACTION_DISABLE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::PARACHUTE_ACTION_ENABLE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::PARACHUTE_ACTION_RELEASE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_GYRO;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_ACCEL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_MAG;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_BARO;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_GPS;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_OPTICAL_FLOW;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_VIO;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_DISTANCE_SENSOR;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SENSOR_AIRSPEED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_BATTERY;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_MOTOR;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_SERVO;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_AVOIDANCE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_RC_SIGNAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_UNIT_SYSTEM_MAVLINK_SIGNAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_OK;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_OFF;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_STUCK;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_GARBAGE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_WRONG;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_SLOW;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_DELAYED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::FAILURE_TYPE_INTERMITTENT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::SPEED_TYPE_AIRSPEED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::SPEED_TYPE_GROUNDSPEED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::SPEED_TYPE_CLIMB_SPEED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::SPEED_TYPE_DESCEND_SPEED;
template<typename ContainerAllocator>
constexpr int8_t VehicleCommand_<ContainerAllocator>::ARMING_ACTION_DISARM;
template<typename ContainerAllocator>
constexpr int8_t VehicleCommand_<ContainerAllocator>::ARMING_ACTION_ARM;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::GRIPPER_ACTION_RELEASE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::GRIPPER_ACTION_GRAB;
template<typename ContainerAllocator>
constexpr uint8_t VehicleCommand_<ContainerAllocator>::ORB_QUEUE_LENGTH;

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_COMMAND__STRUCT_HPP_

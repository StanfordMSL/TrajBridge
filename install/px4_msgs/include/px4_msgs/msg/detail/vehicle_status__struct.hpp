// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from px4_msgs:msg/VehicleStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_HPP_
#define PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__px4_msgs__msg__VehicleStatus __attribute__((deprecated))
#else
# define DEPRECATED__px4_msgs__msg__VehicleStatus __declspec(deprecated)
#endif

namespace px4_msgs
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct VehicleStatus_
{
  using Type = VehicleStatus_<ContainerAllocator>;

  explicit VehicleStatus_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->armed_time = 0ull;
      this->takeoff_time = 0ull;
      this->arming_state = 0;
      this->latest_arming_reason = 0;
      this->latest_disarming_reason = 0;
      this->nav_state_timestamp = 0ull;
      this->nav_state_user_intention = 0;
      this->nav_state = 0;
      this->failure_detector_status = 0;
      this->hil_state = 0;
      this->vehicle_type = 0;
      this->failsafe = false;
      this->failsafe_and_user_took_over = false;
      this->gcs_connection_lost = false;
      this->gcs_connection_lost_counter = 0;
      this->high_latency_data_link_lost = false;
      this->is_vtol = false;
      this->is_vtol_tailsitter = false;
      this->in_transition_mode = false;
      this->in_transition_to_fw = false;
      this->system_type = 0;
      this->system_id = 0;
      this->component_id = 0;
      this->safety_button_available = false;
      this->safety_off = false;
      this->power_input_valid = false;
      this->usb_connected = false;
      this->open_drone_id_system_present = false;
      this->open_drone_id_system_healthy = false;
      this->parachute_system_present = false;
      this->parachute_system_healthy = false;
      this->avoidance_system_required = false;
      this->avoidance_system_valid = false;
      this->rc_calibration_in_progress = false;
      this->calibration_enabled = false;
      this->pre_flight_checks_pass = false;
    }
  }

  explicit VehicleStatus_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->timestamp = 0ull;
      this->armed_time = 0ull;
      this->takeoff_time = 0ull;
      this->arming_state = 0;
      this->latest_arming_reason = 0;
      this->latest_disarming_reason = 0;
      this->nav_state_timestamp = 0ull;
      this->nav_state_user_intention = 0;
      this->nav_state = 0;
      this->failure_detector_status = 0;
      this->hil_state = 0;
      this->vehicle_type = 0;
      this->failsafe = false;
      this->failsafe_and_user_took_over = false;
      this->gcs_connection_lost = false;
      this->gcs_connection_lost_counter = 0;
      this->high_latency_data_link_lost = false;
      this->is_vtol = false;
      this->is_vtol_tailsitter = false;
      this->in_transition_mode = false;
      this->in_transition_to_fw = false;
      this->system_type = 0;
      this->system_id = 0;
      this->component_id = 0;
      this->safety_button_available = false;
      this->safety_off = false;
      this->power_input_valid = false;
      this->usb_connected = false;
      this->open_drone_id_system_present = false;
      this->open_drone_id_system_healthy = false;
      this->parachute_system_present = false;
      this->parachute_system_healthy = false;
      this->avoidance_system_required = false;
      this->avoidance_system_valid = false;
      this->rc_calibration_in_progress = false;
      this->calibration_enabled = false;
      this->pre_flight_checks_pass = false;
    }
  }

  // field types and members
  using _timestamp_type =
    uint64_t;
  _timestamp_type timestamp;
  using _armed_time_type =
    uint64_t;
  _armed_time_type armed_time;
  using _takeoff_time_type =
    uint64_t;
  _takeoff_time_type takeoff_time;
  using _arming_state_type =
    uint8_t;
  _arming_state_type arming_state;
  using _latest_arming_reason_type =
    uint8_t;
  _latest_arming_reason_type latest_arming_reason;
  using _latest_disarming_reason_type =
    uint8_t;
  _latest_disarming_reason_type latest_disarming_reason;
  using _nav_state_timestamp_type =
    uint64_t;
  _nav_state_timestamp_type nav_state_timestamp;
  using _nav_state_user_intention_type =
    uint8_t;
  _nav_state_user_intention_type nav_state_user_intention;
  using _nav_state_type =
    uint8_t;
  _nav_state_type nav_state;
  using _failure_detector_status_type =
    uint16_t;
  _failure_detector_status_type failure_detector_status;
  using _hil_state_type =
    uint8_t;
  _hil_state_type hil_state;
  using _vehicle_type_type =
    uint8_t;
  _vehicle_type_type vehicle_type;
  using _failsafe_type =
    bool;
  _failsafe_type failsafe;
  using _failsafe_and_user_took_over_type =
    bool;
  _failsafe_and_user_took_over_type failsafe_and_user_took_over;
  using _gcs_connection_lost_type =
    bool;
  _gcs_connection_lost_type gcs_connection_lost;
  using _gcs_connection_lost_counter_type =
    uint8_t;
  _gcs_connection_lost_counter_type gcs_connection_lost_counter;
  using _high_latency_data_link_lost_type =
    bool;
  _high_latency_data_link_lost_type high_latency_data_link_lost;
  using _is_vtol_type =
    bool;
  _is_vtol_type is_vtol;
  using _is_vtol_tailsitter_type =
    bool;
  _is_vtol_tailsitter_type is_vtol_tailsitter;
  using _in_transition_mode_type =
    bool;
  _in_transition_mode_type in_transition_mode;
  using _in_transition_to_fw_type =
    bool;
  _in_transition_to_fw_type in_transition_to_fw;
  using _system_type_type =
    uint8_t;
  _system_type_type system_type;
  using _system_id_type =
    uint8_t;
  _system_id_type system_id;
  using _component_id_type =
    uint8_t;
  _component_id_type component_id;
  using _safety_button_available_type =
    bool;
  _safety_button_available_type safety_button_available;
  using _safety_off_type =
    bool;
  _safety_off_type safety_off;
  using _power_input_valid_type =
    bool;
  _power_input_valid_type power_input_valid;
  using _usb_connected_type =
    bool;
  _usb_connected_type usb_connected;
  using _open_drone_id_system_present_type =
    bool;
  _open_drone_id_system_present_type open_drone_id_system_present;
  using _open_drone_id_system_healthy_type =
    bool;
  _open_drone_id_system_healthy_type open_drone_id_system_healthy;
  using _parachute_system_present_type =
    bool;
  _parachute_system_present_type parachute_system_present;
  using _parachute_system_healthy_type =
    bool;
  _parachute_system_healthy_type parachute_system_healthy;
  using _avoidance_system_required_type =
    bool;
  _avoidance_system_required_type avoidance_system_required;
  using _avoidance_system_valid_type =
    bool;
  _avoidance_system_valid_type avoidance_system_valid;
  using _rc_calibration_in_progress_type =
    bool;
  _rc_calibration_in_progress_type rc_calibration_in_progress;
  using _calibration_enabled_type =
    bool;
  _calibration_enabled_type calibration_enabled;
  using _pre_flight_checks_pass_type =
    bool;
  _pre_flight_checks_pass_type pre_flight_checks_pass;

  // setters for named parameter idiom
  Type & set__timestamp(
    const uint64_t & _arg)
  {
    this->timestamp = _arg;
    return *this;
  }
  Type & set__armed_time(
    const uint64_t & _arg)
  {
    this->armed_time = _arg;
    return *this;
  }
  Type & set__takeoff_time(
    const uint64_t & _arg)
  {
    this->takeoff_time = _arg;
    return *this;
  }
  Type & set__arming_state(
    const uint8_t & _arg)
  {
    this->arming_state = _arg;
    return *this;
  }
  Type & set__latest_arming_reason(
    const uint8_t & _arg)
  {
    this->latest_arming_reason = _arg;
    return *this;
  }
  Type & set__latest_disarming_reason(
    const uint8_t & _arg)
  {
    this->latest_disarming_reason = _arg;
    return *this;
  }
  Type & set__nav_state_timestamp(
    const uint64_t & _arg)
  {
    this->nav_state_timestamp = _arg;
    return *this;
  }
  Type & set__nav_state_user_intention(
    const uint8_t & _arg)
  {
    this->nav_state_user_intention = _arg;
    return *this;
  }
  Type & set__nav_state(
    const uint8_t & _arg)
  {
    this->nav_state = _arg;
    return *this;
  }
  Type & set__failure_detector_status(
    const uint16_t & _arg)
  {
    this->failure_detector_status = _arg;
    return *this;
  }
  Type & set__hil_state(
    const uint8_t & _arg)
  {
    this->hil_state = _arg;
    return *this;
  }
  Type & set__vehicle_type(
    const uint8_t & _arg)
  {
    this->vehicle_type = _arg;
    return *this;
  }
  Type & set__failsafe(
    const bool & _arg)
  {
    this->failsafe = _arg;
    return *this;
  }
  Type & set__failsafe_and_user_took_over(
    const bool & _arg)
  {
    this->failsafe_and_user_took_over = _arg;
    return *this;
  }
  Type & set__gcs_connection_lost(
    const bool & _arg)
  {
    this->gcs_connection_lost = _arg;
    return *this;
  }
  Type & set__gcs_connection_lost_counter(
    const uint8_t & _arg)
  {
    this->gcs_connection_lost_counter = _arg;
    return *this;
  }
  Type & set__high_latency_data_link_lost(
    const bool & _arg)
  {
    this->high_latency_data_link_lost = _arg;
    return *this;
  }
  Type & set__is_vtol(
    const bool & _arg)
  {
    this->is_vtol = _arg;
    return *this;
  }
  Type & set__is_vtol_tailsitter(
    const bool & _arg)
  {
    this->is_vtol_tailsitter = _arg;
    return *this;
  }
  Type & set__in_transition_mode(
    const bool & _arg)
  {
    this->in_transition_mode = _arg;
    return *this;
  }
  Type & set__in_transition_to_fw(
    const bool & _arg)
  {
    this->in_transition_to_fw = _arg;
    return *this;
  }
  Type & set__system_type(
    const uint8_t & _arg)
  {
    this->system_type = _arg;
    return *this;
  }
  Type & set__system_id(
    const uint8_t & _arg)
  {
    this->system_id = _arg;
    return *this;
  }
  Type & set__component_id(
    const uint8_t & _arg)
  {
    this->component_id = _arg;
    return *this;
  }
  Type & set__safety_button_available(
    const bool & _arg)
  {
    this->safety_button_available = _arg;
    return *this;
  }
  Type & set__safety_off(
    const bool & _arg)
  {
    this->safety_off = _arg;
    return *this;
  }
  Type & set__power_input_valid(
    const bool & _arg)
  {
    this->power_input_valid = _arg;
    return *this;
  }
  Type & set__usb_connected(
    const bool & _arg)
  {
    this->usb_connected = _arg;
    return *this;
  }
  Type & set__open_drone_id_system_present(
    const bool & _arg)
  {
    this->open_drone_id_system_present = _arg;
    return *this;
  }
  Type & set__open_drone_id_system_healthy(
    const bool & _arg)
  {
    this->open_drone_id_system_healthy = _arg;
    return *this;
  }
  Type & set__parachute_system_present(
    const bool & _arg)
  {
    this->parachute_system_present = _arg;
    return *this;
  }
  Type & set__parachute_system_healthy(
    const bool & _arg)
  {
    this->parachute_system_healthy = _arg;
    return *this;
  }
  Type & set__avoidance_system_required(
    const bool & _arg)
  {
    this->avoidance_system_required = _arg;
    return *this;
  }
  Type & set__avoidance_system_valid(
    const bool & _arg)
  {
    this->avoidance_system_valid = _arg;
    return *this;
  }
  Type & set__rc_calibration_in_progress(
    const bool & _arg)
  {
    this->rc_calibration_in_progress = _arg;
    return *this;
  }
  Type & set__calibration_enabled(
    const bool & _arg)
  {
    this->calibration_enabled = _arg;
    return *this;
  }
  Type & set__pre_flight_checks_pass(
    const bool & _arg)
  {
    this->pre_flight_checks_pass = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t ARMING_STATE_INIT =
    0u;
  static constexpr uint8_t ARMING_STATE_STANDBY =
    1u;
  static constexpr uint8_t ARMING_STATE_ARMED =
    2u;
  static constexpr uint8_t ARMING_STATE_STANDBY_ERROR =
    3u;
  static constexpr uint8_t ARMING_STATE_SHUTDOWN =
    4u;
  static constexpr uint8_t ARMING_STATE_IN_AIR_RESTORE =
    5u;
  static constexpr uint8_t ARMING_STATE_MAX =
    6u;
  static constexpr uint8_t ARM_DISARM_REASON_TRANSITION_TO_STANDBY =
    0u;
  static constexpr uint8_t ARM_DISARM_REASON_RC_STICK =
    1u;
  static constexpr uint8_t ARM_DISARM_REASON_RC_SWITCH =
    2u;
  static constexpr uint8_t ARM_DISARM_REASON_COMMAND_INTERNAL =
    3u;
  static constexpr uint8_t ARM_DISARM_REASON_COMMAND_EXTERNAL =
    4u;
  static constexpr uint8_t ARM_DISARM_REASON_MISSION_START =
    5u;
  static constexpr uint8_t ARM_DISARM_REASON_SAFETY_BUTTON =
    6u;
  static constexpr uint8_t ARM_DISARM_REASON_AUTO_DISARM_LAND =
    7u;
  static constexpr uint8_t ARM_DISARM_REASON_AUTO_DISARM_PREFLIGHT =
    8u;
  static constexpr uint8_t ARM_DISARM_REASON_KILL_SWITCH =
    9u;
  static constexpr uint8_t ARM_DISARM_REASON_LOCKDOWN =
    10u;
  static constexpr uint8_t ARM_DISARM_REASON_FAILURE_DETECTOR =
    11u;
  static constexpr uint8_t ARM_DISARM_REASON_SHUTDOWN =
    12u;
  static constexpr uint8_t ARM_DISARM_REASON_UNIT_TEST =
    13u;
  static constexpr uint8_t NAVIGATION_STATE_MANUAL =
    0u;
  static constexpr uint8_t NAVIGATION_STATE_ALTCTL =
    1u;
  static constexpr uint8_t NAVIGATION_STATE_POSCTL =
    2u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_MISSION =
    3u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_LOITER =
    4u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_RTL =
    5u;
  static constexpr uint8_t NAVIGATION_STATE_UNUSED3 =
    8u;
  static constexpr uint8_t NAVIGATION_STATE_UNUSED =
    9u;
  static constexpr uint8_t NAVIGATION_STATE_ACRO =
    10u;
  static constexpr uint8_t NAVIGATION_STATE_UNUSED1 =
    11u;
  static constexpr uint8_t NAVIGATION_STATE_DESCEND =
    12u;
  static constexpr uint8_t NAVIGATION_STATE_TERMINATION =
    13u;
  static constexpr uint8_t NAVIGATION_STATE_OFFBOARD =
    14u;
  static constexpr uint8_t NAVIGATION_STATE_STAB =
    15u;
  static constexpr uint8_t NAVIGATION_STATE_UNUSED2 =
    16u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_TAKEOFF =
    17u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_LAND =
    18u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_FOLLOW_TARGET =
    19u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_PRECLAND =
    20u;
  static constexpr uint8_t NAVIGATION_STATE_ORBIT =
    21u;
  static constexpr uint8_t NAVIGATION_STATE_AUTO_VTOL_TAKEOFF =
    22u;
  static constexpr uint8_t NAVIGATION_STATE_MAX =
    23u;
  static constexpr uint16_t FAILURE_NONE =
    0u;
  static constexpr uint16_t FAILURE_ROLL =
    1u;
  static constexpr uint16_t FAILURE_PITCH =
    2u;
  static constexpr uint16_t FAILURE_ALT =
    4u;
  static constexpr uint16_t FAILURE_EXT =
    8u;
  static constexpr uint16_t FAILURE_ARM_ESC =
    16u;
  static constexpr uint16_t FAILURE_BATTERY =
    32u;
  static constexpr uint16_t FAILURE_IMBALANCED_PROP =
    64u;
  static constexpr uint16_t FAILURE_MOTOR =
    128u;
  static constexpr uint8_t HIL_STATE_OFF =
    0u;
  static constexpr uint8_t HIL_STATE_ON =
    1u;
  static constexpr uint8_t VEHICLE_TYPE_UNKNOWN =
    0u;
  static constexpr uint8_t VEHICLE_TYPE_ROTARY_WING =
    1u;
  static constexpr uint8_t VEHICLE_TYPE_FIXED_WING =
    2u;
  static constexpr uint8_t VEHICLE_TYPE_ROVER =
    3u;
  static constexpr uint8_t VEHICLE_TYPE_AIRSHIP =
    4u;

  // pointer types
  using RawPtr =
    px4_msgs::msg::VehicleStatus_<ContainerAllocator> *;
  using ConstRawPtr =
    const px4_msgs::msg::VehicleStatus_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleStatus_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      px4_msgs::msg::VehicleStatus_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__px4_msgs__msg__VehicleStatus
    std::shared_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__px4_msgs__msg__VehicleStatus
    std::shared_ptr<px4_msgs::msg::VehicleStatus_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const VehicleStatus_ & other) const
  {
    if (this->timestamp != other.timestamp) {
      return false;
    }
    if (this->armed_time != other.armed_time) {
      return false;
    }
    if (this->takeoff_time != other.takeoff_time) {
      return false;
    }
    if (this->arming_state != other.arming_state) {
      return false;
    }
    if (this->latest_arming_reason != other.latest_arming_reason) {
      return false;
    }
    if (this->latest_disarming_reason != other.latest_disarming_reason) {
      return false;
    }
    if (this->nav_state_timestamp != other.nav_state_timestamp) {
      return false;
    }
    if (this->nav_state_user_intention != other.nav_state_user_intention) {
      return false;
    }
    if (this->nav_state != other.nav_state) {
      return false;
    }
    if (this->failure_detector_status != other.failure_detector_status) {
      return false;
    }
    if (this->hil_state != other.hil_state) {
      return false;
    }
    if (this->vehicle_type != other.vehicle_type) {
      return false;
    }
    if (this->failsafe != other.failsafe) {
      return false;
    }
    if (this->failsafe_and_user_took_over != other.failsafe_and_user_took_over) {
      return false;
    }
    if (this->gcs_connection_lost != other.gcs_connection_lost) {
      return false;
    }
    if (this->gcs_connection_lost_counter != other.gcs_connection_lost_counter) {
      return false;
    }
    if (this->high_latency_data_link_lost != other.high_latency_data_link_lost) {
      return false;
    }
    if (this->is_vtol != other.is_vtol) {
      return false;
    }
    if (this->is_vtol_tailsitter != other.is_vtol_tailsitter) {
      return false;
    }
    if (this->in_transition_mode != other.in_transition_mode) {
      return false;
    }
    if (this->in_transition_to_fw != other.in_transition_to_fw) {
      return false;
    }
    if (this->system_type != other.system_type) {
      return false;
    }
    if (this->system_id != other.system_id) {
      return false;
    }
    if (this->component_id != other.component_id) {
      return false;
    }
    if (this->safety_button_available != other.safety_button_available) {
      return false;
    }
    if (this->safety_off != other.safety_off) {
      return false;
    }
    if (this->power_input_valid != other.power_input_valid) {
      return false;
    }
    if (this->usb_connected != other.usb_connected) {
      return false;
    }
    if (this->open_drone_id_system_present != other.open_drone_id_system_present) {
      return false;
    }
    if (this->open_drone_id_system_healthy != other.open_drone_id_system_healthy) {
      return false;
    }
    if (this->parachute_system_present != other.parachute_system_present) {
      return false;
    }
    if (this->parachute_system_healthy != other.parachute_system_healthy) {
      return false;
    }
    if (this->avoidance_system_required != other.avoidance_system_required) {
      return false;
    }
    if (this->avoidance_system_valid != other.avoidance_system_valid) {
      return false;
    }
    if (this->rc_calibration_in_progress != other.rc_calibration_in_progress) {
      return false;
    }
    if (this->calibration_enabled != other.calibration_enabled) {
      return false;
    }
    if (this->pre_flight_checks_pass != other.pre_flight_checks_pass) {
      return false;
    }
    return true;
  }
  bool operator!=(const VehicleStatus_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct VehicleStatus_

// alias to use template instance with default allocator
using VehicleStatus =
  px4_msgs::msg::VehicleStatus_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_INIT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_STANDBY;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_ARMED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_STANDBY_ERROR;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_SHUTDOWN;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_IN_AIR_RESTORE;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARMING_STATE_MAX;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_TRANSITION_TO_STANDBY;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_RC_STICK;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_RC_SWITCH;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_COMMAND_INTERNAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_COMMAND_EXTERNAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_MISSION_START;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_SAFETY_BUTTON;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_AUTO_DISARM_LAND;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_AUTO_DISARM_PREFLIGHT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_KILL_SWITCH;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_LOCKDOWN;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_FAILURE_DETECTOR;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_SHUTDOWN;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::ARM_DISARM_REASON_UNIT_TEST;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_MANUAL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_ALTCTL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_POSCTL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_MISSION;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_LOITER;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_RTL;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_UNUSED3;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_UNUSED;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_ACRO;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_UNUSED1;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_DESCEND;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_TERMINATION;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_OFFBOARD;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_STAB;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_UNUSED2;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_TAKEOFF;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_LAND;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_FOLLOW_TARGET;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_PRECLAND;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_ORBIT;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_AUTO_VTOL_TAKEOFF;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::NAVIGATION_STATE_MAX;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_NONE;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_ROLL;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_PITCH;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_ALT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_EXT;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_ARM_ESC;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_BATTERY;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_IMBALANCED_PROP;
template<typename ContainerAllocator>
constexpr uint16_t VehicleStatus_<ContainerAllocator>::FAILURE_MOTOR;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::HIL_STATE_OFF;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::HIL_STATE_ON;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::VEHICLE_TYPE_UNKNOWN;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::VEHICLE_TYPE_ROTARY_WING;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::VEHICLE_TYPE_FIXED_WING;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::VEHICLE_TYPE_ROVER;
template<typename ContainerAllocator>
constexpr uint8_t VehicleStatus_<ContainerAllocator>::VEHICLE_TYPE_AIRSHIP;

}  // namespace msg

}  // namespace px4_msgs

#endif  // PX4_MSGS__MSG__DETAIL__VEHICLE_STATUS__STRUCT_HPP_

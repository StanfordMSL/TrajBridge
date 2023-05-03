// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/CellularStatus.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__CELLULAR_STATUS__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__CELLULAR_STATUS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'CELLULAR_STATUS_FLAG_UNKNOWN'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_UNKNOWN = 0
};

/// Constant 'CELLULAR_STATUS_FLAG_FAILED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_FAILED = 1
};

/// Constant 'CELLULAR_STATUS_FLAG_INITIALIZING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_INITIALIZING = 2
};

/// Constant 'CELLULAR_STATUS_FLAG_LOCKED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_LOCKED = 3
};

/// Constant 'CELLULAR_STATUS_FLAG_DISABLED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_DISABLED = 4
};

/// Constant 'CELLULAR_STATUS_FLAG_DISABLING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_DISABLING = 5
};

/// Constant 'CELLULAR_STATUS_FLAG_ENABLING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_ENABLING = 6
};

/// Constant 'CELLULAR_STATUS_FLAG_ENABLED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_ENABLED = 7
};

/// Constant 'CELLULAR_STATUS_FLAG_SEARCHING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_SEARCHING = 8
};

/// Constant 'CELLULAR_STATUS_FLAG_REGISTERED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_REGISTERED = 9
};

/// Constant 'CELLULAR_STATUS_FLAG_DISCONNECTING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_DISCONNECTING = 10
};

/// Constant 'CELLULAR_STATUS_FLAG_CONNECTING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_CONNECTING = 11
};

/// Constant 'CELLULAR_STATUS_FLAG_CONNECTED'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_STATUS_FLAG_CONNECTED = 12
};

/// Constant 'CELLULAR_NETWORK_FAILED_REASON_NONE'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_NETWORK_FAILED_REASON_NONE = 0
};

/// Constant 'CELLULAR_NETWORK_FAILED_REASON_UNKNOWN'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_NETWORK_FAILED_REASON_UNKNOWN = 1
};

/// Constant 'CELLULAR_NETWORK_FAILED_REASON_SIM_MISSING'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_NETWORK_FAILED_REASON_SIM_MISSING = 2
};

/// Constant 'CELLULAR_NETWORK_FAILED_REASON_SIM_ERROR'.
enum
{
  px4_msgs__msg__CellularStatus__CELLULAR_NETWORK_FAILED_REASON_SIM_ERROR = 3
};

// Struct defined in msg/CellularStatus in the package px4_msgs.
typedef struct px4_msgs__msg__CellularStatus
{
  uint64_t timestamp;
  uint16_t status;
  uint8_t failure_reason;
  uint8_t type;
  uint8_t quality;
  uint16_t mcc;
  uint16_t mnc;
  uint16_t lac;
} px4_msgs__msg__CellularStatus;

// Struct for a sequence of px4_msgs__msg__CellularStatus.
typedef struct px4_msgs__msg__CellularStatus__Sequence
{
  px4_msgs__msg__CellularStatus * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__CellularStatus__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__CELLULAR_STATUS__STRUCT_H_

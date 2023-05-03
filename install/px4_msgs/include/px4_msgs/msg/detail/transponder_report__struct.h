// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from px4_msgs:msg/TransponderReport.idl
// generated code does not contain a copyright notice

#ifndef PX4_MSGS__MSG__DETAIL__TRANSPONDER_REPORT__STRUCT_H_
#define PX4_MSGS__MSG__DETAIL__TRANSPONDER_REPORT__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'PX4_ADSB_FLAGS_VALID_COORDS'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_COORDS = 1
};

/// Constant 'PX4_ADSB_FLAGS_VALID_ALTITUDE'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_ALTITUDE = 2
};

/// Constant 'PX4_ADSB_FLAGS_VALID_HEADING'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_HEADING = 4
};

/// Constant 'PX4_ADSB_FLAGS_VALID_VELOCITY'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_VELOCITY = 8
};

/// Constant 'PX4_ADSB_FLAGS_VALID_CALLSIGN'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_CALLSIGN = 16
};

/// Constant 'PX4_ADSB_FLAGS_VALID_SQUAWK'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_VALID_SQUAWK = 32
};

/// Constant 'PX4_ADSB_FLAGS_RETRANSLATE'.
enum
{
  px4_msgs__msg__TransponderReport__PX4_ADSB_FLAGS_RETRANSLATE = 256
};

/// Constant 'ADSB_EMITTER_TYPE_NO_INFO'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_NO_INFO = 0
};

/// Constant 'ADSB_EMITTER_TYPE_LIGHT'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_LIGHT = 1
};

/// Constant 'ADSB_EMITTER_TYPE_SMALL'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_SMALL = 2
};

/// Constant 'ADSB_EMITTER_TYPE_LARGE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_LARGE = 3
};

/// Constant 'ADSB_EMITTER_TYPE_HIGH_VORTEX_LARGE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_HIGH_VORTEX_LARGE = 4
};

/// Constant 'ADSB_EMITTER_TYPE_HEAVY'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_HEAVY = 5
};

/// Constant 'ADSB_EMITTER_TYPE_HIGHLY_MANUV'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_HIGHLY_MANUV = 6
};

/// Constant 'ADSB_EMITTER_TYPE_ROTOCRAFT'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_ROTOCRAFT = 7
};

/// Constant 'ADSB_EMITTER_TYPE_UNASSIGNED'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_UNASSIGNED = 8
};

/// Constant 'ADSB_EMITTER_TYPE_GLIDER'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_GLIDER = 9
};

/// Constant 'ADSB_EMITTER_TYPE_LIGHTER_AIR'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_LIGHTER_AIR = 10
};

/// Constant 'ADSB_EMITTER_TYPE_PARACHUTE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_PARACHUTE = 11
};

/// Constant 'ADSB_EMITTER_TYPE_ULTRA_LIGHT'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_ULTRA_LIGHT = 12
};

/// Constant 'ADSB_EMITTER_TYPE_UNASSIGNED2'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_UNASSIGNED2 = 13
};

/// Constant 'ADSB_EMITTER_TYPE_UAV'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_UAV = 14
};

/// Constant 'ADSB_EMITTER_TYPE_SPACE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_SPACE = 15
};

/// Constant 'ADSB_EMITTER_TYPE_UNASSGINED3'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_UNASSGINED3 = 16
};

/// Constant 'ADSB_EMITTER_TYPE_EMERGENCY_SURFACE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_EMERGENCY_SURFACE = 17
};

/// Constant 'ADSB_EMITTER_TYPE_SERVICE_SURFACE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_SERVICE_SURFACE = 18
};

/// Constant 'ADSB_EMITTER_TYPE_POINT_OBSTACLE'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_POINT_OBSTACLE = 19
};

/// Constant 'ADSB_EMITTER_TYPE_ENUM_END'.
enum
{
  px4_msgs__msg__TransponderReport__ADSB_EMITTER_TYPE_ENUM_END = 20
};

/// Constant 'ORB_QUEUE_LENGTH'.
enum
{
  px4_msgs__msg__TransponderReport__ORB_QUEUE_LENGTH = 8
};

// Struct defined in msg/TransponderReport in the package px4_msgs.
typedef struct px4_msgs__msg__TransponderReport
{
  uint64_t timestamp;
  uint32_t icao_address;
  double lat;
  double lon;
  uint8_t altitude_type;
  float altitude;
  float heading;
  float hor_velocity;
  float ver_velocity;
  uint8_t callsign[9];
  uint8_t emitter_type;
  uint8_t tslc;
  uint16_t flags;
  uint16_t squawk;
  uint8_t uas_id[18];
} px4_msgs__msg__TransponderReport;

// Struct for a sequence of px4_msgs__msg__TransponderReport.
typedef struct px4_msgs__msg__TransponderReport__Sequence
{
  px4_msgs__msg__TransponderReport * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} px4_msgs__msg__TransponderReport__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // PX4_MSGS__MSG__DETAIL__TRANSPONDER_REPORT__STRUCT_H_

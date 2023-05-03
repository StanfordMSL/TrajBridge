// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/SensorGps.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/sensor_gps__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__SensorGps__init(px4_msgs__msg__SensorGps * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // lat
  // lon
  // alt
  // alt_ellipsoid
  // s_variance_m_s
  // c_variance_rad
  // fix_type
  // eph
  // epv
  // hdop
  // vdop
  // noise_per_ms
  // automatic_gain_control
  // jamming_state
  // jamming_indicator
  // spoofing_state
  // vel_m_s
  // vel_n_m_s
  // vel_e_m_s
  // vel_d_m_s
  // cog_rad
  // vel_ned_valid
  // timestamp_time_relative
  // time_utc_usec
  // satellites_used
  // heading
  // heading_offset
  // heading_accuracy
  // rtcm_injection_rate
  // selected_rtcm_instance
  return true;
}

void
px4_msgs__msg__SensorGps__fini(px4_msgs__msg__SensorGps * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // timestamp_sample
  // device_id
  // lat
  // lon
  // alt
  // alt_ellipsoid
  // s_variance_m_s
  // c_variance_rad
  // fix_type
  // eph
  // epv
  // hdop
  // vdop
  // noise_per_ms
  // automatic_gain_control
  // jamming_state
  // jamming_indicator
  // spoofing_state
  // vel_m_s
  // vel_n_m_s
  // vel_e_m_s
  // vel_d_m_s
  // cog_rad
  // vel_ned_valid
  // timestamp_time_relative
  // time_utc_usec
  // satellites_used
  // heading
  // heading_offset
  // heading_accuracy
  // rtcm_injection_rate
  // selected_rtcm_instance
}

bool
px4_msgs__msg__SensorGps__are_equal(const px4_msgs__msg__SensorGps * lhs, const px4_msgs__msg__SensorGps * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // timestamp_sample
  if (lhs->timestamp_sample != rhs->timestamp_sample) {
    return false;
  }
  // device_id
  if (lhs->device_id != rhs->device_id) {
    return false;
  }
  // lat
  if (lhs->lat != rhs->lat) {
    return false;
  }
  // lon
  if (lhs->lon != rhs->lon) {
    return false;
  }
  // alt
  if (lhs->alt != rhs->alt) {
    return false;
  }
  // alt_ellipsoid
  if (lhs->alt_ellipsoid != rhs->alt_ellipsoid) {
    return false;
  }
  // s_variance_m_s
  if (lhs->s_variance_m_s != rhs->s_variance_m_s) {
    return false;
  }
  // c_variance_rad
  if (lhs->c_variance_rad != rhs->c_variance_rad) {
    return false;
  }
  // fix_type
  if (lhs->fix_type != rhs->fix_type) {
    return false;
  }
  // eph
  if (lhs->eph != rhs->eph) {
    return false;
  }
  // epv
  if (lhs->epv != rhs->epv) {
    return false;
  }
  // hdop
  if (lhs->hdop != rhs->hdop) {
    return false;
  }
  // vdop
  if (lhs->vdop != rhs->vdop) {
    return false;
  }
  // noise_per_ms
  if (lhs->noise_per_ms != rhs->noise_per_ms) {
    return false;
  }
  // automatic_gain_control
  if (lhs->automatic_gain_control != rhs->automatic_gain_control) {
    return false;
  }
  // jamming_state
  if (lhs->jamming_state != rhs->jamming_state) {
    return false;
  }
  // jamming_indicator
  if (lhs->jamming_indicator != rhs->jamming_indicator) {
    return false;
  }
  // spoofing_state
  if (lhs->spoofing_state != rhs->spoofing_state) {
    return false;
  }
  // vel_m_s
  if (lhs->vel_m_s != rhs->vel_m_s) {
    return false;
  }
  // vel_n_m_s
  if (lhs->vel_n_m_s != rhs->vel_n_m_s) {
    return false;
  }
  // vel_e_m_s
  if (lhs->vel_e_m_s != rhs->vel_e_m_s) {
    return false;
  }
  // vel_d_m_s
  if (lhs->vel_d_m_s != rhs->vel_d_m_s) {
    return false;
  }
  // cog_rad
  if (lhs->cog_rad != rhs->cog_rad) {
    return false;
  }
  // vel_ned_valid
  if (lhs->vel_ned_valid != rhs->vel_ned_valid) {
    return false;
  }
  // timestamp_time_relative
  if (lhs->timestamp_time_relative != rhs->timestamp_time_relative) {
    return false;
  }
  // time_utc_usec
  if (lhs->time_utc_usec != rhs->time_utc_usec) {
    return false;
  }
  // satellites_used
  if (lhs->satellites_used != rhs->satellites_used) {
    return false;
  }
  // heading
  if (lhs->heading != rhs->heading) {
    return false;
  }
  // heading_offset
  if (lhs->heading_offset != rhs->heading_offset) {
    return false;
  }
  // heading_accuracy
  if (lhs->heading_accuracy != rhs->heading_accuracy) {
    return false;
  }
  // rtcm_injection_rate
  if (lhs->rtcm_injection_rate != rhs->rtcm_injection_rate) {
    return false;
  }
  // selected_rtcm_instance
  if (lhs->selected_rtcm_instance != rhs->selected_rtcm_instance) {
    return false;
  }
  return true;
}

bool
px4_msgs__msg__SensorGps__copy(
  const px4_msgs__msg__SensorGps * input,
  px4_msgs__msg__SensorGps * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // timestamp_sample
  output->timestamp_sample = input->timestamp_sample;
  // device_id
  output->device_id = input->device_id;
  // lat
  output->lat = input->lat;
  // lon
  output->lon = input->lon;
  // alt
  output->alt = input->alt;
  // alt_ellipsoid
  output->alt_ellipsoid = input->alt_ellipsoid;
  // s_variance_m_s
  output->s_variance_m_s = input->s_variance_m_s;
  // c_variance_rad
  output->c_variance_rad = input->c_variance_rad;
  // fix_type
  output->fix_type = input->fix_type;
  // eph
  output->eph = input->eph;
  // epv
  output->epv = input->epv;
  // hdop
  output->hdop = input->hdop;
  // vdop
  output->vdop = input->vdop;
  // noise_per_ms
  output->noise_per_ms = input->noise_per_ms;
  // automatic_gain_control
  output->automatic_gain_control = input->automatic_gain_control;
  // jamming_state
  output->jamming_state = input->jamming_state;
  // jamming_indicator
  output->jamming_indicator = input->jamming_indicator;
  // spoofing_state
  output->spoofing_state = input->spoofing_state;
  // vel_m_s
  output->vel_m_s = input->vel_m_s;
  // vel_n_m_s
  output->vel_n_m_s = input->vel_n_m_s;
  // vel_e_m_s
  output->vel_e_m_s = input->vel_e_m_s;
  // vel_d_m_s
  output->vel_d_m_s = input->vel_d_m_s;
  // cog_rad
  output->cog_rad = input->cog_rad;
  // vel_ned_valid
  output->vel_ned_valid = input->vel_ned_valid;
  // timestamp_time_relative
  output->timestamp_time_relative = input->timestamp_time_relative;
  // time_utc_usec
  output->time_utc_usec = input->time_utc_usec;
  // satellites_used
  output->satellites_used = input->satellites_used;
  // heading
  output->heading = input->heading;
  // heading_offset
  output->heading_offset = input->heading_offset;
  // heading_accuracy
  output->heading_accuracy = input->heading_accuracy;
  // rtcm_injection_rate
  output->rtcm_injection_rate = input->rtcm_injection_rate;
  // selected_rtcm_instance
  output->selected_rtcm_instance = input->selected_rtcm_instance;
  return true;
}

px4_msgs__msg__SensorGps *
px4_msgs__msg__SensorGps__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGps * msg = (px4_msgs__msg__SensorGps *)allocator.allocate(sizeof(px4_msgs__msg__SensorGps), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__SensorGps));
  bool success = px4_msgs__msg__SensorGps__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__SensorGps__destroy(px4_msgs__msg__SensorGps * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__SensorGps__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__SensorGps__Sequence__init(px4_msgs__msg__SensorGps__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGps * data = NULL;

  if (size) {
    data = (px4_msgs__msg__SensorGps *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__SensorGps), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__SensorGps__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__SensorGps__fini(&data[i - 1]);
      }
      allocator.deallocate(data, allocator.state);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
px4_msgs__msg__SensorGps__Sequence__fini(px4_msgs__msg__SensorGps__Sequence * array)
{
  if (!array) {
    return;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();

  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      px4_msgs__msg__SensorGps__fini(&array->data[i]);
    }
    allocator.deallocate(array->data, allocator.state);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

px4_msgs__msg__SensorGps__Sequence *
px4_msgs__msg__SensorGps__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__SensorGps__Sequence * array = (px4_msgs__msg__SensorGps__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__SensorGps__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__SensorGps__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__SensorGps__Sequence__destroy(px4_msgs__msg__SensorGps__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__SensorGps__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__SensorGps__Sequence__are_equal(const px4_msgs__msg__SensorGps__Sequence * lhs, const px4_msgs__msg__SensorGps__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__SensorGps__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__SensorGps__Sequence__copy(
  const px4_msgs__msg__SensorGps__Sequence * input,
  px4_msgs__msg__SensorGps__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__SensorGps);
    px4_msgs__msg__SensorGps * data =
      (px4_msgs__msg__SensorGps *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__SensorGps__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__SensorGps__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!px4_msgs__msg__SensorGps__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

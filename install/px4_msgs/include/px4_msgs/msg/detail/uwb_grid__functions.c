// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from px4_msgs:msg/UwbGrid.idl
// generated code does not contain a copyright notice
#include "px4_msgs/msg/detail/uwb_grid__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "rcutils/allocator.h"


bool
px4_msgs__msg__UwbGrid__init(px4_msgs__msg__UwbGrid * msg)
{
  if (!msg) {
    return false;
  }
  // timestamp
  // initator_time
  // num_anchors
  // target_gps
  // target_pos
  // anchor_pos_0
  // anchor_pos_1
  // anchor_pos_2
  // anchor_pos_3
  // anchor_pos_4
  // anchor_pos_5
  // anchor_pos_6
  // anchor_pos_7
  // anchor_pos_8
  // anchor_pos_9
  // anchor_pos_10
  // anchor_pos_11
  return true;
}

void
px4_msgs__msg__UwbGrid__fini(px4_msgs__msg__UwbGrid * msg)
{
  if (!msg) {
    return;
  }
  // timestamp
  // initator_time
  // num_anchors
  // target_gps
  // target_pos
  // anchor_pos_0
  // anchor_pos_1
  // anchor_pos_2
  // anchor_pos_3
  // anchor_pos_4
  // anchor_pos_5
  // anchor_pos_6
  // anchor_pos_7
  // anchor_pos_8
  // anchor_pos_9
  // anchor_pos_10
  // anchor_pos_11
}

bool
px4_msgs__msg__UwbGrid__are_equal(const px4_msgs__msg__UwbGrid * lhs, const px4_msgs__msg__UwbGrid * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // timestamp
  if (lhs->timestamp != rhs->timestamp) {
    return false;
  }
  // initator_time
  if (lhs->initator_time != rhs->initator_time) {
    return false;
  }
  // num_anchors
  if (lhs->num_anchors != rhs->num_anchors) {
    return false;
  }
  // target_gps
  for (size_t i = 0; i < 4; ++i) {
    if (lhs->target_gps[i] != rhs->target_gps[i]) {
      return false;
    }
  }
  // target_pos
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->target_pos[i] != rhs->target_pos[i]) {
      return false;
    }
  }
  // anchor_pos_0
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_0[i] != rhs->anchor_pos_0[i]) {
      return false;
    }
  }
  // anchor_pos_1
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_1[i] != rhs->anchor_pos_1[i]) {
      return false;
    }
  }
  // anchor_pos_2
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_2[i] != rhs->anchor_pos_2[i]) {
      return false;
    }
  }
  // anchor_pos_3
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_3[i] != rhs->anchor_pos_3[i]) {
      return false;
    }
  }
  // anchor_pos_4
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_4[i] != rhs->anchor_pos_4[i]) {
      return false;
    }
  }
  // anchor_pos_5
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_5[i] != rhs->anchor_pos_5[i]) {
      return false;
    }
  }
  // anchor_pos_6
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_6[i] != rhs->anchor_pos_6[i]) {
      return false;
    }
  }
  // anchor_pos_7
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_7[i] != rhs->anchor_pos_7[i]) {
      return false;
    }
  }
  // anchor_pos_8
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_8[i] != rhs->anchor_pos_8[i]) {
      return false;
    }
  }
  // anchor_pos_9
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_9[i] != rhs->anchor_pos_9[i]) {
      return false;
    }
  }
  // anchor_pos_10
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_10[i] != rhs->anchor_pos_10[i]) {
      return false;
    }
  }
  // anchor_pos_11
  for (size_t i = 0; i < 3; ++i) {
    if (lhs->anchor_pos_11[i] != rhs->anchor_pos_11[i]) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__UwbGrid__copy(
  const px4_msgs__msg__UwbGrid * input,
  px4_msgs__msg__UwbGrid * output)
{
  if (!input || !output) {
    return false;
  }
  // timestamp
  output->timestamp = input->timestamp;
  // initator_time
  output->initator_time = input->initator_time;
  // num_anchors
  output->num_anchors = input->num_anchors;
  // target_gps
  for (size_t i = 0; i < 4; ++i) {
    output->target_gps[i] = input->target_gps[i];
  }
  // target_pos
  for (size_t i = 0; i < 3; ++i) {
    output->target_pos[i] = input->target_pos[i];
  }
  // anchor_pos_0
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_0[i] = input->anchor_pos_0[i];
  }
  // anchor_pos_1
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_1[i] = input->anchor_pos_1[i];
  }
  // anchor_pos_2
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_2[i] = input->anchor_pos_2[i];
  }
  // anchor_pos_3
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_3[i] = input->anchor_pos_3[i];
  }
  // anchor_pos_4
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_4[i] = input->anchor_pos_4[i];
  }
  // anchor_pos_5
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_5[i] = input->anchor_pos_5[i];
  }
  // anchor_pos_6
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_6[i] = input->anchor_pos_6[i];
  }
  // anchor_pos_7
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_7[i] = input->anchor_pos_7[i];
  }
  // anchor_pos_8
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_8[i] = input->anchor_pos_8[i];
  }
  // anchor_pos_9
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_9[i] = input->anchor_pos_9[i];
  }
  // anchor_pos_10
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_10[i] = input->anchor_pos_10[i];
  }
  // anchor_pos_11
  for (size_t i = 0; i < 3; ++i) {
    output->anchor_pos_11[i] = input->anchor_pos_11[i];
  }
  return true;
}

px4_msgs__msg__UwbGrid *
px4_msgs__msg__UwbGrid__create()
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__UwbGrid * msg = (px4_msgs__msg__UwbGrid *)allocator.allocate(sizeof(px4_msgs__msg__UwbGrid), allocator.state);
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(px4_msgs__msg__UwbGrid));
  bool success = px4_msgs__msg__UwbGrid__init(msg);
  if (!success) {
    allocator.deallocate(msg, allocator.state);
    return NULL;
  }
  return msg;
}

void
px4_msgs__msg__UwbGrid__destroy(px4_msgs__msg__UwbGrid * msg)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (msg) {
    px4_msgs__msg__UwbGrid__fini(msg);
  }
  allocator.deallocate(msg, allocator.state);
}


bool
px4_msgs__msg__UwbGrid__Sequence__init(px4_msgs__msg__UwbGrid__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__UwbGrid * data = NULL;

  if (size) {
    data = (px4_msgs__msg__UwbGrid *)allocator.zero_allocate(size, sizeof(px4_msgs__msg__UwbGrid), allocator.state);
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = px4_msgs__msg__UwbGrid__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        px4_msgs__msg__UwbGrid__fini(&data[i - 1]);
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
px4_msgs__msg__UwbGrid__Sequence__fini(px4_msgs__msg__UwbGrid__Sequence * array)
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
      px4_msgs__msg__UwbGrid__fini(&array->data[i]);
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

px4_msgs__msg__UwbGrid__Sequence *
px4_msgs__msg__UwbGrid__Sequence__create(size_t size)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  px4_msgs__msg__UwbGrid__Sequence * array = (px4_msgs__msg__UwbGrid__Sequence *)allocator.allocate(sizeof(px4_msgs__msg__UwbGrid__Sequence), allocator.state);
  if (!array) {
    return NULL;
  }
  bool success = px4_msgs__msg__UwbGrid__Sequence__init(array, size);
  if (!success) {
    allocator.deallocate(array, allocator.state);
    return NULL;
  }
  return array;
}

void
px4_msgs__msg__UwbGrid__Sequence__destroy(px4_msgs__msg__UwbGrid__Sequence * array)
{
  rcutils_allocator_t allocator = rcutils_get_default_allocator();
  if (array) {
    px4_msgs__msg__UwbGrid__Sequence__fini(array);
  }
  allocator.deallocate(array, allocator.state);
}

bool
px4_msgs__msg__UwbGrid__Sequence__are_equal(const px4_msgs__msg__UwbGrid__Sequence * lhs, const px4_msgs__msg__UwbGrid__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!px4_msgs__msg__UwbGrid__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
px4_msgs__msg__UwbGrid__Sequence__copy(
  const px4_msgs__msg__UwbGrid__Sequence * input,
  px4_msgs__msg__UwbGrid__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(px4_msgs__msg__UwbGrid);
    px4_msgs__msg__UwbGrid * data =
      (px4_msgs__msg__UwbGrid *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!px4_msgs__msg__UwbGrid__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          px4_msgs__msg__UwbGrid__fini(&data[i]);
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
    if (!px4_msgs__msg__UwbGrid__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}

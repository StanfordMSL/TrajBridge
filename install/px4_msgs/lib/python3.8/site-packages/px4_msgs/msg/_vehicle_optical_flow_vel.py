# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/VehicleOpticalFlowVel.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'vel_body'
# Member 'vel_ne'
# Member 'flow_uncompensated_integral'
# Member 'flow_compensated_integral'
# Member 'gyro_rate'
# Member 'gyro_rate_integral'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VehicleOpticalFlowVel(type):
    """Metaclass of message 'VehicleOpticalFlowVel'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('px4_msgs')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'px4_msgs.msg.VehicleOpticalFlowVel')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vehicle_optical_flow_vel
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vehicle_optical_flow_vel
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vehicle_optical_flow_vel
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vehicle_optical_flow_vel
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vehicle_optical_flow_vel

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VehicleOpticalFlowVel(metaclass=Metaclass_VehicleOpticalFlowVel):
    """Message class 'VehicleOpticalFlowVel'."""

    __slots__ = [
        '_timestamp',
        '_timestamp_sample',
        '_vel_body',
        '_vel_ne',
        '_flow_uncompensated_integral',
        '_flow_compensated_integral',
        '_gyro_rate',
        '_gyro_rate_integral',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'timestamp_sample': 'uint64',
        'vel_body': 'float[2]',
        'vel_ne': 'float[2]',
        'flow_uncompensated_integral': 'float[2]',
        'flow_compensated_integral': 'float[2]',
        'gyro_rate': 'float[3]',
        'gyro_rate_integral': 'float[3]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 2),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 2),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 2),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 2),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.timestamp_sample = kwargs.get('timestamp_sample', int())
        if 'vel_body' not in kwargs:
            self.vel_body = numpy.zeros(2, dtype=numpy.float32)
        else:
            self.vel_body = numpy.array(kwargs.get('vel_body'), dtype=numpy.float32)
            assert self.vel_body.shape == (2, )
        if 'vel_ne' not in kwargs:
            self.vel_ne = numpy.zeros(2, dtype=numpy.float32)
        else:
            self.vel_ne = numpy.array(kwargs.get('vel_ne'), dtype=numpy.float32)
            assert self.vel_ne.shape == (2, )
        if 'flow_uncompensated_integral' not in kwargs:
            self.flow_uncompensated_integral = numpy.zeros(2, dtype=numpy.float32)
        else:
            self.flow_uncompensated_integral = numpy.array(kwargs.get('flow_uncompensated_integral'), dtype=numpy.float32)
            assert self.flow_uncompensated_integral.shape == (2, )
        if 'flow_compensated_integral' not in kwargs:
            self.flow_compensated_integral = numpy.zeros(2, dtype=numpy.float32)
        else:
            self.flow_compensated_integral = numpy.array(kwargs.get('flow_compensated_integral'), dtype=numpy.float32)
            assert self.flow_compensated_integral.shape == (2, )
        if 'gyro_rate' not in kwargs:
            self.gyro_rate = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.gyro_rate = numpy.array(kwargs.get('gyro_rate'), dtype=numpy.float32)
            assert self.gyro_rate.shape == (3, )
        if 'gyro_rate_integral' not in kwargs:
            self.gyro_rate_integral = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.gyro_rate_integral = numpy.array(kwargs.get('gyro_rate_integral'), dtype=numpy.float32)
            assert self.gyro_rate_integral.shape == (3, )

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.timestamp != other.timestamp:
            return False
        if self.timestamp_sample != other.timestamp_sample:
            return False
        if all(self.vel_body != other.vel_body):
            return False
        if all(self.vel_ne != other.vel_ne):
            return False
        if all(self.flow_uncompensated_integral != other.flow_uncompensated_integral):
            return False
        if all(self.flow_compensated_integral != other.flow_compensated_integral):
            return False
        if all(self.gyro_rate != other.gyro_rate):
            return False
        if all(self.gyro_rate_integral != other.gyro_rate_integral):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def timestamp(self):
        """Message field 'timestamp'."""
        return self._timestamp

    @timestamp.setter
    def timestamp(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp = value

    @property
    def timestamp_sample(self):
        """Message field 'timestamp_sample'."""
        return self._timestamp_sample

    @timestamp_sample.setter
    def timestamp_sample(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp_sample' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp_sample' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp_sample = value

    @property
    def vel_body(self):
        """Message field 'vel_body'."""
        return self._vel_body

    @vel_body.setter
    def vel_body(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'vel_body' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 2, \
                "The 'vel_body' numpy.ndarray() must have a size of 2"
            self._vel_body = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 2 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'vel_body' field must be a set or sequence with length 2 and each value of type 'float'"
        self._vel_body = numpy.array(value, dtype=numpy.float32)

    @property
    def vel_ne(self):
        """Message field 'vel_ne'."""
        return self._vel_ne

    @vel_ne.setter
    def vel_ne(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'vel_ne' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 2, \
                "The 'vel_ne' numpy.ndarray() must have a size of 2"
            self._vel_ne = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 2 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'vel_ne' field must be a set or sequence with length 2 and each value of type 'float'"
        self._vel_ne = numpy.array(value, dtype=numpy.float32)

    @property
    def flow_uncompensated_integral(self):
        """Message field 'flow_uncompensated_integral'."""
        return self._flow_uncompensated_integral

    @flow_uncompensated_integral.setter
    def flow_uncompensated_integral(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'flow_uncompensated_integral' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 2, \
                "The 'flow_uncompensated_integral' numpy.ndarray() must have a size of 2"
            self._flow_uncompensated_integral = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 2 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'flow_uncompensated_integral' field must be a set or sequence with length 2 and each value of type 'float'"
        self._flow_uncompensated_integral = numpy.array(value, dtype=numpy.float32)

    @property
    def flow_compensated_integral(self):
        """Message field 'flow_compensated_integral'."""
        return self._flow_compensated_integral

    @flow_compensated_integral.setter
    def flow_compensated_integral(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'flow_compensated_integral' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 2, \
                "The 'flow_compensated_integral' numpy.ndarray() must have a size of 2"
            self._flow_compensated_integral = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 2 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'flow_compensated_integral' field must be a set or sequence with length 2 and each value of type 'float'"
        self._flow_compensated_integral = numpy.array(value, dtype=numpy.float32)

    @property
    def gyro_rate(self):
        """Message field 'gyro_rate'."""
        return self._gyro_rate

    @gyro_rate.setter
    def gyro_rate(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'gyro_rate' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'gyro_rate' numpy.ndarray() must have a size of 3"
            self._gyro_rate = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'gyro_rate' field must be a set or sequence with length 3 and each value of type 'float'"
        self._gyro_rate = numpy.array(value, dtype=numpy.float32)

    @property
    def gyro_rate_integral(self):
        """Message field 'gyro_rate_integral'."""
        return self._gyro_rate_integral

    @gyro_rate_integral.setter
    def gyro_rate_integral(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'gyro_rate_integral' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'gyro_rate_integral' numpy.ndarray() must have a size of 3"
            self._gyro_rate_integral = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 len(value) == 3 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'gyro_rate_integral' field must be a set or sequence with length 3 and each value of type 'float'"
        self._gyro_rate_integral = numpy.array(value, dtype=numpy.float32)

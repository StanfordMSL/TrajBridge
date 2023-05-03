# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/UwbDistance.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'anchor_distance'
# Member 'aoafirst'
# Member 'position'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_UwbDistance(type):
    """Metaclass of message 'UwbDistance'."""

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
                'px4_msgs.msg.UwbDistance')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__uwb_distance
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__uwb_distance
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__uwb_distance
            cls._TYPE_SUPPORT = module.type_support_msg__msg__uwb_distance
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__uwb_distance

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UwbDistance(metaclass=Metaclass_UwbDistance):
    """Message class 'UwbDistance'."""

    __slots__ = [
        '_timestamp',
        '_time_uwb_ms',
        '_counter',
        '_sessionid',
        '_time_offset',
        '_status',
        '_anchor_distance',
        '_nlos',
        '_aoafirst',
        '_position',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'time_uwb_ms': 'uint32',
        'counter': 'uint32',
        'sessionid': 'uint32',
        'time_offset': 'uint32',
        'status': 'uint16',
        'anchor_distance': 'uint16[12]',
        'nlos': 'boolean[12]',
        'aoafirst': 'float[12]',
        'position': 'float[3]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint32'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint16'), 12),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('boolean'), 12),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 12),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('float'), 3),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.time_uwb_ms = kwargs.get('time_uwb_ms', int())
        self.counter = kwargs.get('counter', int())
        self.sessionid = kwargs.get('sessionid', int())
        self.time_offset = kwargs.get('time_offset', int())
        self.status = kwargs.get('status', int())
        if 'anchor_distance' not in kwargs:
            self.anchor_distance = numpy.zeros(12, dtype=numpy.uint16)
        else:
            self.anchor_distance = numpy.array(kwargs.get('anchor_distance'), dtype=numpy.uint16)
            assert self.anchor_distance.shape == (12, )
        self.nlos = kwargs.get(
            'nlos',
            [bool() for x in range(12)]
        )
        if 'aoafirst' not in kwargs:
            self.aoafirst = numpy.zeros(12, dtype=numpy.float32)
        else:
            self.aoafirst = numpy.array(kwargs.get('aoafirst'), dtype=numpy.float32)
            assert self.aoafirst.shape == (12, )
        if 'position' not in kwargs:
            self.position = numpy.zeros(3, dtype=numpy.float32)
        else:
            self.position = numpy.array(kwargs.get('position'), dtype=numpy.float32)
            assert self.position.shape == (3, )

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
        if self.time_uwb_ms != other.time_uwb_ms:
            return False
        if self.counter != other.counter:
            return False
        if self.sessionid != other.sessionid:
            return False
        if self.time_offset != other.time_offset:
            return False
        if self.status != other.status:
            return False
        if all(self.anchor_distance != other.anchor_distance):
            return False
        if self.nlos != other.nlos:
            return False
        if all(self.aoafirst != other.aoafirst):
            return False
        if all(self.position != other.position):
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
    def time_uwb_ms(self):
        """Message field 'time_uwb_ms'."""
        return self._time_uwb_ms

    @time_uwb_ms.setter
    def time_uwb_ms(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'time_uwb_ms' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'time_uwb_ms' field must be an unsigned integer in [0, 4294967295]"
        self._time_uwb_ms = value

    @property
    def counter(self):
        """Message field 'counter'."""
        return self._counter

    @counter.setter
    def counter(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'counter' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'counter' field must be an unsigned integer in [0, 4294967295]"
        self._counter = value

    @property
    def sessionid(self):
        """Message field 'sessionid'."""
        return self._sessionid

    @sessionid.setter
    def sessionid(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sessionid' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'sessionid' field must be an unsigned integer in [0, 4294967295]"
        self._sessionid = value

    @property
    def time_offset(self):
        """Message field 'time_offset'."""
        return self._time_offset

    @time_offset.setter
    def time_offset(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'time_offset' field must be of type 'int'"
            assert value >= 0 and value < 4294967296, \
                "The 'time_offset' field must be an unsigned integer in [0, 4294967295]"
        self._time_offset = value

    @property
    def status(self):
        """Message field 'status'."""
        return self._status

    @status.setter
    def status(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'status' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'status' field must be an unsigned integer in [0, 65535]"
        self._status = value

    @property
    def anchor_distance(self):
        """Message field 'anchor_distance'."""
        return self._anchor_distance

    @anchor_distance.setter
    def anchor_distance(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint16, \
                "The 'anchor_distance' numpy.ndarray() must have the dtype of 'numpy.uint16'"
            assert value.size == 12, \
                "The 'anchor_distance' numpy.ndarray() must have a size of 12"
            self._anchor_distance = value
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
                 len(value) == 12 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 65536 for val in value)), \
                "The 'anchor_distance' field must be a set or sequence with length 12 and each value of type 'int' and each unsigned integer in [0, 65535]"
        self._anchor_distance = numpy.array(value, dtype=numpy.uint16)

    @property
    def nlos(self):
        """Message field 'nlos'."""
        return self._nlos

    @nlos.setter
    def nlos(self, value):
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
                 len(value) == 12 and
                 all(isinstance(v, bool) for v in value) and
                 True), \
                "The 'nlos' field must be a set or sequence with length 12 and each value of type 'bool'"
        self._nlos = value

    @property
    def aoafirst(self):
        """Message field 'aoafirst'."""
        return self._aoafirst

    @aoafirst.setter
    def aoafirst(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'aoafirst' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 12, \
                "The 'aoafirst' numpy.ndarray() must have a size of 12"
            self._aoafirst = value
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
                 len(value) == 12 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'aoafirst' field must be a set or sequence with length 12 and each value of type 'float'"
        self._aoafirst = numpy.array(value, dtype=numpy.float32)

    @property
    def position(self):
        """Message field 'position'."""
        return self._position

    @position.setter
    def position(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float32, \
                "The 'position' numpy.ndarray() must have the dtype of 'numpy.float32'"
            assert value.size == 3, \
                "The 'position' numpy.ndarray() must have a size of 3"
            self._position = value
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
                "The 'position' field must be a set or sequence with length 3 and each value of type 'float'"
        self._position = numpy.array(value, dtype=numpy.float32)

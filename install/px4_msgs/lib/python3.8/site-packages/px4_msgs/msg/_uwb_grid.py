# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/UwbGrid.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'target_gps'
# Member 'target_pos'
# Member 'anchor_pos_0'
# Member 'anchor_pos_1'
# Member 'anchor_pos_2'
# Member 'anchor_pos_3'
# Member 'anchor_pos_4'
# Member 'anchor_pos_5'
# Member 'anchor_pos_6'
# Member 'anchor_pos_7'
# Member 'anchor_pos_8'
# Member 'anchor_pos_9'
# Member 'anchor_pos_10'
# Member 'anchor_pos_11'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_UwbGrid(type):
    """Metaclass of message 'UwbGrid'."""

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
                'px4_msgs.msg.UwbGrid')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__uwb_grid
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__uwb_grid
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__uwb_grid
            cls._TYPE_SUPPORT = module.type_support_msg__msg__uwb_grid
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__uwb_grid

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class UwbGrid(metaclass=Metaclass_UwbGrid):
    """Message class 'UwbGrid'."""

    __slots__ = [
        '_timestamp',
        '_initator_time',
        '_num_anchors',
        '_target_gps',
        '_target_pos',
        '_anchor_pos_0',
        '_anchor_pos_1',
        '_anchor_pos_2',
        '_anchor_pos_3',
        '_anchor_pos_4',
        '_anchor_pos_5',
        '_anchor_pos_6',
        '_anchor_pos_7',
        '_anchor_pos_8',
        '_anchor_pos_9',
        '_anchor_pos_10',
        '_anchor_pos_11',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'initator_time': 'uint16',
        'num_anchors': 'uint8',
        'target_gps': 'double[4]',
        'target_pos': 'int16[3]',
        'anchor_pos_0': 'int16[3]',
        'anchor_pos_1': 'int16[3]',
        'anchor_pos_2': 'int16[3]',
        'anchor_pos_3': 'int16[3]',
        'anchor_pos_4': 'int16[3]',
        'anchor_pos_5': 'int16[3]',
        'anchor_pos_6': 'int16[3]',
        'anchor_pos_7': 'int16[3]',
        'anchor_pos_8': 'int16[3]',
        'anchor_pos_9': 'int16[3]',
        'anchor_pos_10': 'int16[3]',
        'anchor_pos_11': 'int16[3]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint16'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('double'), 4),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('int16'), 3),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.initator_time = kwargs.get('initator_time', int())
        self.num_anchors = kwargs.get('num_anchors', int())
        if 'target_gps' not in kwargs:
            self.target_gps = numpy.zeros(4, dtype=numpy.float64)
        else:
            self.target_gps = numpy.array(kwargs.get('target_gps'), dtype=numpy.float64)
            assert self.target_gps.shape == (4, )
        if 'target_pos' not in kwargs:
            self.target_pos = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.target_pos = numpy.array(kwargs.get('target_pos'), dtype=numpy.int16)
            assert self.target_pos.shape == (3, )
        if 'anchor_pos_0' not in kwargs:
            self.anchor_pos_0 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_0 = numpy.array(kwargs.get('anchor_pos_0'), dtype=numpy.int16)
            assert self.anchor_pos_0.shape == (3, )
        if 'anchor_pos_1' not in kwargs:
            self.anchor_pos_1 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_1 = numpy.array(kwargs.get('anchor_pos_1'), dtype=numpy.int16)
            assert self.anchor_pos_1.shape == (3, )
        if 'anchor_pos_2' not in kwargs:
            self.anchor_pos_2 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_2 = numpy.array(kwargs.get('anchor_pos_2'), dtype=numpy.int16)
            assert self.anchor_pos_2.shape == (3, )
        if 'anchor_pos_3' not in kwargs:
            self.anchor_pos_3 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_3 = numpy.array(kwargs.get('anchor_pos_3'), dtype=numpy.int16)
            assert self.anchor_pos_3.shape == (3, )
        if 'anchor_pos_4' not in kwargs:
            self.anchor_pos_4 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_4 = numpy.array(kwargs.get('anchor_pos_4'), dtype=numpy.int16)
            assert self.anchor_pos_4.shape == (3, )
        if 'anchor_pos_5' not in kwargs:
            self.anchor_pos_5 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_5 = numpy.array(kwargs.get('anchor_pos_5'), dtype=numpy.int16)
            assert self.anchor_pos_5.shape == (3, )
        if 'anchor_pos_6' not in kwargs:
            self.anchor_pos_6 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_6 = numpy.array(kwargs.get('anchor_pos_6'), dtype=numpy.int16)
            assert self.anchor_pos_6.shape == (3, )
        if 'anchor_pos_7' not in kwargs:
            self.anchor_pos_7 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_7 = numpy.array(kwargs.get('anchor_pos_7'), dtype=numpy.int16)
            assert self.anchor_pos_7.shape == (3, )
        if 'anchor_pos_8' not in kwargs:
            self.anchor_pos_8 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_8 = numpy.array(kwargs.get('anchor_pos_8'), dtype=numpy.int16)
            assert self.anchor_pos_8.shape == (3, )
        if 'anchor_pos_9' not in kwargs:
            self.anchor_pos_9 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_9 = numpy.array(kwargs.get('anchor_pos_9'), dtype=numpy.int16)
            assert self.anchor_pos_9.shape == (3, )
        if 'anchor_pos_10' not in kwargs:
            self.anchor_pos_10 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_10 = numpy.array(kwargs.get('anchor_pos_10'), dtype=numpy.int16)
            assert self.anchor_pos_10.shape == (3, )
        if 'anchor_pos_11' not in kwargs:
            self.anchor_pos_11 = numpy.zeros(3, dtype=numpy.int16)
        else:
            self.anchor_pos_11 = numpy.array(kwargs.get('anchor_pos_11'), dtype=numpy.int16)
            assert self.anchor_pos_11.shape == (3, )

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
        if self.initator_time != other.initator_time:
            return False
        if self.num_anchors != other.num_anchors:
            return False
        if all(self.target_gps != other.target_gps):
            return False
        if all(self.target_pos != other.target_pos):
            return False
        if all(self.anchor_pos_0 != other.anchor_pos_0):
            return False
        if all(self.anchor_pos_1 != other.anchor_pos_1):
            return False
        if all(self.anchor_pos_2 != other.anchor_pos_2):
            return False
        if all(self.anchor_pos_3 != other.anchor_pos_3):
            return False
        if all(self.anchor_pos_4 != other.anchor_pos_4):
            return False
        if all(self.anchor_pos_5 != other.anchor_pos_5):
            return False
        if all(self.anchor_pos_6 != other.anchor_pos_6):
            return False
        if all(self.anchor_pos_7 != other.anchor_pos_7):
            return False
        if all(self.anchor_pos_8 != other.anchor_pos_8):
            return False
        if all(self.anchor_pos_9 != other.anchor_pos_9):
            return False
        if all(self.anchor_pos_10 != other.anchor_pos_10):
            return False
        if all(self.anchor_pos_11 != other.anchor_pos_11):
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
    def initator_time(self):
        """Message field 'initator_time'."""
        return self._initator_time

    @initator_time.setter
    def initator_time(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'initator_time' field must be of type 'int'"
            assert value >= 0 and value < 65536, \
                "The 'initator_time' field must be an unsigned integer in [0, 65535]"
        self._initator_time = value

    @property
    def num_anchors(self):
        """Message field 'num_anchors'."""
        return self._num_anchors

    @num_anchors.setter
    def num_anchors(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'num_anchors' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'num_anchors' field must be an unsigned integer in [0, 255]"
        self._num_anchors = value

    @property
    def target_gps(self):
        """Message field 'target_gps'."""
        return self._target_gps

    @target_gps.setter
    def target_gps(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.float64, \
                "The 'target_gps' numpy.ndarray() must have the dtype of 'numpy.float64'"
            assert value.size == 4, \
                "The 'target_gps' numpy.ndarray() must have a size of 4"
            self._target_gps = value
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
                 len(value) == 4 and
                 all(isinstance(v, float) for v in value) and
                 True), \
                "The 'target_gps' field must be a set or sequence with length 4 and each value of type 'float'"
        self._target_gps = numpy.array(value, dtype=numpy.float64)

    @property
    def target_pos(self):
        """Message field 'target_pos'."""
        return self._target_pos

    @target_pos.setter
    def target_pos(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'target_pos' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'target_pos' numpy.ndarray() must have a size of 3"
            self._target_pos = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'target_pos' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._target_pos = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_0(self):
        """Message field 'anchor_pos_0'."""
        return self._anchor_pos_0

    @anchor_pos_0.setter
    def anchor_pos_0(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_0' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_0' numpy.ndarray() must have a size of 3"
            self._anchor_pos_0 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_0' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_0 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_1(self):
        """Message field 'anchor_pos_1'."""
        return self._anchor_pos_1

    @anchor_pos_1.setter
    def anchor_pos_1(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_1' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_1' numpy.ndarray() must have a size of 3"
            self._anchor_pos_1 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_1' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_1 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_2(self):
        """Message field 'anchor_pos_2'."""
        return self._anchor_pos_2

    @anchor_pos_2.setter
    def anchor_pos_2(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_2' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_2' numpy.ndarray() must have a size of 3"
            self._anchor_pos_2 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_2' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_2 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_3(self):
        """Message field 'anchor_pos_3'."""
        return self._anchor_pos_3

    @anchor_pos_3.setter
    def anchor_pos_3(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_3' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_3' numpy.ndarray() must have a size of 3"
            self._anchor_pos_3 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_3' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_3 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_4(self):
        """Message field 'anchor_pos_4'."""
        return self._anchor_pos_4

    @anchor_pos_4.setter
    def anchor_pos_4(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_4' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_4' numpy.ndarray() must have a size of 3"
            self._anchor_pos_4 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_4' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_4 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_5(self):
        """Message field 'anchor_pos_5'."""
        return self._anchor_pos_5

    @anchor_pos_5.setter
    def anchor_pos_5(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_5' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_5' numpy.ndarray() must have a size of 3"
            self._anchor_pos_5 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_5' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_5 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_6(self):
        """Message field 'anchor_pos_6'."""
        return self._anchor_pos_6

    @anchor_pos_6.setter
    def anchor_pos_6(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_6' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_6' numpy.ndarray() must have a size of 3"
            self._anchor_pos_6 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_6' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_6 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_7(self):
        """Message field 'anchor_pos_7'."""
        return self._anchor_pos_7

    @anchor_pos_7.setter
    def anchor_pos_7(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_7' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_7' numpy.ndarray() must have a size of 3"
            self._anchor_pos_7 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_7' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_7 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_8(self):
        """Message field 'anchor_pos_8'."""
        return self._anchor_pos_8

    @anchor_pos_8.setter
    def anchor_pos_8(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_8' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_8' numpy.ndarray() must have a size of 3"
            self._anchor_pos_8 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_8' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_8 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_9(self):
        """Message field 'anchor_pos_9'."""
        return self._anchor_pos_9

    @anchor_pos_9.setter
    def anchor_pos_9(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_9' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_9' numpy.ndarray() must have a size of 3"
            self._anchor_pos_9 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_9' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_9 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_10(self):
        """Message field 'anchor_pos_10'."""
        return self._anchor_pos_10

    @anchor_pos_10.setter
    def anchor_pos_10(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_10' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_10' numpy.ndarray() must have a size of 3"
            self._anchor_pos_10 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_10' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_10 = numpy.array(value, dtype=numpy.int16)

    @property
    def anchor_pos_11(self):
        """Message field 'anchor_pos_11'."""
        return self._anchor_pos_11

    @anchor_pos_11.setter
    def anchor_pos_11(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.int16, \
                "The 'anchor_pos_11' numpy.ndarray() must have the dtype of 'numpy.int16'"
            assert value.size == 3, \
                "The 'anchor_pos_11' numpy.ndarray() must have a size of 3"
            self._anchor_pos_11 = value
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
                 all(isinstance(v, int) for v in value) and
                 all(val >= -32768 and val < 32768 for val in value)), \
                "The 'anchor_pos_11' field must be a set or sequence with length 3 and each value of type 'int' and each integer in [-32768, 32767]"
        self._anchor_pos_11 = numpy.array(value, dtype=numpy.int16)

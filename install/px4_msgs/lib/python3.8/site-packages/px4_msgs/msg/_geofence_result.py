# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/GeofenceResult.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_GeofenceResult(type):
    """Metaclass of message 'GeofenceResult'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
        'GF_ACTION_NONE': 0,
        'GF_ACTION_WARN': 1,
        'GF_ACTION_LOITER': 2,
        'GF_ACTION_RTL': 3,
        'GF_ACTION_TERMINATE': 4,
        'GF_ACTION_LAND': 5,
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
                'px4_msgs.msg.GeofenceResult')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__geofence_result
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__geofence_result
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__geofence_result
            cls._TYPE_SUPPORT = module.type_support_msg__msg__geofence_result
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__geofence_result

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
            'GF_ACTION_NONE': cls.__constants['GF_ACTION_NONE'],
            'GF_ACTION_WARN': cls.__constants['GF_ACTION_WARN'],
            'GF_ACTION_LOITER': cls.__constants['GF_ACTION_LOITER'],
            'GF_ACTION_RTL': cls.__constants['GF_ACTION_RTL'],
            'GF_ACTION_TERMINATE': cls.__constants['GF_ACTION_TERMINATE'],
            'GF_ACTION_LAND': cls.__constants['GF_ACTION_LAND'],
        }

    @property
    def GF_ACTION_NONE(self):
        """Message constant 'GF_ACTION_NONE'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_NONE']

    @property
    def GF_ACTION_WARN(self):
        """Message constant 'GF_ACTION_WARN'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_WARN']

    @property
    def GF_ACTION_LOITER(self):
        """Message constant 'GF_ACTION_LOITER'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_LOITER']

    @property
    def GF_ACTION_RTL(self):
        """Message constant 'GF_ACTION_RTL'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_RTL']

    @property
    def GF_ACTION_TERMINATE(self):
        """Message constant 'GF_ACTION_TERMINATE'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_TERMINATE']

    @property
    def GF_ACTION_LAND(self):
        """Message constant 'GF_ACTION_LAND'."""
        return Metaclass_GeofenceResult.__constants['GF_ACTION_LAND']


class GeofenceResult(metaclass=Metaclass_GeofenceResult):
    """
    Message class 'GeofenceResult'.

    Constants:
      GF_ACTION_NONE
      GF_ACTION_WARN
      GF_ACTION_LOITER
      GF_ACTION_RTL
      GF_ACTION_TERMINATE
      GF_ACTION_LAND
    """

    __slots__ = [
        '_timestamp',
        '_geofence_violation_reason',
        '_primary_geofence_breached',
        '_primary_geofence_action',
        '_home_required',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'geofence_violation_reason': 'uint8',
        'primary_geofence_breached': 'boolean',
        'primary_geofence_action': 'uint8',
        'home_required': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.geofence_violation_reason = kwargs.get('geofence_violation_reason', int())
        self.primary_geofence_breached = kwargs.get('primary_geofence_breached', bool())
        self.primary_geofence_action = kwargs.get('primary_geofence_action', int())
        self.home_required = kwargs.get('home_required', bool())

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
        if self.geofence_violation_reason != other.geofence_violation_reason:
            return False
        if self.primary_geofence_breached != other.primary_geofence_breached:
            return False
        if self.primary_geofence_action != other.primary_geofence_action:
            return False
        if self.home_required != other.home_required:
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
    def geofence_violation_reason(self):
        """Message field 'geofence_violation_reason'."""
        return self._geofence_violation_reason

    @geofence_violation_reason.setter
    def geofence_violation_reason(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'geofence_violation_reason' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'geofence_violation_reason' field must be an unsigned integer in [0, 255]"
        self._geofence_violation_reason = value

    @property
    def primary_geofence_breached(self):
        """Message field 'primary_geofence_breached'."""
        return self._primary_geofence_breached

    @primary_geofence_breached.setter
    def primary_geofence_breached(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'primary_geofence_breached' field must be of type 'bool'"
        self._primary_geofence_breached = value

    @property
    def primary_geofence_action(self):
        """Message field 'primary_geofence_action'."""
        return self._primary_geofence_action

    @primary_geofence_action.setter
    def primary_geofence_action(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'primary_geofence_action' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'primary_geofence_action' field must be an unsigned integer in [0, 255]"
        self._primary_geofence_action = value

    @property
    def home_required(self):
        """Message field 'home_required'."""
        return self._home_required

    @home_required.setter
    def home_required(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'home_required' field must be of type 'bool'"
        self._home_required = value

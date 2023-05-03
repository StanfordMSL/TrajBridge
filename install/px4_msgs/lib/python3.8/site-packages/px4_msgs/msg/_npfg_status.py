# generated from rosidl_generator_py/resource/_idl.py.em
# with input from px4_msgs:msg/NpfgStatus.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_NpfgStatus(type):
    """Metaclass of message 'NpfgStatus'."""

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
                'px4_msgs.msg.NpfgStatus')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__npfg_status
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__npfg_status
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__npfg_status
            cls._TYPE_SUPPORT = module.type_support_msg__msg__npfg_status
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__npfg_status

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class NpfgStatus(metaclass=Metaclass_NpfgStatus):
    """Message class 'NpfgStatus'."""

    __slots__ = [
        '_timestamp',
        '_wind_est_valid',
        '_lat_accel',
        '_lat_accel_ff',
        '_bearing_feas',
        '_bearing_feas_on_track',
        '_signed_track_error',
        '_track_error_bound',
        '_airspeed_ref',
        '_bearing',
        '_heading_ref',
        '_min_ground_speed_ref',
        '_adapted_period',
        '_p_gain',
        '_time_const',
    ]

    _fields_and_field_types = {
        'timestamp': 'uint64',
        'wind_est_valid': 'uint8',
        'lat_accel': 'float',
        'lat_accel_ff': 'float',
        'bearing_feas': 'float',
        'bearing_feas_on_track': 'float',
        'signed_track_error': 'float',
        'track_error_bound': 'float',
        'airspeed_ref': 'float',
        'bearing': 'float',
        'heading_ref': 'float',
        'min_ground_speed_ref': 'float',
        'adapted_period': 'float',
        'p_gain': 'float',
        'time_const': 'float',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint8'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
        rosidl_parser.definition.BasicType('float'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.timestamp = kwargs.get('timestamp', int())
        self.wind_est_valid = kwargs.get('wind_est_valid', int())
        self.lat_accel = kwargs.get('lat_accel', float())
        self.lat_accel_ff = kwargs.get('lat_accel_ff', float())
        self.bearing_feas = kwargs.get('bearing_feas', float())
        self.bearing_feas_on_track = kwargs.get('bearing_feas_on_track', float())
        self.signed_track_error = kwargs.get('signed_track_error', float())
        self.track_error_bound = kwargs.get('track_error_bound', float())
        self.airspeed_ref = kwargs.get('airspeed_ref', float())
        self.bearing = kwargs.get('bearing', float())
        self.heading_ref = kwargs.get('heading_ref', float())
        self.min_ground_speed_ref = kwargs.get('min_ground_speed_ref', float())
        self.adapted_period = kwargs.get('adapted_period', float())
        self.p_gain = kwargs.get('p_gain', float())
        self.time_const = kwargs.get('time_const', float())

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
        if self.wind_est_valid != other.wind_est_valid:
            return False
        if self.lat_accel != other.lat_accel:
            return False
        if self.lat_accel_ff != other.lat_accel_ff:
            return False
        if self.bearing_feas != other.bearing_feas:
            return False
        if self.bearing_feas_on_track != other.bearing_feas_on_track:
            return False
        if self.signed_track_error != other.signed_track_error:
            return False
        if self.track_error_bound != other.track_error_bound:
            return False
        if self.airspeed_ref != other.airspeed_ref:
            return False
        if self.bearing != other.bearing:
            return False
        if self.heading_ref != other.heading_ref:
            return False
        if self.min_ground_speed_ref != other.min_ground_speed_ref:
            return False
        if self.adapted_period != other.adapted_period:
            return False
        if self.p_gain != other.p_gain:
            return False
        if self.time_const != other.time_const:
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
    def wind_est_valid(self):
        """Message field 'wind_est_valid'."""
        return self._wind_est_valid

    @wind_est_valid.setter
    def wind_est_valid(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'wind_est_valid' field must be of type 'int'"
            assert value >= 0 and value < 256, \
                "The 'wind_est_valid' field must be an unsigned integer in [0, 255]"
        self._wind_est_valid = value

    @property
    def lat_accel(self):
        """Message field 'lat_accel'."""
        return self._lat_accel

    @lat_accel.setter
    def lat_accel(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lat_accel' field must be of type 'float'"
        self._lat_accel = value

    @property
    def lat_accel_ff(self):
        """Message field 'lat_accel_ff'."""
        return self._lat_accel_ff

    @lat_accel_ff.setter
    def lat_accel_ff(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'lat_accel_ff' field must be of type 'float'"
        self._lat_accel_ff = value

    @property
    def bearing_feas(self):
        """Message field 'bearing_feas'."""
        return self._bearing_feas

    @bearing_feas.setter
    def bearing_feas(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bearing_feas' field must be of type 'float'"
        self._bearing_feas = value

    @property
    def bearing_feas_on_track(self):
        """Message field 'bearing_feas_on_track'."""
        return self._bearing_feas_on_track

    @bearing_feas_on_track.setter
    def bearing_feas_on_track(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bearing_feas_on_track' field must be of type 'float'"
        self._bearing_feas_on_track = value

    @property
    def signed_track_error(self):
        """Message field 'signed_track_error'."""
        return self._signed_track_error

    @signed_track_error.setter
    def signed_track_error(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'signed_track_error' field must be of type 'float'"
        self._signed_track_error = value

    @property
    def track_error_bound(self):
        """Message field 'track_error_bound'."""
        return self._track_error_bound

    @track_error_bound.setter
    def track_error_bound(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'track_error_bound' field must be of type 'float'"
        self._track_error_bound = value

    @property
    def airspeed_ref(self):
        """Message field 'airspeed_ref'."""
        return self._airspeed_ref

    @airspeed_ref.setter
    def airspeed_ref(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'airspeed_ref' field must be of type 'float'"
        self._airspeed_ref = value

    @property
    def bearing(self):
        """Message field 'bearing'."""
        return self._bearing

    @bearing.setter
    def bearing(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'bearing' field must be of type 'float'"
        self._bearing = value

    @property
    def heading_ref(self):
        """Message field 'heading_ref'."""
        return self._heading_ref

    @heading_ref.setter
    def heading_ref(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'heading_ref' field must be of type 'float'"
        self._heading_ref = value

    @property
    def min_ground_speed_ref(self):
        """Message field 'min_ground_speed_ref'."""
        return self._min_ground_speed_ref

    @min_ground_speed_ref.setter
    def min_ground_speed_ref(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'min_ground_speed_ref' field must be of type 'float'"
        self._min_ground_speed_ref = value

    @property
    def adapted_period(self):
        """Message field 'adapted_period'."""
        return self._adapted_period

    @adapted_period.setter
    def adapted_period(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'adapted_period' field must be of type 'float'"
        self._adapted_period = value

    @property
    def p_gain(self):
        """Message field 'p_gain'."""
        return self._p_gain

    @p_gain.setter
    def p_gain(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'p_gain' field must be of type 'float'"
        self._p_gain = value

    @property
    def time_const(self):
        """Message field 'time_const'."""
        return self._time_const

    @time_const.setter
    def time_const(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time_const' field must be of type 'float'"
        self._time_const = value

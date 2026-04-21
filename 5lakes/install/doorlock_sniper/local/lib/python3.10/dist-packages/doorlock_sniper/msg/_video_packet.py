# generated from rosidl_generator_py/resource/_idl.py.em
# with input from doorlock_sniper:msg/VideoPacket.idl
# generated code does not contain a copyright notice


# Import statements for member types

import builtins  # noqa: E402, I100

# Member 'data'
import numpy  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_VideoPacket(type):
    """Metaclass of message 'VideoPacket'."""

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
            module = import_type_support('doorlock_sniper')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'doorlock_sniper.msg.VideoPacket')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__video_packet
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__video_packet
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__video_packet
            cls._TYPE_SUPPORT = module.type_support_msg__msg__video_packet
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__video_packet

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class VideoPacket(metaclass=Metaclass_VideoPacket):
    """Message class 'VideoPacket'."""

    __slots__ = [
        '_sequence_id',
        '_timestamp_ns',
        '_data',
    ]

    _fields_and_field_types = {
        'sequence_id': 'uint64',
        'timestamp_ns': 'uint64',
        'data': 'uint8[150]',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.BasicType('uint64'),  # noqa: E501
        rosidl_parser.definition.Array(rosidl_parser.definition.BasicType('uint8'), 150),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.sequence_id = kwargs.get('sequence_id', int())
        self.timestamp_ns = kwargs.get('timestamp_ns', int())
        if 'data' not in kwargs:
            self.data = numpy.zeros(150, dtype=numpy.uint8)
        else:
            self.data = numpy.array(kwargs.get('data'), dtype=numpy.uint8)
            assert self.data.shape == (150, )

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
        if self.sequence_id != other.sequence_id:
            return False
        if self.timestamp_ns != other.timestamp_ns:
            return False
        if any(self.data != other.data):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def sequence_id(self):
        """Message field 'sequence_id'."""
        return self._sequence_id

    @sequence_id.setter
    def sequence_id(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'sequence_id' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'sequence_id' field must be an unsigned integer in [0, 18446744073709551615]"
        self._sequence_id = value

    @builtins.property
    def timestamp_ns(self):
        """Message field 'timestamp_ns'."""
        return self._timestamp_ns

    @timestamp_ns.setter
    def timestamp_ns(self, value):
        if __debug__:
            assert \
                isinstance(value, int), \
                "The 'timestamp_ns' field must be of type 'int'"
            assert value >= 0 and value < 18446744073709551616, \
                "The 'timestamp_ns' field must be an unsigned integer in [0, 18446744073709551615]"
        self._timestamp_ns = value

    @builtins.property
    def data(self):
        """Message field 'data'."""
        return self._data

    @data.setter
    def data(self, value):
        if isinstance(value, numpy.ndarray):
            assert value.dtype == numpy.uint8, \
                "The 'data' numpy.ndarray() must have the dtype of 'numpy.uint8'"
            assert value.size == 150, \
                "The 'data' numpy.ndarray() must have a size of 150"
            self._data = value
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
                 len(value) == 150 and
                 all(isinstance(v, int) for v in value) and
                 all(val >= 0 and val < 256 for val in value)), \
                "The 'data' field must be a set or sequence with length 150 and each value of type 'int' and each unsigned integer in [0, 255]"
        self._data = numpy.array(value, dtype=numpy.uint8)

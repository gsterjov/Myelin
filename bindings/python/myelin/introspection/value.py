

import ctypes

from type import Type
from pointer import Pointer


# get library
import myelin.library
_lib = myelin.library.get_library()




class Value (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a value
        if ptr is None:
            ptr = _lib.myelin_value_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Value pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_value_free (self)
        
        
    def get_type (self):
        return Type.from_pointer (_lib.myelin_value_get_type (self), False)
    
    def is_empty (self):
        return _lib.myelin_value_is_empty (self)
    
    def clear (self):
        _lib.myelin_value_clear (self)
    
    
    def get_bool (self):
        return _lib.myelin_value_get_bool (self)
    def set_bool (self, value):
        _lib.myelin_value_set_bool (self, value)    
    
    def get_char (self):
        return _lib.myelin_value_get_char (self)
    def set_char (self, value):
        _lib.myelin_value_set_char (self, value)
    
    def get_uchar (self):
        return _lib.myelin_value_get_uchar (self)
    def set_uchar (self, value):
        _lib.myelin_value_set_uchar (self, value)
    
    def get_int (self):
        return _lib.myelin_value_get_int (self)
    def set_int (self, value):
        _lib.myelin_value_set_int (self, value)
    
    def get_uint (self):
        return _lib.myelin_value_get_uint (self)
    def set_uint (self, value):
        _lib.myelin_value_set_uint (self, value)
    
    def get_long (self):
        return _lib.myelin_value_get_long (self)
    def set_long (self, value):
        _lib.myelin_value_set_long (self, value)
    
    def get_ulong (self):
        return _lib.myelin_value_get_ulong (self)
    def set_ulong (self, value):
        _lib.myelin_value_set_ulong (self, value)
    
    def get_int64 (self):
        return _lib.myelin_value_get_int64 (self)
    def set_int64 (self, value):
        _lib.myelin_value_set_int64 (self, value)
    
    def get_uint64 (self):
        return _lib.myelin_value_get_uint64 (self)
    def set_uint64 (self, value):
        _lib.myelin_value_set_uint64 (self, value)
    
    def get_float (self):
        return _lib.myelin_value_get_float (self)
    def set_float (self, value):
        _lib.myelin_value_set_float (self, value)
    
    def get_double (self):
        return _lib.myelin_value_get_double (self)
    def set_double (self, value):
        _lib.myelin_value_set_double (self, value)
    
    def get_string (self):
        return _lib.myelin_value_get_string (self)
    def set_string (self, value):
        _lib.myelin_value_set_string (self, value)
    
    def get_pointer (self):
        return Pointer.from_pointer (_lib.myelin_value_get_pointer (self),
                                     True)
    def set_pointer (self, value):
        _lib.myelin_value_set_pointer (self, value)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_value_new.argtypes = None
_lib.myelin_value_new.restype  = ctypes.c_void_p

_lib.myelin_value_free.argtypes = [Value]
_lib.myelin_value_free.restype  = None

_lib.myelin_value_get_type.argtypes = [Value]
_lib.myelin_value_get_type.restype  = ctypes.c_void_p

_lib.myelin_value_is_empty.argtypes = [Value]
_lib.myelin_value_is_empty.restype  = ctypes.c_bool

_lib.myelin_value_clear.argtypes = [Value]
_lib.myelin_value_clear.restype  = None


# boolean
_lib.myelin_value_get_bool.argtypes = [Value]
_lib.myelin_value_get_bool.restype  = ctypes.c_bool
_lib.myelin_value_set_bool.argtypes = [Value, ctypes.c_bool]
_lib.myelin_value_set_bool.restype  = None

# char
_lib.myelin_value_get_char.argtypes = [Value]
_lib.myelin_value_get_char.restype  = ctypes.c_char
_lib.myelin_value_set_char.argtypes = [Value, ctypes.c_char]
_lib.myelin_value_set_char.restype  = None

# uchar
_lib.myelin_value_get_uchar.argtypes = [Value]
_lib.myelin_value_get_uchar.restype  = ctypes.c_ubyte
_lib.myelin_value_set_uchar.argtypes = [Value, ctypes.c_ubyte]
_lib.myelin_value_set_uchar.restype  = None

# integer
_lib.myelin_value_get_int.argtypes = [Value]
_lib.myelin_value_get_int.restype  = ctypes.c_int
_lib.myelin_value_set_int.argtypes = [Value, ctypes.c_int]
_lib.myelin_value_set_int.restype  = None

# uint
_lib.myelin_value_get_uint.argtypes = [Value]
_lib.myelin_value_get_uint.restype  = ctypes.c_bool
_lib.myelin_value_set_uint.argtypes = [Value, ctypes.c_uint]
_lib.myelin_value_set_uint.restype  = None

# long
_lib.myelin_value_get_long.argtypes = [Value]
_lib.myelin_value_get_long.restype  = ctypes.c_long
_lib.myelin_value_set_long.argtypes = [Value, ctypes.c_long]
_lib.myelin_value_set_long.restype  = None

# ulong
_lib.myelin_value_get_ulong.argtypes = [Value]
_lib.myelin_value_get_ulong.restype  = ctypes.c_ulong
_lib.myelin_value_set_ulong.argtypes = [Value, ctypes.c_ulong]
_lib.myelin_value_set_ulong.restype  = None

# 64bit integer
_lib.myelin_value_get_int64.argtypes = [Value]
_lib.myelin_value_get_int64.restype  = ctypes.c_int64
_lib.myelin_value_set_int64.argtypes = [Value, ctypes.c_int64]
_lib.myelin_value_set_int64.restype  = None

# unsigned 64bit integer
_lib.myelin_value_get_uint64.argtypes = [Value]
_lib.myelin_value_get_uint64.restype  = ctypes.c_uint64
_lib.myelin_value_set_uint64.argtypes = [Value, ctypes.c_uint64]
_lib.myelin_value_set_uint64.restype  = None

# float
_lib.myelin_value_get_float.argtypes = [Value]
_lib.myelin_value_get_float.restype  = ctypes.c_float
_lib.myelin_value_set_float.argtypes = [Value, ctypes.c_float]
_lib.myelin_value_set_float.restype  = None

# double
_lib.myelin_value_get_double.argtypes = [Value]
_lib.myelin_value_get_double.restype  = ctypes.c_double
_lib.myelin_value_set_double.argtypes = [Value, ctypes.c_double]
_lib.myelin_value_set_double.restype  = None

# string
_lib.myelin_value_get_string.argtypes = [Value]
_lib.myelin_value_get_string.restype  = ctypes.c_char_p
_lib.myelin_value_set_string.argtypes = [Value, ctypes.c_char_p]
_lib.myelin_value_set_string.restype  = None

# pointer
_lib.myelin_value_get_pointer.argtypes = [Value]
_lib.myelin_value_get_pointer.restype  = ctypes.c_void_p
_lib.myelin_value_set_pointer.argtypes = [Value, Pointer]
_lib.myelin_value_set_pointer.restype  = None


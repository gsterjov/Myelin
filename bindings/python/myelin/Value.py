
from ctypes import *

from Type import Type
import Library



lib = Library.get_library()



class Value (object):
    
    _value_ptr = None
    
    
    def __init__ (self):
        
        # create a value
        if self._value_ptr is None:
            raise NotImplementedError, 'Values can only be retrieved'
        
        
    @classmethod
    def from_pointer (cls, value_ptr):
        cls._value_ptr = value_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._value_ptr
        
        
        
    def get_type (self):
        return Type.from_pointer (lib.myelin_value_get_type (self))
        
        
    def get_data (self):
        return lib.myelin_value_get_data (self)
    
        
        
    def get_bool (self): return lib.myelin_value_get_bool (self)
    def set_bool (self, value): lib.myelin_value_set_bool (self, value)    
    
    def get_char (self): return lib.myelin_value_get_char (self)
    def set_char (self, value): lib.myelin_value_set_char (self, value)
    
    def get_uchar (self): return lib.myelin_value_get_uchar (self)
    def set_uchar (self, value): lib.myelin_value_set_uchar (self, value)
    
    def get_int (self): return lib.myelin_value_get_int (self)
    def set_int (self, value): lib.myelin_value_set_int (self, value)
    
    def get_uint (self): return lib.myelin_value_get_uint (self)
    def set_uint (self, value): lib.myelin_value_set_uint (self, value)
    
    def get_long (self): return lib.myelin_value_get_long (self)
    def set_long (self, value): lib.myelin_value_set_long (self, value)
    
    def get_ulong (self): return lib.myelin_value_get_ulong (self)
    def set_ulong (self, value): lib.myelin_value_set_ulong (self, value)
    
    def get_int64 (self): return lib.myelin_value_get_int64 (self)
    def set_int64 (self, value): lib.myelin_value_set_int64 (self, value)
    
    def get_uint64 (self): return lib.myelin_value_get_uint64 (self)
    def set_uint64 (self, value): lib.myelin_value_set_uint64 (self, value)
    
    def get_float (self): return lib.myelin_value_get_float (self)
    def set_float (self, value): lib.myelin_value_set_float (self, value)
    
    def get_double (self): return lib.myelin_value_get_double (self)
    def set_double (self, value): lib.myelin_value_set_double (self, value)
    
    def get_string (self): return lib.myelin_value_get_string (self)
    def set_string (self, value): lib.myelin_value_set_string (self, value)
    
    def get_pointer (self): return lib.myelin_value_get_pointer (self)
    def set_pointer (self, value): lib.myelin_value_set_pointer (self, value)





# set value prototypes
lib.myelin_value_get_type.argtypes = [Value]
lib.myelin_value_get_type.restype = c_void_p

lib.myelin_value_get_data.argtypes = [Value]
lib.myelin_value_get_data.restype = c_void_p



# boolean
lib.myelin_value_get_bool.argtypes = [Value]
lib.myelin_value_get_bool.restype = c_bool

lib.myelin_value_set_bool.argtypes = [Value, c_bool]
lib.myelin_value_set_bool.restype = None

# char
lib.myelin_value_get_char.argtypes = [Value]
lib.myelin_value_get_char.restype = c_char

lib.myelin_value_set_char.argtypes = [Value, c_char]
lib.myelin_value_set_char.restype = None

# uchar
lib.myelin_value_get_uchar.argtypes = [Value]
lib.myelin_value_get_uchar.restype = c_ubyte

lib.myelin_value_set_uchar.argtypes = [Value, c_ubyte]
lib.myelin_value_set_uchar.restype = None

# integer
lib.myelin_value_get_int.argtypes = [Value]
lib.myelin_value_get_int.restype = c_int

lib.myelin_value_set_int.argtypes = [Value, c_int]
lib.myelin_value_set_int.restype = None

# uint
lib.myelin_value_get_uint.argtypes = [Value]
lib.myelin_value_get_uint.restype = c_bool

lib.myelin_value_set_uint.argtypes = [Value, c_uint]
lib.myelin_value_set_uint.restype = None

# long
lib.myelin_value_get_long.argtypes = [Value]
lib.myelin_value_get_long.restype = c_long

lib.myelin_value_set_long.argtypes = [Value, c_long]
lib.myelin_value_set_long.restype = None

# ulong
lib.myelin_value_get_ulong.argtypes = [Value]
lib.myelin_value_get_ulong.restype = c_ulong

lib.myelin_value_set_ulong.argtypes = [Value, c_ulong]
lib.myelin_value_set_ulong.restype = None

# 64bit integer
lib.myelin_value_get_int64.argtypes = [Value]
lib.myelin_value_get_int64.restype = c_int64

lib.myelin_value_set_int64.argtypes = [Value, c_int64]
lib.myelin_value_set_int64.restype = None

# unsigned 64bit integer
lib.myelin_value_get_uint64.argtypes = [Value]
lib.myelin_value_get_uint64.restype = c_uint64

lib.myelin_value_set_uint64.argtypes = [Value, c_uint64]
lib.myelin_value_set_uint64.restype = None

# float
lib.myelin_value_get_float.argtypes = [Value]
lib.myelin_value_get_float.restype = c_float

lib.myelin_value_set_float.argtypes = [Value, c_float]
lib.myelin_value_set_float.restype = None

# double
lib.myelin_value_get_double.argtypes = [Value]
lib.myelin_value_get_double.restype = c_double

lib.myelin_value_set_double.argtypes = [Value, c_double]
lib.myelin_value_set_double.restype = None

# string
lib.myelin_value_get_string.argtypes = [Value]
lib.myelin_value_get_string.restype = c_char_p

lib.myelin_value_set_string.argtypes = [Value, c_char_p]
lib.myelin_value_set_string.restype = None

# pointer
lib.myelin_value_get_pointer.argtypes = [Value]
lib.myelin_value_get_pointer.restype = c_void_p

lib.myelin_value_set_pointer.argtypes = [Value, c_void_p]
lib.myelin_value_set_pointer.restype = None


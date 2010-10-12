

import ctypes

from type import Type
from pointer import Pointer
from value import Value


# get library
import myelin.library
_lib = myelin.library.get_library()




class Converter (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            raise NotImplementedError ("A Converter can only be retrieved")
        
        self._ptr = ptr
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Converter pointer cannot be 'None'")
        return cls (None, ptr)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_input_type (self):
        type = _lib.myelin_converter_get_input_type (self)
        return Type.from_pointer (type)
    
    def get_output_type (self):
        type = _lib.myelin_converter_get_output_type (self)
        return Type.from_pointer (type)
    
    
    def convert_value (self, value):
        val = _lib.myelin_converter_convert_value (self, value)
        return Value.from_pointer (val)
        
    def convert_pointer (self, pointer):
        val = _lib.myelin_converter_convert_pointer (self, pointer)
        return Value.from_pointer (val)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_converter_get_input_type.argtypes = [Converter]
_lib.myelin_converter_get_input_type.restype  = ctypes.c_void_p

_lib.myelin_converter_get_output_type.argtypes = [Converter]
_lib.myelin_converter_get_output_type.restype  = ctypes.c_void_p


_lib.myelin_converter_convert_value.argtypes = [Converter, Value]
_lib.myelin_converter_convert_value.restype  = ctypes.c_void_p

_lib.myelin_converter_convert_pointer.argtypes = [Converter, Pointer]
_lib.myelin_converter_convert_pointer.restype  = ctypes.c_void_p



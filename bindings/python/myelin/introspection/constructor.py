

import ctypes

from type import Type
from pointer import Pointer
from list import List


# get library
import myelin.library
_lib = myelin.library.get_library()




class Constructor (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            raise NotImplementedError ("Meta constructors can only be retrieved")
        
        self._ptr = ptr
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Constructor pointer cannot be 'None'")
        return cls (ptr)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_param_count (self):
        return _lib.myelin_constructor_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = _lib.myelin_constructor_get_param_type (self, index)
        return Type.from_pointer (type)
    
    
    def get_param_types (self):
        list = _lib.myelin_constructor_get_param_types (self)
        return List.from_pointer (list)
    
    
    def call (self, params):
#        check_param_types (self.get_param_types(), params)
        
        val = _lib.myelin_constructor_call (self, params)
        return Pointer.from_pointer (val)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_constructor_get_param_count.argtypes = [Constructor]
_lib.myelin_constructor_get_param_count.restype  = ctypes.c_int

_lib.myelin_constructor_get_param_type.argtypes = [Constructor, ctypes.c_int]
_lib.myelin_constructor_get_param_type.restype  = ctypes.c_void_p

_lib.myelin_constructor_get_param_types.argtypes = [Constructor]
_lib.myelin_constructor_get_param_types.restype  = ctypes.c_void_p

_lib.myelin_constructor_call.argtypes = [Constructor, List]
_lib.myelin_constructor_call.restype  = ctypes.c_void_p


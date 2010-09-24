

import ctypes

from type import Type


# get library
import myelin.library
_lib = myelin.library.get_library()




class Pointer (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a pointer
        if ptr is None:
            ptr = _lib.myelin_pointer_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Pointer pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_pointer_free (self)
        
        
    def get_type (self):
        return Type.from_pointer (_lib.myelin_pointer_get_type (self), False)
    
    def is_empty (self):
        return _lib.myelin_pointer_is_empty (self)
    
    def clear (self):
        _lib.myelin_pointer_clear (self)
    
    
    def get_raw (self):
        return _lib.myelin_pointer_get_raw (self)
    
    
    def set (self, ptr, type):
        _lib.myelin_pointer_set (self, ptr, type)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_pointer_new.argtypes = None
_lib.myelin_pointer_new.restype  = ctypes.c_void_p

_lib.myelin_pointer_free.argtypes = [Pointer]
_lib.myelin_pointer_free.restype  = None

_lib.myelin_pointer_get_type.argtypes = [Pointer]
_lib.myelin_pointer_get_type.restype  = ctypes.c_void_p

_lib.myelin_pointer_is_empty.argtypes = [Pointer]
_lib.myelin_pointer_is_empty.restype  = ctypes.c_bool

_lib.myelin_pointer_clear.argtypes = [Pointer]
_lib.myelin_pointer_clear.restype  = None

_lib.myelin_pointer_get_raw.argtypes = [Pointer]
_lib.myelin_pointer_get_raw.restype  = ctypes.c_void_p

_lib.myelin_pointer_set.argtypes = [Pointer, ctypes.c_void_p, Type]
_lib.myelin_pointer_set.restype  = None


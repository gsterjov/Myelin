

import ctypes

from value import Value


# get library
import myelin.library
_lib = myelin.library.get_library()




class List (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a list
        if ptr is None:
            ptr = _lib.myelin_list_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    def __len__ (self):
        return _lib.myelin_list_size (self)
    
    
    def __getitem__ (self, index):
        if not isinstance (index, int):
            raise TypeError ("The index must be a non-negative integer")
        if index < 0 or index >= _lib.myelin_list_size (self):
            raise IndexError
        
        return Value.from_pointer (_lib.myelin_list_index (self, index),
                                   True)
    
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("List pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_list_free (self)
        
        
    def get_size (self):
        return _lib.myelin_list_size (self)
    
    
    def get_value (self, index):
        return Value.from_pointer (_lib.myelin_list_index (self, index),
                                   True)
    
    
    def append (self, value):
        _lib.myelin_list_append (self, value)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_list_new.argtypes = None
_lib.myelin_list_new.restype  = ctypes.c_void_p

_lib.myelin_list_free.argtypes = [List]
_lib.myelin_list_free.restype  = None

_lib.myelin_list_size.argtypes = [List]
_lib.myelin_list_size.restype  = ctypes.c_uint

_lib.myelin_list_index.argtypes = [List, ctypes.c_uint]
_lib.myelin_list_index.restype  = ctypes.c_void_p

_lib.myelin_list_append.argtypes = [List, Value]
_lib.myelin_list_append.restype  = None


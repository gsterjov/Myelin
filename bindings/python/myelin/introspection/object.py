

import ctypes

from pointer import Pointer
from value import Value
from list import List
from class_ import Class


# get library
import myelin.library
_lib = myelin.library.get_library()




class Object (object):
    
    def __init__ (self, klass, instance, ptr = None, owner = True):
        # create an object
        if ptr is None:
            if klass is not None:
                # create with instance
                if instance is not None:
                    ptr = _lib.myelin_object_new_with_instance (klass,
                                                                   instance)
                # create with class
                else:
                    ptr = _lib.myelin_object_new_with_class (klass)
            # just create empty object
            else:
                ptr = _lib.myelin_object_new ()
        
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Object pointer cannot be 'None'")
        return cls (None, None, ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_object_free (self)
    
    
    def set_class (self, klass):
        _lib.myelin_object_set_class (self, jkass)
    
    
    def get_class (self):
        klass = _lib.myelin_object_get_class (self)
        return Class.from_pointer (klass, False)
    
    
    def set_instance (self, instance):
        _lib.myelin_object_set_instance (self, instance)
    
    
    def get_instance (self):
        instance = _lib.myelin_object_get_instance (self)
        return Pointer.from_pointer (instance, False)
    
    
    def call (self, name, params):
        val = _lib.myelin_object_call (self, name, params)
        return Value.from_pointer (val, True)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_object_new.argtypes = None
_lib.myelin_object_new.restype  = ctypes.c_void_p

_lib.myelin_object_new_with_class.argtypes = [Class]
_lib.myelin_object_new_with_class.restype  = ctypes.c_void_p

_lib.myelin_object_new_with_instance.argtypes = [Class, Pointer]
_lib.myelin_object_new_with_instance.restype  = ctypes.c_void_p

_lib.myelin_object_free.argtypes = [Object]
_lib.myelin_object_free.restype  = None


_lib.myelin_object_set_class.argtypes = [Object, Class]
_lib.myelin_object_set_class.restype  = None

_lib.myelin_object_get_class.argtypes = [Object]
_lib.myelin_object_get_class.restype  = ctypes.c_void_p

_lib.myelin_object_set_instance.argtypes = [Object, Pointer]
_lib.myelin_object_set_instance.restype  = None

_lib.myelin_object_get_instance.argtypes = [Object]
_lib.myelin_object_get_instance.restype  = ctypes.c_void_p


_lib.myelin_object_call.argtypes = [Object, ctypes.c_char_p, List]
_lib.myelin_object_call.restype  = ctypes.c_void_p


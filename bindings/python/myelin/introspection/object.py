

import ctypes

from value import Value
from list import List
from class_ import Class


# get library
import myelin.library
_lib = myelin.library.get_library()




class Object (object):
    
    def __init__ (self, klass, instance, ptr = None):
        
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
    
    
    def __del__ (self):
        _lib.myelin_object_unref (self)
    
    
    def __repr__ (self):
        return ("<%s.%s meta-object at %#x implementing %s with an instance " \
                "of type %s at %#x>" %
               (self.__module__,
                self.__class__.__name__,
                id(self),
                self.get_class().get_name(),
                self.get_instance().get_type().get_name(),
                self.get_instance().as_pointer()))
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Object pointer cannot be 'None'")
        
        instance = cls (None, None, ptr)
        _lib.myelin_object_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def set_class (self, klass):
        _lib.myelin_object_set_class (self, klass)
    
    
    def get_class (self):
        klass = _lib.myelin_object_get_class (self)
        return Class.from_pointer (klass)
    
    
    def set_instance (self, instance):
        _lib.myelin_object_set_instance (self, instance)
    
    
    def get_instance (self):
        instance = _lib.myelin_object_get_instance (self)
        return Value.from_pointer (instance)
    
    
    def call (self, name, params):
        val = _lib.myelin_object_call (self, name, params)
        return Value.from_pointer (val)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_object_new.argtypes = None
_lib.myelin_object_new.restype  = ctypes.c_void_p

_lib.myelin_object_new_with_class.argtypes = [Class]
_lib.myelin_object_new_with_class.restype  = ctypes.c_void_p

_lib.myelin_object_new_with_instance.argtypes = [Class, Value]
_lib.myelin_object_new_with_instance.restype  = ctypes.c_void_p

_lib.myelin_object_ref.argtypes = [Object]
_lib.myelin_object_ref.restype  = ctypes.c_void_p

_lib.myelin_object_unref.argtypes = [Object]
_lib.myelin_object_unref.restype  = None


_lib.myelin_object_set_class.argtypes = [Object, Class]
_lib.myelin_object_set_class.restype  = None

_lib.myelin_object_get_class.argtypes = [Object]
_lib.myelin_object_get_class.restype  = ctypes.c_void_p

_lib.myelin_object_set_instance.argtypes = [Object, Value]
_lib.myelin_object_set_instance.restype  = None

_lib.myelin_object_get_instance.argtypes = [Object]
_lib.myelin_object_get_instance.restype  = ctypes.c_void_p


_lib.myelin_object_call.argtypes = [Object, ctypes.c_char_p, List]
_lib.myelin_object_call.restype  = ctypes.c_void_p


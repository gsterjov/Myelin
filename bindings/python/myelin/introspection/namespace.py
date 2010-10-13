

import ctypes

from list import List
from class_ import Class


# get library
import myelin.library
_lib = myelin.library.get_library()




class Namespace (object):
    
    def __init__ (self, name, ptr = None):
        
        if ptr is None:
            if name is None:
                raise ValueError ("A namespace name must be provided")
            ptr = _lib.myelin_namespace_new (name)
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_namespace_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Namespace pointer cannot be 'None'")
        
        instance = cls (None, ptr)
        _lib.myelin_namespace_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return _lib.myelin_namespace_get_name (self)
    
    
    def add_class (self, klass):
        _lib.myelin_namespace_add_class (self, klass)
    
    
    def get_class (self, name):
        klass = _lib.myelin_namespace_get_class (self, name)
        return Class.from_pointer (klass)
    
    
    def get_classes (self):
        list = _lib.myelin_namespace_get_classes (self)
        return List.from_pointer (list)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_namespace_new.argtypes = [ctypes.c_char_p]
_lib.myelin_namespace_new.restype  = ctypes.c_void_p

_lib.myelin_namespace_ref.argtypes = [Namespace]
_lib.myelin_namespace_ref.restype  = ctypes.c_void_p

_lib.myelin_namespace_unref.argtypes = [Namespace]
_lib.myelin_namespace_unref.restype  = None

_lib.myelin_namespace_get_name.argtypes = [Namespace]
_lib.myelin_namespace_get_name.restype  = ctypes.c_char_p

_lib.myelin_namespace_add_class.argtypes = [Namespace, Class]
_lib.myelin_namespace_add_class.restype  = None

_lib.myelin_namespace_get_class.argtypes = [Namespace, ctypes.c_char_p]
_lib.myelin_namespace_get_class.restype  = ctypes.c_void_p

_lib.myelin_namespace_get_classes.argtypes = [Namespace]
_lib.myelin_namespace_get_classes.restype  = ctypes.c_void_p


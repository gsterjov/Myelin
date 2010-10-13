

import ctypes

from list import List
from namespace import Namespace


# get library
import myelin.library
_lib = myelin.library.get_library()




class Repository (object):
    
    def __init__ (self, name, ptr = None):
        
        if ptr is None:
            if name is None:
                raise ValueError ("A repository name must be provided")
            ptr = _lib.myelin_repository_new (name)
        
        self._ptr = ptr
        self._types = []
    
    
    def __del__ (self):
        _lib.myelin_repository_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Repository pointer cannot be 'None'")
        
        instance = cls (None, ptr)
        _lib.myelin_repository_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return _lib.myelin_repository_get_name (self)
    
    
    def add_namespace (self, namespace):
        _lib.myelin_repository_add_namespace (self, namespace)
    
    
    def get_namespace (self, name):
        namespace = _lib.myelin_repository_get_namespace (self, name)
        return Namespace.from_pointer (namespace)
    
    
    def get_namespaces (self):
        list = _lib.myelin_repository_get_namespaces (self)
        return List.from_pointer (list)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_repository_new.argtypes = [ctypes.c_char_p]
_lib.myelin_repository_new.restype  = ctypes.c_void_p

_lib.myelin_repository_ref.argtypes = [Repository]
_lib.myelin_repository_ref.restype  = ctypes.c_void_p

_lib.myelin_repository_unref.argtypes = [Repository]
_lib.myelin_repository_unref.restype  = None

_lib.myelin_repository_get_name.argtypes = [Repository]
_lib.myelin_repository_get_name.restype  = ctypes.c_char_p

_lib.myelin_repository_add_namespace.argtypes = [Repository, Namespace]
_lib.myelin_repository_add_namespace.restype  = None

_lib.myelin_repository_get_namespace.argtypes = [Repository, ctypes.c_char_p]
_lib.myelin_repository_get_namespace.restype  = ctypes.c_void_p

_lib.myelin_repository_get_namespaces.argtypes = [Repository]
_lib.myelin_repository_get_namespaces.restype  = ctypes.c_void_p


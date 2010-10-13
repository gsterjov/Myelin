

import ctypes

from type import Type
from list import List
from pointer import Pointer
from constructor import Constructor
from function import Function
from vtable import VTable


# get library
import myelin.library
_lib = myelin.library.get_library()




class Class (object):
    
    def __init__ (self, name, ptr = None):
        
        if ptr is None:
            if name is None:
                raise ValueError ("A class name must be provided")
            ptr = _lib.myelin_class_new (name)
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_class_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Class pointer cannot be 'None'")
        
        instance = cls (None, ptr)
        _lib.myelin_class_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return _lib.myelin_class_get_name (self)
    
    
    def get_type (self):
        return Type.from_pointer (_lib.myelin_class_get_type (self))
    
    
    def add_constructor (self, constructor):
        _lib.myelin_class_add_constructor (self, constructor)
    
    
    def get_constructors (self):
        list = _lib.myelin_class_get_constructors (self)
        return List.from_pointer (list)
    
    
    
    def add_function (self, function):
        _lib.myelin_class_add_function (self, function)
    
    
    def get_all_functions (self):
        list = _lib.myelin_class_get_all_functions (self)
        return List.from_pointer (list)
    
    
    def get_functions (self, name):
        list = _lib.myelin_class_get_functions (self, name)
        return List.from_pointer (list)
    
    
    
    def get_vtable (self):
        vtable = _lib.myelin_class_get_vtable (self)
        return VTable.from_pointer (vtable)
    
    
    def set_vtable (self, vtable):
        _lib.myelin_class_set_vtable (self, vtable)
    
    
    
    def create_instance (self, params):
        instance = _lib.myelin_class_create_instance (self, params)
        return Pointer.from_pointer (instance)
    
    
    def create_object (self, params):
        obj = _lib.myelin_class_create_object (self, params)
        
        if obj is not None:
            return Object.from_pointer (obj)
        
        return None
    





# defer importing to prevent circular imports
from object import Object



###############################################
# Prototypes                                  #
###############################################

_lib.myelin_class_new.argtypes = [ctypes.c_char_p]
_lib.myelin_class_new.restype  = ctypes.c_void_p

_lib.myelin_class_ref.argtypes = [Class]
_lib.myelin_class_ref.restype  = ctypes.c_void_p

_lib.myelin_class_unref.argtypes = [Class]
_lib.myelin_class_unref.restype  = None

_lib.myelin_class_get_name.argtypes = [Class]
_lib.myelin_class_get_name.restype  = ctypes.c_char_p

_lib.myelin_class_get_type.argtypes = [Class]
_lib.myelin_class_get_type.restype  = ctypes.c_void_p

_lib.myelin_class_add_constructor.argtypes = [Class, Constructor]
_lib.myelin_class_add_constructor.restype  = None

_lib.myelin_class_get_constructors.argtypes = [Class]
_lib.myelin_class_get_constructors.restype  = ctypes.c_void_p

_lib.myelin_class_add_function.argtypes = [Class, Function]
_lib.myelin_class_add_function.restype  = None

_lib.myelin_class_get_all_functions.argtypes = [Class]
_lib.myelin_class_get_all_functions.restype  = ctypes.c_void_p

_lib.myelin_class_get_functions.argtypes = [Class, ctypes.c_char_p]
_lib.myelin_class_get_functions.restype  = ctypes.c_void_p


_lib.myelin_class_get_vtable.argtypes = [Class]
_lib.myelin_class_get_vtable.restype  = ctypes.c_void_p

_lib.myelin_class_set_vtable.argtypes = [Class, VTable]
_lib.myelin_class_set_vtable.restype  = None


_lib.myelin_class_create_instance.argtypes = [Class, List]
_lib.myelin_class_create_instance.restype  = ctypes.c_void_p

_lib.myelin_class_create_object.argtypes = [Class, List]
_lib.myelin_class_create_object.restype  = ctypes.c_void_p


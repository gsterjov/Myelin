

import ctypes

from type import Type
from list import List
from value import Value
from pointer import Pointer


# get library
import myelin.library
_lib = myelin.library.get_library()




def check_param_types (types, params):
    pass



def check_param_types2 (types, params):
    # check param size
    if params.get_size() <> types.get_size():
        raise ValueError ("Parameter list must have '%d' matching values, " \
                          "'%d' was given" %
                          (types.get_size(), params.get_size()))
    
    # check param types
    for i in range(0, len(params)):
        
        # get types
        param_type = params[i].get_type()
        expected_type = Type.from_pointer (types[i].get_pointer().get_raw(),
                                           False)
        
        # get real pointer type from generic pointer
        if param_type.get_atom() == Type.type_pointer():
            param_type = params[i].get_pointer().get_type()
        
        
        # make sure we have the same type atom
        if param_type.get_atom() != expected_type.get_atom():
            raise TypeError ("Parameter '%d' does not match the appropriate " \
                             "type. Expected '%s', got '%s'" %
                             (i + 1,
                              expected_type.get_name(),
                              param_type.get_name()))
        
        
        # reference parameter types must be a pointer
        if expected_type.is_reference() and not param_type.is_pointer():
            raise TypeError ("Parameter '%d' is a reference type '%s' but " \
                             "the expected type is not a pointer, " \
                             "instead '%s' was given" %
                             (i + 1,
                              expected_type.get_name(),
                              param_type.get_name()))




class Function (object):
    
    def __init__ (self, ptr = None, owner = True):
        
        if ptr is None:
            raise NotImplementedError ("Meta functions can only be retrieved")
        
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Function pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get_name (self):
        return _lib.myelin_function_get_name (self)
    
    
    def get_type (self):
        type = _lib.myelin_function_get_type (self)
        return FunctionType.from_pointer (type, False)
    
    
    def call (self, params):
#        check_param_types (self.get_param_types(), params)
        
        val = _lib.myelin_function_call (self, params)
        return Value.from_pointer (val, True)
    
    
    def bind (self, instance):
        _lib.myelin_function_bind (self, instance)






class FunctionType (object):
    
    def __init__ (self, ptr = None, owner = True):
        
        if ptr is None:
            raise NotImplementedError ("FunctionTypes can only be retrieved")
        
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("FunctionType pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get_return_type (self):
        type = _lib.myelin_function_type_get_return_type (self)
        return Type.from_pointer (type, False)
    
    
    def get_param_count (self):
        return _lib.myelin_function_type_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = _lib.myelin_function_type_get_param_type (self, index)
        return Type.from_pointer (type, False)
    
    
    def get_param_types (self):
        list = _lib.myelin_function_type_get_param_types (self)
        return List.from_pointer (list, True)
    
    
    def check_param_types (self, params):
        return _lib.myelin_function_type_check_param_types (self, params)
    
    
    def set_instance (self, instance):
        _lib.myelin_function_type_set_instance (self, instance)
    
    
    def call (self, params):
        val = _lib.myelin_function_type_call (self, params)
        return Value.from_pointer (val, True)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_function_get_name.argtypes = [Function]
_lib.myelin_function_get_name.restype  = ctypes.c_char_p

_lib.myelin_function_get_type.argtypes = [Function]
_lib.myelin_function_get_type.restype  = ctypes.c_void_p

_lib.myelin_function_call.argtypes = [Function, List]
_lib.myelin_function_call.restype  = ctypes.c_void_p

_lib.myelin_function_bind.argtypes = [Function, Pointer]
_lib.myelin_function_bind.restype  = None



_lib.myelin_function_type_get_return_type.argtypes = [Function]
_lib.myelin_function_type_get_return_type.restype  = ctypes.c_void_p

_lib.myelin_function_type_get_param_count.argtypes = [Function]
_lib.myelin_function_type_get_param_count.restype  = ctypes.c_int

_lib.myelin_function_type_get_param_type.argtypes = [Function, ctypes.c_int]
_lib.myelin_function_type_get_param_type.restype  = ctypes.c_void_p

_lib.myelin_function_type_get_param_types.argtypes = [Function]
_lib.myelin_function_type_get_param_types.restype  = ctypes.c_void_p

_lib.myelin_function_type_check_param_types.argtypes = [Function, List]
_lib.myelin_function_type_check_param_types.restype  = ctypes.c_bool

_lib.myelin_function_type_set_instance.argtypes = [Function, Pointer]
_lib.myelin_function_type_set_instance.restype  = None

_lib.myelin_function_type_call.argtypes = [Function, List]
_lib.myelin_function_type_call.restype  = ctypes.c_void_p


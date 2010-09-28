

import ctypes
import weakref

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
    
    def __init__ (self, name, type, ptr = None, owner = True):
        
        if ptr is None:
            ptr = _lib.myelin_function_new (name, type)
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Function pointer cannot be 'None'")
        return cls (None, None, ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_function_free (self)
    
    
    
    def get_name (self):
        return _lib.myelin_function_get_name (self)
    
    
    def get_type (self):
        type = _lib.myelin_function_get_type (self)
        return FunctionType.from_pointer (type, False)
    
    
    def is_constant (self):
        return _lib.myelin_function_is_constant (self)
    
    
    def is_virtual (self):
        return _lib.myelin_function_is_virtual (self)
    
    
    def is_pure (self):
        return _lib.myelin_function_is_pure (self)
    
    
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






class CustomFunctionType (FunctionType):
    
    def __init__ (self, callback, ptr = None, owner = True):
        
        if ptr is None:
            cb = CALLBACK_FUNC (self._callback)
            ptr = _lib.myelin_custom_function_type_new (cb)
            
            self._callback_type = cb
            self._callback_func = callback
        
        self._ptr = ptr
        self._owner = owner
        self._self_object = None
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("FunctionType pointer cannot be 'None'")
        return cls (None, ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def _callback (self, params):
        
        args = []
        list = List.from_pointer (ctypes.c_void_p (params), False)
        
        for val in list:
            args.append (val.get())
        
        
        # class method
        if self._self_object is not None:
            ret = self._callback_func (self._self_object(), *args)
        else:
            ret = self._callback_func (*args)
        
        
        val = Value (owner = False)
        
        if ret is not None:
            val.set (ret)
        
        return val._ptr
    
    
    
    def set_self_object (self, object):
        self._self_object = weakref.ref (object)
    
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = _lib.myelin_custom_function_type_free (self)
    
    
    def add_param_type (self, type):
        _lib.myelin_custom_function_type_add_param_type (self, type)
    
    def set_return_type (self, type):
        _lib.myelin_custom_function_type_set_return_type (self, type)
    
    
    def call (self, params):
        val = _lib.myelin_custom_function_type_call (self, params)
        return Value.from_pointer (val, True)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_function_new.argtypes = [ctypes.c_char_p, FunctionType]
_lib.myelin_function_new.restype  = ctypes.c_void_p

_lib.myelin_function_free.argtypes = [Function]
_lib.myelin_function_free.restype  = None

_lib.myelin_function_get_name.argtypes = [Function]
_lib.myelin_function_get_name.restype  = ctypes.c_char_p

_lib.myelin_function_get_type.argtypes = [Function]
_lib.myelin_function_get_type.restype  = ctypes.c_void_p

_lib.myelin_function_is_constant.argtypes = [Function]
_lib.myelin_function_is_constant.restype  = ctypes.c_bool

_lib.myelin_function_is_virtual.argtypes = [Function]
_lib.myelin_function_is_virtual.restype  = ctypes.c_bool

_lib.myelin_function_is_pure.argtypes = [Function]
_lib.myelin_function_is_pure.restype  = ctypes.c_bool

_lib.myelin_function_call.argtypes = [Function, List]
_lib.myelin_function_call.restype  = ctypes.c_void_p

_lib.myelin_function_bind.argtypes = [Function, Pointer]
_lib.myelin_function_bind.restype  = None



_lib.myelin_function_type_get_return_type.argtypes = [FunctionType]
_lib.myelin_function_type_get_return_type.restype  = ctypes.c_void_p

_lib.myelin_function_type_get_param_count.argtypes = [FunctionType]
_lib.myelin_function_type_get_param_count.restype  = ctypes.c_int

_lib.myelin_function_type_get_param_type.argtypes = [FunctionType, ctypes.c_int]
_lib.myelin_function_type_get_param_type.restype  = ctypes.c_void_p

_lib.myelin_function_type_get_param_types.argtypes = [FunctionType]
_lib.myelin_function_type_get_param_types.restype  = ctypes.c_void_p

_lib.myelin_function_type_check_param_types.argtypes = [FunctionType, List]
_lib.myelin_function_type_check_param_types.restype  = ctypes.c_bool

_lib.myelin_function_type_set_instance.argtypes = [FunctionType, Pointer]
_lib.myelin_function_type_set_instance.restype  = None

_lib.myelin_function_type_call.argtypes = [FunctionType, List]
_lib.myelin_function_type_call.restype  = ctypes.c_void_p



# function callback type
CALLBACK_FUNC = ctypes.CFUNCTYPE (ctypes.c_void_p, ctypes.c_void_p)


_lib.myelin_custom_function_type_new.argtypes = [CALLBACK_FUNC]
_lib.myelin_custom_function_type_new.restype  = ctypes.c_void_p

_lib.myelin_custom_function_type_free.argtypes = [CustomFunctionType]
_lib.myelin_custom_function_type_free.restype  = None

_lib.myelin_custom_function_type_add_param_type.argtypes = [CustomFunctionType, Type]
_lib.myelin_custom_function_type_add_param_type.restype  = None

_lib.myelin_custom_function_type_set_return_type.argtypes = [CustomFunctionType, Type]
_lib.myelin_custom_function_type_set_return_type.restype  = None

_lib.myelin_custom_function_type_call.argtypes = [CustomFunctionType, List]
_lib.myelin_custom_function_type_call.restype  = ctypes.c_void_p





import ctypes
import weakref

from type import Type
from list import List
from value import Value


# get library
import myelin.library
_lib = myelin.library.get_library()





def check_param_types (types, params):
    # check param size
    if params.get_size() <> types.get_size():
        raise ValueError ("Parameter list must have '%d' matching values, " \
                          "'%d' was given" %
                          (types.get_size(), params.get_size()))
    
    # check param types
    for i in range(0, len(params)):
        
        # get types
        param_type = params[i].get_type()
        expected_type = Type.from_pointer (types[i].get_pointer().get_raw())
        
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
    
    def __init__ (self, name, type, ptr = None):
        
        if ptr is None:
            ptr = _lib.myelin_function_new (name, type)
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_function_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Function pointer cannot be 'None'")
        
        instance = cls (None, None, ptr)
        _lib.myelin_function_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get_name (self):
        return _lib.myelin_function_get_name (self)
    
    
    def get_type (self):
        type = _lib.myelin_function_get_type (self)
        return FunctionType.from_pointer (type)
    
    
    def is_constant (self):
        return _lib.myelin_function_is_constant (self)
    
    
    def is_virtual (self):
        return _lib.myelin_function_is_virtual (self)
    
    
    def is_pure (self):
        return _lib.myelin_function_is_pure (self)
    
    
    def call (self, params):
#        check_param_types (self.get_type().get_param_types(), params)
        
        val = _lib.myelin_function_call (self, params)
        return Value.from_pointer (val)
    
    
    def bind (self, instance):
        _lib.myelin_function_bind (self, instance)






class FunctionType (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            raise NotImplementedError ("FunctionTypes can only be retrieved")
        
        self._ptr = ptr
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("FunctionType pointer cannot be 'None'")
        return cls (ptr)
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get_return_type (self):
        type = _lib.myelin_function_type_get_return_type (self)
        return Type.from_pointer (type)
    
    
    def get_param_count (self):
        return _lib.myelin_function_type_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = _lib.myelin_function_type_get_param_type (self, index)
        return Type.from_pointer (type)
    
    
    def get_param_types (self):
        list = _lib.myelin_function_type_get_param_types (self)
        return List.from_pointer (list)
    
    
    def check_param_types (self, params):
        return _lib.myelin_function_type_check_param_types (self, params)
    
    
    def set_instance (self, instance):
        _lib.myelin_function_type_set_instance (self, instance)
    
    
    def call (self, params):
        val = _lib.myelin_function_type_call (self, params)
        return Value.from_pointer (val)






class CustomFunctionType (FunctionType):
    
    def __init__ (self, callback, ptr = None):
        
        if ptr is None:
            cb = CALLBACK_FUNC (self._callback)
            ptr = _lib.myelin_custom_function_type_new (cb)
            
            self._callback_type = cb
            self._callback_func = callback
        
        self._ptr = ptr
        self._self_object = None
    
    
    def __del__ (self):
        _lib.myelin_custom_function_type_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("FunctionType pointer cannot be 'None'")
        
        instance = cls (None, ptr)
        _lib.myelin_custom_function_type_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def _callback (self, params):
        
        args = []
        list = List.from_pointer (ctypes.c_void_p (params))
        
        for val in list:
            args.append (val.get())
        
        
        # class method
        if self._self_object is not None:
            ret = self._callback_func (self._self_object(), *args)
        else:
            ret = self._callback_func (*args)
        
        
        if isinstance (ret, Value):
            _lib.myelin_value_ref (ret)
            return ret._ptr
        
        else:
            val = Value()
            
            if ret is not None:
                val.set (ret)
            
            _lib.myelin_value_ref (val)
            return val._ptr
    
    
    
    def set_self_object (self, object):
        self._self_object = weakref.ref (object)
    
    
    
    def add_param_type (self, type):
        _lib.myelin_custom_function_type_add_param_type (self, type)
    
    def set_return_type (self, type):
        _lib.myelin_custom_function_type_set_return_type (self, type)
    
    
    def call (self, params):
        val = _lib.myelin_custom_function_type_call (self, params)
        return Value.from_pointer (val)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_function_new.argtypes = [ctypes.c_char_p, FunctionType]
_lib.myelin_function_new.restype  = ctypes.c_void_p

_lib.myelin_function_ref.argtypes = [Function]
_lib.myelin_function_ref.restype  = ctypes.c_void_p

_lib.myelin_function_unref.argtypes = [Function]
_lib.myelin_function_unref.restype  = None

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

_lib.myelin_function_bind.argtypes = [Function, Value]
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

_lib.myelin_function_type_set_instance.argtypes = [FunctionType, Value]
_lib.myelin_function_type_set_instance.restype  = None

_lib.myelin_function_type_call.argtypes = [FunctionType, List]
_lib.myelin_function_type_call.restype  = ctypes.c_void_p



# function callback type
CALLBACK_FUNC = ctypes.CFUNCTYPE (ctypes.c_void_p, ctypes.c_void_p)


_lib.myelin_custom_function_type_new.argtypes = [CALLBACK_FUNC]
_lib.myelin_custom_function_type_new.restype  = ctypes.c_void_p

_lib.myelin_custom_function_type_ref.argtypes = [CustomFunctionType]
_lib.myelin_custom_function_type_ref.restype  = ctypes.c_void_p

_lib.myelin_custom_function_type_unref.argtypes = [CustomFunctionType]
_lib.myelin_custom_function_type_unref.restype  = None

_lib.myelin_custom_function_type_add_param_type.argtypes = [CustomFunctionType, Type]
_lib.myelin_custom_function_type_add_param_type.restype  = None

_lib.myelin_custom_function_type_set_return_type.argtypes = [CustomFunctionType, Type]
_lib.myelin_custom_function_type_set_return_type.restype  = None

_lib.myelin_custom_function_type_call.argtypes = [CustomFunctionType, List]
_lib.myelin_custom_function_type_call.restype  = ctypes.c_void_p



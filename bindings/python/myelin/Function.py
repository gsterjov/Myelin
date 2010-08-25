
from ctypes import *

from List import List
from Value import Value
from Type import Type
import Library



lib = Library.get_library()



class Function (object):
    
    _function_ptr = None
    
    
    def __init__ (self):
        
        # create a function
        if self._function_ptr is None:
            raise NotImplementedError, 'Meta functions can only be retrieved'
        
        
    @classmethod
    def from_pointer (cls, function_ptr):
        cls._function_ptr = function_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._function_ptr
        
        
        
    def get_name (self):
        return lib.myelin_function_get_name (self)
    
    
    def get_return_type (self):
        return Type.from_pointer (lib.myelin_function_get_return_type (self))
    
    
    def get_param_count (self):
        return lib.myelin_function_get_param_type (self)
    
    
    def get_param_type (self, index):
        return Type.from_pointer (lib.myelin_function_get_param_type (self, index))
    
    
    def get_param_list (self):
        return List.from_pointer (lib.myelin_function_get_param_list (self))
    
    
    def call (self, object, params):
        return Value.from_pointer (lib.myelin_function_call (self, object, params))





# set function prototypes
lib.myelin_function_get_name.argtypes = [Function]
lib.myelin_function_get_name.restype = c_char_p

lib.myelin_function_get_return_type.argtypes = [Function]
lib.myelin_function_get_return_type.restype = c_void_p

lib.myelin_function_get_param_count.argtypes = [Function]
lib.myelin_function_get_param_count.restype = c_int

lib.myelin_function_get_param_type.argtypes = [Function, c_int]
lib.myelin_function_get_param_type.restype = c_void_p

lib.myelin_function_get_param_list.argtypes = [Function]
lib.myelin_function_get_param_list.restype = c_void_p

lib.myelin_function_call.argtypes = [Function, c_void_p, List]
lib.myelin_function_call.restype = c_void_p


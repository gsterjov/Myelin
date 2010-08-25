
from ctypes import *

from List import List
import Library



lib = Library.get_library()



class Class (object):
    
    _class_ptr = None
    
    
    def __init__ (self):
        
        # create a class
        if self._class_ptr is None:
            raise NotImplementedError, 'Meta classes can only be retrieved'
        
        
    @classmethod
    def from_pointer (cls, class_ptr):
        cls._class_ptr = class_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._class_ptr
        
        
        
    def get_name (self):
        return str (lib.myelin_class_get_name (self))
    
    
    def register_function (self, function):
        lib.myelin_class_register_function (self, function)
    
    
    def get_function (self, name):
        return lib.myelin_class_get_function (self, name)
    
    
    def get_function_list (self):
        return List.from_pointer (lib.myelin_class_get_function_list (self))





# set class prototypes
lib.myelin_class_get_name.argtypes = [Class]
lib.myelin_class_get_name.restype = c_char_p

lib.myelin_class_register_function.argtypes = [Class, c_void_p]
lib.myelin_class_register_function.restype = None

lib.myelin_class_get_function.argtypes = [Class, c_char_p]
lib.myelin_class_get_function.restype = c_void_p

lib.myelin_class_get_function_list.argtypes = [Class]
lib.myelin_class_get_function_list.restype = c_void_p


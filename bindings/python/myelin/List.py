
from ctypes import *

from Value import Value
import Library



lib = Library.get_library()



class List (object):
    
    _list_ptr = None
    _can_delete = False
    
    
    def __init__ (self):
        
        # create a list
        if self._list_ptr is None:
            self._list_ptr = lib.myelin_list_new ()
        
        
    def __del__ (self):
        if self._can_delete:
            lib.myelin_list_free (self)
            self._list_ptr = None
            self._can_delete = False
        
        
    @classmethod
    def from_pointer (cls, list_ptr):
        cls._list_ptr = list_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._list_ptr
        
        
        
    def get_size (self):
        return lib.myelin_list_size (self)
    
    
    def get_value (self, index):
        return Value.from_pointer (lib.myelin_list_index (self, index))





# set list prototypes
lib.myelin_list_new.argtypes = None
lib.myelin_list_new.restype = c_void_p

lib.myelin_list_free.argtypes = [List]
lib.myelin_list_free.restype = None

lib.myelin_list_size.argtypes = [List]
lib.myelin_list_size.restype = c_uint

lib.myelin_list_index.argtypes = [List, c_uint]
lib.myelin_list_index.restype = c_void_p



from ctypes import *

import Library



lib = Library.get_library()



class Type (object):
    
    _type_ptr = None
    
    
    def __init__ (self):
        
        # create a type
        if self._type_ptr is None:
            raise NotImplementedError, 'Types can only be retrieved'
        
        
    @classmethod
    def from_pointer (cls, type_ptr):
        cls._type_ptr = type_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._type_ptr


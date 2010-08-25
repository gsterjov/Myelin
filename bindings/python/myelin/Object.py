
from ctypes import *

from List import List
from Value import Value
import Library



lib = Library.get_library()



class Object (object):
    
    _object_ptr = None
    
    
    def __init__ (self):
        
        # create an object
        if self._object_ptr is None:
            raise NotImplementedError, 'Meta objects can only be retrieved'
        
        
    @classmethod
    def from_pointer (cls, object_ptr):
        cls._object_ptr = object_ptr
        return cls()
        
        
        
    def from_param (self):
        return self._object_ptr
        
        
        
    def call (self, name, params):
        return Value.from_pointer (lib.myelin_object_call (self, name, params))





# set object prototypes
lib.myelin_object_call.argtypes = [Object, c_char_p, List]
lib.myelin_object_call.restype = c_void_p


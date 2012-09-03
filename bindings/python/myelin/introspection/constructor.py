#
#    Copyright 2009-2010 Goran Sterjov
#    This file is part of Myelin.
#
#    Myelin is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Myelin is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
#

import ctypes

from type import Type
from value import Value
from list import List


# get library
import myelin.library
_lib = myelin.library.get_library()




class Constructor (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            raise NotImplementedError ("Meta constructors can only be retrieved")
        
        self._ptr = ptr
    
    
    def __repr__ (self):
        
        params = ""
        
        for param in self.get_param_types():
            type = Type.from_pointer (param.as_pointer())
            
            if len(params) > 0:
                params = params + ", " + type.get_name()
            else: params = type.get_name()
        
        if (len(params) > 0):
            params = "requiring the parameters (%s)" % params
        else:
            params = "requiring no parameters"
        
        return ("<%s.%s object at %#x with a constructor object instance at " \
                "%#x %s>" %
                (self.__module__,
                 self.__class__.__name__,
                 id(self),
                 self._ptr,
                 params))
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Constructor pointer cannot be 'None'")
        return cls (ptr)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_param_count (self):
        return _lib.myelin_constructor_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = _lib.myelin_constructor_get_param_type (self, index)
        return Type.from_pointer (type)
    
    
    def get_param_types (self):
        list = _lib.myelin_constructor_get_param_types (self)
        return List.from_pointer (list)
    
    
    def call (self, params):
#        check_param_types (self.get_param_types(), params)
        
        val = _lib.myelin_constructor_call (self, params)
        return Value.from_pointer (val)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_constructor_get_param_count.argtypes = [Constructor]
_lib.myelin_constructor_get_param_count.restype  = ctypes.c_int

_lib.myelin_constructor_get_param_type.argtypes = [Constructor, ctypes.c_int]
_lib.myelin_constructor_get_param_type.restype  = ctypes.c_void_p

_lib.myelin_constructor_get_param_types.argtypes = [Constructor]
_lib.myelin_constructor_get_param_types.restype  = ctypes.c_void_p

_lib.myelin_constructor_call.argtypes = [Constructor, List]
_lib.myelin_constructor_call.restype  = ctypes.c_void_p


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

from value import Value


# get library
import myelin.library
_lib = myelin.library.get_library()




class List (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            ptr = _lib.myelin_list_new ()
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_list_unref (self)
    
    
    def __len__ (self):
        return _lib.myelin_list_size (self)
    
    
    def __getitem__ (self, index):
        if not isinstance (index, int):
            raise TypeError ("The index must be a non-negative integer")
        if index < 0 or index >= _lib.myelin_list_size (self):
            raise IndexError
        
        val = _lib.myelin_list_index (self, index)
        return Value.from_pointer (val)
    
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("List pointer cannot be 'None'")
        
        instance = cls (ptr)
        _lib.myelin_list_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
        
        
    def get_size (self):
        return _lib.myelin_list_size (self)
    
    
    def get_value (self, index):
        val = _lib.myelin_list_index (self, index)
        return Value.from_pointer (val)
    
    
    def append (self, value):
        _lib.myelin_list_append (self, value)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_list_new.argtypes = None
_lib.myelin_list_new.restype  = ctypes.c_void_p

_lib.myelin_list_ref.argtypes = [List]
_lib.myelin_list_ref.restype  = ctypes.c_void_p

_lib.myelin_list_unref.argtypes = [List]
_lib.myelin_list_unref.restype  = None

_lib.myelin_list_size.argtypes = [List]
_lib.myelin_list_size.restype  = ctypes.c_uint

_lib.myelin_list_index.argtypes = [List, ctypes.c_uint]
_lib.myelin_list_index.restype  = ctypes.c_void_p

_lib.myelin_list_append.argtypes = [List, Value]
_lib.myelin_list_append.restype  = None


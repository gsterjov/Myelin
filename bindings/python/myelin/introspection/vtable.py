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

from function import Function


# get library
import myelin.library
_lib = myelin.library.get_library()




class VTable (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            raise NotImplementedError ("A VTable can only be retrieved")
        
        self._ptr = ptr
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("VTable pointer cannot be 'None'")
        return cls (ptr)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get (self):
        func = _lib.myelin_vtable_get (self)
        return Function.from_pointer (func)
    
    
    def set (self, function):
        _lib.myelin_vtable_set (self, function)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_vtable_get.argtypes = [VTable, ctypes.c_char_p]
_lib.myelin_vtable_get.restype  = ctypes.c_void_p

_lib.myelin_vtable_set.argtypes = [VTable, Function]
_lib.myelin_vtable_set.restype  = None


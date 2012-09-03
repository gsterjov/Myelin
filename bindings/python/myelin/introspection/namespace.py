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

from list import List
from class_ import Class


# get library
import myelin.library
_lib = myelin.library.get_library()




class Namespace (object):
    
    def __init__ (self, name, ptr = None):
        
        if ptr is None:
            if name is None:
                raise ValueError ("A namespace name must be provided")
            ptr = _lib.myelin_namespace_new (name)
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_namespace_unref (self)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Namespace pointer cannot be 'None'")
        
        instance = cls (None, ptr)
        _lib.myelin_namespace_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return _lib.myelin_namespace_get_name (self)
    
    
    def add_class (self, klass):
        _lib.myelin_namespace_add_class (self, klass)
    
    
    def get_class (self, name):
        klass = _lib.myelin_namespace_get_class (self, name)
        return Class.from_pointer (klass)
    
    
    def get_classes (self):
        list = _lib.myelin_namespace_get_classes (self)
        return List.from_pointer (list)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_namespace_new.argtypes = [ctypes.c_char_p]
_lib.myelin_namespace_new.restype  = ctypes.c_void_p

_lib.myelin_namespace_ref.argtypes = [Namespace]
_lib.myelin_namespace_ref.restype  = ctypes.c_void_p

_lib.myelin_namespace_unref.argtypes = [Namespace]
_lib.myelin_namespace_unref.restype  = None

_lib.myelin_namespace_get_name.argtypes = [Namespace]
_lib.myelin_namespace_get_name.restype  = ctypes.c_char_p

_lib.myelin_namespace_add_class.argtypes = [Namespace, Class]
_lib.myelin_namespace_add_class.restype  = None

_lib.myelin_namespace_get_class.argtypes = [Namespace, ctypes.c_char_p]
_lib.myelin_namespace_get_class.restype  = ctypes.c_void_p

_lib.myelin_namespace_get_classes.argtypes = [Namespace]
_lib.myelin_namespace_get_classes.restype  = ctypes.c_void_p


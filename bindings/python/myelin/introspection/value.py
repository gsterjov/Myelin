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


# get library
import myelin.library
_lib = myelin.library.get_library()



_types = []


def add_type (klass):
    _types.append (klass)


def get_type (type):
    
    for klass in _types:
        if klass._class.get_type().get_atom() == type.get_atom():
            return klass
    
    return None


def get_types ():
    return _types





class Value (object):
    
    def __init__ (self, ptr = None):
        
        if ptr is None:
            ptr = _lib.myelin_value_new ()
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_value_unref (self)
    
    
    def __repr__ (self):
        return ("<%s.%s object at %#x with an instance of type %s at %#x>" %
               (self.__module__,
                self.__class__.__name__,
                id(self),
                self.get_type().get_name(),
                self.as_pointer()))
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Value pointer cannot be 'None'")
        
        instance = cls (ptr)
        _lib.myelin_value_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get (self):
        
        # empty value
        if self.is_empty(): return None
        
        # get value type
        type = self.get_type()
        atom = type.get_atom()
        
        # convert value types
        if not type.is_pointer() and not type.is_reference():
            
            # fundamental types
            if   atom == Type.type_bool    (): return self.get_bool    ()
            elif atom == Type.type_char    (): return self.get_char    ()
            elif atom == Type.type_uchar   (): return self.get_uchar   ()
            elif atom == Type.type_int     (): return self.get_int     ()
            elif atom == Type.type_uint    (): return self.get_uint    ()
            elif atom == Type.type_long    (): return self.get_long    ()
            elif atom == Type.type_ulong   (): return self.get_ulong   ()
            elif atom == Type.type_int64   (): return self.get_int64   ()
            elif atom == Type.type_uint64  (): return self.get_uint64  ()
            elif atom == Type.type_float   (): return self.get_float   ()
            elif atom == Type.type_double  (): return self.get_double  ()
#            elif atom == Type.type_string  (): return self.get_string  ()
        
        
        # convert value to meta class instance
        class_type = get_type (type)
        
        if class_type is not None:
            return class_type (instance = self)
        
        # dont know how to convert value so just return it as is
        else:
            return self
    
    
    
    def set (self, value, atom = None):
        
        from myelin.module import MetaObject
        
        # convert python types
        if type(value) is bool: self.set_bool (value)
        
        # set the right integer type
        elif type(value) is int or type(value) is long:
            
            if atom is not None:
                if   atom == Type.type_char():  self.set_char  (value)
                elif atom == Type.type_uchar(): self.set_uchar (value)
                elif atom == Type.type_int():   self.set_int   (value)
                elif atom == Type.type_uint():  self.set_uint  (value)
                elif atom == Type.type_long():  self.set_long  (value)
                elif atom == Type.type_ulong(): self.set_ulong (value)
                
                # for long only
                elif type(value) is long:
                    if   atom == Type.type_int64():  self.set_int64 (value)
                    elif atom == Type.type_uint64(): self.set_uint64 (value)
            
            else:
                if type(value) is int: self.set_long (value)
                else: self.set_int64 (value)
        
        
        elif type(value) is float:
            if atom is not None:
                if   atom == Type.type_float():  self.set_float  (value)
                elif atom == Type.type_double(): self.set_double (value)
            
            else: self.set_double (value)
        
        
        elif type(value) is str: self.set_string (value)
        
        
        # set meta object instance
        elif isinstance(value, MetaObject):
            val = value._object.get_instance()
            self.set_pointer (val.get_type(), val.as_pointer())
        
        
        else:
            raise TypeError ("Cannot determine an equivalent type for the " \
                             "value type '%s'. Conversion failed." %
                             type(value))
    
    
    
    
    def get_type (self):
        type = _lib.myelin_value_get_type (self)
        return Type.from_pointer (type)
    
    def is_empty (self):
        return _lib.myelin_value_is_empty (self)
    
    def clear (self):
        _lib.myelin_value_clear (self)
    
    
    def get_bool (self):
        return _lib.myelin_value_get_bool (self)
    def set_bool (self, value):
        _lib.myelin_value_set_bool (self, value)    
    
    def get_char (self):
        return _lib.myelin_value_get_char (self)
    def set_char (self, value):
        _lib.myelin_value_set_char (self, value)
    
    def get_uchar (self):
        return _lib.myelin_value_get_uchar (self)
    def set_uchar (self, value):
        _lib.myelin_value_set_uchar (self, value)
    
    def get_int (self):
        return _lib.myelin_value_get_int (self)
    def set_int (self, value):
        _lib.myelin_value_set_int (self, value)
    
    def get_uint (self):
        return _lib.myelin_value_get_uint (self)
    def set_uint (self, value):
        _lib.myelin_value_set_uint (self, value)
    
    def get_long (self):
        return _lib.myelin_value_get_long (self)
    def set_long (self, value):
        _lib.myelin_value_set_long (self, value)
    
    def get_ulong (self):
        return _lib.myelin_value_get_ulong (self)
    def set_ulong (self, value):
        _lib.myelin_value_set_ulong (self, value)
    
    def get_int64 (self):
        return _lib.myelin_value_get_int64 (self)
    def set_int64 (self, value):
        _lib.myelin_value_set_int64 (self, value)
    
    def get_uint64 (self):
        return _lib.myelin_value_get_uint64 (self)
    def set_uint64 (self, value):
        _lib.myelin_value_set_uint64 (self, value)
    
    def get_float (self):
        return _lib.myelin_value_get_float (self)
    def set_float (self, value):
        _lib.myelin_value_set_float (self, value)
    
    def get_double (self):
        return _lib.myelin_value_get_double (self)
    def set_double (self, value):
        _lib.myelin_value_set_double (self, value)
    
    def get_string (self):
        return _lib.myelin_value_get_string (self)
    def set_string (self, value):
        _lib.myelin_value_set_string (self, value)
    
    def as_pointer (self):
        return _lib.myelin_value_as_pointer (self)
    def set_pointer (self, type, pointer):
        _lib.myelin_value_set_pointer (self, type, pointer)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_value_new.argtypes = None
_lib.myelin_value_new.restype  = ctypes.c_void_p

_lib.myelin_value_ref.argtypes = [Value]
_lib.myelin_value_ref.restype  = ctypes.c_void_p

_lib.myelin_value_unref.argtypes = [Value]
_lib.myelin_value_unref.restype  = None

_lib.myelin_value_get_type.argtypes = [Value]
_lib.myelin_value_get_type.restype  = ctypes.c_void_p

_lib.myelin_value_is_empty.argtypes = [Value]
_lib.myelin_value_is_empty.restype  = ctypes.c_bool

_lib.myelin_value_clear.argtypes = [Value]
_lib.myelin_value_clear.restype  = None


# boolean
_lib.myelin_value_get_bool.argtypes = [Value]
_lib.myelin_value_get_bool.restype  = ctypes.c_bool
_lib.myelin_value_set_bool.argtypes = [Value, ctypes.c_bool]
_lib.myelin_value_set_bool.restype  = None

# char
_lib.myelin_value_get_char.argtypes = [Value]
_lib.myelin_value_get_char.restype  = ctypes.c_char
_lib.myelin_value_set_char.argtypes = [Value, ctypes.c_char]
_lib.myelin_value_set_char.restype  = None

# uchar
_lib.myelin_value_get_uchar.argtypes = [Value]
_lib.myelin_value_get_uchar.restype  = ctypes.c_ubyte
_lib.myelin_value_set_uchar.argtypes = [Value, ctypes.c_ubyte]
_lib.myelin_value_set_uchar.restype  = None

# integer
_lib.myelin_value_get_int.argtypes = [Value]
_lib.myelin_value_get_int.restype  = ctypes.c_int
_lib.myelin_value_set_int.argtypes = [Value, ctypes.c_int]
_lib.myelin_value_set_int.restype  = None

# uint
_lib.myelin_value_get_uint.argtypes = [Value]
_lib.myelin_value_get_uint.restype  = ctypes.c_bool
_lib.myelin_value_set_uint.argtypes = [Value, ctypes.c_uint]
_lib.myelin_value_set_uint.restype  = None

# long
_lib.myelin_value_get_long.argtypes = [Value]
_lib.myelin_value_get_long.restype  = ctypes.c_long
_lib.myelin_value_set_long.argtypes = [Value, ctypes.c_long]
_lib.myelin_value_set_long.restype  = None

# ulong
_lib.myelin_value_get_ulong.argtypes = [Value]
_lib.myelin_value_get_ulong.restype  = ctypes.c_ulong
_lib.myelin_value_set_ulong.argtypes = [Value, ctypes.c_ulong]
_lib.myelin_value_set_ulong.restype  = None

# 64bit integer
_lib.myelin_value_get_int64.argtypes = [Value]
_lib.myelin_value_get_int64.restype  = ctypes.c_int64
_lib.myelin_value_set_int64.argtypes = [Value, ctypes.c_int64]
_lib.myelin_value_set_int64.restype  = None

# unsigned 64bit integer
_lib.myelin_value_get_uint64.argtypes = [Value]
_lib.myelin_value_get_uint64.restype  = ctypes.c_uint64
_lib.myelin_value_set_uint64.argtypes = [Value, ctypes.c_uint64]
_lib.myelin_value_set_uint64.restype  = None

# float
_lib.myelin_value_get_float.argtypes = [Value]
_lib.myelin_value_get_float.restype  = ctypes.c_float
_lib.myelin_value_set_float.argtypes = [Value, ctypes.c_float]
_lib.myelin_value_set_float.restype  = None

# double
_lib.myelin_value_get_double.argtypes = [Value]
_lib.myelin_value_get_double.restype  = ctypes.c_double
_lib.myelin_value_set_double.argtypes = [Value, ctypes.c_double]
_lib.myelin_value_set_double.restype  = None

# string
_lib.myelin_value_get_string.argtypes = [Value]
_lib.myelin_value_get_string.restype  = ctypes.c_char_p
_lib.myelin_value_set_string.argtypes = [Value, ctypes.c_char_p]
_lib.myelin_value_set_string.restype  = None

# pointer
_lib.myelin_value_as_pointer.argtypes = [Value]
_lib.myelin_value_as_pointer.restype  = ctypes.c_void_p
_lib.myelin_value_set_pointer.argtypes = [Value, Type, ctypes.c_void_p]
_lib.myelin_value_set_pointer.restype  = None


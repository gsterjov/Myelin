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
from introspection import Type



class Reference (object):
    
    def __init__ (self, value, atom = None):
        
        # convert python types
        if type(value) is bool:
            self.__type__ = Types.type_bool()
            self.__instance__ = ctypes.c_bool (value)
        
        # set the right integer type
        elif type(value) is int or type(value) is long:
            
            if atom is not None:
                
                if atom == Type.type_char():
                    self.__type__ = Types.type_char()
                    self.__instance__ = ctypes.c_char (value)
                    
                elif atom == Type.type_uchar():
                    self.__type__ = Types.type_uchar()
                    self.__instance__ = ctypes.c_ubyte (value)
                    
                elif atom == Type.type_int():
                    self.__type__ = Types.type_int()
                    self.__instance__ = ctypes.c_int (value)
                    
                elif atom == Type.type_uint():
                    self.__type__ = Types.type_uint()
                    self.__instance__ = ctypes.c_uint (value)
                    
                elif atom == Type.type_long():
                    self.__type__ = Types.type_long()
                    self.__instance__ = ctypes.c_long (value)
                    
                elif atom == Type.type_ulong():
                    self.__type__ = Types.type_ulong()
                    self.__instance__ = ctypes.c_ulong (value)
                
                # for long only
                elif type(value) is long:
                    if atom == Type.type_int64():
                        self.__type__ = Types.type_int64()
                        self.__instance__ = ctypes.c_int64 (value)
                        
                    elif atom == Type.type_uint64():
                        self.__type__ = Types.type_uint64()
                        self.__instance__ = ctypes.c_uint64 (value)
            
            
            if type(value) is long:
                self.__type__ = Types.type_long()
                self.__instance__ = ctypes.c_long (value)
            else:
                self.__type__ = Types.type_int()
                self.__instance__ = ctypes.c_int (value)
        
        
        elif type(value) is float:
            if atom is not None:
                if   atom == Type.type_float():
                    self.__type__ = Types.type_float()
                    self.__instance__ = ctypes.c_float (value)
                    
                elif atom == Type.type_double():
                    self.__type__ = Types.type_double()
                    self.__instance__ = ctypes.c_double (value)
            
            else:
                self.__type__ = Types.type_float()
                self.__instance__ = ctypes.c_float (value)
        
        
        # strings need their own type created since one isn't provided.
        # ultimately 'const char*'s are read by the myelin type system as
        # a 'char' who is constant and a pointer. And so its not fundamental
        elif type(value) is str:
            
            # create string traits
            traits = Type.Traits()
            traits.add_constant()
            traits.add_pointer()
            
            # create type
            self.__type__ = Type (Type.type_char(), traits)
            self.__instance__ = ctypes.c_char_p (value)
        
        
        else: raise TypeError ("Reference values can only be a built-in " \
                               "type: 'bool, int, long, float or str'. " \
                               "Value type given: '%s'" % type(value))
    
    
    @property
    def instance (self):
        return self.__instance__
    
    @property
    def _as_parameter_ (self):
        return self.__instance__.value
    
    
    @property
    def value (self):
        return self.__instance__.value
    
    @property
    def type (self):
        return self.__type__




def byref (value):
    return Reference (value)


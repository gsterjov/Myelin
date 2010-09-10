

import ctypes
from introspection import Type



class Reference (object):
    
    def __init__ (self, value):
        
        
        # convert python types
        if   type(value) is bool:  self.__instance__ = ctypes.c_bool   (value)
        elif type(value) is int:   self.__instance__ = ctypes.c_int    (value)
        elif type(value) is long:  self.__instance__ = ctypes.c_long   (value)
        elif type(value) is float: self.__instance__ = ctypes.c_float  (value)
        elif type(value) is str:   self.__instance__ = ctypes.c_char_p (value)
        
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
    
    
    
    def can_cast_to (self, cast_type):
        
        atom = cast_type.get_atom()
        val_type = type(self.__instance__.value)
        
        
        if atom == Type.type_bool() and val_type is bool:
            return True
        
        if atom == Type.type_char()  or \
           atom == Type.type_uchar() or \
           atom == Type.type_int()   or \
           atom == Type.type_uint()  or \
           atom == Type.type_long()  or \
           atom == Type.type_ulong():
            
            if val_type is int or val_type is long:
                return True
           
        elif atom == Type.type_int64() or atom == Type.type_uint64():
            if val_type is long:
                return True
        
        elif atom == Type.type_float() or atom == Type.type_double():
            if val_type is float:
                return True
        
        elif atom == Type.type_string() and val_type is str:
            return True




def byref (value):
    return Reference (value)


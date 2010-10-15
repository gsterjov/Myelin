

import ctypes


# get library
import myelin.library
_lib = myelin.library.get_library()




class Type (object):
    
    # Atom nested class
    class Atom (object):
        
        def __init__ (self, ptr = None):
            
            if ptr is None:
                raise NotImplementedError ("Type atoms can only be retrieved")
            
            self._ptr = ptr
        
        
        def __eq__ (self, other):
            if type(other) is type(self):
                return other._ptr == self._ptr
            return False
        
        
        def __ne__ (self, other):
            return not self.__eq__ (other)
        
        
        @classmethod
        def from_pointer (cls, ptr):
            if ptr is None:
                raise ValueError ("Type atom pointer cannot be 'None'")
            return cls (ptr)
        
        
        def from_param (self):
            return self._ptr
        
        
        def get_name (self):
            return _lib.myelin_type_atom_get_name (self)
    
    
    
    # Atom nested class
    class Traits (object):
        
        def __init__ (self, ptr = None):
            
            if ptr is None:
                ptr = _lib.myelin_type_traits_new ()
            
            self._ptr = ptr
        
        
        def __del__ (self):
            _lib.myelin_type_traits_unref (self)
        
        
        def __eq__ (self, other):
            if type(other) is type(self):
                return other._ptr == self._ptr
            return False
        
        
        def __ne__ (self, other):
            return not self.__eq__ (other)
        
        
        @classmethod
        def from_pointer (cls, ptr):
            if ptr is None:
                raise ValueError ("Type traits pointer cannot be 'None'")
        
            instance = cls (ptr)
            _lib.myelin_type_traits_ref (instance)
            return instance
        
        
        def from_param (self):
            return self._ptr
        
        
        def add_constant (self):
            return _lib.myelin_type_traits_add_constant (self)
        
        def add_reference (self):
            return _lib.myelin_type_traits_add_reference (self)
        
        def add_pointer (self):
            return _lib.myelin_type_traits_add_pointer (self)
        
        def add_volatile (self):
            return _lib.myelin_type_traits_add_volatile (self)
        
        
        def is_constant (self):
            return _lib.myelin_type_traits_is_constant (self)
        
        def is_reference (self):
            return _lib.myelin_type_traits_is_reference (self)
        
        def is_pointer (self):
            return _lib.myelin_type_traits_is_pointer (self)
        
        def is_volatile (self):
            return _lib.myelin_type_traits_is_volatile (self)
    
    
    
    
    # Type
    def __init__ (self, atom, traits, ptr = None):
        
        if ptr is None:
            ptr = _lib.myelin_type_new (atom, traits)
        
        self._ptr = ptr
    
    
    def __del__ (self):
        _lib.myelin_type_unref (self)
    
    
    def __eq__ (self, other):
        if type(other) is type(self):
            return other._ptr == self._ptr
        return False
    
    
    def __ne__ (self, other):
        return not self.__eq__ (other)
    
    
    @classmethod
    def from_pointer (cls, ptr):
        if ptr is None:
            raise ValueError ("Type pointer cannot be 'None'")
        
        instance = cls (None, None, ptr)
        _lib.myelin_type_ref (instance)
        return instance
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return _lib.myelin_type_get_name (self)
    
    def get_atom (self):
        atom = _lib.myelin_type_get_atom (self)
        return Type.Atom.from_pointer (atom)
    
    def get_traits (self):
        return _lib.myelin_type_get_traits (self)
    
    
    def is_constant (self):
        return _lib.myelin_type_is_constant (self)
    
    def is_reference (self):
        return _lib.myelin_type_is_reference (self)
    
    def is_pointer (self):
        return _lib.myelin_type_is_pointer (self)
    
    def is_volatile (self):
        return _lib.myelin_type_is_volatile (self)
    
    
    def equals (self, type):
        return _lib.myelin_type_equals (self, type)
    
    
    
    @classmethod
    def type_bool (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_bool())
    @classmethod
    def type_char (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_char())
    @classmethod
    def type_uchar (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_uchar())
    @classmethod
    def type_int (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_int())
    @classmethod
    def type_uint (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_uint())
    @classmethod
    def type_long (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_long())
    @classmethod
    def type_ulong (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_ulong())
    @classmethod
    def type_int64 (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_int64())
    @classmethod
    def type_uint64 (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_uint64())
    @classmethod
    def type_float (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_float())
    @classmethod
    def type_double (cls):
        return Type.Atom.from_pointer (_lib.myelin_type_double())
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_type_init.argtypes = None
_lib.myelin_type_init.restype  = None


_lib.myelin_type_traits_new.argtypes = None
_lib.myelin_type_traits_new.restype  = ctypes.c_void_p

_lib.myelin_type_traits_ref.argtypes = [Type.Traits]
_lib.myelin_type_traits_ref.restype  = ctypes.c_void_p

_lib.myelin_type_traits_unref.argtypes = [Type.Traits]
_lib.myelin_type_traits_unref.restype  = None


_lib.myelin_type_traits_add_constant.argtypes = [Type.Traits]
_lib.myelin_type_traits_add_constant.restype  = None
_lib.myelin_type_traits_add_reference.argtypes = [Type.Traits]
_lib.myelin_type_traits_add_reference.restype  = None
_lib.myelin_type_traits_add_pointer.argtypes = [Type.Traits]
_lib.myelin_type_traits_add_pointer.restype  = None
_lib.myelin_type_traits_add_volatile.argtypes = [Type.Traits]
_lib.myelin_type_traits_add_volatile.restype  = None

_lib.myelin_type_traits_is_constant.argtypes = [Type.Traits]
_lib.myelin_type_traits_is_constant.restype  = ctypes.c_bool
_lib.myelin_type_traits_is_reference.argtypes = [Type.Traits]
_lib.myelin_type_traits_is_reference.restype  = ctypes.c_bool
_lib.myelin_type_traits_is_pointer.argtypes = [Type.Traits]
_lib.myelin_type_traits_is_pointer.restype  = ctypes.c_bool
_lib.myelin_type_traits_is_volatile.argtypes = [Type.Traits]
_lib.myelin_type_traits_is_volatile.restype  = ctypes.c_bool


_lib.myelin_type_new.argtypes = [Type.Atom, Type.Traits]
_lib.myelin_type_new.restype  = ctypes.c_void_p

_lib.myelin_type_ref.argtypes = [Type]
_lib.myelin_type_ref.restype  = ctypes.c_void_p

_lib.myelin_type_unref.argtypes = [Type]
_lib.myelin_type_unref.restype  = None

_lib.myelin_type_get_name.argtypes = [Type]
_lib.myelin_type_get_name.restype  = ctypes.c_char_p

_lib.myelin_type_get_atom.argtypes = [Type]
_lib.myelin_type_get_atom.restype  = ctypes.c_void_p

_lib.myelin_type_get_traits.argtypes = [Type]
_lib.myelin_type_get_traits.restype  = ctypes.c_void_p


_lib.myelin_type_is_constant.argtypes = [Type]
_lib.myelin_type_is_constant.restype  = ctypes.c_bool

_lib.myelin_type_is_reference.argtypes = [Type]
_lib.myelin_type_is_reference.restype  = ctypes.c_bool

_lib.myelin_type_is_pointer.argtypes = [Type]
_lib.myelin_type_is_pointer.restype  = ctypes.c_bool

_lib.myelin_type_is_volatile.argtypes = [Type]
_lib.myelin_type_is_volatile.restype  = ctypes.c_bool


_lib.myelin_type_equals.argtypes = [Type, Type]
_lib.myelin_type_equals.restype  = ctypes.c_bool


_lib.myelin_type_bool.argtypes = None
_lib.myelin_type_bool.restype  = ctypes.c_void_p
_lib.myelin_type_char.argtypes = None
_lib.myelin_type_char.restype  = ctypes.c_void_p
_lib.myelin_type_uchar.argtypes = None
_lib.myelin_type_uchar.restype  = ctypes.c_void_p
_lib.myelin_type_int.argtypes = None
_lib.myelin_type_int.restype  = ctypes.c_void_p
_lib.myelin_type_uint.argtypes = None
_lib.myelin_type_uint.restype  = ctypes.c_void_p
_lib.myelin_type_long.argtypes = None
_lib.myelin_type_long.restype  = ctypes.c_void_p
_lib.myelin_type_ulong.argtypes = None
_lib.myelin_type_ulong.restype  = ctypes.c_void_p
_lib.myelin_type_int64.argtypes = None
_lib.myelin_type_int64.restype  = ctypes.c_void_p
_lib.myelin_type_uint64.argtypes = None
_lib.myelin_type_uint64.restype  = ctypes.c_void_p
_lib.myelin_type_float.argtypes = None
_lib.myelin_type_float.restype  = ctypes.c_void_p
_lib.myelin_type_double.argtypes = None
_lib.myelin_type_double.restype  = ctypes.c_void_p


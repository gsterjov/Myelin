


import ctypes
__lib__ = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")
__lib__.myelin_type_init ()






def check_param_types (types, params):
    # check param size
    if params.get_size() <> types.get_size():
        raise ValueError ("Parameter list must have '%d' matching values, " \
                          "'%d' was given" %
                          (types.get_size(), params.get_size()))
    
    # check param types
    for i in range(0, len(params)):
        
        # get types
        param_type = params[i].get_type()
        expected_type = Type.from_pointer (types[i].get_pointer().get_raw(),
                                           False)
        
        # get real pointer type from generic pointer
        if param_type.get_atom() == Type.type_pointer():
            param_type = params[i].get_pointer().get_type()
        
        
        # make sure we have the same type atom
        if param_type.get_atom() != expected_type.get_atom():
            raise TypeError ("Parameter '%d' does not match the appropriate " \
                             "type. Expected '%s', got '%s'" %
                             (i + 1,
                              expected_type.get_name(),
                              param_type.get_name()))
        
        
        # reference parameter types must be a pointer
        if expected_type.is_reference() and not param_type.is_pointer():
            raise TypeError ("Parameter '%d' is a reference type '%s' but " \
                             "the expected type is not a pointer, " \
                             "instead '%s' was given" %
                             (i + 1,
                              expected_type.get_name(),
                              param_type.get_name()))




###############################################
# Type                                        #
###############################################

class Type (object):
    
    # Atom nested class
    class Atom (object):
        def __init__ (self, ptr = None, owner = True):
            # create a type atom
            if ptr is None:
                raise NotImplementedError ("Type atoms can only be retrieved")
            
            self._ptr = ptr
            self._owner = owner
        
        
        def __eq__ (self, other):
            if type(other) is type(self):
                return other._ptr == self._ptr
            return False
        
        
        def __ne__ (self, other):
            return not self.__eq__ (other)
        
        
        @classmethod
        def from_pointer (cls, ptr, owner):
            if ptr is None:
                raise ValueError ("Type atom pointer cannot be 'None'")
            return cls (ptr, owner)
        
        
        def from_param (self):
            return self._ptr
        
        
        def get_name (self):
            return __lib__.myelin_type_atom_get_name (self)
    
    
    
    # Atom nested class
    class Traits (object):
        def __init__ (self, ptr = None, owner = True):
            # create type traits
            if ptr is None:
                ptr = __lib__.myelin_type_traits_create()
            
            self._ptr = ptr
            self._owner = owner
        
        
        def __del__ (self):
            if (self._owner):
                self.free()
        
        
        def __eq__ (self, other):
            if type(other) is type(self):
                return other._ptr == self._ptr
            return False
        
        
        def __ne__ (self, other):
            return not self.__eq__ (other)
        
        
        @classmethod
        def from_pointer (cls, ptr, owner):
            if ptr is None:
                raise ValueError ("Type traits pointer cannot be 'None'")
            return cls (ptr, owner)
        
        @classmethod
        def create (cls):
            return cls (__lib__.myelin_type_traits_create(), True)
        
        
        def from_param (self):
            return self._ptr
        
        
        def free (self):
            if self._ptr is not None:
                self._ptr = __lib__.myelin_type_traits_free (self)
        
        
        def add_constant (self):
            return __lib__.myelin_type_traits_add_constant (self)
        
        def add_reference (self):
            return __lib__.myelin_type_traits_add_reference (self)
        
        def add_pointer (self):
            return __lib__.myelin_type_traits_add_pointer (self)
        
        def add_volatile (self):
            return __lib__.myelin_type_traits_add_volatile (self)
        
        
        def is_constant (self):
            return __lib__.myelin_type_traits_is_constant (self)
        
        def is_reference (self):
            return __lib__.myelin_type_traits_is_reference (self)
        
        def is_pointer (self):
            return __lib__.myelin_type_traits_is_pointer (self)
        
        def is_volatile (self):
            return __lib__.myelin_type_traits_is_volatile (self)
    
    
    
    
    # Type
    def __init__ (self, atom, traits, ptr = None, owner = True):
        # create a type
        if ptr is None:
            ptr = __lib__.myelin_type_create (atom, traits)
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    def __eq__ (self, other):
        if type(other) is type(self):
            return other._ptr == self._ptr
        return False
    
    
    def __ne__ (self, other):
        return not self.__eq__ (other)
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Type pointer cannot be 'None'")
        return cls (None, None, ptr, owner)
    
    @classmethod
    def create (cls, atom, traits):
        return cls (atom, traits)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = __lib__.myelin_type_free (self)
    
    
    def get_name (self):
        return __lib__.myelin_type_get_name (self)
    
    def get_atom (self):
        atom = __lib__.myelin_type_get_atom (self)
        return Type.Atom.from_pointer (atom, False)
    
    def get_traits (self):
        return __lib__.myelin_type_get_traits (self)
    
    
    def is_constant (self):
        return __lib__.myelin_type_is_constant (self)
    
    def is_reference (self):
        return __lib__.myelin_type_is_reference (self)
    
    def is_pointer (self):
        return __lib__.myelin_type_is_pointer (self)
    
    def is_volatile (self):
        return __lib__.myelin_type_is_volatile (self)
    
    
    def equals (self, type):
        return __lib__.myelin_type_equals (self, type)
    
    
    
    @classmethod
    def type_bool (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_bool(), False)
    @classmethod
    def type_char (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_char(), False)
    @classmethod
    def type_uchar (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_uchar(), False)
    @classmethod
    def type_int (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_int(), False)
    @classmethod
    def type_uint (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_uint(), False)
    @classmethod
    def type_long (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_long(), False)
    @classmethod
    def type_ulong (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_ulong(), False)
    @classmethod
    def type_int64 (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_int64(), False)
    @classmethod
    def type_uint64 (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_uint64(), False)
    @classmethod
    def type_float (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_float(), False)
    @classmethod
    def type_double (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_double(), False)
    @classmethod
    def type_string (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_string(), False)
    @classmethod
    def type_pointer (cls):
        return Type.Atom.from_pointer (__lib__.myelin_type_pointer(), False)






###############################################
# Value                                       #
###############################################

class Pointer (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a pointer
        if ptr is None:
            ptr = __lib__.myelin_pointer_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Pointer pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            pass
#            self._ptr = __lib__.myelin_pointer_free (self)
        
        
    def get_type (self):
        return Type.from_pointer (__lib__.myelin_pointer_get_type (self), False)
    
    def is_empty (self):
        return __lib__.myelin_pointer_is_empty (self)
    
    def clear (self):
        __lib__.myelin_pointer_clear (self)
    
    
    def get_raw (self):
        return __lib__.myelin_pointer_get_raw (self)
    
    
    def set (self, ptr, atom):
        __lib__.myelin_pointer_set (self, ptr, atom)
    
    def set_const (self, ptr, atom):
        __lib__.myelin_pointer_set_const (self, ptr, atom)






###############################################
# Value                                       #
###############################################

class Value (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a value
        if ptr is None:
            ptr = __lib__.myelin_value_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Value pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = __lib__.myelin_value_free (self)
        
        
    def get_type (self):
        return Type.from_pointer (__lib__.myelin_value_get_type (self), False)
    
    def is_empty (self):
        return __lib__.myelin_value_is_empty (self)
    
    def clear (self):
        __lib__.myelin_value_clear (self)
    
    
    def get_bool (self):
        return __lib__.myelin_value_get_bool (self)
    def set_bool (self, value):
        __lib__.myelin_value_set_bool (self, value)    
    
    def get_char (self):
        return __lib__.myelin_value_get_char (self)
    def set_char (self, value):
        __lib__.myelin_value_set_char (self, value)
    
    def get_uchar (self):
        return __lib__.myelin_value_get_uchar (self)
    def set_uchar (self, value):
        __lib__.myelin_value_set_uchar (self, value)
    
    def get_int (self):
        return __lib__.myelin_value_get_int (self)
    def set_int (self, value):
        __lib__.myelin_value_set_int (self, value)
    
    def get_uint (self):
        return __lib__.myelin_value_get_uint (self)
    def set_uint (self, value):
        __lib__.myelin_value_set_uint (self, value)
    
    def get_long (self):
        return __lib__.myelin_value_get_long (self)
    def set_long (self, value):
        __lib__.myelin_value_set_long (self, value)
    
    def get_ulong (self):
        return __lib__.myelin_value_get_ulong (self)
    def set_ulong (self, value):
        __lib__.myelin_value_set_ulong (self, value)
    
    def get_int64 (self):
        return __lib__.myelin_value_get_int64 (self)
    def set_int64 (self, value):
        __lib__.myelin_value_set_int64 (self, value)
    
    def get_uint64 (self):
        return __lib__.myelin_value_get_uint64 (self)
    def set_uint64 (self, value):
        __lib__.myelin_value_set_uint64 (self, value)
    
    def get_float (self):
        return __lib__.myelin_value_get_float (self)
    def set_float (self, value):
        __lib__.myelin_value_set_float (self, value)
    
    def get_double (self):
        return __lib__.myelin_value_get_double (self)
    def set_double (self, value):
        __lib__.myelin_value_set_double (self, value)
    
    def get_string (self):
        return __lib__.myelin_value_get_string (self)
    def set_string (self, value):
        __lib__.myelin_value_set_string (self, value)
    
    def get_pointer (self):
        return Pointer.from_pointer (__lib__.myelin_value_get_pointer (self),
                                     True)
    def set_pointer (self, value):
        __lib__.myelin_value_set_pointer (self, value)






###############################################
# List                                        #
###############################################

class List (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a list
        if ptr is None:
            ptr = __lib__.myelin_list_new ()
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    def __len__ (self):
        return __lib__.myelin_list_size (self)
    
    
    def __getitem__ (self, index):
        if not isinstance (index, int):
            raise TypeError ("The index must be a non-negative integer")
        if index < 0 or index >= __lib__.myelin_list_size (self):
            raise IndexError
        
        return Value.from_pointer (__lib__.myelin_list_index (self, index),
                                   True)
    
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("List pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
        
        
    def free (self):
        if self._ptr is not None:
            self._ptr = __lib__.myelin_list_free (self)
        
        
    def get_size (self):
        return __lib__.myelin_list_size (self)
    
    
    def get_value (self, index):
        return Value.from_pointer (__lib__.myelin_list_index (self, index),
                                   True)
    
    
    def append (self, value):
        __lib__.myelin_list_append (self, value)






###############################################
# Object                                      #
###############################################

class Object (object):
    
    def __init__ (self, klass, params, ptr = None, owner = True):
        # create an object
        if ptr is None:
            if klass is None:
                raise ValueError ("A class must be provided")
            if params is None:
                raise ValueError ("A parameter list must be provided")
            
            ptr = __lib__.myelin_object_new (klass, params)
        
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner):
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Object pointer cannot be 'None'")
        return cls (None, None, ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def free (self):
        if self._ptr is not None:
            self._ptr = __lib__.myelin_object_free (self)
    
    
    def call (self, name, params):
        val = __lib__.myelin_object_call (self, name, params)
        return Value.from_pointer (val, True)
    
    
    def set_instance (self, instance):
        __lib__.myelin_object_set_instance (self, instance)
    
    
    def get_instance (self):
        return __lib__.myelin_object_get_instance (self)






###############################################
# Function                                    #
###############################################

class Function (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a function
        if ptr is None:
            raise NotImplementedError ("Meta functions can only be retrieved")
        
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Function pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    
    def get_name (self):
        return __lib__.myelin_function_get_name (self)
    
    
    def get_return_type (self):
        type = __lib__.myelin_function_get_return_type (self)
        return Type.from_pointer (type, False)
    
    
    def get_param_count (self):
        return __lib__.myelin_function_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = __lib__.myelin_function_get_param_type (self, index)
        return Type.from_pointer (type, False)
    
    
    def get_param_list (self):
        list = __lib__.myelin_function_get_param_list (self)
        return List.from_pointer (list, True)
    
    
    def call (self, instance, params):
        check_param_types (self.get_param_list(), params)
        
        val = __lib__.myelin_function_call (self, instance, params)
        return Value.from_pointer (val, True)






###############################################
# Constructor                                 #
###############################################

class Constructor (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a constructor
        if ptr is None:
            raise NotImplementedError ("Meta constructors can only be retrieved")
        
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Constructor pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_param_count (self):
        return __lib__.myelin_constructor_get_param_count (self)
    
    
    def get_param_type (self, index):
        type = __lib__.myelin_constructor_get_param_type (self, index)
        return Type.from_pointer (type, False)
    
    
    def get_param_list (self):
        list = __lib__.myelin_constructor_get_param_list (self)
        return List.from_pointer (list, True)
    
    
    def call (self, params):
        check_param_types (self.get_param_list(), params)
        
        val = __lib__.myelin_constructor_call (self, params)
        return Value.from_pointer (val, True)







###############################################
# Class                                       #
###############################################

class Class (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a class
        if ptr is None:
            raise NotImplementedError ("Meta classes can only be retrieved")
        
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Class pointer cannot be 'None'")
        return cls (ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def get_name (self):
        return __lib__.myelin_class_get_name (self)
    
    
    def get_namespace (self):
        list = List.from_pointer (__lib__.myelin_class_get_namespace (self),
                                  True)
        
        namespace = []
        for val in list:
            namespace.append (val.get_string())
        return namespace
    
    
    def register_constructor (self, constructor):
        __lib__.myelin_class_register_constructor (self, constructor)
    
    
    def get_constructor_list (self):
        list = __lib__.myelin_class_get_constructor_list (self)
        return List.from_pointer (list, True)
    
    
    
    def register_function (self, function):
        __lib__.myelin_class_register_function (self, function)
    
    
    def get_function (self, name):
        func = __lib__.myelin_class_get_function (self, name)
        return Function.from_pointer (func, False)
    
    
    def get_function_list (self):
        list = __lib__.myelin_class_get_function_list (self)
        return List.from_pointer (list, True)
    
    
    
    def create_instance (self, params):
        return __lib__.myelin_class_create_instance (self, params)
    
    
    def create_object (self, params):
        obj = __lib__.myelin_class_create_object (self, params)
        return Object.from_pointer (obj, True)
    
    
    def create_object_instance (self, instance):
        obj = __lib__.myelin_class_create_object_instance (self, instance)
        return Object.from_pointer (obj, True)






###############################################
# Repository                                  #
###############################################

class Repository (object):
    
    def __init__ (self, name, ptr = None, owner = True):
        # create a repository
        if ptr is None:
            if name is None:
                raise ValueError ("A repository name must be provided")
            ptr = __lib__.myelin_repository_new (name)
        
        # generic pointer type
        elif isinstance(ptr, Pointer):
            self._ptr = ptr.get_raw()
        
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if self._owner:
            self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None:
            raise ValueError ("Repository pointer cannot be 'None'")
        return cls (None, ptr, owner)
    
    
    def from_param (self):
        return self._ptr
    
    
    def free (self):
        if self._ptr is not None:
            self_.ptr = __lib__.myelin_repository_free (self)
    
    
    def get_name (self):
        return __lib__.myelin_repository_get_name (self)
    
    
    def get_class (self, name):
        klass = __lib__.myelin_repository_get_class (self, name)
        return Class.from_pointer (klass, False)
    
    
    def register_class (self, klass):
        __lib__.myelin_repository_register_class (self, klass)
    
    
    def get_class_list (self):
        list = __lib__.myelin_repository_get_class_list (self)
        return List.from_pointer (list, True)






###############################################
# Repository Factory                          #
###############################################

class RepositoryFactory (object):
    
    @classmethod
    def create (cls, name):
        repo = __lib__.myelin_repository_factory_create (name)
        return Repository.from_pointer (repo, True)
    
    
    @classmethod
    def get (cls, name):
        repo = __lib__.myelin_repository_factory_get (name)
        return Repository.from_pointer (repo, False)
    
    
    @classmethod
    def add (cls, repo):
        __lib__.myelin_repository_factory_add (repo)
    
    
    @classmethod
    def get_repository_list (cls):
        list = __lib__.myelin_repository_factory_get_repository_list()
        return List.from_pointer (list, True)







###############################################
# Set Type Prototypes                         #
###############################################

__lib__.myelin_type_init.argtypes = None
__lib__.myelin_type_init.restype  = None


__lib__.myelin_type_traits_create.argtypes = None
__lib__.myelin_type_traits_create.restype  = ctypes.c_void_p

__lib__.myelin_type_traits_free.argtypes = [Type.Traits]
__lib__.myelin_type_traits_free.restype  = None


__lib__.myelin_type_traits_add_constant.argtypes = [Type.Traits]
__lib__.myelin_type_traits_add_constant.restype  = None
__lib__.myelin_type_traits_add_reference.argtypes = [Type.Traits]
__lib__.myelin_type_traits_add_reference.restype  = None
__lib__.myelin_type_traits_add_pointer.argtypes = [Type.Traits]
__lib__.myelin_type_traits_add_pointer.restype  = None
__lib__.myelin_type_traits_add_volatile.argtypes = [Type.Traits]
__lib__.myelin_type_traits_add_volatile.restype  = None

__lib__.myelin_type_traits_is_constant.argtypes = [Type.Traits]
__lib__.myelin_type_traits_is_constant.restype  = ctypes.c_bool
__lib__.myelin_type_traits_is_reference.argtypes = [Type.Traits]
__lib__.myelin_type_traits_is_reference.restype  = ctypes.c_bool
__lib__.myelin_type_traits_is_pointer.argtypes = [Type.Traits]
__lib__.myelin_type_traits_is_pointer.restype  = ctypes.c_bool
__lib__.myelin_type_traits_is_volatile.argtypes = [Type.Traits]
__lib__.myelin_type_traits_is_volatile.restype  = ctypes.c_bool


__lib__.myelin_type_create.argtypes = [Type.Atom, Type.Traits]
__lib__.myelin_type_create.restype  = ctypes.c_void_p

__lib__.myelin_type_free.argtypes = [Type]
__lib__.myelin_type_free.restype  = None

__lib__.myelin_type_get_name.argtypes = [Type]
__lib__.myelin_type_get_name.restype  = ctypes.c_char_p

__lib__.myelin_type_get_atom.argtypes = [Type]
__lib__.myelin_type_get_atom.restype  = ctypes.c_void_p

__lib__.myelin_type_get_traits.argtypes = [Type]
__lib__.myelin_type_get_traits.restype  = ctypes.c_void_p


__lib__.myelin_type_is_constant.argtypes = [Type]
__lib__.myelin_type_is_constant.restype  = ctypes.c_bool

__lib__.myelin_type_is_reference.argtypes = [Type]
__lib__.myelin_type_is_reference.restype  = ctypes.c_bool

__lib__.myelin_type_is_pointer.argtypes = [Type]
__lib__.myelin_type_is_pointer.restype  = ctypes.c_bool

__lib__.myelin_type_is_volatile.argtypes = [Type]
__lib__.myelin_type_is_volatile.restype  = ctypes.c_bool


__lib__.myelin_type_equals.argtypes = [Type, Type]
__lib__.myelin_type_equals.restype  = ctypes.c_bool


__lib__.myelin_type_bool.argtypes = None
__lib__.myelin_type_bool.restype  = ctypes.c_void_p
__lib__.myelin_type_char.argtypes = None
__lib__.myelin_type_char.restype  = ctypes.c_void_p
__lib__.myelin_type_uchar.argtypes = None
__lib__.myelin_type_uchar.restype  = ctypes.c_void_p
__lib__.myelin_type_int.argtypes = None
__lib__.myelin_type_int.restype  = ctypes.c_void_p
__lib__.myelin_type_uint.argtypes = None
__lib__.myelin_type_uint.restype  = ctypes.c_void_p
__lib__.myelin_type_long.argtypes = None
__lib__.myelin_type_long.restype  = ctypes.c_void_p
__lib__.myelin_type_ulong.argtypes = None
__lib__.myelin_type_ulong.restype  = ctypes.c_void_p
__lib__.myelin_type_int64.argtypes = None
__lib__.myelin_type_int64.restype  = ctypes.c_void_p
__lib__.myelin_type_uint64.argtypes = None
__lib__.myelin_type_uint64.restype  = ctypes.c_void_p
__lib__.myelin_type_float.argtypes = None
__lib__.myelin_type_float.restype  = ctypes.c_void_p
__lib__.myelin_type_double.argtypes = None
__lib__.myelin_type_double.restype  = ctypes.c_void_p
__lib__.myelin_type_string.argtypes = None
__lib__.myelin_type_string.restype  = ctypes.c_void_p
__lib__.myelin_type_pointer.argtypes = None
__lib__.myelin_type_pointer.restype  = ctypes.c_void_p




###############################################
# Set Pointer Prototypes                      #
###############################################

__lib__.myelin_pointer_new.argtypes = None
__lib__.myelin_pointer_new.restype  = ctypes.c_void_p

__lib__.myelin_pointer_free.argtypes = [Pointer]
__lib__.myelin_pointer_free.restype  = None

__lib__.myelin_pointer_get_type.argtypes = [Pointer]
__lib__.myelin_pointer_get_type.restype  = ctypes.c_void_p

__lib__.myelin_pointer_is_empty.argtypes = [Pointer]
__lib__.myelin_pointer_is_empty.restype  = ctypes.c_bool

__lib__.myelin_pointer_clear.argtypes = [Pointer]
__lib__.myelin_pointer_clear.restype  = None

__lib__.myelin_pointer_get_raw.argtypes = [Pointer]
__lib__.myelin_pointer_get_raw.restype  = ctypes.c_void_p

__lib__.myelin_pointer_set.argtypes = [Pointer, ctypes.c_void_p, Type.Atom]
__lib__.myelin_pointer_set.restype  = None

__lib__.myelin_pointer_set_const.argtypes = [Pointer, ctypes.c_void_p, Type.Atom]
__lib__.myelin_pointer_set_const.restype  = None




###############################################
# Set Value Prototypes                        #
###############################################

__lib__.myelin_value_new.argtypes = None
__lib__.myelin_value_new.restype  = ctypes.c_void_p

__lib__.myelin_value_free.argtypes = [Value]
__lib__.myelin_value_free.restype  = None

__lib__.myelin_value_get_type.argtypes = [Value]
__lib__.myelin_value_get_type.restype  = ctypes.c_void_p

__lib__.myelin_value_is_empty.argtypes = [Value]
__lib__.myelin_value_is_empty.restype  = ctypes.c_bool

__lib__.myelin_value_clear.argtypes = [Value]
__lib__.myelin_value_clear.restype  = None


# boolean
__lib__.myelin_value_get_bool.argtypes = [Value]
__lib__.myelin_value_get_bool.restype  = ctypes.c_bool
__lib__.myelin_value_set_bool.argtypes = [Value, ctypes.c_bool]
__lib__.myelin_value_set_bool.restype  = None

# char
__lib__.myelin_value_get_char.argtypes = [Value]
__lib__.myelin_value_get_char.restype  = ctypes.c_char
__lib__.myelin_value_set_char.argtypes = [Value, ctypes.c_char]
__lib__.myelin_value_set_char.restype  = None

# uchar
__lib__.myelin_value_get_uchar.argtypes = [Value]
__lib__.myelin_value_get_uchar.restype  = ctypes.c_ubyte
__lib__.myelin_value_set_uchar.argtypes = [Value, ctypes.c_ubyte]
__lib__.myelin_value_set_uchar.restype  = None

# integer
__lib__.myelin_value_get_int.argtypes = [Value]
__lib__.myelin_value_get_int.restype  = ctypes.c_int
__lib__.myelin_value_set_int.argtypes = [Value, ctypes.c_int]
__lib__.myelin_value_set_int.restype  = None

# uint
__lib__.myelin_value_get_uint.argtypes = [Value]
__lib__.myelin_value_get_uint.restype  = ctypes.c_bool
__lib__.myelin_value_set_uint.argtypes = [Value, ctypes.c_uint]
__lib__.myelin_value_set_uint.restype  = None

# long
__lib__.myelin_value_get_long.argtypes = [Value]
__lib__.myelin_value_get_long.restype  = ctypes.c_long
__lib__.myelin_value_set_long.argtypes = [Value, ctypes.c_long]
__lib__.myelin_value_set_long.restype  = None

# ulong
__lib__.myelin_value_get_ulong.argtypes = [Value]
__lib__.myelin_value_get_ulong.restype  = ctypes.c_ulong
__lib__.myelin_value_set_ulong.argtypes = [Value, ctypes.c_ulong]
__lib__.myelin_value_set_ulong.restype  = None

# 64bit integer
__lib__.myelin_value_get_int64.argtypes = [Value]
__lib__.myelin_value_get_int64.restype  = ctypes.c_int64
__lib__.myelin_value_set_int64.argtypes = [Value, ctypes.c_int64]
__lib__.myelin_value_set_int64.restype  = None

# unsigned 64bit integer
__lib__.myelin_value_get_uint64.argtypes = [Value]
__lib__.myelin_value_get_uint64.restype  = ctypes.c_uint64
__lib__.myelin_value_set_uint64.argtypes = [Value, ctypes.c_uint64]
__lib__.myelin_value_set_uint64.restype  = None

# float
__lib__.myelin_value_get_float.argtypes = [Value]
__lib__.myelin_value_get_float.restype  = ctypes.c_float
__lib__.myelin_value_set_float.argtypes = [Value, ctypes.c_float]
__lib__.myelin_value_set_float.restype  = None

# double
__lib__.myelin_value_get_double.argtypes = [Value]
__lib__.myelin_value_get_double.restype  = ctypes.c_double
__lib__.myelin_value_set_double.argtypes = [Value, ctypes.c_double]
__lib__.myelin_value_set_double.restype  = None

# string
__lib__.myelin_value_get_string.argtypes = [Value]
__lib__.myelin_value_get_string.restype  = ctypes.c_char_p
__lib__.myelin_value_set_string.argtypes = [Value, ctypes.c_char_p]
__lib__.myelin_value_set_string.restype  = None

# pointer
__lib__.myelin_value_get_pointer.argtypes = [Value]
__lib__.myelin_value_get_pointer.restype  = ctypes.c_void_p
__lib__.myelin_value_set_pointer.argtypes = [Value, Pointer]
__lib__.myelin_value_set_pointer.restype  = None




###############################################
# Set List Prototypes                         #
###############################################

__lib__.myelin_list_new.argtypes = None
__lib__.myelin_list_new.restype  = ctypes.c_void_p

__lib__.myelin_list_free.argtypes = [List]
__lib__.myelin_list_free.restype  = None

__lib__.myelin_list_size.argtypes = [List]
__lib__.myelin_list_size.restype  = ctypes.c_uint

__lib__.myelin_list_index.argtypes = [List, ctypes.c_uint]
__lib__.myelin_list_index.restype  = ctypes.c_void_p

__lib__.myelin_list_append.argtypes = [List, Value]
__lib__.myelin_list_append.restype  = None




###############################################
# Set Object Prototypes                       #
###############################################

__lib__.myelin_object_new.argtypes = [Class, List]
__lib__.myelin_object_new.restype  = ctypes.c_void_p

__lib__.myelin_object_new_instance.argtypes = [Class, ctypes.c_void_p]
__lib__.myelin_object_new_instance.restype  = ctypes.c_void_p

__lib__.myelin_object_free.argtypes = [Object]
__lib__.myelin_object_free.restype  = None


__lib__.myelin_object_call.argtypes = [Object, ctypes.c_char_p, List]
__lib__.myelin_object_call.restype  = ctypes.c_void_p


__lib__.myelin_object_set_instance.argtypes = [Object, ctypes.c_void_p]
__lib__.myelin_object_set_instance.restype  = None

__lib__.myelin_object_get_instance.argtypes = [Object]
__lib__.myelin_object_get_instance.restype  = ctypes.c_void_p




###############################################
# Set Function Prototypes                     #
###############################################

__lib__.myelin_function_get_name.argtypes = [Function]
__lib__.myelin_function_get_name.restype  = ctypes.c_char_p

__lib__.myelin_function_get_return_type.argtypes = [Function]
__lib__.myelin_function_get_return_type.restype  = ctypes.c_void_p

__lib__.myelin_function_get_param_count.argtypes = [Function]
__lib__.myelin_function_get_param_count.restype  = ctypes.c_int

__lib__.myelin_function_get_param_type.argtypes = [Function, ctypes.c_int]
__lib__.myelin_function_get_param_type.restype  = ctypes.c_void_p

__lib__.myelin_function_get_param_list.argtypes = [Function]
__lib__.myelin_function_get_param_list.restype  = ctypes.c_void_p

__lib__.myelin_function_call.argtypes = [Function, ctypes.c_void_p, List]
__lib__.myelin_function_call.restype  = ctypes.c_void_p




###############################################
# Set Constructor Prototypes                  #
###############################################

__lib__.myelin_constructor_get_param_count.argtypes = [Constructor]
__lib__.myelin_constructor_get_param_count.restype  = ctypes.c_int

__lib__.myelin_constructor_get_param_type.argtypes = [Constructor, ctypes.c_int]
__lib__.myelin_constructor_get_param_type.restype  = ctypes.c_void_p

__lib__.myelin_constructor_get_param_list.argtypes = [Constructor]
__lib__.myelin_constructor_get_param_list.restype  = ctypes.c_void_p

__lib__.myelin_constructor_call.argtypes = [Constructor, List]
__lib__.myelin_constructor_call.restype  = ctypes.c_void_p




###############################################
# Set Class Prototypes                        #
###############################################

__lib__.myelin_class_get_name.argtypes = [Class]
__lib__.myelin_class_get_name.restype  = ctypes.c_char_p

__lib__.myelin_class_get_namespace.argtypes = [Class]
__lib__.myelin_class_get_namespace.restype  = ctypes.c_void_p

__lib__.myelin_class_register_constructor.argtypes = [Class, Constructor]
__lib__.myelin_class_register_constructor.restype  = None

__lib__.myelin_class_get_constructor_list.argtypes = [Class]
__lib__.myelin_class_get_constructor_list.restype  = ctypes.c_void_p

__lib__.myelin_class_register_function.argtypes = [Class, Function]
__lib__.myelin_class_register_function.restype  = None

__lib__.myelin_class_get_function.argtypes = [Class, ctypes.c_char_p]
__lib__.myelin_class_get_function.restype  = ctypes.c_void_p

__lib__.myelin_class_get_function_list.argtypes = [Class]
__lib__.myelin_class_get_function_list.restype  = ctypes.c_void_p


__lib__.myelin_class_create_instance.argtypes = [Class, List]
__lib__.myelin_class_create_instance.restype  = ctypes.c_void_p

__lib__.myelin_class_create_object.argtypes = [Class, List]
__lib__.myelin_class_create_object.restype  = ctypes.c_void_p

__lib__.myelin_class_create_object_instance.argtypes = [Class, ctypes.c_void_p]
__lib__.myelin_class_create_object_instance.restype  = ctypes.c_void_p




###############################################
# Set Repository Prototypes                   #
###############################################

__lib__.myelin_repository_new.argtypes = [ctypes.c_char_p]
__lib__.myelin_repository_new.restype  = ctypes.c_void_p

__lib__.myelin_repository_free.argtypes = [Repository]
__lib__.myelin_repository_free.restype  = None

__lib__.myelin_repository_get_name.argtypes = [Repository]
__lib__.myelin_repository_get_name.restype  = ctypes.c_char_p

__lib__.myelin_repository_get_class.argtypes = [Repository, ctypes.c_char_p]
__lib__.myelin_repository_get_class.restype  = ctypes.c_void_p

__lib__.myelin_repository_register_class.argtypes = [Repository, ctypes.c_void_p]
__lib__.myelin_repository_register_class.restype  = None

__lib__.myelin_repository_get_class_list.argtypes = [Repository]
__lib__.myelin_repository_get_class_list.restype  = ctypes.c_void_p




###############################################
# Set Repository Factory Prototypes           #
###############################################

__lib__.myelin_repository_factory_create.argtypes = [ctypes.c_char_p]
__lib__.myelin_repository_factory_create.restype  = ctypes.c_void_p

__lib__.myelin_repository_factory_get.argtypes = [ctypes.c_char_p]
__lib__.myelin_repository_factory_get.restype  = ctypes.c_void_p

__lib__.myelin_repository_factory_add.argtypes = [Repository]
__lib__.myelin_repository_factory_add.restype  = None

__lib__.myelin_repository_factory_get_repository_list.argtypes = None
__lib__.myelin_repository_factory_get_repository_list.restype  = ctypes.c_void_p





import ctypes
__lib__ = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")





###############################################
# Type                                        #
###############################################

class Type (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a type
        if ptr is None: raise NotImplementedError, 'Types can only be retrieved'
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Type pointer cannot be 'None'"
        return cls (ptr, owner)
    
    
    def from_param (self): return self._ptr






###############################################
# Value                                       #
###############################################

class Value (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a value
        if ptr is None: ptr = __lib__.myelin_value_new ()
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner): self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Value pointer cannot be 'None'"
        return cls (ptr, owner)
    
    
    def from_param (self): return self._ptr
        
        
    def free (self):
        if self._ptr is not None: self._ptr = __lib__.myelin_value_free (self)
        
        
    def get_type (self):
        return Type.from_pointer (__lib__.myelin_value_get_type (self), True)
        
        
    def get_bool (self): return __lib__.myelin_value_get_bool (self)
    def set_bool (self, value): __lib__.myelin_value_set_bool (self, value)    
    
    def get_char (self): return __lib__.myelin_value_get_char (self)
    def set_char (self, value): __lib__.myelin_value_set_char (self, value)
    
    def get_uchar (self): return __lib__.myelin_value_get_uchar (self)
    def set_uchar (self, value): __lib__.myelin_value_set_uchar (self, value)
    
    def get_int (self): return __lib__.myelin_value_get_int (self)
    def set_int (self, value): __lib__.myelin_value_set_int (self, value)
    
    def get_uint (self): return __lib__.myelin_value_get_uint (self)
    def set_uint (self, value): __lib__.myelin_value_set_uint (self, value)
    
    def get_long (self): return __lib__.myelin_value_get_long (self)
    def set_long (self, value): __lib__.myelin_value_set_long (self, value)
    
    def get_ulong (self): return __lib__.myelin_value_get_ulong (self)
    def set_ulong (self, value): __lib__.myelin_value_set_ulong (self, value)
    
    def get_int64 (self): return __lib__.myelin_value_get_int64 (self)
    def set_int64 (self, value): __lib__.myelin_value_set_int64 (self, value)
    
    def get_uint64 (self): return __lib__.myelin_value_get_uint64 (self)
    def set_uint64 (self, value): __lib__.myelin_value_set_uint64 (self, value)
    
    def get_float (self): return __lib__.myelin_value_get_float (self)
    def set_float (self, value): __lib__.myelin_value_set_float (self, value)
    
    def get_double (self): return __lib__.myelin_value_get_double (self)
    def set_double (self, value): __lib__.myelin_value_set_double (self, value)
    
    def get_string (self): return __lib__.myelin_value_get_string (self)
    def set_string (self, value): __lib__.myelin_value_set_string (self, value)
    
    def get_pointer (self): return __lib__.myelin_value_get_pointer (self)
    def set_pointer (self, value): __lib__.myelin_value_set_pointer (self, value)






###############################################
# List                                        #
###############################################

class List (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a list
        if ptr is None: ptr = __lib__.myelin_list_new ()
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner): self.free()
    
    
    def __len__ (self):
        return __lib__.myelin_list_size (self)
    
    
    def __getitem__ (self, index):
        if not isinstance (index, int): raise TypeError, "The index must be a non-negative integer"
        if index >= __lib__.myelin_list_size (self): raise IndexError
        
        return Value.from_pointer (__lib__.myelin_list_index (self, index), True)
    
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "List pointer cannot be 'None'"
        return cls (ptr, owner)
    
    
    def from_param (self): return self._ptr
        
        
    def free (self):
        if self._ptr is not None: self._ptr = __lib__.myelin_list_free (self)
        
        
    def get_size (self):
        return __lib__.myelin_list_size (self)
    
    
    def get_value (self, index):
        return Value.from_pointer (__lib__.myelin_list_index (self, index), True)
    
    
    def append (self, value):
        __lib__.myelin_list_append (self, value)






###############################################
# Object                                      #
###############################################

class Object (object):
    
    def __init__ (self, klass, params, ptr = None, owner = True):
        # create an object
        if ptr is None:
            if klass is None: raise ValueError, "A class must be provided"
            if params is None: raise ValueError, "A parameter list must be provided"
            
            ptr = __lib__.myelin_object_new (klass, params)
        
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if (self._owner): self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Object pointer cannot be 'None'"
        return cls (None, None, ptr, owner)
    
    
    def from_param (self): return self._ptr
    
    
    def free (self):
        if self._ptr is not None: self._ptr = __lib__.myelin_object_free (self)
    
    
    def call (self, name, params):
        return Value.from_pointer (__lib__.myelin_object_call (self, name, params), True)
    
    
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
        if ptr is None: raise NotImplementedError, 'Meta functions can only be retrieved'
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Function pointer cannot be 'None'"
        return cls (ptr, owner)
    
    
    def from_param (self): return self._ptr
    
    
    
    def get_name (self):
        return __lib__.myelin_function_get_name (self)
    
    
    def get_return_type (self):
        return Type.from_pointer (__lib__.myelin_function_get_return_type (self), True)
    
    
    def get_param_count (self):
        return __lib__.myelin_function_get_param_count (self)
    
    
    def get_param_type (self, index):
        return Type.from_pointer (__lib__.myelin_function_get_param_type (self, index), True)
    
    
    def get_param_list (self):
        return List.from_pointer (__lib__.myelin_function_get_param_list (self), True)
    
    
    def call (self, object, params):
        if params.get_size() <> self.get_param_count():
            raise ValueError, "Parameter list must have '%d' matching values, '%d' was given" % (self.get_param_count(), params.get_size())
        
        for index in range(0, params.get_size()):
            if params[index].get_type() != self.get_param_type (index):
                raise TypeError, "Parameter '%d' does not match the appropriate type" % (index+1)
        
        return Value.from_pointer (__lib__.myelin_function_call (self, object, params), True)






###############################################
# Class                                       #
###############################################

class Class (object):
    
    def __init__ (self, ptr = None, owner = True):
        # create a class
        if ptr is None: raise NotImplementedError, 'Meta classes can only be retrieved'
        self._ptr = ptr
        self._owner = owner
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Class pointer cannot be 'None'"
        return cls (ptr, owner)
    
    
    def from_param (self): return self._ptr
    
    
    def get_name (self):
        return __lib__.myelin_class_get_name (self)
    
    
    def register_function (self, function):
        __lib__.myelin_class_register_function (self, function)
    
    
    def get_function (self, name):
        return Function.from_pointer (__lib__.myelin_class_get_function (self, name), False)
    
    
    def get_function_list (self):
        return List.from_pointer (__lib__.myelin_class_get_function_list (self), True)
    
    
    
    def create_instance (self, params):
        return __lib__.myelin_class_create_instance (self, params)
    
    
    def create_object (self, params):
        return Object.from_pointer (__lib__.myelin_class_create_object (self, params), True)






###############################################
# Repository                                  #
###############################################

class Repository (object):
    
    def __init__ (self, name, ptr = None, owner = True):
        # create a repository
        if ptr is None:
            if name is None:
                raise ValueError, "A repository name must be provided"
            ptr = __lib__.myelin_repository_new (name)
            
        self._ptr = ptr
        self._owner = owner
    
    
    def __del__ (self):
        if self._owner: self.free()
    
    
    @classmethod
    def from_pointer (cls, ptr, owner):
        if ptr is None: raise ValueError, "Repository pointer cannot be 'None'"
        return cls (None, ptr, owner)
    
    
    def from_param (self): return self._ptr
    
    
    def free (self):
        if self._ptr is not None: self_.ptr = __lib__.myelin_repository_free (self)
    
    
    def get_name (self):
        return __lib__.myelin_repository_get_name (self)
    
    
    def get_class (self, name):
        return Class.from_pointer (__lib__.myelin_repository_get_class (self, name), False)
    
    
    def register_class (self, klass):
        __lib__.myelin_repository_register_class (self, klass)
    
    
    def get_class_list (self):
        return List.from_pointer (__lib__.myelin_repository_get_class_list (self), True)






###############################################
# Repository Factory                          #
###############################################

class RepositoryFactory (object):
    
    @classmethod
    def create (cls, name):
        return Repository.from_pointer (__lib__.myelin_repository_factory_create (name), True)
    
    
    @classmethod
    def get (cls, name):
        return Repository.from_pointer (__lib__.myelin_repository_factory_get (name), False)
    
    
    @classmethod
    def add (cls, repo):
        __lib__.myelin_repository_factory_add (repo)
    
    
    @classmethod
    def get_repository_list (cls):
        return List.from_pointer (__lib__.myelin_repository_factory_get_repository_list(), True)







###############################################
# Set Value Prototypes                        #
###############################################

__lib__.myelin_value_new.argtypes = None
__lib__.myelin_value_new.restype  = ctypes.c_void_p

__lib__.myelin_value_free.argtypes = [Value]
__lib__.myelin_value_free.restype  = None

__lib__.myelin_value_get_type.argtypes = [Value]
__lib__.myelin_value_get_type.restype  = ctypes.c_void_p


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
__lib__.myelin_value_set_pointer.argtypes = [Value, ctypes.c_void_p]
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

__lib__.myelin_function_call.argtypes = [Function, Object, List]
__lib__.myelin_function_call.restype  = ctypes.c_void_p




###############################################
# Set Class Prototypes                        #
###############################################

__lib__.myelin_class_get_name.argtypes = [Class]
__lib__.myelin_class_get_name.restype  = ctypes.c_char_p

__lib__.myelin_class_register_function.argtypes = [Class, ctypes.c_void_p]
__lib__.myelin_class_register_function.restype  = None

__lib__.myelin_class_get_function.argtypes = [Class, ctypes.c_char_p]
__lib__.myelin_class_get_function.restype  = ctypes.c_void_p

__lib__.myelin_class_get_function_list.argtypes = [Class]
__lib__.myelin_class_get_function_list.restype  = ctypes.c_void_p


__lib__.myelin_class_create_instance.argtypes = [Class, List]
__lib__.myelin_class_create_instance.restype  = ctypes.c_void_p

__lib__.myelin_class_create_object.argtypes = [Class, List]
__lib__.myelin_class_create_object.restype  = ctypes.c_void_p




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


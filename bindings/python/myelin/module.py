

import sys
import ctypes

from namespace import *
from reference import *
from introspection import *




# set generic value
def create_value (value, param_type):
    
    val = Value ()
    
    
    # pointer/reference type
    if param_type.is_pointer() or param_type.is_reference():
        
        # use given pointer
        if isinstance (value, Pointer):
            val.set_pointer (value)
        
        # use given reference
        elif isinstance (value, Reference):
            # make sure cast is possible
            if value.can_cast_to (param_type):
                ptr = Pointer ()
                ptr.set (ctypes.byref (value.instance), param_type.get_atom())
                val.set_pointer (ptr)
        
        # create a reference
        else:
            ref = Reference (value)
            
            # make sure cast is possible
            if ref.can_cast_to (param_type):
                ptr = Pointer ()
                ptr.set (ctypes.byref (ref.instance), param_type.get_atom())
                val.set_pointer (ptr)
        
        return val
    
    
    # value type
    if   param_type.get_atom() == Type.type_bool   (): val.set_bool    (value)
    elif param_type.get_atom() == Type.type_char   (): val.set_char    (value)
    elif param_type.get_atom() == Type.type_uchar  (): val.set_uchar   (value)
    elif param_type.get_atom() == Type.type_int    (): val.set_int     (value)
    elif param_type.get_atom() == Type.type_uint   (): val.set_uint    (value)
    elif param_type.get_atom() == Type.type_long   (): val.set_long    (value)
    elif param_type.get_atom() == Type.type_ulong  (): val.set_ulong   (value)
    elif param_type.get_atom() == Type.type_int64  (): val.set_int64   (value)
    elif param_type.get_atom() == Type.type_uint64 (): val.set_uint64  (value)
    elif param_type.get_atom() == Type.type_float  (): val.set_float   (value)
    elif param_type.get_atom() == Type.type_double (): val.set_double  (value)
    elif param_type.get_atom() == Type.type_string (): val.set_string  (value)
    elif param_type.get_atom() == Type.type_pointer(): val.set_pointer (value)
    
    
    if val.is_empty():
        raise TypeError ("Cannot create a value of type '%s' from the given " \
                         "type '%s'. Conversion failed." %
                         (param_type.get_name(), type(value)))
    
    return val





class MetaConstructor (object):
    def __init__ (self, ctor):
        self._ctor = ctor
        
        
    def __call__ (self, cls, *args):
        params = List ()
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._ctor.get_param_type(i)
            params.append (create_value (args[i], type))
        
        
        # call constructor
        ret = self._ctor.call (params)
        instance = ret.get_pointer().get_raw()
        
        return cls (instance)




class MetaFunction (object):
    def __init__ (self, func):
        self._func = func
        
        
    def __call__ (self, object, *args):
        
        params = List ()
        val_ref = None
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._func.get_param_type(i)
            params.append (create_value (args[i], type))
        
        
        # call function
        return self._func.call (object.get_instance(), params)





def create_constructor (meta_ctor, name):
    
    def callback (cls, *args):
        return meta_ctor (cls, *args)
        
    callback._meta_ctor = meta_ctor
    callback.__name__ = name
    
    return callback




def create_function (meta_func, name):
    
    def callback (self, *args):
        return meta_func (self._object, *args)
        
    callback._meta_func = meta_func
    callback.__name__ = name
    
    return callback




class MetaClass (type):
    
    def __init__ (cls, name, bases, dict):
        
        type.__init__ (cls, name, bases, dict)
        
        if ("_class" not in dict):
            return
        
        
        cls._class = dict["_class"]
        cls._add_constructors()
        cls._add_functions()
        
    
    
    def _add_constructors(cls):
        for value in cls._class.get_constructor_list():
            ctor = Constructor.from_pointer (value.get_pointer().get_raw(),
                                             False)
            name = "create"
            
            meta_ctor = MetaConstructor (ctor)
            
            func = create_constructor (meta_ctor, name)
            cls_func = classmethod(func)
            setattr (cls, name, cls_func)
    
    
    def _add_functions (cls):
        for value in cls._class.get_function_list():
            func = Function.from_pointer (value.get_pointer().get_raw(), False)
            name = func.get_name()
            
            meta_func = MetaFunction (func)
            setattr (cls, name, create_function (meta_func, name))




class MetaObject (object):
    __metaclass__ = MetaClass
    
    def __init__ (self, instance = None):
        
        if instance is None:
            self._object = self._class.create_object (List())
        else:
            self._object = self._class.create_object_instance (instance)




class MetaModule (object):
    
    def __init__ (self, repo_name, namespace):
        
        repo = RepositoryFactory.get (repo_name)
        
        for value in repo.get_class_list():
            klass = Class.from_pointer (value.get_pointer().get_raw(), False)
            
            
            nspace = None
            list = klass.get_namespace()
            
            for val in list:
                if nspace is None: nspace = val
                else: nspace += "." + val
            
            
            if nspace == namespace or nspace == repo_name:
                name = klass.get_name()
                dict = {"_class": klass}
                setattr (self, name, type(name, (MetaObject,), dict))


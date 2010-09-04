

import sys
import ctypes

from namespace import *
from introspection import *



def convert_value (value, param_type):
    val = Value ()
    
    # bools have a natural translation
    if type(value) is bool:
        if param_type == Type.type_bool: val.set_bool  (value)
    
    # integers can convert to any integer below and including long.
    elif type(value) is int:
        if   param_type == Type.type_char():   val.set_char (value)
        elif param_type == Type.type_uchar():  val.set_uchar (value)
        elif param_type == Type.type_int():    val.set_int (value)
        elif param_type == Type.type_uint():   val.set_uint (value)
        elif param_type == Type.type_long():   val.set_long (value)
        elif param_type == Type.type_ulong():  val.set_ulong (value)
    
    # longs can pretty much handle any integer length
    elif type(value) is long:
        if   param_type == Type.type_char():   val.set_char (value)
        elif param_type == Type.type_uchar():  val.set_uchar (value)
        elif param_type == Type.type_int():    val.set_int (value)
        elif param_type == Type.type_uint():   val.set_uint (value)
        elif param_type == Type.type_long():   val.set_long (value)
        elif param_type == Type.type_ulong():  val.set_ulong (value)
        elif param_type == Type.type.int64():  val.set_int64 (value)
        elif param_type == Type.type.uint64(): val.set_uint64 (value)
    
    # floats are a double int python
    elif type(value) is float:
        if   param_type == Type.type_float(): val.set_float (value)
        elif param_type == Type.type_double(): val.set_float (value)
    
    # strings translate easily if the function wont modify it
    elif type(value) is str:
        if param_type == Type.type_string(): val.set_string (value)
    
    # ctype pointers are straight conversions
    elif isinstance (value, ctypes.c_void_p):
        if param_type == Type.type_pointer(): val.set_pointer (value)
    
    
    if val.is_empty(): raise TypeError, "Could not convert value to match the appropriate type"
    return val




class MetaConstructor (object):
    def __init__ (self, ctor):
        self._ctor = ctor
        
        
    def __call__ (self, cls, *args):
        # make sure arg list is the same as contructor parameter count
        if len(args) <> self._ctor.get_param_count():
            raise ValueError, "A call to the constructor must provide exactly '%d' arguments. '%d' given" % (self._ctor.get_param_count(), len(args))
        
        
        params = List ()
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._ctor.get_param_type(i)
            val = convert_value (args[i], type)
            
            params.append (val)
        
        # call constructor
        ret = self._ctor.call (params)
        instance = ret.get_pointer()
        
        return cls (instance)




class MetaFunction (object):
    def __init__ (self, func):
        self._func = func
        
        
    def __call__ (self, object, *args):
        # make sure arg list is the same as function parameter count
        if len(args) <> self._func.get_param_count():
            raise ValueError, "A call to the function '%s' must provide exactly '%d' arguments" % (self._func.get_name(), self._func.get_param_count())
        
        
        params = List ()
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._func.get_param_type(i)
            val = convert_value (args[i], type)
            
            params.append (val)
        
        # call function
        self._func.call (object.get_instance(), params)





def create_constructor (meta_ctor, name):
    
    def ctor_callback (cls, *args):
        return meta_ctor (cls, *args)
        
    ctor_callback._meta_ctor = meta_ctor
    ctor_callback.__name__ = name
    
    return ctor_callback




def create_function (meta_func, name):
    
    def func_callback (self, *args):
        meta_func (self._object, *args)
        
    func_callback._meta_func = meta_func
    func_callback.__name__ = name
    
    return func_callback




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
            ctor = Constructor.from_pointer (value.get_pointer(), False)
            name = "create"
            
            meta_ctor = MetaConstructor (ctor)
            
            func = create_constructor (meta_ctor, name)
            cls_func = classmethod(func)
            setattr (cls, name, cls_func)
    
    
    def _add_functions (cls):
        for value in cls._class.get_function_list():
            func = Function.from_pointer (value.get_pointer(), False)
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
            klass = Class.from_pointer (value.get_pointer(), False)
            
            
            nspace = None
            list = klass.get_namespace()
            
            for val in list:
                if nspace is None: nspace = val
                else: nspace += "." + val
            
            
            if nspace == namespace or nspace == repo_name:
                name = klass.get_name()
                dict = {"_class": klass}
                setattr (self, name, type(name, (MetaObject,), dict))




import sys
import ctypes

from namespace import *
from reference import *
from introspection import *




# set generic value
def create_value (value, param_type):
    
    val = Value ()
    atom = param_type.get_atom()
    
    ptr = None
    
    
    # value is a pointer
    if isinstance (value, Pointer): val.set_pointer (value)
    
    # value is a reference
    elif isinstance (value, Reference):
        ptr = Pointer ()
        
        if type(value.instance) == ctypes.c_char_p:
            ptr.set (value.instance, value.type)
        else:
            ptr.set (ctypes.byref (value.instance), value.type)
        
        val.set_pointer (ptr)
    
    
    elif isinstance (value, MetaObject):
        ptr = value._object.get_instance()
        val.set_pointer (ptr)
    
    
    # convert python types
    elif type(value) is bool: val.set_bool (value)
    
    # set the right integer type
    elif type(value) is int or type(value) is long:
        if   atom == Type.type_char():  val.set_char  (value)
        elif atom == Type.type_uchar(): val.set_uchar (value)
        elif atom == Type.type_int():   val.set_int   (value)
        elif atom == Type.type_uint():  val.set_uint  (value)
        elif atom == Type.type_long():  val.set_long  (value)
        elif atom == Type.type_ulong(): val.set_ulong (value)
        
        # for long only
        elif type(value) is long:
            if   atom == Type.type_int64(): val.set_int64 (value)
            elif atom == Type.type_uint64(): val.set_uint64 (value)
    
    
    elif type(value) is float:
        if   atom == Type.type_float():  val.set_float  (value)
        elif atom == Type.type_double(): val.set_double (value)
    
    
    elif type(value) is str: val.set_string (value)
    
    
    if val.is_empty():
        raise TypeError ("Cannot create a value of type '%s' from the given " \
                         "type '%s'. Conversion failed." %
                         (param_type.get_name(), type(value)))
    
    return val, ptr





class MetaConstructor (object):
    def __init__ (self, ctor):
        self._ctor = ctor
        
        
    def __call__ (self, *args):
        params = List ()
        
        references = []
        pointers = []
        
        # convert argument types
        for i in range(0, len(args)):
            ref = None
            ptr = None
            
            type = self._ctor.get_param_type(i)
            
            if type.is_pointer() or type.is_reference():
                val, ptr = create_value (args[i], type)
#                ref = Reference (args[i])
#                val, ptr = create_value (ref, type)
                params.append (val)
            else:
                val, ptr = create_value (args[i], type)
                params.append (val)
            
            references.append (ref)
            pointers.append (ptr)
        
        
        # call constructor
        return self._ctor.call (params)




class MetaFunction (object):
    def __init__ (self, func):
        self._func = func
        
        
    def __call__ (self, *args):
        
        params = List ()
        val_ref = None
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._func.get_type().get_param_type(i)
            val, ptr = create_value (args[i], type)
            params.append (val)
        
        
        # call function
        ret = self._func.call (params)
        return ret.get()





def create_constructor (meta_ctor, name):
    
    def callback (cls, *args):
        return cls (instance = meta_ctor (*args))
        
    callback._meta_ctor = meta_ctor
    callback.__name__ = name
    
    return callback




def create_function (meta_func, name):
    
    def callback (self, *args):
        return meta_func (*args)
        
    callback._meta_func = meta_func
    callback.__name__ = name
    
    return callback




def create_pure_function (name):
    
    def callback (self, *args):
        
        if hasattr (self, name):
            func = getattr (self, name)
            return func (*args)
            
        else:
            raise NotImplementedError ("Cannot call the function '%s' " \
                                       "because it has not been implemented " \
                                       "by the derived class. All pure " \
                                       "virtual functions must be implemented."
                                       % name)
    
    callback.__name__ = name
    return callback




class MetaClass (type):
    
    def __new__ (cls, name, bases, dict):
        
        type.__init__ (cls, name, bases, dict)
        
        if ("_class" not in dict):
            return type.__new__ (cls, name, bases, dict)
        
        
        meta = type.__new__ (cls, name, bases, dict)
        
        meta._add_constructors()
        meta._add_functions()
        
        return meta
        
    
    
    def _add_constructors (cls):
        
        cls._constructors = []
        
        for value in cls._class.get_constructors():
            
            ctor = Constructor.from_pointer (value.get_pointer().get_raw(),
                                             False)
            name = "new"
            
            meta_ctor = MetaConstructor (ctor)
            cls._constructors.append (meta_ctor)
            
            func = create_constructor (meta_ctor, name)
            cls_func = classmethod(func)
            setattr (cls, name, cls_func)
    
    
    def _add_functions (cls):
        
        cls._functions = []
        cls._function_types = []
        
        for value in cls._class.get_all_functions():
            
            func = Function.from_pointer (value.get_pointer().get_raw(), False)
            cls._functions.append (func)
            
            name = func.get_name()
            
            if func.is_pure():
                
                vtable = cls._class.get_vtable()
                
                pure_func = create_pure_function (name)
                func_type = CustomFunctionType (pure_func, owner = False)
                func_cb = Function (name, func_type, owner = False)
                
                # copy function parameter types
                type = func.get_type()
                
                for i in range (0, type.get_param_count()):
                    func_type.add_param_type (type.get_param_type (i))
                
                func_type.set_return_type (type.get_return_type())
                
                
                vtable.set (func_cb)
                cls._function_types.append (func_type)
                
                setattr (cls, "__%s_hook" % name, pure_func)
            
            else:
                meta_func = MetaFunction (func)
                setattr (cls, name, create_function (meta_func, name))




class MetaObject (object):
    __metaclass__ = MetaClass
    
    
    def __init__ (self, *args, **kwargs):
        
        # an object instance was provided
        if kwargs.has_key ("instance"):
            self._object = Object (self._class, kwargs["instance"])
        
        # create an object with parameters
        else:
            params = List ()
            references = []
            pointers = []
            
            # convert argument types
            for arg in args:
                ref = Reference (arg)
                val, ptr = create_value (ref, ref.type)
                params.append (val)
                
                references.append (ref)
                pointers.append (ptr)
            
            self._object = self._class.create_object (params)
            
            # no object can be created
            if self._object is None:
                raise NotImplementedError ("Could not find an appropriate " \
                                           "constructor for the class type " \
                                           "'%s'. Either the wrong " \
                                           "parameters are given or the " \
                                           "class does not provide a " \
                                           "constructor" %
                                           self._class.get_name())
            
            
        # bind functions
        for func in self._functions:
            func.bind (self._object.get_instance())
        
        # bind virtuals
        for func_type in self._function_types:
            func_type.set_self_object (self)




class MetaModule (object):
    
    def __init__ (self, namespace):
        
        for value in namespace.get_classes():
            klass = Class.from_pointer (value.get_pointer().get_raw(), False)
            
            name = klass.get_name()
            dict = {"_class": klass}
            setattr (self, name, type(name, (MetaObject,), dict))


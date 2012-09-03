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

import sys
import ctypes

from namespace import *
from reference import *
from introspection import *



# set generic value
def create_value (value, param_type):
    
    val = Value ()
    atom = param_type.get_atom()
    
    
    # value is a reference
    if isinstance (value, Reference):
        
        if type(value.instance) == ctypes.c_char_p:
            val.set_pointer (value.type, value.instance)
        else:
            val.set_pointer (value.type, ctypes.byref (value.instance))
    
    
    elif isinstance (value, MetaObject):
        val = value._object.get_instance()
    
    
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
    
    return val





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
            
            type = self._ctor.get_param_type(i)
            
            if type.is_pointer() or type.is_reference():
                val = create_value (args[i], type)
#                ref = Reference (args[i])
#                val, ptr = create_value (ref, type)
                params.append (val)
                
            else:
                val, ptr = create_value (args[i], type)
                params.append (val)
            
            references.append (ref)
        
        
        # call constructor
        return self._ctor.call (params)




class MetaFunction (object):
    def __init__ (self, func):
        self._func = func
        
        
    def __call__ (self, *args):
        
        params = List ()
        
        # convert argument types
        for i in range(0, len(args)):
            type = self._func.get_type().get_param_type(i)
            val = create_value (args[i], type)
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
            
            ctor = Constructor.from_pointer (value.as_pointer())
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
            
            func = Function.from_pointer (value.as_pointer())
            cls._functions.append (func)
            
            name = func.get_name()
            
            # check for vtable. hack to get around generator not
            # creating a vtable for template instances
            if func.is_virtual() and cls._class.has_vtable():
                
                vtable = cls._class.get_vtable()
                
                pure_func = create_pure_function (name)
                func_type = CustomFunctionType (pure_func)
                func_cb = Function (name, func_type)
                
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
            
            # convert argument types
            for arg in args:
                val = Value ()
                val.set (arg)
                params.append (val)
            
            self._object = self._class.create_object (params)
            
            # no object can be created
            if self._object is None:
                raise TypeError ("Could not find an appropriate constructor " \
                                 "for the class type '%s'. Either the wrong " \
                                 "parameters are given or the class does " \
                                 "not provide a constructor" %
                                 self._class.get_name())
            
            
        # bind functions
        for func in self._functions:
            func.bind (self._object.get_instance())
        
        # bind virtuals
        for func_type in self._function_types:
            func_type.set_self_object (self)
    
    
    def __repr__ (self):
        return ("<%s.%s meta-object at %#x with an instance " \
                "of type %s at %#x>" %
               (self.__module__,
                self.__class__.__name__,
                id(self),
                self._object.get_instance().get_type().get_name(),
                self._object.get_instance().as_pointer()))




class MetaModule (object):
    
    def __init__ (self, namespace):
        
        for val in namespace.get_classes():
            klass = Class.from_pointer (val.as_pointer())
            
            name = klass.get_name()
            dict = {"_class": klass}
            
            class_type = type(name, (MetaObject,), dict)
            setattr (self, name, class_type)
            
            import introspection.value
            introspection.value.add_type (class_type)


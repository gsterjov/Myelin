

import ctypes
from introspection import *



class MetaFunction (object):
    def __init__ (self, func):
        self._func = func
        
        
    def __call__ (self, object, *args):
        params = List ()
        
        for arg in args:
            val = Value()
            
            if   isinstance (arg, bool):  val.set_bool  (arg)
            elif isinstance (arg, int):   val.set_int   (arg)
            elif isinstance (arg, long):  val.set_long  (arg)
            elif isinstance (arg, float): val.set_float (arg)
            
            params.append (val)
        
        self._func.call (object, params)




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
        cls._add_functions()
        
    
    
    def _add_functions(cls):
        for value in cls._class.get_function_list():
            func = Function.from_pointer (value.get_pointer(), False)
            name = func.get_name()
            
            meta_func = MetaFunction (func)
            setattr (cls, name, create_function (meta_func, name))




class MetaObject (object):
    __metaclass__ = MetaClass
    
    def __init__ (self):
        self._object = Object (self._class, List())





class MetaModule (object):
    
    def __init__ (self, path, namespace):
        
        
        repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelinTestLibrary.so")
        repo_lib.create_repository ()
        
        
        repo = RepositoryFactory.get (namespace)
        
        for value in repo.get_class_list():
            klass = Class.from_pointer (value.get_pointer(), False)
            
            name = klass.get_name()
            dict = {"_class": klass}
            setattr (self, name, type(name, (MetaObject,), dict))



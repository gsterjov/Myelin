

from ctypes import *



class MetaFunction (object):
    def __init__ (self, library, object, name):
        
        self._library = library
        self._object = object
        self._name = name
        
        
    def __call__ (self):
        self._library.meta_object_call (self._object, self._name)



class MetaObject (object):
    def __init__ (self, library, name):
        self._library = library
        
        self._meta_object = self._library.meta_object_new (class_name);
        
        func_list = self._library.meta_class_get_function_list (namespace)
        
        meta_func = self._library.myelin_array_index (func_list, 0)
        
        
        name_func = self._library.meta_function_get_name
        name_func.restype = c_char_p
        
        name = name_func (meta_func)
        
        func = MetaFunction (self._library, self._meta_object, name)
        self.__dict__[name] = func



class MetaModule (object):
    
    def __init__ (self, namespace):
        
        self._library = cdll.LoadLibrary("/devel/build/Myelin/libMyelinTestLibrary.so")
        self._library.initialise ();
        
        class_name = c_char_p (namespace)
        
        
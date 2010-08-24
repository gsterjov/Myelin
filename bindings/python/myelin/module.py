

from ctypes import *



class MetaFunction (object):
    def __init__ (self, library, meta_func):
        
        self._meta_func = meta_func
        self._library = library
        
        self._name = self.get_name()
        
        
    def __call__ (self, object):
        self._library.meta_object_call (object, self._name)
        
        
    def get_name (self):
        func = self._library.meta_function_get_name
        func.restype = c_char_p
        
        self._name = func (self._meta_func)
        return self._name




def create_function (meta_func):
    
    def func_callback (self):
        meta_func (self._object)
        
    func_callback._meta_func = meta_func
    func_callback.__name__ = meta_func.get_name()
    
    return func_callback




class MetaClass (type):
    
    def __init__ (cls, name, bases, dict):
        
        type.__init__ (cls, name, bases, dict)
        
        if ('_library' not in dict):
            return
        
        
        cls._library = dict['_library']
        cls._class_name = c_char_p (name)
        
        cls._connect_functions()
        
    
    
    def _connect_functions(cls):
        
        get_func_list = cls._library.meta_class_get_function_list
        get_func_list.restype = c_void_p
        
        func_list = get_func_list (cls._class_name)
        
        size = cls._library.myelin_array_size (func_list)
        
        for i in range(0, size):
            
            meta_func = cls._library.myelin_array_index (func_list, i)
            
            func = MetaFunction (cls._library, meta_func)
            
            f = create_function (func)
            
            setattr (cls, func.get_name(), f)
        
    




class MetaObject (object):
    __metaclass__ = MetaClass
    
    def __init__ (self):
        
        self._object = self._library.meta_object_new (self._class_name)
        




class MetaModule (object):
    
    def __init__ (self, path, namespace):
        
        self._library = cdll.LoadLibrary("/devel/build/Myelin/libMyelinTestLibrary.so")
        self._library.create_repository ();
        
        dict = {'_library': self._library}
        
        
        
        
        lib = cdll.LoadLibrary("/devel/build/Myelin/libMyelin.so")
        
        get_repo = lib.myelin_repository_factory_get
        get_repo.argtypes = [c_char_p]
        get_repo.restype = c_void_p
        
        
        rep = get_repo ("LibraryTest")
        
        
        import Repository
        self.repo = Repository.Repository.from_pointer (rep)
        
#        lib = Repository.Library ("/devel/build/Myelin/libMyelin.so")
        
        
#        self._library2 = cdll.LoadLibrary("/devel/build/Myelin/libMyelin.so")
#        
#        get_repo = self._library2.myelin_repository_factory_get
#        get_repo.restype = c_void_p
#        
#        name = c_char_p ("LibraryTest")
#        
#        self._repo = get_repo (name)
#        
#        
#        get_repo_name = self._library2.myelin_repository_get_name
#        get_repo_name.restype = c_char_p
#        
#        
#        self._str = get_repo_name (self._repo)
#        print self._str
        
        
        
#        name_space = c_char_p (namespace)
#        
#        get_classes = self._library.meta_class_get_class_list
#        get_classes.restype = c_void_p
#        
#        classes = get_classes (name_space)
#        
#        
#        size = self._library.myelin_array_size (classes)
#        
#        for i in range(0, size):
#            
#            meta_class = self._library.myelin_array_index (classes, i)
#            
#            func = self._library.meta_class_get_name
#            func.restype = c_char_p
#            
#            name = func (meta_class)
#            
#            setattr (self, name, type (name, (MetaObject,), dict));
#        
#        self.__dict__[namespace] = type (namespace, (MetaObject,), dict)
        
        
        
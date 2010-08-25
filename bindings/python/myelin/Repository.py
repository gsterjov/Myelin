
from ctypes import *

from List import List
from Class import Class
import Library



lib = Library.get_library()



class Repository (object):
    
    _repo_ptr = None
    _can_delete = False
    
    
    def __init__ (self, name):
        
        # create a repository
        if self._repo_ptr is None:
            self._repo_ptr = lib.myelin_repository_new (name)
            _can_delete = True
        
        
    def __del__ (self):
        if self._can_delete:
            lib.myelin_repository_free (self)
            self._repo_ptr = None
            self._can_delete = False
        
        
    @classmethod
    def from_pointer (cls, repo_ptr):
        cls._repo_ptr = repo_ptr
        
        return cls(None)
        
        
        
    def from_param (self):
        return self._repo_ptr
        
        
        
    def get_name (self):
        return lib.myelin_repository_get_name (self)
    
    
    def get_class (self, name):
        return Class.from_pointer (lib.myelin_repository_get_class (self, name))
    
    
    def register_class (self, klass):
        lib.myelin_repository_register_class (self, klass)
    
    
    def get_class_list (self):
        return List.from_pointer (lib.myelin_repository_get_class_list (self))




class RepositoryFactory (object):
    
    @classmethod
    def create (cls, name):
        return Repository.from_pointer (lib.myelin_repository_factory_create (name))
    
    
    @classmethod
    def get (cls, name):
        return Repository.from_pointer (lib.myelin_repository_factory_get (name))
    
    
    @classmethod
    def add (cls, repo):
        lib.myelin_repository_factory_add (repo)
    
    
    @classmethod
    def get_repository_list (cls):
        return List.from_pointer (lib.myelin_repository_factory_get_repository_list())
    
    
    
    
    
    

# set repository prototypes
lib.myelin_repository_new.argtypes = [c_char_p]
lib.myelin_repository_new.restype = c_void_p

lib.myelin_repository_free.argtypes = [Repository]
lib.myelin_repository_free.restype = None

lib.myelin_repository_get_name.argtypes = [Repository]
lib.myelin_repository_get_name.restype = c_char_p

lib.myelin_repository_get_class.argtypes = [Repository, c_char_p]
lib.myelin_repository_get_class.restype = c_void_p

lib.myelin_repository_register_class.argtypes = [Repository, c_void_p]
lib.myelin_repository_register_class.restype = None

lib.myelin_repository_get_class_list.argtypes = [Repository]
lib.myelin_repository_get_class_list.restype = c_void_p


# set repository factory prototypes
lib.myelin_repository_factory_create.argtypes = [c_char_p]
lib.myelin_repository_factory_create.restype = c_void_p

lib.myelin_repository_factory_get.argtypes = [c_char_p]
lib.myelin_repository_factory_get.restype = c_void_p

lib.myelin_repository_factory_add.argtypes = [Repository]
lib.myelin_repository_factory_add.restype = None

lib.myelin_repository_factory_get_repository_list.argtypes = None
lib.myelin_repository_factory_get_repository_list.restype = c_void_p


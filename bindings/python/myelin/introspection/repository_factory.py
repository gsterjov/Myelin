

import ctypes

from list import List
from repository import Repository


# get library
import myelin.library
_lib = myelin.library.get_library()




class RepositoryFactory (object):
    
    @classmethod
    def create (cls, name):
        repo = _lib.myelin_repository_factory_create (name)
        return Repository.from_pointer (repo)
    
    
    @classmethod
    def get (cls, name):
        repo = _lib.myelin_repository_factory_get (name)
        return Repository.from_pointer (repo)
    
    
    @classmethod
    def add (cls, repo):
        _lib.myelin_repository_factory_add (repo)
    
    
    @classmethod
    def get_all (cls):
        list = _lib.myelin_repository_factory_get_all()
        return List.from_pointer (list)
    




###############################################
# Prototypes                                  #
###############################################

_lib.myelin_repository_factory_create.argtypes = [ctypes.c_char_p]
_lib.myelin_repository_factory_create.restype  = ctypes.c_void_p

_lib.myelin_repository_factory_get.argtypes = [ctypes.c_char_p]
_lib.myelin_repository_factory_get.restype  = ctypes.c_void_p

_lib.myelin_repository_factory_add.argtypes = [Repository]
_lib.myelin_repository_factory_add.restype  = None

_lib.myelin_repository_factory_get_all.argtypes = None
_lib.myelin_repository_factory_get_all.restype  = ctypes.c_void_p




import sys
import ctypes

from namespace import NamespaceModule
from module import MetaModule

from introspection import Repository, RepositoryFactory, Namespace



#repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")
#repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libLibraryTest.so")
repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libSimpleTest.so")
#repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Soma/libSoma.so")
repo_lib.create_repository ()



class RepositoryImporter (object):
    
    def __init__ (self, path):
        self.path = path
    
    
    def find_module (self, fullname, path = None):
        
        if not fullname.startswith (self.path):
            return
        
        path, repo_name = fullname.rsplit (".", 1)
        if path != self.path:
            return
        
        
        return self
    
    
    
    def load_module (self, fullname):
        
        if fullname in sys.modules:
            return sys.modules[fullname]
        
        path, repo_name = fullname.rsplit (".", 1)
        
        
        # find repo
        repo = RepositoryFactory.get (repo_name)
        
        # get root namespace
        root = repo.get_namespace ("")
        sys.meta_path.append (NamespaceModule (root.get_name(), root))
        
        
        # hook namespaces into the import system
        for value in repo.get_namespaces():
            nspace = Namespace.from_pointer (value.get_pointer().get_raw())
            
            path = root.get_name() + "." + nspace.get_name()
            sys.meta_path.append (NamespaceModule (path, nspace))
        
        
        # create a module from the root namespace
        meta_module = MetaModule (root)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[repo_name] = meta_module
        return meta_module
    

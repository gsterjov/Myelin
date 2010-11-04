

import sys
import ctypes

import library
from namespace import NamespaceModule
from module import MetaModule

from introspection import Repository, Namespace



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
        
        # get repository
        repo = library.get_repository (repo_name)
        
        
        # get root namespace
        root = repo.get_namespace ("")
        sys.meta_path.append (NamespaceModule (root.get_name(), root))
        
        
        # hook namespaces into the import system
        for value in repo.get_namespaces():
            nspace = Namespace.from_pointer (value.as_pointer())
            
            path = root.get_name()
            names = nspace.get_name().split ("::")
            
            if names[0] == root.get_name():
                names.pop(0)
            
            for name in names:
                path = path + "." + name
            
            sys.meta_path.append (NamespaceModule (path, nspace))
        
        
        # create a module from the root namespace
        meta_module = MetaModule (root)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[repo_name] = meta_module
        return meta_module
    



import sys
from namespace import *
from module import MetaModule


repo_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelinTestLibrary.so")
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
        
        sys.meta_path.append (Namespace (repo_name))
        
        
        # find repo
        repo = RepositoryFactory.get (repo_name)
        
        namespaces = [repo_name]
        
        # hook namespaces into the import system
        for value in repo.get_class_list():
            klass = Class.from_pointer (value.get_pointer(), False)
            
            nspace = None
            list = klass.get_namespace()
            
            if len(list) == 0:
                continue
            
            for val in list:
                if nspace is None: nspace = val
                else: nspace += "." + val
                
            
            if nspace not in namespaces:
                sys.meta_path.append (Namespace (nspace))
                namespaces.append (nspace)
        
        
        
        meta_module = MetaModule (repo_name, None)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[repo_name] = meta_module
        
        return meta_module
    

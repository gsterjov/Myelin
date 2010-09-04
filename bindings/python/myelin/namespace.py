

import sys
from introspection import *
from module import MetaModule



class Namespace (object):
    
    def __init__ (self, path):
        self.path = path
    
    
    def find_module (self, fullname, path = None):
        if fullname == self.path:
            return self
    
    
    def load_module (self, fullname):
        if fullname in sys.modules:
            return sys.modules[fullname]
        
        repo_name, namespace = fullname.split (".", 1)
        
        meta_module = MetaModule (repo_name, fullname)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[fullname] = meta_module
        return meta_module




import sys
from introspection import *
from module import MetaModule



class NamespaceModule (object):
    
    def __init__ (self, path, namespace):
        self.path = path
        self.namespace = namespace
    
    
    def find_module (self, fullname, path = None):
        if fullname == self.path:
            return self
    
    
    def load_module (self, fullname):
        if fullname in sys.modules:
            return sys.modules[fullname]
        
        
        # create a module from the namespace
        meta_module = MetaModule (self.namespace)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[fullname] = meta_module
        return meta_module


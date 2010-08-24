

import sys
from module import MetaModule


class RepositoryImporter (object):
    
    def __init__ (self, path):
        self.path = path
    
    
    def find_module (self, fullname, path = None):
        
        if not fullname.startswith (self.path):
            return
        
        path, namespace = fullname.rsplit (".", 1)
        if path != self.path:
            return
        
        
        return self
    
    
    
    def load_module (self, fullname):
        
        if fullname in sys.modules:
            return sys.modules[fullname]
        
        path, namespace = fullname.rsplit (".", 1)
        
        meta_module = MetaModule (path, namespace)
        meta_module.__file__ = '<%s>' % fullname
        meta_module.__loader__ = self
        meta_module.__path__ = []
        
        sys.modules[fullname] = meta_module
        return meta_module
    

#
#    Copyright 2009-2010 Goran Sterjov
#    This file is part of Myelin.
#
#    Myelin is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    Myelin is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#    You should have received a copy of the GNU Lesser General Public License
#    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
#

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


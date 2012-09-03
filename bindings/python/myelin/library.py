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

import ctypes


try:
    _lib = ctypes.cdll.LoadLibrary ("libMyelin.so")
    _lib.myelin_type_init ()

except:
    raise ImportError ("Cannot find the core Myelin library. Make sure " \
                       "that the library can be found by the Python " \
                       "interpreter.")


def get_library ():
    return _lib




# loaded repositories
_repositories = {}



def get_repository (name):
    
    repo = None
    
    # repo lib already loaded
    if _repositories.has_key (name):
        return _repositories[name]
    
    # look for repo
    else:
        path = "lib" + name + ".so"
        add_repository (name, path)
        return _repositories[name]



def add_repository (name, path):
    
    lib = None
    
    # load shared library
    try:
        lib = ctypes.cdll.LoadLibrary (path)
        
    except:
        raise ImportError ("Cannot find the introspection library " \
                           "for the repository '%s'. Make sure the " \
                           "Python interpreter can find the " \
                           "required shared library '%s'." % (name, path))
    
    
    # get repository definition
    from introspection.repository import Repository
    
    
    # create repository metadata
    ptr = lib.myelin_create_repository ()
    repo = Repository (None, ctypes.c_void_p (ptr))
    
    # store repository
    _repositories[name] = repo


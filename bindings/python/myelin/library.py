

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
    
    try:
        repo = ctypes.cdll.LoadLibrary (path)
        
        _repositories[name] = repo
        
        # create repository listing
        repo.create_repository ()
        
    except:
        raise ImportError ("Cannot find the introspection library " \
                           "for the repository '%s'. Make sure the " \
                           "Python interpreter can find the " \
                           "required shared library '%s'." % (name, path))




from ctypes import *



__library = cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")


def load_library (path):
    __library = cdll.LoadLibrary (path)


def get_library ():
    if __library is None:
        raise RuntimeError, 'The library must be loaded before it can be used'
    
    return __library


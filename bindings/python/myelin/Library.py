

from ctypes import *


class Library (object):
    
    def __init__ (self, path):
        
        self.path = path
        self.library = cdll.LoadLibrary(path)

    
    def get_library (self):
        return self.library



library = cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")

def get_library ():
    return library


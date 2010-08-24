

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




class Repository (object):
    def __init__ (self, name):
        print "testing"
        self._library = get_library()
        
        self.__get_name = self._library.myelin_repository_get_name
        self.__get_name.argtypes = [c_void_p]
        self.__get_name.restype = c_char_p
        
        self.__get_class = self._library.myelin_repository_get_class
        self.__get_class.argtypes = [c_void_p, c_char_p]
        self.__get_class.restype = c_void_p
        
        
        
    @classmethod
    def from_pointer (cls, repo):
        cls.__repo = repo
        
        return cls("test")
        
        
        
        
    def get_name (self):
        return str(self.__get_name (self.__repo))
    
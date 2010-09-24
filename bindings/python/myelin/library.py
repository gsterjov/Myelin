

import ctypes
_lib = ctypes.cdll.LoadLibrary ("/devel/build/Myelin/libMyelin.so")
_lib.myelin_type_init ()



def get_library ():
    return _lib


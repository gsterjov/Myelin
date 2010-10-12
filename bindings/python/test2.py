
from myelin.repository import SimpleTest


test = SimpleTest.Test()

#test.test1()
#print test.test2()

ptr, val = test.test3()

ptr2 = val.create_pointer()

val_test = SimpleTest.ValTest (instance = ptr)

print val
print ptr.get_raw()
print ptr2.get_raw()

print val_test.get()

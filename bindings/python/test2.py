
import myelin
myelin.add_repository ("SimpleTest", "/devel/build/Myelin/libSimpleTest.so")

from myelin.repository import SimpleTest


test = SimpleTest.Test()

test.test1()
print test.test2()

val = test.test3()
print val.get()


val = test.test4()
print val.get()


val = test.test5()
print val.get()


test.test6 (val)

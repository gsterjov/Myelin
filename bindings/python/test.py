from myelin.repository import LibraryTest
from myelin.reference import *

test = LibraryTest.TestLibrary()
test.test(4)


ref = byref(7)

print ref.value
test.anotherTest(ref)
print ref.value

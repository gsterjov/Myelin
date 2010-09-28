#from myelin.repository import Myelin
#klass = Myelin.Class.new("testing")
#
#print "value = " + klass.getName().get_string()
#
#
#
#from myelin.introspection import *
#
#
#def test_func(val):
#	print "test func: ", val
#
#
#
#func = CustomFunctionType (test_func)
#
#type = Type (Type.type_int(), Type.Traits())
#func.add_param_type (type)
#
#value = Value()
#value.set_int (123)
#
#list = List()
#list.append (value)
#
#func.call (list)



from myelin.repository import LibraryTest


class Test (LibraryTest.Test1):
	pass
	def call (self, arg):
		print arg
		return 102


test1 = Test()
test2 = LibraryTest.Test2()

test2.call_me (test1._object.get_instance())


#f = Function ("call", new_func)
#f.call(List())



#from myelin.repository import LibraryTest
#from myelin.reference import *

#test = LibraryTest.TestLibrary()
#test.test(4)


#ref = byref(7)

#print ref.value
#test.anotherTest(ref)
#print ref.value

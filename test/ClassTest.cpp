
#include <gtest/gtest.h>
#include <Myelin/GenericClass.h>
#include <Myelin/GenericObject.h>
#include <Myelin/GenericFunction.h>

#include "MockClass.h"
#include <iostream>


namespace Myelin {
namespace Test {


	/* test simple meta class creation */
	TEST (ClassTest, CreateClass)
	{
		GenericClass<MockClass> klass ("MockClass");
		
		EXPECT_EQ ("MockClass", klass.getName());
		
		
		GenericFunction func0 ("test0", &MockClass::test0);
		klass.registerFunction (&func0);
		
		
		MockClass mock;
		GenericObject<MockClass> object (&klass, &mock);
		
		
		EXPECT_CALL (mock, test0()).Times(1);
		
		
		object.call ("test0");
	}

}}

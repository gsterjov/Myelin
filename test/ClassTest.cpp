
#include <gtest/gtest.h>
#include <Myelin/GenericClass.h>
#include <Myelin/GenericObject.h>

#include "MockClass.h"
#include <iostream>


namespace Myelin {
namespace Test {


	/* test simple meta class creation */
	TEST (ClassTest, CreateClass)
	{
		GenericClass<MockClass> klass ("MockClass");
		
		EXPECT_EQ ("MockClass", klass.getName());
		
		
		MockClass mock;
		GenericObject<MockClass> object (&klass, &mock);
	}

}}

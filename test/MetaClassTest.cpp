
#include <gtest/gtest.h>
#include <Myelin/MetaClass.h>
#include <Myelin/MetaObject.h>

#include "MockClass.h"
#include <iostream>


namespace Myelin {
namespace Test {


	/* test simple metaclass creation */
	TEST (MetaClassTest, CreateMetaClass)
	{
		MetaClass<MockClass> meta ("MockClass");
		
		EXPECT_EQ ("MockClass", meta.getName());
		
		meta.addFunction ("method1", &MockClass::method1);
		
		MetaFunction* func = meta.getFunction ("method1");
		
		
		
		MetaObject<MockClass> object (&meta);
		
		EXPECT_CALL (*object.getObject(), method1()).Times(1);
		
		object.call ("method1");
		
		delete object.getObject();
	}


}}

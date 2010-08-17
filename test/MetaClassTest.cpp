
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
		
//		meta.addFunction<void> ("method1", &MockClass::method1);
		meta.addFunction<bool,int> ("method2", &MockClass::method2);
		
		
		MetaObject object ("MockClass");
		
		MockClass* obj = static_cast<MockClass*> (object.getObject());
		
//		EXPECT_CALL (*obj, method1()).Times(1);
		EXPECT_CALL (*obj, method2(2)).Times(1).WillOnce(testing::Return(true));
		
//		object.call<MockClass, void> ("method1");
//		object.call<MockClass, bool> ("method2", 2);
		
		
		bool ret = object.call("method2", 2);
		EXPECT_EQ (true, ret);
		
		
		delete obj;
	}


}}

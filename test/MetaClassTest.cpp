
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
		
		meta.addFunction<void, std::string> ("test1", &MockClass::test1);
//		meta.addFunction<void, bool, std::string> ("test2", &MockClass::test2);
//		meta.addFunction<void, bool, bool, std::string> ("test3", &MockClass::test3);
//		meta.addFunction<void, bool, bool, bool, std::string> ("test4", &MockClass::test4);
//		meta.addFunction<void, bool, bool, bool, bool, std::string> ("test5", &MockClass::test5);
		
//		meta.addFunction<bool, int> ("method2", &MockClass::method2);
//		meta.addFunction<bool, int, bool> ("method3", &MockClass::method3);
//		meta.addFunction<void, int, bool> ("method4", &MockClass::method4);
//		meta.addFunction<void, int, bool, std::string> ("method5", &MockClass::method5);
		
		
		MetaObject object ("MockClass");
		
		MockClass* obj = static_cast<MockClass*> (object.getObject());
		
//		EXPECT_CALL (*obj, method1()).Times(3);
		
		EXPECT_CALL (*obj, test1("test")).Times(2);
//		EXPECT_CALL (*obj, test2(true,"test")).Times(2);
//		EXPECT_CALL (*obj, test3(true,true,"test")).Times(2);
//		EXPECT_CALL (*obj, test4(true,true,true,"test")).Times(2);
//		EXPECT_CALL (*obj, test5(true,true,true,true,"test")).Times(2);
		
//		EXPECT_CALL (*obj, method2(2)).Times(1).WillOnce(testing::Return(true));
//		EXPECT_CALL (*obj, method3(3,true)).Times(2).WillRepeatedly(testing::Return(true));
//		EXPECT_CALL (*obj, method4(4,true)).Times(1);
//		EXPECT_CALL (*obj, method5(5,true,"test")).Times(1);
		
		
		
		
		std::string test = "test";
		
		object.call ("test1", "test");
//		object.call ("test2", true, test);
//		object.call ("test3", true, true, test);
//		object.call ("test4", true, true, true, test);
//		object.call ("test5", true, true, true, true, test);
		
//		object.call<MockClass, void, std::string> ("test1", "test");
//		object.call<MockClass, void, bool, std::string> ("test2", true, test);
//		object.call<MockClass, void, bool, bool, std::string> ("test3", true, true, test);
//		object.call<MockClass, void, bool, bool, bool, std::string> ("test4", true, true, true, test);
//		object.call<MockClass, void, bool, bool, bool, bool, std::string> ("test5", true, true, true, true, test);
		
		
		
//		std::vector<Value> empty;
//		
//		
//		object.call<MockClass, void> ("method1");
//		object.call ("method1", empty);
//		object.call ("method1");
//		
//		
//		bool ret1 = object.call ("method2", 2);
//		EXPECT_EQ (true, ret1);
//		
//		
//		bool ret2 = object.call ("method3", 3, true);
//		EXPECT_EQ (true, ret2);
//		
//		
//		std::vector<Value> args;
//		
//		args.push_back (3);
//		args.push_back (true);
//		
//		bool ret3 = object.call ("method3", args);
//		EXPECT_EQ (true, ret3);
//		
//		object.call ("method4", 4, true);
		
		
//		object.call<MockClass, void, int, bool, const std::string&> ("method5", 5, true, test);
//		object.call ("method5", 5, true, test);
		
		
		
		delete obj;
	}


}}


#include <gtest/gtest.h>
#include <Myelin/Value.h>

#include "MockClass.h"


namespace Myelin {
namespace Test {


	class ValueTestClass
	{
	public:
		bool value;
	};
	
	
	
	/* test generic value creation */
	TEST (ValueTest, CreateValue)
	{
		Types::init_types();
		
		ValueTestClass class1;
		ValueTestClass* class2 = new ValueTestClass();
		
		std::string test ("test2");
		
		
		class1.value = true;
		class2->value = true;
		
		
		Value value1 (1);
		Value value2 (test);
		Value value3 (class1);
		Value value4 (class2);
		
		
		EXPECT_EQ (true, TYPE_INFO(int) == value1.getTypeInfo());
		EXPECT_EQ (true, TYPE_INFO(std::string) == value2.getTypeInfo());
		
		EXPECT_EQ (true, TYPE_INFO(ValueTestClass)  == value3.getTypeInfo());
		EXPECT_EQ (true, TYPE_INFO(ValueTestClass*) == value4.getTypeInfo());
		
		
		int         val1 = value_cast<int>         (value1);
		std::string val2 = value_cast<std::string> (value2);
		
		ValueTestClass  val3 = value_cast<ValueTestClass>  (value3);
		ValueTestClass* val4 = value_cast<ValueTestClass*> (value4);
		
		void* val5 = value_cast<void*> (value4);
		ValueTestClass* val6 = static_cast<ValueTestClass*> (val5);
		
		
		EXPECT_EQ (1, val1);
		EXPECT_EQ (test, val2);
		
		EXPECT_NE (&class1, &val3);
		EXPECT_EQ (class2, val4);
		EXPECT_EQ (class2, val5);
		EXPECT_EQ (class2, val6);
		
		EXPECT_EQ (class1.value, val3.value);
		EXPECT_EQ (class2->value, val4->value);
		EXPECT_EQ (class2->value, val6->value);
	}

}}

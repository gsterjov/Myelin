
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
		
		
		EXPECT_EQ (true, *TYPE(int) == *value1.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value2.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass)  == *value3.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass*) == *value4.getType());
		
		
		int         val1 = value1.get <int> ();
		std::string val2 = value2.get <std::string> ();
		
		ValueTestClass  val3 = value3.get <ValueTestClass> ();
		ValueTestClass* val4 = value4.get <ValueTestClass*> ();
		
//		void* val5 = value4.get <void*> ();
//		ValueTestClass* val6 = static_cast<ValueTestClass*> (val5);
		
		
		EXPECT_EQ (1, val1);
		EXPECT_EQ (test, val2);
		
		EXPECT_NE (&class1, &val3);
		EXPECT_EQ (class2, val4);
//		EXPECT_EQ (class2, val5);
//		EXPECT_EQ (class2, val6);
		
		EXPECT_EQ (class1.value, val3.value);
		EXPECT_EQ (class2->value, val4->value);
//		EXPECT_EQ (class2->value, val6->value);
	}

}}

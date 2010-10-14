
#include <gtest/gtest.h>
#include <Myelin/Value.h>

#include "MockClass.h"


namespace Myelin {
namespace Test {


	class ValueTestClass
	{
	public:
		ValueTestClass () : value(true) {}
		bool value;
	};
	
	
	
	/* value test fixture */
	class ValueTest : public testing::Test
	{
	public:
		ValueTest ()
		: ptr (new ValueTestClass()),
		  ref (klass),
		  str ("test"),
		  
		  value_int (1),
		  value_string (str),
		  value_class (klass),
		  value_ptr (ptr),
		  value_ref (ref)
		{
			Types::init_types();
		}
		
		
		~ValueTest ()
		{
			delete ptr;
		}
		
		
	protected:
		ValueTestClass klass;
		ValueTestClass* ptr;
		ValueTestClass& ref;
		
		std::string str;
		
		Value value_empty;
		Value value_int;
		Value value_string;
		Value value_class;
		Value value_ptr;
		Value value_ref;
	};
	
	
	
	/* test generic value creation */
	TEST_F (ValueTest, CreateValue)
	{
		EXPECT_EQ (true, *TYPE(void) == *value_empty.getType());
		EXPECT_EQ (true, *TYPE(int) == *value_int.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value_string.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass)  == *value_class.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass*) == *value_ptr.getType());
		
		/* FIXME: Value not storing references */
//		EXPECT_EQ (true, *TYPE(ValueTestClass&) == *value_ref.getType());
	}
	
	
	
	
	/* test value retrieval */
	TEST_F (ValueTest, GetValue)
	{
		/* values */
		int val1;
		std::string val2;
		ValueTestClass val3;
		ValueTestClass* val4;
		
		/* get values */
		EXPECT_NO_THROW ({ val1 = value_int.get <int> (); });
		EXPECT_NO_THROW ({ val2 = value_string.get <std::string> (); });
		EXPECT_NO_THROW ({ val3 = value_class.get <ValueTestClass> (); });
		EXPECT_NO_THROW ({ val4 = value_ptr.get <ValueTestClass*> (); });
		
		
		/* check values */
		EXPECT_EQ (1, val1);
		EXPECT_EQ (str, val2);
		EXPECT_EQ (true, val3.value);
		EXPECT_EQ (true, val4->value);
		
		/* check class pointers */
		EXPECT_NE (&klass, &val3);
		EXPECT_EQ (ptr, val4);
		
		/* check class values */
		EXPECT_EQ (klass.value, val3.value);
		EXPECT_EQ (ptr->value, val4->value);
	}
	
	
	
	/* test bad value cast */
	TEST_F (ValueTest, GetValue_BadCast)
	{
		void* dummy;
		
		/* get values expecting a bad cast */
		EXPECT_ANY_THROW ({ dummy = value_empty.get <void*> (); });
		EXPECT_ANY_THROW ({ dummy = value_int.get <void*> (); });
		EXPECT_ANY_THROW ({ dummy = value_string.get <void*> (); });
		EXPECT_ANY_THROW ({ dummy = value_class.get <void*> (); });
		EXPECT_ANY_THROW ({ dummy = value_ptr.get <void*> (); });
	}
	
	
	
	
	/* test get pointer */
	TEST_F (ValueTest, GetPointer)
	{
		Pointer val (ptr);
		Pointer& val_ref = val;
		
		Value value1 (new Pointer (ptr));
		Value value2 (val_ref);
		Value value3 (val);
		
		
		/* values */
		Pointer* val1 = 0;
		Pointer* val2 = 0;
		Pointer* val3 = 0;
		Pointer* val4 = 0;
		
		EXPECT_NO_THROW ({ val1 = value1.getPointer (); });
		EXPECT_NO_THROW ({ val2 = value2.getPointer (); });
		EXPECT_NO_THROW ({ val3 = value3.getPointer (); });
		EXPECT_NO_THROW ({ val4 = value_ptr.getPointer (); });
		
		EXPECT_EQ (true, val1 != 0);
		EXPECT_EQ (true, val2 != 0);
		EXPECT_EQ (true, val3 != 0);
		EXPECT_EQ (true, val4 != 0);
	}
	
	
	
	/* test bad pointer cast */
	TEST_F (ValueTest, GetPointer_BadCast)
	{
		/* values */
		Pointer* val1 = 0;
		
		EXPECT_ANY_THROW ({ val1 = value_empty.getPointer (); });
		EXPECT_ANY_THROW ({ val1 = value_int.getPointer (); });
		EXPECT_ANY_THROW ({ val1 = value_string.getPointer (); });
		EXPECT_ANY_THROW ({ val1 = value_class.getPointer (); });
	}
	
	
	
	/* test create pointer */
	TEST_F (ValueTest, CreatePointer)
	{
//		klass.value = true;
//		
//		Value val (klass);
//		
//		Pointer* pointer = 0;
//		ValueTestClass* val_ptr = 0;
//		
//		EXPECT_NO_THROW ({ pointer = val.createPointer(); });
//		EXPECT_NO_THROW ({ val_ptr = pointer->get <ValueTestClass> (); });
//		
//		EXPECT_TRUE (val_ptr != 0);
//		EXPECT_EQ (true, val_ptr->value);
	}
	
	
	
	
	/* test value setting */
	TEST_F (ValueTest, SetValue)
	{
		/* new values */
		std::string new_str = "new test";
		
		ValueTestClass new_klass;
		ValueTestClass* new_ptr = new ValueTestClass();
		
		new_klass.value = false;
		new_ptr->value = false;
		
		
		/* set values to same type */
		value_int.set (2);
		value_string.set (new_str);
		value_class.set (new_klass);
		value_ptr.set (new_ptr);
		
		
		/* check types */
		EXPECT_EQ (true, *TYPE(void) == *value_empty.getType());
		EXPECT_EQ (true, *TYPE(int) == *value_int.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value_string.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass)  == *value_class.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass*) == *value_ptr.getType());
		
		
		/* values */
		int val1;
		std::string val2;
		ValueTestClass val3;
		ValueTestClass* val4;
		
		/* get values */
		EXPECT_NO_THROW ({ val1 = value_int.get <int> (); });
		EXPECT_NO_THROW ({ val2 = value_string.get <std::string> (); });
		EXPECT_NO_THROW ({ val3 = value_class.get <ValueTestClass> (); });
		EXPECT_NO_THROW ({ val4 = value_ptr.get <ValueTestClass*> (); });
		
		
		/* check values */
		EXPECT_EQ (2, val1);
		EXPECT_EQ (new_str, val2);
		EXPECT_EQ (false, val3.value);
		EXPECT_EQ (false, val4->value);
		
		/* check class pointers */
		EXPECT_NE (&klass, &val3);
		EXPECT_NE (&new_klass, &val3);
		EXPECT_NE (ptr, val4);
		EXPECT_EQ (new_ptr, val4);
		
		/* check class values */
		EXPECT_NE (klass.value, val3.value);
		EXPECT_NE (ptr->value, val4->value);
		EXPECT_EQ (new_klass.value, val3.value);
		EXPECT_EQ (new_ptr->value, val4->value);
	}
	
	
	
	
	/* test value setting with new type */
	TEST_F (ValueTest, SetValue_NewType)
	{
		/* new values */
		std::string new_str = "new test";
		
		ValueTestClass new_klass;
		ValueTestClass* new_ptr = new ValueTestClass();
		
		new_klass.value = false;
		new_ptr->value = false;
		
		
		/* set values to different type */
		value_empty.set (3.0f);
		value_int.set (new_str);
		value_string.set (2);
		value_class.set (new_ptr);
		value_ptr.set (new_klass);
		
		
		/* check types */
		EXPECT_EQ (true, *TYPE(float) == *value_empty.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value_int.getType());
		EXPECT_EQ (true, *TYPE(int) == *value_string.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass*)  == *value_class.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass) == *value_ptr.getType());
		
		
		
		/* values */
		float val1;
		std::string val2;
		int val3;
		ValueTestClass* val4;
		ValueTestClass val5;
		
		/* get values */
		EXPECT_NO_THROW ({ val1 = value_empty.get <float> (); });
		EXPECT_NO_THROW ({ val2 = value_int.get <std::string> (); });
		EXPECT_NO_THROW ({ val3 = value_string.get <int> (); });
		EXPECT_NO_THROW ({ val4 = value_class.get <ValueTestClass*> (); });
		EXPECT_NO_THROW ({ val5 = value_ptr.get <ValueTestClass> (); });
		
		
		/* check values */
		EXPECT_EQ (3.0f, val1);
		EXPECT_EQ (new_str, val2);
		EXPECT_EQ (2, val3);
		EXPECT_EQ (false, val4->value);
		EXPECT_EQ (false, val5.value);
		
		/* check class pointers */
		EXPECT_NE (ptr, val4);
		EXPECT_EQ (new_ptr, val4);
		EXPECT_NE (&klass, &val5);
		EXPECT_NE (&new_klass, &val5);
		
		/* check class values */
		EXPECT_NE (ptr->value, val4->value);
		EXPECT_NE (klass.value, val5.value);
		EXPECT_EQ (new_ptr->value, val4->value);
		EXPECT_EQ (new_klass.value, val5.value);
	}

}}

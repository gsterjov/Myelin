
#include <gtest/gtest.h>
#include <Myelin/Value.h>

#include "MockClass.h"
#include <iostream>

namespace Myelin {
namespace Test {


	class ValueTestClass
	{
	public:
		ValueTestClass () : value(true) {}
		bool value;
	};
	
	
	
	class TestClass
	{
	public:
		
		TestClass (int& val) : value(val) {}
		
		int& value;
	};
	
	
	
	/* value test fixture */
	class ValueTest : public testing::Test
	{
	public:
		ValueTest ()
		: ptr (new ValueTestClass()),
		  ref (klass),
		  str ("test")
		{
			Types::init_types();
			
			value_int = 1;
			value_string = str;
			value_class = klass;
			value_ptr = ptr;
			
			/* references have to be set explicitly */
			value_ref.set <ValueTestClass&> (ref);
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
		EXPECT_EQ (true, *TYPE(ValueTestClass&) == *value_ref.getType());
	}
	
	
	
	
	/* test value retrieval */
	TEST_F (ValueTest, GetValue)
	{
		/* values */
		int val1;
		std::string val2;
		ValueTestClass val3;
		ValueTestClass* val4;
		
		/* references cant be reseated so we retrieve it here */
		ValueTestClass& val5 = value_ref.get <ValueTestClass&> ();
		
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
		EXPECT_EQ (true, val5.value);
		
		/* check class pointers */
		EXPECT_NE (&klass, &val3);
		EXPECT_EQ (ptr, val4);
		EXPECT_EQ (&ref, &val5);
		
		/* check class values */
		EXPECT_EQ (klass.value, val3.value);
		EXPECT_EQ (ptr->value, val4->value);
		EXPECT_EQ (ref.value, val5.value);
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
		EXPECT_ANY_THROW ({ dummy = value_ref.get <void*> (); });
	}
	
	
	
	
	/* test get pointer */
	TEST_F (ValueTest, GetPointer)
	{
		/* values */
		void* val1 = 0;
		void* val2 = 0;
		void* val3 = 0;
		void* val4 = 0;
		void* val5 = 0;
		
		/* get pointers of all values */
		EXPECT_NO_THROW ({ val1 = value_int.getPointer (); });
		EXPECT_NO_THROW ({ val2 = value_string.getPointer (); });
		EXPECT_NO_THROW ({ val3 = value_class.getPointer (); });
		EXPECT_NO_THROW ({ val4 = value_ptr.getPointer (); });
		EXPECT_NO_THROW ({ val5 = value_ref.getPointer (); });
		
		/* all values are valid pointers */
		EXPECT_TRUE (val1 != 0);
		EXPECT_TRUE (val2 != 0);
		EXPECT_TRUE (val3 != 0);
		EXPECT_TRUE (val4 != 0);
		EXPECT_TRUE (val5 != 0);
		
		/* pointers point to data inside value */
		EXPECT_EQ (&value_int.get <int> (), val1);
		EXPECT_EQ (&value_string.get <std::string> (), val2);
		EXPECT_EQ (&value_class.get <ValueTestClass> (), val3);
		EXPECT_EQ (value_ptr.get <ValueTestClass*> (), val4);
		EXPECT_EQ (&value_ref.get <ValueTestClass&> (), val5);
	}
	
	
	
	/* test bad pointer cast */
	TEST_F (ValueTest, GetPointer_BadCast)
	{
		/* values */
		void* val1 = 0;
		EXPECT_ANY_THROW ({ val1 = value_empty.getPointer (); });
	}
	
	
	
	
	/* test value setting */
	TEST_F (ValueTest, SetValue)
	{
		/* new values */
		std::string new_str = "new test";
		
		ValueTestClass new_klass;
		ValueTestClass* new_ptr = new ValueTestClass();
		
		ValueTestClass ref_klass;
		ValueTestClass& new_ref = ref_klass;
		
		
		new_klass.value = false;
		new_ptr->value = false;
		new_ref.value = false;
		
		
		/* set values to same type */
		value_int.set (2);
		value_string.set (new_str);
		value_class.set (new_klass);
		value_ptr.set (new_ptr);
		value_ref.set <ValueTestClass&> (new_ref);
		
		
		/* check types */
		EXPECT_EQ (true, *TYPE(void) == *value_empty.getType());
		EXPECT_EQ (true, *TYPE(int) == *value_int.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value_string.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass)  == *value_class.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass*) == *value_ptr.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass&) == *value_ref.getType());
		
		
		/* values */
		int val1;
		std::string val2;
		ValueTestClass val3;
		ValueTestClass* val4;
		ValueTestClass& val5 = value_ref.get <ValueTestClass&> ();
		
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
		EXPECT_EQ (false, val5.value);
		
		/* check class pointers */
		EXPECT_NE (&klass, &val3);
		EXPECT_NE (&new_klass, &val3);
		EXPECT_NE (ptr, val4);
		EXPECT_NE (&ref, &val5);
		
		EXPECT_EQ (new_ptr, val4);
		EXPECT_EQ (&new_ref, &val5);
		
		/* check class values */
		EXPECT_NE (klass.value, val3.value);
		EXPECT_NE (ptr->value, val4->value);
		EXPECT_NE (ref.value, val5.value);
		
		EXPECT_EQ (new_klass.value, val3.value);
		EXPECT_EQ (new_ptr->value, val4->value);
		EXPECT_EQ (new_ref.value, val5.value);
		
		/* check reference link */
		ref_klass.value = true;
		EXPECT_EQ (true, val5.value);
		EXPECT_EQ (true, value_ref.get<ValueTestClass&>().value);
	}
	
	
	
	
	/* test value setting with new type */
	TEST_F (ValueTest, SetValue_NewType)
	{
		/* new values */
		std::string new_str = "new test";
		
		ValueTestClass new_klass;
		ValueTestClass* new_ptr = new ValueTestClass();
		
		ValueTestClass ref_klass;
		ValueTestClass& new_ref = ref_klass;
		
		new_klass.value = false;
		new_ptr->value = false;
		new_ref.value = false;
		
		
		/* set values to different type */
		value_empty.set <ValueTestClass&> (new_ref);
		value_int.set (new_str);
		value_string.set (2);
		value_class.set (new_ptr);
		value_ptr.set (new_klass);
		value_ref.set (3.0f);
		
		
		/* check types */
		EXPECT_EQ (true, *TYPE(ValueTestClass&) == *value_empty.getType());
		EXPECT_EQ (true, *TYPE(std::string) == *value_int.getType());
		EXPECT_EQ (true, *TYPE(int) == *value_string.getType());
		
		EXPECT_EQ (true, *TYPE(ValueTestClass*)  == *value_class.getType());
		EXPECT_EQ (true, *TYPE(ValueTestClass) == *value_ptr.getType());
		EXPECT_EQ (true, *TYPE(float) == *value_ref.getType());
		
		
		
		/* values */
		ValueTestClass& val1 = value_empty.get <ValueTestClass&> ();
		std::string val2;
		int val3;
		ValueTestClass* val4;
		ValueTestClass val5;
		float val6;
		
		/* get values */
		EXPECT_NO_THROW ({ val2 = value_int.get <std::string> (); });
		EXPECT_NO_THROW ({ val3 = value_string.get <int> (); });
		EXPECT_NO_THROW ({ val4 = value_class.get <ValueTestClass*> (); });
		EXPECT_NO_THROW ({ val5 = value_ptr.get <ValueTestClass> (); });
		EXPECT_NO_THROW ({ val6 = value_ref.get <float> (); });
		
		
		/* check values */
		EXPECT_EQ (false, val1.value);
		EXPECT_EQ (new_str, val2);
		EXPECT_EQ (2, val3);
		EXPECT_EQ (false, val4->value);
		EXPECT_EQ (false, val5.value);
		EXPECT_EQ (3.0f, val6);
		
		/* check class pointers */
		EXPECT_EQ (&new_ref, &val1);
		EXPECT_EQ (new_ptr, val4);
		EXPECT_NE (&new_klass, &val5);
		
		/* check class values */
		EXPECT_EQ (new_ref.value, val1.value);
		EXPECT_EQ (new_ptr->value, val4->value);
		EXPECT_EQ (new_klass.value, val5.value);
		
		/* check reference link */
		ref_klass.value = true;
		EXPECT_EQ (true, val1.value);
		EXPECT_EQ (true, value_empty.get<ValueTestClass&>().value);
	}

}}

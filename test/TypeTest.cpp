
#include <gtest/gtest.h>
#include <Myelin/Type.h>


namespace Myelin {
namespace Test {

	/* test generic type creation */
	TEST (TypeTest, CreateType)
	{
		Types::init_types();
		
		const Type* t1 = TYPE(bool);
		const Type* t2 = TYPE(bool);
		const Type* t3 = TYPE(int);
		
		
		EXPECT_EQ (Types::bool_type(), t1);
		EXPECT_EQ (Types::bool_type(), t2);
		EXPECT_EQ (Types::int_type(), t3);
		
		EXPECT_EQ (t1, t2);
		EXPECT_EQ (t2, t1);
		
//		EXPECT_EQ ("bool", Types::bool_type->getName());
//		EXPECT_EQ ("bool", t1->getName());
//		EXPECT_EQ ("bool", t2->getName());
//		
//		EXPECT_EQ ("int", Types::int_type->getName());
//		EXPECT_EQ ("int", t3->getName());
	}

}}

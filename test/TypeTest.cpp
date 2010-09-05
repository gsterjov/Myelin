
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
		
		
		EXPECT_EQ (Types::bool_t, t1->getAtom());
		EXPECT_EQ (Types::bool_t, t2->getAtom());
		EXPECT_EQ (Types::int_t, t3->getAtom());
		
		EXPECT_EQ (t1, t2);
		EXPECT_EQ (t2, t1);
		
		
		/* with diferent qualifiers */
		const Type* test1 = Types::get_type<bool>();
		const Type* test2 = Types::get_type<bool*>();
		const Type* test3 = Types::get_type<const bool&>();
		
		
		/* test trait flags */
		EXPECT_EQ (false, test1->isConstant());
		EXPECT_EQ (false, test1->isReference());
		EXPECT_EQ (false, test1->isPointer());
		EXPECT_EQ (false, test1->isVolatile());
		
		EXPECT_EQ (false, test2->isConstant());
		EXPECT_EQ (false, test2->isReference());
		EXPECT_EQ (true,  test2->isPointer());
		EXPECT_EQ (false, test2->isVolatile());
		
		EXPECT_EQ (true,  test3->isConstant());
		EXPECT_EQ (true,  test3->isReference());
		EXPECT_EQ (false, test3->isPointer());
		EXPECT_EQ (false, test3->isVolatile());
		
		
		/* test fundamental type atoms */
		EXPECT_EQ (Types::bool_t, test1->getAtom());
		EXPECT_EQ (Types::bool_t, test2->getAtom());
		EXPECT_EQ (Types::bool_t, test3->getAtom());
		
		
		/* types with diferent traits shouldnt match */
		EXPECT_NE (test1, test2); EXPECT_EQ (false, test1->equals (test2));
		EXPECT_NE (test1, test3); EXPECT_EQ (false, test1->equals (test3));
		
		EXPECT_NE (test2, test1); EXPECT_EQ (false, test2->equals (test1));
		EXPECT_NE (test2, test3); EXPECT_EQ (false, test2->equals (test3));
		
		EXPECT_NE (test3, test1); EXPECT_EQ (false, test3->equals (test1));
		EXPECT_NE (test3, test2); EXPECT_EQ (false, test3->equals (test2));
		
		
		/* types should be able to match if the same atom and traits */
		EXPECT_EQ (true, test1->equals (test1));
		EXPECT_EQ (true, *test1 == *test1);
		
		EXPECT_EQ (true, test2->equals (test2));
		EXPECT_EQ (true, *test2 == *test2);
		
		EXPECT_EQ (true, test2->equals (test2));
		EXPECT_EQ (true, *test2 == *test2);
	}

}}

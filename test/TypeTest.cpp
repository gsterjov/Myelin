
#include <gtest/gtest.h>

#include <Myelin/Type.h>
#include <Myelin/Value.h>
#include <Myelin/Class.h>
#include <Myelin/Converter.h>


namespace Myelin {
namespace Test {

	/* test classes */
	class TestGetTypes {};
	class TestRegisterTypes {};
	
	/* forwarded test classes */
	class TestFwdGetTypes;
	class TestFwdRegisterTypes;
	
	
	
	/* type test fixture */
	class TypeTest : public testing::Test
	{
	public:
		TypeTest ()
		{
			Types::init_types();
		}
	};
	
	
	
	/* test type initialisation */
	TEST_F (TypeTest, InitTypes)
	{
		/* make sure fundamental types match */
		EXPECT_EQ (TYPE(void)->getAtom(),    Types::void_t);
		EXPECT_EQ (TYPE(bool)->getAtom(),    Types::bool_t);
		EXPECT_EQ (TYPE(char)->getAtom(),    Types::char_t);
		EXPECT_EQ (TYPE(uchar)->getAtom(),   Types::uchar_t);
		EXPECT_EQ (TYPE(int)->getAtom(),     Types::int_t);
		EXPECT_EQ (TYPE(uint)->getAtom(),    Types::uint_t);
		EXPECT_EQ (TYPE(long)->getAtom(),    Types::long_t);
		EXPECT_EQ (TYPE(ulong)->getAtom(),   Types::ulong_t);
		EXPECT_EQ (TYPE(int64)->getAtom(),   Types::int64_t);
		EXPECT_EQ (TYPE(uint64)->getAtom(),  Types::uint64_t);
		EXPECT_EQ (TYPE(float)->getAtom(),   Types::float_t);
		EXPECT_EQ (TYPE(double)->getAtom(),  Types::double_t);
	}
	
	
	
	/* test type retrieval */
	TEST_F (TypeTest, GetTypes)
	{
		/* test fundamental type retrieval */
		const Type* test1 = Types::get_type <bool> ();
		EXPECT_EQ (Types::bool_t, test1->getAtom());
		
		
		/* trying to get an unregistered type should
		 * automatically register and return it. */
		const Type* test2 = Types::get_type <TestGetTypes> ();
		const Type* test3 = Types::get_type <TestGetTypes*> ();
		
		EXPECT_EQ (true, test2 != 0);
		EXPECT_EQ (true, test3 != 0);
		EXPECT_EQ (true, test2->getAtom() != 0);
		EXPECT_EQ (true, test3->getAtom() != 0);
		
		EXPECT_EQ (false, test2 == test3);
		EXPECT_EQ (true,  test2->getAtom() == test3->getAtom());
		
		
		/* getting type info should work for incomplete types also */
		const Type* test4 = Types::get_type <TestFwdGetTypes> ();
		const Type* test5 = Types::get_type <TestFwdGetTypes*> ();
		
		EXPECT_EQ (true, test4 != 0);
		EXPECT_EQ (true, test5 != 0);
		EXPECT_EQ (true, test4->getAtom() != 0);
		EXPECT_EQ (true, test5->getAtom() != 0);
		
		EXPECT_EQ (false, test4 == test5);
		EXPECT_EQ (true,  test4->getAtom() == test5->getAtom());
	}
	
	
	
	/* test type registration */
	TEST_F (TypeTest, RegisterTypes)
	{
		/* test fundamental type registration */
		const Type::Atom* test1 = Types::register_type <bool> ();
		EXPECT_EQ (Types::bool_t, test1);
		
		
		/* register a new type. If a type atom exists then the
		 * the name should replaced */
		const Type::Atom* test2 = Types::register_type <TestRegisterTypes> ("TestRegisterTypes");
		const Type::Atom* test3 = Types::register_type <TestRegisterTypes*> ("test");
		
		EXPECT_EQ (true, test2 != 0);
		EXPECT_EQ (true, test3 != 0);
		EXPECT_EQ (true, test2 == test3);
		
		EXPECT_EQ ("test", test2->getName());
		EXPECT_EQ ("test", test3->getName());
		
		
		/* registering a type should work for incomplete types also */
		const Type::Atom* test4 = Types::register_type <TestFwdRegisterTypes> ("TestFwdRegisterTypes");
		const Type::Atom* test5 = Types::register_type <TestFwdRegisterTypes*> ("test");
		
		EXPECT_EQ (true, test4 != 0);
		EXPECT_EQ (true, test5 != 0);
		EXPECT_EQ (true, test4 == test5);
		
		EXPECT_EQ ("test", test4->getName());
		EXPECT_EQ ("test", test5->getName());
	}
	
	
	
	
	/* test type conversion */
	TEST_F (TypeTest, ConvertTypes)
	{
		const char* str = "test";
		const Type* type = TYPE(std::string);
		
		const Class* klass = type->getAtom()->getClass();
		ConverterList list = klass->getConverters();
		
		std::string res;
		Value val = list[0]->convert (str);
		
		EXPECT_EQ (Types::string_t, val.getType()->getAtom());
		EXPECT_NO_THROW ({ res = val.get <std::string> (); });
		EXPECT_EQ (str, res);
	}
	
	
	
	/* test comparing types */
	TEST_F (TypeTest, CompareTypes)
	{
		/* create types */
		const Type* t1 = TYPE(bool);
		const Type* t2 = TYPE(bool);
		const Type* t3 = TYPE(int);
		
		/* types should be the same as fundamental types */
		EXPECT_EQ (Types::bool_t, t1->getAtom());
		EXPECT_EQ (Types::bool_t, t2->getAtom());
		EXPECT_EQ (Types::int_t, t3->getAtom());
		
		/* same types should equal each other if 
		 * they have the same qualifiers */
		EXPECT_EQ (true, t1->equals (t2));
		EXPECT_EQ (true, t2->equals (t1));
		
		
		/* with diferent qualifiers */
		const Type* test1 = Types::get_type<bool>();
		const Type* test2 = Types::get_type<bool*>();
		const Type* test3 = Types::get_type<bool&>();
		const Type* test4 = Types::get_type<const bool&>();
		const Type* test5 = Types::get_type<const bool*>();
		
		
		/* test fundamental type atoms */
		EXPECT_EQ (Types::bool_t, test1->getAtom());
		EXPECT_EQ (Types::bool_t, test2->getAtom());
		EXPECT_EQ (Types::bool_t, test3->getAtom());
		EXPECT_EQ (Types::bool_t, test4->getAtom());
		EXPECT_EQ (Types::bool_t, test5->getAtom());
	}
	
	
	
	/* test comparing type traits */
	TEST_F (TypeTest, CompareTraits)
	{
		/* same type, different qualifiers */
		const Type* test1 = Types::get_type<bool>();
		const Type* test2 = Types::get_type<bool*>();
		const Type* test3 = Types::get_type<bool&>();
		const Type* test4 = Types::get_type<const bool&>();
		const Type* test5 = Types::get_type<const bool*>();
		
		
		/* test trait flags */
		EXPECT_EQ (false, test1->isConstant());
		EXPECT_EQ (false, test1->isReference());
		EXPECT_EQ (false, test1->isPointer());
		EXPECT_EQ (false, test1->isVolatile());
		
		EXPECT_EQ (false, test2->isConstant());
		EXPECT_EQ (false, test2->isReference());
		EXPECT_EQ (true,  test2->isPointer());
		EXPECT_EQ (false, test2->isVolatile());
		
		EXPECT_EQ (false, test3->isConstant());
		EXPECT_EQ (true,  test3->isReference());
		EXPECT_EQ (false, test3->isPointer());
		EXPECT_EQ (false, test3->isVolatile());
		
		EXPECT_EQ (true,  test4->isConstant());
		EXPECT_EQ (true,  test4->isReference());
		EXPECT_EQ (false, test4->isPointer());
		EXPECT_EQ (false, test4->isVolatile());
		
		EXPECT_EQ (true,  test5->isConstant());
		EXPECT_EQ (false, test5->isReference());
		EXPECT_EQ (true,  test5->isPointer());
		EXPECT_EQ (false, test5->isVolatile());
		
		
		
		/* types with diferent traits shouldnt match */
		/* test 1 */
		EXPECT_EQ (false,  test1->equals (test2));
		EXPECT_EQ (false,  test1->equals (test3));
		EXPECT_EQ (false,  test1->equals (test4));
		EXPECT_EQ (false,  test1->equals (test5));
		
		EXPECT_EQ (false, *test1 == *test2);
		EXPECT_EQ (false, *test1 == *test3);
		EXPECT_EQ (false, *test1 == *test4);
		EXPECT_EQ (false, *test1 == *test5);
		
		EXPECT_EQ (true,  *test1 != *test2);
		EXPECT_EQ (true,  *test1 != *test3);
		EXPECT_EQ (true,  *test1 != *test4);
		EXPECT_EQ (true,  *test1 != *test5);
		
		/* test 2 */
		EXPECT_EQ (false,  test2->equals (test1));
		EXPECT_EQ (false,  test2->equals (test3));
		EXPECT_EQ (false,  test2->equals (test4));
		EXPECT_EQ (false,  test2->equals (test5));
		
		EXPECT_EQ (false, *test2 == *test1);
		EXPECT_EQ (false, *test2 == *test3);
		EXPECT_EQ (false, *test2 == *test4);
		EXPECT_EQ (false, *test2 == *test5);
		
		EXPECT_EQ (true,  *test2 != *test1);
		EXPECT_EQ (true,  *test2 != *test3);
		EXPECT_EQ (true,  *test2 != *test4);
		EXPECT_EQ (true,  *test2 != *test5);
		
		/* test 3 */
		EXPECT_EQ (false,  test3->equals (test1));
		EXPECT_EQ (false,  test3->equals (test2));
		EXPECT_EQ (false,  test3->equals (test4));
		EXPECT_EQ (false,  test3->equals (test5));
		
		EXPECT_EQ (false, *test3 == *test1);
		EXPECT_EQ (false, *test3 == *test2);
		EXPECT_EQ (false, *test3 == *test4);
		EXPECT_EQ (false, *test3 == *test5);
		
		EXPECT_EQ (true,  *test3 != *test1);
		EXPECT_EQ (true,  *test3 != *test2);
		EXPECT_EQ (true,  *test3 != *test4);
		EXPECT_EQ (true,  *test3 != *test5);
		
		/* test 4 */
		EXPECT_EQ (false,  test4->equals (test1));
		EXPECT_EQ (false,  test4->equals (test2));
		EXPECT_EQ (false,  test4->equals (test3));
		EXPECT_EQ (false,  test4->equals (test5));
		
		EXPECT_EQ (false, *test4 == *test1);
		EXPECT_EQ (false, *test4 == *test2);
		EXPECT_EQ (false, *test4 == *test3);
		EXPECT_EQ (false, *test4 == *test5);
		
		EXPECT_EQ (true,  *test4 != *test1);
		EXPECT_EQ (true,  *test4 != *test2);
		EXPECT_EQ (true,  *test4 != *test3);
		EXPECT_EQ (true,  *test4 != *test5);
		
		/* test 5 */
		EXPECT_EQ (false,  test5->equals (test1));
		EXPECT_EQ (false,  test5->equals (test2));
		EXPECT_EQ (false,  test5->equals (test3));
		EXPECT_EQ (false,  test5->equals (test4));
		
		EXPECT_EQ (false, *test5 == *test1);
		EXPECT_EQ (false, *test5 == *test2);
		EXPECT_EQ (false, *test5 == *test3);
		EXPECT_EQ (false, *test5 == *test4);
		
		EXPECT_EQ (true,  *test5 != *test1);
		EXPECT_EQ (true,  *test5 != *test2);
		EXPECT_EQ (true,  *test5 != *test3);
		EXPECT_EQ (true,  *test5 != *test4);
		
		
		
		/* create matching types */
		const Type* matching1 = Types::get_type<bool>();
		const Type* matching2 = Types::get_type<bool*>();
		const Type* matching3 = Types::get_type<bool&>();
		const Type* matching4 = Types::get_type<const bool&>();
		const Type* matching5 = Types::get_type<const bool*>();
		
		
		/* types should be able to match if the same atom and traits */
		EXPECT_EQ (true,   test1->equals (test1));
		EXPECT_EQ (true,   test1->equals (matching1));
		EXPECT_EQ (true,  *test1 == *test1);
		EXPECT_EQ (true,  *test1 == *matching1);
		EXPECT_EQ (false, *test1 != *test1);
		EXPECT_EQ (false, *test1 != *matching1);
		
		EXPECT_EQ (true,   test2->equals (test2));
		EXPECT_EQ (true,   test2->equals (matching2));
		EXPECT_EQ (true,  *test2 == *test2);
		EXPECT_EQ (true,  *test2 == *matching2);
		EXPECT_EQ (false, *test2 != *test2);
		EXPECT_EQ (false, *test2 != *matching2);
		
		EXPECT_EQ (true,   test3->equals (test3));
		EXPECT_EQ (true,   test3->equals (matching3));
		EXPECT_EQ (true,  *test3 == *test3);
		EXPECT_EQ (true,  *test3 == *matching3);
		EXPECT_EQ (false, *test3 != *test3);
		EXPECT_EQ (false, *test3 != *matching3);
		
		EXPECT_EQ (true,   test4->equals (test4));
		EXPECT_EQ (true,   test4->equals (matching4));
		EXPECT_EQ (true,  *test4 == *test4);
		EXPECT_EQ (true,  *test4 == *matching4);
		EXPECT_EQ (false, *test4 != *test4);
		EXPECT_EQ (false, *test4 != *matching4);
		
		EXPECT_EQ (true,   test5->equals (test5));
		EXPECT_EQ (true,   test5->equals (matching5));
		EXPECT_EQ (true,  *test5 == *test5);
		EXPECT_EQ (true,  *test5 == *matching5);
		EXPECT_EQ (false, *test5 != *test5);
		EXPECT_EQ (false, *test5 != *matching5);
	}

}}

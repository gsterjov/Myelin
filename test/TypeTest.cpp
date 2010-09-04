
#include <gtest/gtest.h>
#include <Myelin/Type.h>
#include <Myelin/TypeInfo.h>


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
		
		
		const TypeInfo* test1 = Types::get_type_info<int>();
		const TypeInfo* test2 = Types::get_type_info<int*>();
		
		const TypeInfo* test3 = Types::get_type_info<void>();
		const TypeInfo* test4 = Types::get_type_info<void*>();
		
		const TypeInfo* test5 = Types::get_type_info<Type>();
		const TypeInfo* test6 = Types::get_type_info<Type*>();
		
		const TypeInfo* test7 = Types::get_type_info<bool>();
		const TypeInfo* test8 = Types::get_type_info<bool*>();
		const TypeInfo* test9 = Types::get_type_info<const bool&>();
		
		
//		std::cout << test7->getType() << "-" << test7->getName() << "-" << test7->isConstant() << "-" << test7->isReference() << "-" << test7->isPointer() << std::endl;
//		std::cout << test8->getType() << "-" << test8->getName() << "-" << test8->isConstant() << "-" << test8->isReference() << "-" << test8->isPointer() << std::endl;
//		std::cout << test9->getType() << "-" << test9->getName() << "-" << test9->isConstant() << "-" << test9->isReference() << "-" << test9->isPointer() << std::endl;
		
		
//		EXPECT_EQ ("bool", Types::bool_type->getName());
//		EXPECT_EQ ("bool", t1->getName());
//		EXPECT_EQ ("bool", t2->getName());
//		
//		EXPECT_EQ ("int", Types::int_type->getName());
//		EXPECT_EQ ("int", t3->getName());
	}

}}

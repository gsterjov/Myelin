
#include <gtest/gtest.h>

#include <Myelin/Value.h>
#include <Myelin/Function.h>
#include <Myelin/Types/FunctionType.h>

#include "MockClass.h"


namespace Myelin {
namespace Test {



	/* function test fixture */
	class FunctionTest : public testing::Test
	{
	public:
		FunctionTest ()
		{
			Types::init_types();
		}
		
		
	protected:
		MockClass mock;
	};
	
	
	
	/* test functions from classes */
	TEST_F (FunctionTest, Call_Functions)
	{
		function_type <void ()>                        type0 (&MockClass::test0);
		function_type <void (int)>                     type1 (&MockClass::test1);
		function_type <void (int, int)>                type2 (&MockClass::test2);
		function_type <void (int, int, int)>           type3 (&MockClass::test3);
		function_type <void (int, int, int, int)>      type4 (&MockClass::test4);
		function_type <void (int, int, int, int, int)> type5 (&MockClass::test5);
		
		Function func0 ("test0", type0.type);
		Function func1 ("test1", type1.type);
		Function func2 ("test2", type2.type);
		Function func3 ("test3", type3.type);
		Function func4 ("test4", type4.type);
		Function func5 ("test5", type5.type);
		
		/* set instance */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		func3.bind (&mock);
		func4.bind (&mock);
		func5.bind (&mock);
		
		
		EXPECT_CALL (mock, test0 ()).Times(1);
		EXPECT_CALL (mock, test1 (1)).Times(1);
		EXPECT_CALL (mock, test2 (1,2)).Times(1);
		EXPECT_CALL (mock, test3 (1,2,3)).Times(1);
		EXPECT_CALL (mock, test4 (1,2,3,4)).Times(1);
		EXPECT_CALL (mock, test5 (1,2,3,4,5)).Times(1);
		
		
		List params;
		
		
		EXPECT_NO_THROW ({ func0.call (params); });
		
		params.push_back (1);
		EXPECT_NO_THROW ({ func1.call (params); });
		
		params.push_back (2);
		EXPECT_NO_THROW ({ func2.call (params); });
		
		params.push_back (3);
		EXPECT_NO_THROW ({ func3.call (params); });
		
		params.push_back (4);
		EXPECT_NO_THROW ({ func4.call (params); });
		
		params.push_back (5);
		EXPECT_NO_THROW ({ func5.call (params); });
	}
	
	
	
	
	/* test constant functions from classes */
	TEST_F (FunctionTest, Call_ConstantFunctions)
	{
		function_type <void () const>                        type0 (&MockClass::const_test0);
		function_type <void (int) const>                     type1 (&MockClass::const_test1);
		function_type <void (int, int) const>                type2 (&MockClass::const_test2);
		function_type <void (int, int, int) const>           type3 (&MockClass::const_test3);
		function_type <void (int, int, int, int) const>      type4 (&MockClass::const_test4);
		function_type <void (int, int, int, int, int) const> type5 (&MockClass::const_test5);
		
		Function func0 ("const_test0", type0.type);
		Function func1 ("const_test1", type1.type);
		Function func2 ("const_test2", type2.type);
		Function func3 ("const_test3", type3.type);
		Function func4 ("const_test4", type4.type);
		Function func5 ("const_test5", type5.type);
		
		/* set instance */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		func3.bind (&mock);
		func4.bind (&mock);
		func5.bind (&mock);
		
		
		EXPECT_CALL (mock, const_test0 ()).Times(1);
		EXPECT_CALL (mock, const_test1 (1)).Times(1);
		EXPECT_CALL (mock, const_test2 (1,2)).Times(1);
		EXPECT_CALL (mock, const_test3 (1,2,3)).Times(1);
		EXPECT_CALL (mock, const_test4 (1,2,3,4)).Times(1);
		EXPECT_CALL (mock, const_test5 (1,2,3,4,5)).Times(1);
		
		
		List params;
		
		
		EXPECT_NO_THROW ({ func0.call (params); });
		
		params.push_back (1);
		EXPECT_NO_THROW ({ func1.call (params); });
		
		params.push_back (2);
		EXPECT_NO_THROW ({ func2.call (params); });
		
		params.push_back (3);
		EXPECT_NO_THROW ({ func3.call (params); });
		
		params.push_back (4);
		EXPECT_NO_THROW ({ func4.call (params); });
		
		params.push_back (5);
		EXPECT_NO_THROW ({ func5.call (params); });
	}
	
	
	
	
	TEST_F (FunctionTest, Call_ReferenceParameter)
	{
		/* FIXME: Calling function with a reference parameter */
		
//		using namespace testing;
//		
//		Function <bool (const bool&)>        type0 (&MockClass::test_ref);
//		Function <const bool& (const bool&)> type1 (&MockClass::test_ret);
//		
//		MemberFunction func0 ("test_ref", type0.type);
//		MemberFunction func1 ("test_ret", type1.type);
//		
//		
//		EXPECT_CALL (mock, test_ref(true)).Times(1).WillRepeatedly(Return(true));
//		EXPECT_CALL (mock, test_ret(true)).Times(1).WillOnce(ReturnArg<0>());
//		
//		bool param = true;
//		List params;
//		Pointer instance (&mock);
//		
//		
//		/* reference parameter */
//		params.push_back (param);
//		
//		Value val1;
//		bool ret1;
//		
//		EXPECT_NO_THROW ({ val1 = func0.call (instance, params); });
//		EXPECT_NO_THROW ({ ret1 = val1.get<bool>(); });
//		EXPECT_EQ (true, ret1);
//		
//		
//		/* reference parameter, same reference return */
//		Value val2;
//		const bool* ret2;
//		
//		EXPECT_NO_THROW ({ val2 = func1.call (instance, params); });
//		EXPECT_NO_THROW ({ ret2 = val2.get<const bool*>(); });
//		
//		EXPECT_EQ (true, *ret2);
//		EXPECT_EQ (&param, ret2);
//		
//		/* test linkage */
//		param = false;
//		EXPECT_EQ (false, *ret2);
	}
	
	
	
	TEST_F (FunctionTest, Call_PointerParameter)
	{
		using namespace testing;
		
		function_type <bool (bool*)> type0 (&MockClass::test_ptr);
		Function func0 ("test_ptr", type0.type);
		func0.bind (&mock);
		
		
		EXPECT_CALL (mock, test_ptr(_)).Times(1).WillRepeatedly(Return(true));
		
		bool param = true;
		List params;
		
		
		/* pointer parameter */
		params.push_back (&param);
		
		Value val1;
		bool ret1;
		
		EXPECT_NO_THROW ({ val1 = func0.call (params); });
		EXPECT_NO_THROW ({ ret1 = val1.get<bool>(); });
		EXPECT_EQ (true, ret1);
		
		
		/* generic pointer parameter */
		
		/* FIXME: Cant convert generic pointers to parameter type */
		
//		Pointer ptr (&param);
//		
//		params.clear ();
//		params.push_back (ptr);
//		
//		Value val2;
//		bool ret2;
//		
//		EXPECT_NO_THROW ({ val2 = func0.call (instance, params); });
//		EXPECT_NO_THROW ({ ret2 = val2.get<bool>(); });
//		EXPECT_EQ (true, ret2);
	}
	
	
	
	TEST_F (FunctionTest, Call_GenericPointerAsParameter)
	{
//		using namespace testing;
//		
//		Function <bool (const bool&)> type0 (&MockClass::test_ref);
//		MemberFunction func0 ("test_ref", type0.type);
//		
//		
//		EXPECT_CALL (mock, test_ref(true)).Times(3).WillRepeatedly(Return(true));
//		
//		bool param = true;
//		List params;
//		Pointer instance (&mock);
//		
//		
//		/* pointer */
//		params.push_back (new Pointer(&param));
//		
//		Value val1;
//		bool ret1;
//		
//		EXPECT_NO_THROW ({ val1 = func0.call (instance, params); });
//		EXPECT_NO_THROW ({ ret1 = val1.get<bool>(); });
//		EXPECT_EQ (true, ret1);
//		
//		
//		/* value */
//		Pointer ptr1 (&param);
//		params.clear();
//		params.push_back (ptr1);
//		
//		Value val2;
//		bool ret2;
//		
//		EXPECT_NO_THROW ({ val2 = func0.call (instance, params); });
//		EXPECT_NO_THROW ({ ret2 = val2.get<bool>(); });
//		EXPECT_EQ (true, ret2);
//		
//		
//		/* reference */
//		Pointer& ptr2 = ptr1;
//		params.clear();
//		params.push_back (ptr2);
//		
//		Value val3;
//		bool ret3;
//		
//		EXPECT_NO_THROW ({ val3 = func0.call (instance, params); });
//		EXPECT_NO_THROW ({ ret3 = val3.get<bool>(); });
//		EXPECT_EQ (true, ret3);
	}
	
	
	
	
	/* test bad function parameters */
	TEST_F (FunctionTest, Call_BadParameters)
	{
		function_type <void (int, int, int, int, int)> type0 (&MockClass::test5);
		Function func0 ("test5", type0.type);
		func0.bind (&mock);
		
		List params;
		
		/* no parameters */
		EXPECT_ANY_THROW ({ func0.call (params); });
		
		/* not enough parameters */
		params.push_back (1);
		params.push_back (2);
		params.push_back (3);
		params.push_back (4);
		EXPECT_ANY_THROW ({ func0.call (params); });
		
		/* too many parameters */
		params.push_back (5);
		params.push_back (6);
		EXPECT_ANY_THROW ({ func0.call (params); });
		
		
		std::string test = "test";
		
		/* wrong types start */
		params.clear ();
		params.push_back (test);
		params.push_back (2);
		params.push_back (3);
		params.push_back (4);
		params.push_back (5);
		EXPECT_ANY_THROW ({ func0.call (params); });
		
		/* wrong types end */
		params.clear ();
		params.push_back (1);
		params.push_back (2);
		params.push_back (3);
		params.push_back (4);
		params.push_back (test);
		EXPECT_ANY_THROW ({ func0.call (params); });
		
		/* wrong types middle */
		params.clear ();
		params.push_back (1);
		params.push_back (2);
		params.push_back (test);
		params.push_back (4);
		params.push_back (5);
		EXPECT_ANY_THROW ({ func0.call (params); });
	}


}}

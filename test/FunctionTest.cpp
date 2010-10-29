
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
	
	
	
	
	TEST_F (FunctionTest, Call_ValueParameter)
	{
		using namespace testing;
		
		
		function_type <void (bool)>             type0 (&MockClass::val_test0);
		function_type <void (const bool)>       type1 (&MockClass::val_test1);
		function_type <bool (bool)>             type2 (&MockClass::val_test2);
		function_type <const bool (bool)>       type3 (&MockClass::val_test3);
		function_type <const bool (const bool)> type4 (&MockClass::val_test4);
		
		Function func0 ("val_test0", type0.type);
		Function func1 ("val_test1", type1.type);
		Function func2 ("val_test2", type2.type);
		Function func3 ("val_test3", type3.type);
		Function func4 ("val_test4", type4.type);
		
		/* set instance */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		func3.bind (&mock);
		func4.bind (&mock);
		
		
		EXPECT_CALL (mock, val_test0(_)).Times(2);
		EXPECT_CALL (mock, val_test1(_)).Times(2);
		EXPECT_CALL (mock, val_test2(_)).Times(2).WillRepeatedly(ReturnArg<0>());
		EXPECT_CALL (mock, val_test3(_)).Times(2).WillRepeatedly(ReturnArg<0>());
		EXPECT_CALL (mock, val_test4(_)).Times(2).WillRepeatedly(ReturnArg<0>());
		
		
		/* parameter value */
		bool param = true;
		const bool const_val = true;
		
		List params;
		params.push_back (param);
		
		List const_params;
		const_params.push_back (const_val);
		
		
		/* value parameter, no const downgrade */
		EXPECT_NO_THROW ({ func0.call (params); });
		EXPECT_NO_THROW ({ func0.call (const_params); });
		
		/* value parameter, const upgrade */
		EXPECT_NO_THROW ({ func1.call (params); });
		EXPECT_NO_THROW ({ func1.call (const_params); });
		
		
		/* value parameter, no return*/
		Value val2;
		bool ret2 = false;
		
		EXPECT_NO_THROW ({ val2 = func2.call (const_params); });
		EXPECT_NO_THROW ({ ret2 = val2.get <bool> (); });
		
		EXPECT_EQ (true, ret2);
		EXPECT_NE (&ret2, &param);
		
		/* const upgrade */
		EXPECT_NO_THROW ({ val2 = func2.call (params); });
		EXPECT_NO_THROW ({ ret2 = val2.get <bool> (); });
		
		EXPECT_EQ (true, ret2);
		EXPECT_NE (&ret2, &param);
		
		
		/* value parameter, const return */
		Value val3;
		bool ret3 = false;
		
		EXPECT_NO_THROW ({ val3 = func3.call (const_params); });
		EXPECT_NO_THROW ({ ret3 = val3.get <const bool> (); });
		
		EXPECT_EQ (true, ret3);
		EXPECT_NE (&ret3, &param);
		
		/* const upgrade */
		EXPECT_NO_THROW ({ val3 = func3.call (params); });
		EXPECT_NO_THROW ({ ret3 = val3.get <const bool> (); });
		
		EXPECT_EQ (true, ret3);
		EXPECT_NE (&ret3, &param);
		
		
		/* value parameter, const return, const param */
		Value val4;
		bool ret4 = false;
		
		EXPECT_NO_THROW ({ val4 = func4.call (const_params); });
		EXPECT_NO_THROW ({ ret4 = val4.get <const bool> (); });
		
		EXPECT_EQ (true, ret4);
		EXPECT_NE (&ret4, &const_val);
		
		/* const upgrade */
		EXPECT_NO_THROW ({ val4 = func4.call (params); });
		EXPECT_NO_THROW ({ ret4 = val4.get <const bool> (); });
		
		EXPECT_EQ (true, ret4);
		EXPECT_NE (&ret4, &param);
	}
	
	
	
	
	TEST_F (FunctionTest, Call_ReferenceParameter)
	{
		using namespace testing;
		
		
		function_type <void (bool&)>              type0 (&MockClass::ref_test0);
		function_type <void (const bool&)>        type1 (&MockClass::ref_test1);
		function_type <bool& (bool&)>             type2 (&MockClass::ref_test2);
		function_type <const bool& (bool&)>       type3 (&MockClass::ref_test3);
		function_type <const bool& (const bool&)> type4 (&MockClass::ref_test4);
		
		Function func0 ("ref_test0", type0.type);
		Function func1 ("ref_test1", type1.type);
		Function func2 ("ref_test2", type2.type);
		Function func3 ("ref_test3", type3.type);
		Function func4 ("ref_test4", type4.type);
		
		/* set instance */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		func3.bind (&mock);
		func4.bind (&mock);
		
		
		EXPECT_CALL (mock, ref_test0(_)).Times(1);
		EXPECT_CALL (mock, ref_test1(_)).Times(2);
		EXPECT_CALL (mock, ref_test2(_)).Times(1).WillOnce(ReturnArg<0>());
		EXPECT_CALL (mock, ref_test3(_)).Times(1).WillOnce(ReturnArg<0>());
		EXPECT_CALL (mock, ref_test4(_)).Times(2).WillRepeatedly(ReturnArg<0>());
		
		
		/* parameter value */
		bool param = true;
		bool& ref = param;
		const bool& const_ref = param;
		
		List params;
		params.push_back <bool&> (ref);
		
		List const_params;
		const_params.push_back <const bool&> (const_ref);
		
		
		/* reference parameter, no const downgrade */
		EXPECT_NO_THROW  ({ func0.call (params); });
		EXPECT_ANY_THROW ({ func0.call (const_params); });
		
		/* reference parameter, const upgrade */
		EXPECT_NO_THROW  ({ func1.call (params); });
		EXPECT_NO_THROW  ({ func1.call (const_params); });
		
		
		/* reference parameter, same reference return, no const downgrade */
		Value val2;
		
		EXPECT_ANY_THROW ({ func2.call (const_params); });
		EXPECT_NO_THROW ({ val2 = func2.call (params); });
		bool& ret2 = val2.get <bool&> ();
		
		EXPECT_EQ (true, ret2);
		EXPECT_EQ (&ret2, &param);
		
		
		/* reference parameter, const reference return, no const downgrade */
		Value val3;
		
		EXPECT_ANY_THROW ({ func3.call (const_params); });
		EXPECT_NO_THROW ({ val3 = func3.call (params); });
		const bool& ret3 = val3.get <const bool&> ();
		
		EXPECT_EQ (true, ret3);
		EXPECT_EQ (&ret3, &param);
		
		
		/* reference parameter, const reference return, const upgrade */
		Value val4;
		
		EXPECT_NO_THROW ({ val4 = func4.call (const_params); });
		const bool& ret4 = val4.get <const bool&> ();
		
		EXPECT_EQ (true, ret4);
		EXPECT_EQ (&ret4, &param);
		
		/* const upgrade */
		Value val5;
		
		EXPECT_NO_THROW ({ val5 = func4.call (params); });
		const bool& ret5 = val5.get <const bool&> ();
		
		EXPECT_EQ (true, ret5);
		EXPECT_EQ (&ret5, &param);
	}
	
	
	
	
	TEST_F (FunctionTest, Call_PointerParameter)
	{
		using namespace testing;
		
		
		function_type <void (bool*)>              type0 (&MockClass::ptr_test0);
		function_type <void (const bool*)>        type1 (&MockClass::ptr_test1);
		function_type <bool* (bool*)>             type2 (&MockClass::ptr_test2);
		function_type <const bool* (bool*)>       type3 (&MockClass::ptr_test3);
		function_type <const bool* (const bool*)> type4 (&MockClass::ptr_test4);
		
		Function func0 ("ptr_test0", type0.type);
		Function func1 ("ptr_test1", type1.type);
		Function func2 ("ptr_test2", type2.type);
		Function func3 ("ptr_test3", type3.type);
		Function func4 ("ptr_test4", type4.type);
		
		/* set instances */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		func3.bind (&mock);
		func4.bind (&mock);
		
		
		EXPECT_CALL (mock, ptr_test0(_)).Times(1);
		EXPECT_CALL (mock, ptr_test1(_)).Times(2);
		EXPECT_CALL (mock, ptr_test2(_)).Times(1).WillOnce(ReturnArg<0>());
		EXPECT_CALL (mock, ptr_test3(_)).Times(1).WillOnce(ReturnArg<0>());
		EXPECT_CALL (mock, ptr_test4(_)).Times(2).WillRepeatedly(ReturnArg<0>());
		
		
		/* parameter value */
		bool param = true;
		bool* ptr = &param;
		const bool* const_ptr = &param;
		
		List params;
		params.push_back (ptr);
		
		List const_params;
		const_params.push_back (const_ptr);
		
		
		/* pointer parameter, no const downgrade */
		EXPECT_NO_THROW  ({ func0.call (params); });
		EXPECT_ANY_THROW ({ func0.call (const_params); });
		
		/* pointer parameter, const upgrade */
		EXPECT_NO_THROW  ({ func1.call (params); });
		EXPECT_NO_THROW  ({ func1.call (const_params); });
		
		
		/* pointer parameter, same pointer return, no const downgrade */
		Value val2;
		bool* ret2 = 0;
		
		EXPECT_ANY_THROW ({ func2.call (const_params); });
		EXPECT_NO_THROW ({ val2 = func2.call (params); });
		EXPECT_NO_THROW ({ ret2 = val2.get <bool*> (); });
		
		EXPECT_EQ (true, *ret2);
		EXPECT_EQ (ret2, &param);
		
		
		/* pointer parameter, const pointer return, no const downgrade */
		Value val3;
		const bool* ret3 = 0;
		
		EXPECT_ANY_THROW ({ func3.call (const_params); });
		EXPECT_NO_THROW ({ val3 = func3.call (params); });
		EXPECT_NO_THROW ({ ret3 = val3.get <const bool*> (); });
		
		EXPECT_EQ (true, *ret3);
		EXPECT_EQ (ret3, &param);
		
		
		/* pointer parameter, const pointer return, const upgrade */
		Value val4;
		const bool* ret4 = 0;
		
		EXPECT_NO_THROW ({ val4 = func4.call (const_params); });
		EXPECT_NO_THROW ({ ret4 = val4.get <const bool*> (); });
		
		EXPECT_EQ (true, *ret4);
		EXPECT_EQ (ret4, &param);
		
		/* const upgrade */
		Value val5;
		const bool* ret5 = 0;
		
		EXPECT_NO_THROW ({ val5 = func4.call (params); });
		EXPECT_NO_THROW ({ ret5 = val5.get <const bool*> (); });
		
		EXPECT_EQ (true, *ret5);
		EXPECT_EQ (ret5, &param);
	}
	
	
	
	
	TEST_F (FunctionTest, Call_ValueToReferenceParameter)
	{
		using namespace testing;
		
		
		function_type <void (bool&)>       type0 (&MockClass::ref_test0);
		function_type <void (const bool&)> type1 (&MockClass::ref_test1);
		function_type <bool& (bool&)>      type2 (&MockClass::ref_test2);
		
		Function func0 ("ref_test0", type0.type);
		Function func1 ("ref_test1", type1.type);
		Function func2 ("ref_test2", type2.type);
		
		/* set instances */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		
		
		EXPECT_CALL (mock, ref_test0(_)).Times(1);
		EXPECT_CALL (mock, ref_test1(_)).Times(2);
		EXPECT_CALL (mock, ref_test2(_)).Times(1).WillOnce(ReturnArg<0>());
		
		
		/* parameter value */
		bool param = true;
		const bool const_val = true;
		
		List params;
		params.push_back (param);
		
		List const_params;
		/* explicitly set the type since const gets truncated */
		const_params.push_back <const bool> (const_val);
		
		
		/* reference parameter, no const downgrade */
		EXPECT_NO_THROW  ({ func0.call (params); });
		EXPECT_ANY_THROW ({ func0.call (const_params); });
		
		/* reference parameter, const upgrade */
		EXPECT_NO_THROW  ({ func1.call (params); });
		EXPECT_NO_THROW  ({ func1.call (const_params); });
		
		
		/* test reference return of value */
		Value val2;
		
		EXPECT_NO_THROW  ({ val2 = func2.call (params); });
		bool& ret2 = val2.get <bool&> ();
		
		EXPECT_EQ (true, ret2);
		
		/* make sure returned reference changes wrapped value */
		ret2 = false;
		EXPECT_EQ (false, val2.get <bool&> ());
	}
	
	
	
	
	TEST_F (FunctionTest, Call_PointerToReferenceParameter)
	{
		using namespace testing;
		
		
		function_type <void (bool&)>       type0 (&MockClass::ref_test0);
		function_type <void (const bool&)> type1 (&MockClass::ref_test1);
		function_type <bool& (bool&)>      type2 (&MockClass::ref_test2);
		
		Function func0 ("ref_test0", type0.type);
		Function func1 ("ref_test1", type1.type);
		Function func2 ("ref_test2", type2.type);
		
		/* set instances */
		func0.bind (&mock);
		func1.bind (&mock);
		func2.bind (&mock);
		
		
		EXPECT_CALL (mock, ref_test0(_)).Times(1);
		EXPECT_CALL (mock, ref_test1(_)).Times(2);
		EXPECT_CALL (mock, ref_test2(_)).Times(1).WillOnce(ReturnArg<0>());
		
		
		/* parameter value */
		bool param = true;
		const bool const_val = true;
		
		List params;
		params.push_back (&param);
		
		List const_params;
		const_params.push_back (&const_val);
		
		
		/* reference parameter, no const downgrade */
		EXPECT_NO_THROW  ({ func0.call (params); });
		EXPECT_ANY_THROW ({ func0.call (const_params); });
		
		/* reference parameter, const upgrade */
		EXPECT_NO_THROW  ({ func1.call (params); });
		EXPECT_NO_THROW  ({ func1.call (const_params); });
		
		
		/* test reference return of value */
		Value val2;
		
		EXPECT_NO_THROW  ({ val2 = func2.call (params); });
		bool& ret2 = val2.get <bool&> ();
		
		EXPECT_EQ (true, ret2);
		
		/* make sure returned reference changes wrapped value */
		ret2 = false;
		EXPECT_EQ (false, val2.get <bool&> ());
		EXPECT_EQ (false, param);
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

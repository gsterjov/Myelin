
#include <gtest/gtest.h>
#include <Myelin/GenericFunction.h>

#include "MockClass.h"


namespace Myelin {
namespace Test {


	/* test functions from classes without inheritance */
	TEST (FunctionTest, CallFunction)
	{
		Types::init_types();
		
		GenericFunction func0 ("test0", &MockClass::test0);
		GenericFunction func1 ("test1", &MockClass::test1);
		GenericFunction func2 ("test2", &MockClass::test2);
		GenericFunction func3 ("test3", &MockClass::test3);
		GenericFunction func4 ("test4", &MockClass::test4);
		GenericFunction func5 ("test5", &MockClass::test5);
		
		MockClass mock;
		
		EXPECT_CALL (mock, test0()).Times(1);
		EXPECT_CALL (mock, test1("test")).Times(1);
		EXPECT_CALL (mock, test2(true, "test")).Times(1);
		EXPECT_CALL (mock, test3(true, true, "test")).Times(1);
		EXPECT_CALL (mock, test4(true, true, true, "test")).Times(1);
		EXPECT_CALL (mock, test5(true, true, true, true, "test")).Times(1);
		
		
		std::string test = "test";
		
		List params;
		func0.call (&mock, params);
		
		params.push_back (test);
		func1.call (&mock, params);
		
		params.pop_back(); params.push_back (true); params.push_back (test);
		func2.call (&mock, params);
		
		params.pop_back(); params.push_back (true); params.push_back (test);
		func3.call (&mock, params);
		
		params.pop_back(); params.push_back (true); params.push_back (test);
		func4.call (&mock, params);
		
		params.pop_back(); params.push_back (true); params.push_back (test);
		func5.call (&mock, params);
	}
	
	
	
	TEST (FunctionTest, Call_ReferenceParameter)
	{
		GenericFunction func_ref ("test_ref", &MockClass::test_ref);
		GenericFunction func_ret ("test_ret", &MockClass::test_ret);
		
		MockClass mock;
//		EXPECT_CALL (mock, test_ref(true)).Times(1).WillRepeatedly(testing::Return(true));
//		EXPECT_CALL (mock, test_ret(true)).Times(1).WillOnce(testing::ReturnArg<0>());
		
		bool param = true;
		List params;
		
		
		/* reference parameter */
		params.push_back (param);
		
//		Value val1 = func_ref.call (&mock, params);
//		bool ret1 = val1.get<bool>();
//		
//		EXPECT_EQ (true, ret1);
		
		
		/* reference parameter, same reference return */
//		Value val2 = func_ret.call (&mock, params);
//		const bool* ret2 = val2.get<const bool*>();
//		
//		EXPECT_EQ (true, *ret2);
//		EXPECT_EQ (&param, ret2);
//		
//		/* linkage */
//		param = false;
//		EXPECT_EQ (false, *ret2);
	}
	
	
	
	TEST (FunctionTest, Call_PointerParameter)
	{
		using namespace testing;
		
		GenericFunction func_ptr ("testptr", &MockClass::test_ptr);
		
		MockClass mock;
		EXPECT_CALL (mock, test_ptr(_)).Times(2).WillRepeatedly(Return(true));
		
		bool param = true;
		List params;
		
		
		/* pointer parameter */
		params.push_back (&param);
		
		Value val1 = func_ptr.call (&mock, params);
		bool ret1 = val1.get<bool>();
		
		EXPECT_EQ (true, ret1);
		
		
		/* generic pointer parameter */
		Pointer ptr (&param);
		
		params.clear ();
		params.push_back (ptr);
		
		Value val2 = func_ptr.call (&mock, params);
		bool ret2 = val2.get<bool>();
		
		EXPECT_EQ (true, ret2);
	}
	
	
	
	TEST (FunctionTest, Call_GenericPointer)
	{
		GenericFunction func_ref ("test_ref", &MockClass::test_ref);
		
		MockClass mock;
		EXPECT_CALL (mock, test_ref(true)).Times(3).WillRepeatedly(testing::Return(true));
		
		bool param = true;
		List params;
		
		
		/* pointer */
		params.push_back (new Pointer(&param));
		
		Value val1 = func_ref.call (&mock, params);
		bool ret1 = val1.get<bool>();
		
		EXPECT_EQ (true, ret1);
		
		
		/* value */
		Pointer ptr1 (&param);
		params.clear();
		params.push_back (ptr1);
		
		Value val2 = func_ref.call (&mock, params);
		bool ret2 = val2.get<bool>();
		
		EXPECT_EQ (true, ret2);
		
		
		/* reference */
		Pointer& ptr2 = ptr1;
		params.clear();
		params.push_back (ptr2);
		
		Value val3 = func_ref.call (&mock, params);
		bool ret3 = val3.get<bool>();
		
		EXPECT_EQ (true, ret3);
	}


}}

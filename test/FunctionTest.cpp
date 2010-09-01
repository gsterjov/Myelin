
#include <gtest/gtest.h>
#include <Myelin/GenericFunction.h>

#include "MockClass.h"


namespace Myelin {
namespace Test {


	/* test functions from classes without inheritance */
	TEST (FunctionTest, CallFunction)
	{
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


}}

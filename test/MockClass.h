
#ifndef MYELIN_MOCK_CLASS_H_
#define MYELIN_MOCK_CLASS_H_


#include <gmock/gmock.h>


namespace Myelin {
namespace Test {

	class MockBaseClass
	{
	public:
		virtual void vfunc () = 0;
	};
	
	
	
	class MockClass
	{
	public:
		MOCK_METHOD0 (test0, void ());
		MOCK_METHOD1 (test1, void (int p1));
		MOCK_METHOD2 (test2, void (int p1, int p2));
		MOCK_METHOD3 (test3, void (int p1, int p2, int p3));
		MOCK_METHOD4 (test4, void (int p1, int p2, int p3, int p4));
		MOCK_METHOD5 (test5, void (int p1, int p2, int p3, int p4, int p5));
		
		MOCK_CONST_METHOD0 (const_test0, void ());
		MOCK_CONST_METHOD1 (const_test1, void (int p1));
		MOCK_CONST_METHOD2 (const_test2, void (int p1, int p2));
		MOCK_CONST_METHOD3 (const_test3, void (int p1, int p2, int p3));
		MOCK_CONST_METHOD4 (const_test4, void (int p1, int p2, int p3, int p4));
		MOCK_CONST_METHOD5 (const_test5, void (int p1, int p2, int p3, int p4, int p5));
		
		
		MOCK_METHOD1 (test_ref, bool (const bool& p1));
		MOCK_METHOD1 (test_ret, const bool& (const bool& p1));
		
		
		MOCK_METHOD1 (test_ptr, bool (bool* p1));
	};

}}


#endif /* MYELIN_MOCK_CLASS_H_ */

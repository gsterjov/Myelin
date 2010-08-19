
#ifndef MYELIN_MOCK_CLASS_H_
#define MYELIN_MOCK_CLASS_H_


#include <gmock/gmock.h>


namespace Myelin {
namespace Test {

	class MockClass
	{
	public:
//		MOCK_METHOD0 (method1, void());
//		
//		MOCK_METHOD1 (method2, bool(int arg1));
		
		
		MOCK_METHOD1 (test1, void(std::string arg1));
		MOCK_METHOD2 (test2, void(bool arg, std::string arg1));
		MOCK_METHOD3 (test3, void(bool arg, bool arg2, std::string arg1));
		MOCK_METHOD4 (test4, void(bool arg, bool arg2, bool arg3, std::string arg1));
		MOCK_METHOD5 (test5, void(bool arg, bool arg2, bool arg3, bool arg4, std::string arg1));
		
		
//		MOCK_METHOD2 (method3, bool(int arg1, bool arg2));
//		
//		MOCK_METHOD2 (method4, void(int arg1, bool arg2));
//		
//		MOCK_METHOD3 (method5, void(int arg1, bool arg2, std::string arg3));
	};

}}


#endif /* MYELIN_MOCK_CLASS_H_ */

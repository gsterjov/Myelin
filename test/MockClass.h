
#ifndef MYELIN_MOCK_CLASS_H_
#define MYELIN_MOCK_CLASS_H_


#include <gmock/gmock.h>


namespace Myelin {
namespace Test {

	class MockClass
	{
	public:
		MOCK_METHOD0 (method1, void());
		MOCK_METHOD1 (method2, bool(int arg1));
	};

}}


#endif /* MYELIN_MOCK_CLASS_H_ */

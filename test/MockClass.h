
#ifndef MYELIN_MOCK_CLASS_H_
#define MYELIN_MOCK_CLASS_H_


#include <gmock/gmock.h>


namespace Myelin {
namespace Test {

	class MockClass
	{
	public:
		MOCK_METHOD0 (method1, void());
	};

}}


#endif /* MYELIN_MOCK_CLASS_H_ */

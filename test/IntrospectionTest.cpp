
#include <gtest/gtest.h>

#include <Myelin/Myelin.h>


extern "C"
{
	extern void create_repository();
}


namespace Myelin {
namespace Test {



	/* function test fixture */
	class IntrospectionTest : public testing::Test
	{
	public:
		IntrospectionTest ()
		{
			Types::init_types();
		}
	};
	
	
	
	
	/* test instance creation */
	TEST_F (IntrospectionTest, CreateRepository)
	{
		create_repository();
	}

}}

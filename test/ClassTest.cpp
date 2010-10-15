
#include <gtest/gtest.h>

#include <Myelin/Value.h>
#include <Myelin/Class.h>
#include <Myelin/Constructor.h>
#include <Myelin/Types/ConstructorType.h>

#include "MockClass.h"



namespace Myelin {
namespace Test {



	/* function test fixture */
	class ClassTest : public testing::Test
	{
	public:
		ClassTest () : klass("MockClass")
		{
			Types::init_types();
		}
		
		
	protected:
		MockClass mock;
		
		Class klass;
	};
	
	
	
	
	/* test instance creation */
	TEST_F (ClassTest, CreateInstance)
	{
		ConstructorType0 <MockClass> type;
		Constructor ctor (&type);
		
		klass.addConstructor (&ctor);
		
		List params;
		Value instance = klass.createInstance (params);
		
		EXPECT_FALSE (instance.isEmpty());
		EXPECT_TRUE (instance.getPointer() != 0);
		EXPECT_TRUE (TYPE(MockClass*)->equals (instance.getType()));
		
		
		MockClass* mock = 0;
		EXPECT_NO_THROW ({ mock = instance.get<MockClass*>(); });
		
		if (mock) delete mock;
	}

}}

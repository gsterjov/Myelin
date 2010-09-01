
#include <gtest/gtest.h>
#include <Myelin/Repository.h>
#include <Myelin/RepositoryFactory.h>
#include <Myelin/TypeCreator.h>

#include <Myelin/Type.h>

#include "MockClass.h"



namespace Myelin {
namespace Test {


	extern "C" void create_repository ()
	{
		Repository* repo = RepositoryFactory::create ("TestRepo");
		ClassType<MockClass>::create (repo, "MockClass");
	}
	
	
	
	/* test simple meta class creation */
	TEST (ClassTest, CreateClass)
	{
		GenericClass<MockClass> klass ("MockClass");
		
		EXPECT_EQ ("MockClass", klass.getName());
		
		
		create_repository ();
		
		Repository* repo = RepositoryFactory::get ("TestRepo");
		
		EXPECT_EQ ("MockClass", repo->getClass("MockClass")->getName());
	}
	
	
	
	/* test instance creation */
	TEST (ClassTest, CreateInstance)
	{
		GenericClass<MockClass> klass ("MockClass");
		
		List params;
		
		Object* object = klass.createObject (params);
		
		EXPECT_TRUE (object != 0);
		EXPECT_TRUE (object->getInstance() != 0);
		
		
		void* instance = klass.createInstance (params);
		
		EXPECT_TRUE (instance != 0);
		
		
		if (object) delete object;
		if (instance) delete static_cast<MockClass*> (instance);
	}
	
	
	
	/* test instance creation */
	TEST (ClassTest, CreateInstance_C_API)
	{
		GenericClass<MockClass> klass ("MockClass");
		
		List* params = myelin_list_new();
		
		Object* object = myelin_class_create_object (&klass, params);
		
		EXPECT_TRUE (object != 0);
		EXPECT_TRUE (object->getInstance() != 0);
		
		
		void* instance = myelin_class_create_instance (&klass, params);
		
		EXPECT_TRUE (instance != 0);
		
		
		/* clean up */
		myelin_object_free (object);
		myelin_list_free (params);
		
		if (instance) delete static_cast<MockClass*> (instance);
	}

}}

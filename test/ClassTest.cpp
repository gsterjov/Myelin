
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

}}

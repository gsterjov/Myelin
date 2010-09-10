
#include <Myelin/Repository.h>
#include <Myelin/RepositoryFactory.h>
#include <Myelin/TypeCreator.h>
#include <Myelin/GenericClass.h>
#include <Myelin/GenericFunction.h>
#include <iostream>



class Forward;


class TestLibrary
{
public:
	bool test (int arg) { std::cout <<"LIBRARY TEST: " << arg << std::endl; return true; }
	bool anotherTest (int& arg)
	{
		std::cout <<"yet another test: " << arg << std::endl;
		arg++;
		return true;
	}
};


class AnotherClass
{
public:
	AnotherClass (int val) {}
	
	void test () { std::cout <<"ANOTHER LIBRARY TEST" << std::endl; }
	void forwarded (Forward* test) {}
};




extern "C" void create_repository ()
{
	Myelin::Repository* repo = Myelin::RepositoryFactory::create ("LibraryTest");
	
	
	Myelin::ClassType<TestLibrary>::create (repo, "TestLibrary")
						.function ("test", &TestLibrary::test)
						.function ("anotherTest", &TestLibrary::anotherTest);
	
	Myelin::ClassType<AnotherClass>::create (repo, "AnotherClass", "LibraryTest::Another")
						.constructor<int>()
						.function ("test", &AnotherClass::test)
						.function ("forwarded", &AnotherClass::forwarded);
}


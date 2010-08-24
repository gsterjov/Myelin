
#include <Myelin/Repository.h>
#include <Myelin/GenericClass.h>
#include <Myelin/GenericFunction.h>
#include <iostream>


class TestLibrary
{
public:
	bool test (int arg) { std::cout <<"LIBRARY TEST" << std::endl; return true; }
	bool anotherTest (int arg) { std::cout <<"yet another test" << std::endl; return true; }
};


class AnotherClass
{
public:
	bool test (int arg) { std::cout <<"ANOTHER LIBRARY TEST" << std::endl; return true; }
};




extern "C" void create_repository ()
{
	Myelin::Repository* repo = Myelin::RepositoryFactory::create ("LibraryTest");
	
	Myelin::ClassType::create<TestLibrary> (repo, "TestLibrary");
	Myelin::ClassType::create<AnotherClass> (repo, "AnotherClass");
	
	Myelin::Class *klass1 = repo->getClass("TestLibrary");
	Myelin::Class *klass2 = repo->getClass("AnotherClass");
	
	
	klass1->registerFunction (new Myelin::GenericFunction ("test", &TestLibrary::test));
	klass1->registerFunction (new Myelin::GenericFunction ("anotherTest", &TestLibrary::anotherTest));
	
	klass2->registerFunction (new Myelin::GenericFunction ("test", &AnotherClass::test));
}


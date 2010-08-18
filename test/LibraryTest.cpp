
#include "MetaClass.h"
#include "CMyelin.h"
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



extern "C" void initialise ()
{
	Myelin::MetaClass<TestLibrary>* meta = new Myelin::MetaClass<TestLibrary> ("TestLibrary");
	
	meta->addFunction<bool, int> ("test", &TestLibrary::test);
	meta->addFunction<bool, int> ("anotherTest", &TestLibrary::anotherTest);
	
	
	
	Myelin::MetaClass<AnotherClass>* meta2 = new Myelin::MetaClass<AnotherClass> ("AnotherClass");
	
	meta2->addFunction<bool, int> ("test", &AnotherClass::test);
}


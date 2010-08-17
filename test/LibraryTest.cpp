
#include "MetaClass.h"
#include "CMyelin.h"
#include <iostream>


class TestLibrary
{
public:
	bool test (int arg) { std::cout <<"LIBRARY TEST" << std::endl; return true; }
};



extern "C" void initialise ()
{
	Myelin::MetaClass<TestLibrary>* meta = new Myelin::MetaClass<TestLibrary> ("TestLibrary");
	
	meta->addFunction<bool, int> ("test", &TestLibrary::test);
}


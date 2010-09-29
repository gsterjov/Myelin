

#include <Myelin/Myelin.h>
#include <iostream>


namespace LibraryTest
{

	class Test1
	{
	public:
		virtual int call (int arg) = 0;
		
		void test() { std::cout << "testing" << std::endl; }
	};
	
	
	class Test2
	{
	public:
		void call_me (Test1* test1) { std::cout << test1->call(7) << std::endl; }
	};
	
	
	
	/* wrap function type virtuals */
	class Test1Wrapper : public Test1,
	                     public Myelin::Overridable <Test1Wrapper>
	{
	public:
		int call (int arg)
		{
			Myelin::List list;
			list.push_back (arg);
			
			return get("call")->call (list).get<long>();
		}
	};

}



extern "C"
{
	void create_repository ()
	{
		using namespace Myelin;
		using namespace LibraryTest;
		
		Repository* repo = RepositoryFactory::create ("LibraryTest");
		
		ClassType<Test1Wrapper>::create ("Test1")
				.constructor()
				.name_space (repo, "")
				.inherits <Test1> ()
				.pure ("call", &Test1::call)
				.function ("test", &Test1::test);
		
		ClassType<Test2>::create ("Test2")
				.constructor()
				.name_space (repo, "")
				.function ("call_me", &Test2::call_me);
	}
}

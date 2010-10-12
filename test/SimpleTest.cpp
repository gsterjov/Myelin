

#include <Myelin/Myelin.h>
#include <iostream>


namespace SimpleTest
{

	struct ValTest
	{
		int val;
		
		int get() { return val; }
	};
	
	
	
	class Test
	{
	public:
		void test1() { std::cout << "testing" << std::endl; }
		int test2() { return 3; }
		
		ValTest test3() { ValTest val; val.val = 4; return val; }
	};
	
}



extern "C"
{
	void create_repository ()
	{
		using namespace Myelin;
		using namespace SimpleTest;
		
		Repository* repo = RepositoryFactory::create ("SimpleTest");
		
		
		ClassType<ValTest>::create ("ValTest")
				.constructor()
				.name_space (repo, "")
				.function ("get", &ValTest::get);
		
		
		ClassType<Test>::create ("Test")
				.constructor()
				.name_space (repo, "")
				.function ("test1", &Test::test1)
				.function ("test2", &Test::test2)
				.function ("test3", &Test::test3);
	}
}

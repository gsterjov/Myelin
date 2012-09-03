/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

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
		
		
		ValTest test3()
		{
			ValTest val;
			val.val = 4;
			return val;
		}
		
		
		ValTest* test4()
		{
			ValTest* val = new ValTest();
			val->val = 5;
			return val;
		}
		
		
		ValTest& test5()
		{
			mVal.val = 6;
			return mVal;
		}
		
		
		void test6 (const ValTest& val)
		{
			std::cout << val.val << std::endl;
		}
		
		
	private:
		ValTest mVal;
	};
	
}



extern "C"
{
	Myelin::Repository* myelin_create_repository ()
	{
		using namespace Myelin;
		using namespace SimpleTest;
		
		Repository* repo = new Repository ("SimpleTest");
		
		
		ClassType<ValTest>::create ("ValTest")
				.constructor()
				.name_space (repo, "")
				.function ("get", &ValTest::get);
		
		
		ClassType<Test>::create ("Test")
				.constructor()
				.name_space (repo, "")
				.function ("test1", &Test::test1)
				.function ("test2", &Test::test2)
				.function ("test3", &Test::test3)
				.function ("test4", &Test::test4)
				.function ("test5", &Test::test5)
				.function ("test6", &Test::test6);
		
		
		return repo;
	}
}

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
	Myelin::Repository* myelin_create_repository ()
	{
		using namespace Myelin;
		using namespace LibraryTest;
		
		Repository* repo = new Repository ("LibraryTest");
		
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
		
		
		return repo;
	}
}

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

#include <gtest/gtest.h>

#include <Myelin/Value.h>
#include <Myelin/Class.h>
#include <Myelin/Constructor.h>
#include <Myelin/Types/ConstructorType.h>

#include "MockClass.h"



namespace Myelin {
namespace Test {



	/* function test fixture */
	class ClassTest : public testing::Test
	{
	public:
		ClassTest () : klass("MockClass")
		{
			Types::init_types();
		}
		
		
	protected:
		MockClass mock;
		
		Class klass;
	};
	
	
	
	
	/* test instance creation */
	TEST_F (ClassTest, CreateInstance)
	{
		ConstructorType0 <MockClass> type;
		Constructor ctor (&type);
		
		klass.addConstructor (&ctor);
		
		List params;
		Value instance = klass.createInstance (params);
		
		EXPECT_FALSE (instance.isEmpty());
		EXPECT_TRUE (instance.asPointer() != 0);
		EXPECT_TRUE (TYPE(MockClass*)->equals (instance.getType()));
		
		
		MockClass* mock = 0;
		EXPECT_NO_THROW ({ mock = instance.get<MockClass*>(); });
		
		if (mock) delete mock;
	}

}}

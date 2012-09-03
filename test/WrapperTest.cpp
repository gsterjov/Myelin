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

#include <Myelin/Type.h>
#include <Myelin/VTable.h>
#include <Myelin/Function.h>

#include <Myelin/Types/FunctionType.h>

#include "MockClass.h"
#include <iostream>


namespace Myelin {
namespace Test {



	/* function test fixture */
	class WrapperTest : public testing::Test
	{
	public:
		WrapperTest ()
		{
			Types::init_types();
		}
	};
	
	
	
	class MockBaseClassWrapper : public MockBaseClass,
	                             public Overridable <MockBaseClassWrapper>
	{
	public:
		void vfunc () { get("vfunc")->call (List()); }
	};
	
	
	class MockImpl
	{
	public:
		void vfunc () { std::cout << "vfunc called" << std::endl; }
	};
	
	
	
	/* test instance creation */
	TEST_F (WrapperTest, WrapClass)
	{
		MockBaseClassWrapper wrapper;
		MockImpl impl;
		
		
		function_type <void()> type (&MockImpl::vfunc);
		Function func ("vfunc", type.type);
		func.bind (&impl);
		
		wrapper.getVTable()->set (&func);
		
		MockBaseClass* base = &wrapper;
		base->vfunc();
	}

}}

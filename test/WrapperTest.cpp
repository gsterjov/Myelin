
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
		
		Pointer instance (&impl);
		func.bind (instance);
		
		wrapper.getVTable().set (&func);
		
		MockBaseClass* base = &wrapper;
		base->vfunc();
	}

}}

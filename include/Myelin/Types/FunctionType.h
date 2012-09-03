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

#ifndef MYELIN_FUNCTION_TYPE_H_
#define MYELIN_FUNCTION_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>

#include <Myelin/Function.h>
#include <Myelin/Types/MemberFunctionType.h>


namespace Myelin
{


	template <typename Signature>
	class function_type;
	
	
	
	/**
	 * Automatic function wrapper.
	 */
	template <typename ReturnType>
	class function_type <ReturnType ()>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)())
		{
			type = new MemberFunctionType0 <ClassType, ReturnType> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1>
	class function_type <ReturnType (Param1)>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1))
		{
			type = new MemberFunctionType1 <ClassType, ReturnType, Param1> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2>
	class function_type <ReturnType (Param1, Param2)>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2))
		{
			type = new MemberFunctionType2 <ClassType, ReturnType, Param1, Param2> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3>
	class function_type <ReturnType (Param1, Param2, Param3)>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3))
		{
			type = new MemberFunctionType3 <ClassType, ReturnType, Param1, Param2, Param3> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	class function_type <ReturnType (Param1, Param2, Param3, Param4)>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3, Param4))
		{
			type = new MemberFunctionType4 <ClassType, ReturnType, Param1, Param2, Param3, Param4> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class function_type <ReturnType (Param1, Param2, Param3, Param4, Param5)>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3, Param4, Param5))
		{
			type = new MemberFunctionType5 <ClassType, ReturnType, Param1, Param2, Param3, Param4, Param5> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	
	
	
	
	template <typename ReturnType>
	class function_type <ReturnType () const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)() const)
		{
			type = new ConstMemberFunctionType0 <ClassType, ReturnType> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1>
	class function_type <ReturnType (Param1) const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1) const)
		{
			type = new ConstMemberFunctionType1 <ClassType, ReturnType, Param1> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2>
	class function_type <ReturnType (Param1, Param2) const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2) const)
		{
			type = new ConstMemberFunctionType2 <ClassType, ReturnType, Param1, Param2> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3>
	class function_type <ReturnType (Param1, Param2, Param3) const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3) const)
		{
			type = new ConstMemberFunctionType3 <ClassType, ReturnType, Param1, Param2, Param3> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	class function_type <ReturnType (Param1, Param2, Param3, Param4) const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3, Param4) const)
		{
			type = new ConstMemberFunctionType4 <ClassType, ReturnType, Param1, Param2, Param3, Param4> (func);
		}
		
		~function_type() { delete type; }
	};
	
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	class function_type <ReturnType (Param1, Param2, Param3, Param4, Param5) const>
	{
	public:
		FunctionType* type;
		
		template <typename ClassType>
		function_type (ReturnType (ClassType::*func)(Param1, Param2, Param3, Param4, Param5) const)
		{
			type = new ConstMemberFunctionType5 <ClassType, ReturnType, Param1, Param2, Param3, Param4, Param5> (func);
		}
		
		~function_type() { delete type; }
	};

}


#endif /* MYELIN_FUNCTION_TYPE_H_ */

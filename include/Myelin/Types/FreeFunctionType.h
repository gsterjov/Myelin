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

#ifndef MYELIN_FREE_FUNCTION_TYPE_H_
#define MYELIN_FREE_FUNCTION_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Function.h>
#include <Myelin/Type.h>
#include <Myelin/List.h>
#include <Myelin/Value.h>

#include <Myelin/Types/ParameterType.h>


namespace Myelin
{

/*****************************************************************************
 *                                                                           *
 * Free function callers used for easy specialisation of void return types   *
 *                                                                           *
 *****************************************************************************/
	
	template <typename ReturnType>
	struct FreeCaller0
	{
		typedef ReturnType (*FuncType)();
		static Value call (FuncType func)
		{ return func (); }
	};
	
	template <typename ReturnType, typename Param1>
	struct FreeCaller1
	{
		typedef ReturnType (*FuncType)(Param1);
		static Value call (FuncType func, Param1 param1)
		{ return func (param1); }
	};
	
	template <typename ReturnType, typename Param1, typename Param2>
	struct FreeCaller2
	{
		typedef ReturnType (*FuncType)(Param1, Param2);
		static Value call (FuncType func, Param1 param1, Param2 param2)
		{ return func (param1, param2); }
	};
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3>
	struct FreeCaller3
	{
		typedef ReturnType (*FuncType)(Param1, Param2, Param3);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3)
		{ return func (param1, param2, param3); }
	};
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct FreeCaller4
	{
		typedef ReturnType (*FuncType)(Param1, Param2, Param3, Param4);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
		{ return func (param1, param2, param3, param4); }
	};
	
	template <typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct FreeCaller5
	{
		typedef ReturnType (*FuncType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5)
		{ return func (param1, param2, param3, param4, param5); }
	};
	
	
	
	
	
	/**
	 * No parameter free function.
	 */
	template <typename ReturnType>
	class FreeFunctionType0 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) ();
		
		FreeFunctionType0 (FuncType function) : mFunction(function)
		{
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller0<ReturnType>::call (mFunction);
		}
		
	private:
		FuncType mFunction;
	};
	
	
	
	/**
	 * 1 parameter free function.
	 */
	template <typename ReturnType,
	          typename Param1>
	class FreeFunctionType1 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) (Param1);
		
		FreeFunctionType1 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller1<ReturnType,
			              Param1>::call (mFunction,
					mParam1.unpack (params[0]));
		}
		
	private:
		FuncType mFunction;
		ParameterType <Param1> mParam1;
	};
	
	
	
	/**
	 * 2 parameter free function.
	 */
	template <typename ReturnType,
	          typename Param1,
	          typename Param2>
	class FreeFunctionType2 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) (Param1,
		                                Param2);
		
		FreeFunctionType2 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller2<ReturnType,
			              Param1,
			              Param2>::call (mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]));
		}
		
	private:
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
	};
	
	
	
	/**
	 * 3 parameter free function.
	 */
	template <typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3>
	class FreeFunctionType3 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) (Param1,
		                                Param2,
		                                Param3);
		
		FreeFunctionType3 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller3<ReturnType,
			              Param1,
			              Param2,
			              Param3>::call (mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]));
		}
		
	private:
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
	};
	
	
	
	/**
	 * 4 parameter free function.
	 */
	template <typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4>
	class FreeFunctionType4 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) (Param1,
		                                Param2,
		                                Param3,
		                                Param4);
		
		FreeFunctionType4 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mParamTypes.push_back (TYPE(Param4));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller4<ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4>::call (mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]));
		}
		
	private:
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
	};
	
	
	
	/**
	 * 5 parameter free function.
	 */
	template <typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4,
	          typename Param5>
	class FreeFunctionType5 : public FunctionType
	{
	public:
		typedef ReturnType (*FuncType) (Param1,
		                                Param2,
		                                Param3,
		                                Param4,
		                                Param5);
		
		FreeFunctionType5 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mParamTypes.push_back (TYPE(Param4));
			this->mParamTypes.push_back (TYPE(Param5));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			return FreeCaller5<ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4,
			              Param5>::call (mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]),
					mParam5.unpack (params[4]));
		}
		
	private:
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
		ParameterType <Param5> mParam5;
	};
	
	
	
	
	
/*****************************************************************************
 *                                                                           *
 * Specialisation of void return types                                       *
 *                                                                           *
 *****************************************************************************/
	
	template <>
	struct FreeCaller0<void>
	{
		typedef void (*FuncType)();
		static Value call (FuncType func) { func (); return Value(); }
	};
	
	
	template <typename Param1>
	struct FreeCaller1<void, Param1>
	{
		typedef void (*FuncType)(Param1);
		static Value call (FuncType func, Param1 param1) { func (param1); return Value(); }
	};
	
	
	template <typename Param1, typename Param2>
	struct FreeCaller2<void, Param1, Param2>
	{
		typedef void (*FuncType)(Param1, Param2);
		static Value call (FuncType func, Param1 param1, Param2 param2) { func (param1, param2); return Value(); }
	};
	
	
	template <typename Param1, typename Param2, typename Param3>
	struct FreeCaller3<void, Param1, Param2, Param3>
	{
		typedef void (*FuncType)(Param1,Param2,Param3);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3) { func (param1, param2, param3); return Value(); }
	};
	
	
	template <typename Param1, typename Param2, typename Param3, typename Param4>
	struct FreeCaller4<void, Param1, Param2, Param3, Param4>
	{
		typedef void (*FuncType)(Param1, Param2, Param3, Param4);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { func (param1, param2, param3, param4); return Value(); }
	};
	
	
	template <typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct FreeCaller5<void, Param1, Param2, Param3, Param4, Param5>
	{
		typedef void (*FuncType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { func (param1, param2, param3, param4, param5); return Value(); }
	};

}


#endif /* MYELIN_MEMBER_FUNCTION_TYPE_H_ */

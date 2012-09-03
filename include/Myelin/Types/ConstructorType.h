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

#ifndef MYELIN_CONSTRUCTOR_TYPE_H_
#define MYELIN_CONSTRUCTOR_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/List.h>
#include <Myelin/Value.h>
#include <Myelin/Types/ParameterType.h>


namespace Myelin
{

	/**
	 * Base constructor type.
	 */
	struct ConstructorType
	{
		/**
		 * Create a class with the constructor.
		 */
		virtual Value create (const List& params) const = 0;
		
		/**
		 * The parameter types of the constructor.
		 */
		virtual const TypeList& getParamTypes() const = 0;
	};
	
	
	
	/**
	 * No parameters constructor type.
	 */
	template <typename ClassType>
	struct ConstructorType0 : ConstructorType
	{
		Value create (const List& params) const
		{
			return Value (new ClassType());
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
	};
	
	
	/**
	 * 1 parameter constructor type.
	 */
	template <typename ClassType,
	          typename Param1>
	struct ConstructorType1 : ConstructorType
	{
		ConstructorType1 ()
		{
			mParamTypes.push_back (TYPE(Param1));
		}
		
		Value create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]));
			return Value (ptr);
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
		ParameterType <Param1> mParam1;
	};
	
	
	/**
	 * 2 parameters constructor type.
	 */
	template <typename ClassType,
	          typename Param1,
	          typename Param2>
	struct ConstructorType2 : ConstructorType
	{
		ConstructorType2 ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
		}
		
		Value create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]));
			return Value (ptr);
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
	};
	
	
	/**
	 * 3 parameters constructor type.
	 */
	template <typename ClassType,
	          typename Param1,
	          typename Param2,
	          typename Param3>
	struct ConstructorType3 : ConstructorType
	{
		ConstructorType3 ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
		}
		
		Value create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]));
			return Value (ptr);
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
	};
	
	
	/**
	 * 4 parameters constructor type.
	 */
	template <typename ClassType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4>
	struct ConstructorType4 : ConstructorType
	{
		ConstructorType4 ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
		}
		
		Value create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]),
			                                mParam4.unpack (params[3]));
			return Value (ptr);
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
	};
	
	
	/**
	 * 5 parameters constructor type.
	 */
	template <typename ClassType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4,
	          typename Param5>
	struct ConstructorType5 : ConstructorType
	{
		ConstructorType5 ()
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
			mParamTypes.push_back (TYPE(Param5));
		}
		
		Value create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]),
			                                mParam4.unpack (params[3]),
			                                mParam5.unpack (params[4]));
			return Value (ptr);
		}
		
		const TypeList& getParamTypes () const { return mParamTypes; }
		
	private:
		TypeList mParamTypes;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
		ParameterType <Param5> mParam5;
	};

}


#endif /* MYELIN_CONSTRUCTOR_TYPE_H_ */

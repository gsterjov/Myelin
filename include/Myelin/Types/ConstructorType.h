
#ifndef MYELIN_CONSTRUCTOR_TYPE_H_
#define MYELIN_CONSTRUCTOR_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/List.h>
#include <Myelin/Pointer.h>
#include <Myelin/Types/Utils.h>
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
		virtual Pointer create (const List& params) const = 0;
		
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
		Pointer create (const List& params) const
		{
			return Pointer (new ClassType());
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
		
		Pointer create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]));
			return Pointer (ptr);
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
		
		Pointer create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]));
			return Pointer (ptr);
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
		
		Pointer create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]));
			return Pointer (ptr);
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
		
		Pointer create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]),
			                                mParam4.unpack (params[3]));
			return Pointer (ptr);
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
		
		Pointer create (const List& params) const
		{
			ClassType* ptr = new ClassType (mParam1.unpack (params[0]),
			                                mParam2.unpack (params[1]),
			                                mParam3.unpack (params[2]),
			                                mParam4.unpack (params[3]),
			                                mParam5.unpack (params[4]));
			return Pointer (ptr);
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

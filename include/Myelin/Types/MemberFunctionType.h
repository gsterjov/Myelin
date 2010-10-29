
#ifndef MYELIN_MEMBER_FUNCTION_TYPE_H_
#define MYELIN_MEMBER_FUNCTION_TYPE_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/Function.h>
#include <Myelin/Type.h>
#include <Myelin/List.h>
#include <Myelin/Value.h>

#include <Myelin/Types/ParameterType.h>


namespace Myelin
{

	/**
	 * Ensure the member function instance is valid.
	 */
	#define CHECK_INSTANCE(instance) \
		if (instance.isEmpty()) \
			throw std::runtime_error ("The member function has not been " \
					"bound to an instance and thus cannot be called.");
	
	/**
	 * Unpack the instance from a value.
	 */
	#define UNPACK_INSTANCE(instance,type) \
		instance.getType()->isPointer() ? \
				mInstance.get <type*>() : \
				static_cast<type*> (mInstance.asPointer ())



/*****************************************************************************
 *                                                                           *
 * Member function callers used for easy specialisation of void return types *
 *                                                                           *
 *****************************************************************************/
	
	template <typename ClassType, typename ReturnType>
	struct MemberCaller0
	{
		typedef ReturnType (ClassType::*FuncType)();
		static Value call (ClassType* instance, FuncType func)
		{ Value ret; ret.set <ReturnType> ((instance->*func)()); return ret; }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1>
	struct MemberCaller1
	{
		typedef ReturnType (ClassType::*FuncType)(Param1);
		static Value call (ClassType* instance, FuncType func, Param1 param1)
		{ Value ret; ret.set <ReturnType> ((instance->*func)(param1)); return ret; }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2>
	struct MemberCaller2
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2)
		{ Value ret; ret.set <ReturnType> ((instance->*func)(param1, param2)); return ret; }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3>
	struct MemberCaller3
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3)
		{ Value ret; ret.set <ReturnType> ((instance->*func)(param1, param2, param3)); return ret; }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct MemberCaller4
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3, Param4);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
		{ Value ret; ret.set <ReturnType> ((instance->*func)(param1, param2, param3, param4)); return ret; }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct MemberCaller5
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5)
		{ Value ret; ret.set <ReturnType> ((instance->*func)(param1, param2, param3, param4, param5)); return ret; }
	};
	
	
	
	
	template <typename ClassType, typename ReturnType>
	struct ConstMemberCaller0
	{
		typedef ReturnType (ClassType::*FuncType)() const;
		static Value call (ClassType* instance, FuncType func)
		{ return (instance->*func)(); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1>
	struct ConstMemberCaller1
	{
		typedef ReturnType (ClassType::*FuncType)(Param1) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1)
		{ return (instance->*func)(param1); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2>
	struct ConstMemberCaller2
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2)
		{ return (instance->*func)(param1, param2); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3>
	struct ConstMemberCaller3
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3)
		{ return (instance->*func)(param1, param2, param3); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct ConstMemberCaller4
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3, Param4) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4)
		{ return (instance->*func)(param1, param2, param3, param4); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct ConstMemberCaller5
	{
		typedef ReturnType (ClassType::*FuncType)(Param1, Param2, Param3, Param4, Param5) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5)
		{ return (instance->*func)(param1, param2, param3, param4, param5); }
	};
	
	
	
	
	
	/**
	 * No parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType>
	class MemberFunctionType0 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) ();
		
		MemberFunctionType0 (FuncType function) : mFunction(function)
		{
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller0<ClassType, ReturnType>::call (
					instance, mFunction);
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
	};
	
	
	
	/**
	 * 1 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1>
	class MemberFunctionType1 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1);
		
		MemberFunctionType1 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller1<ClassType,
			              ReturnType,
			              Param1>::call (instance, mFunction,
					mParam1.unpack (params[0]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
	};
	
	
	
	/**
	 * 2 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2>
	class MemberFunctionType2 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2);
		
		MemberFunctionType2 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller2<ClassType,
			              ReturnType,
			              Param1,
			              Param2>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
	};
	
	
	
	/**
	 * 3 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3>
	class MemberFunctionType3 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3);
		
		MemberFunctionType3 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller3<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
	};
	
	
	
	/**
	 * 4 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4>
	class MemberFunctionType4 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3,
		                                           Param4);
		
		MemberFunctionType4 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mParamTypes.push_back (TYPE(Param4));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller4<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
	};
	
	
	
	/**
	 * 5 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4,
	          typename Param5>
	class MemberFunctionType5 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3,
		                                           Param4,
		                                           Param5);
		
		MemberFunctionType5 (FuncType function) : mFunction(function)
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
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return MemberCaller5<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4,
			              Param5>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]),
					mParam5.unpack (params[4]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
		ParameterType <Param5> mParam5;
	};
	
	
	
	
	
	
	/**
	 * No parameter constant member function.
	 */
	template <typename ClassType,
	          typename ReturnType>
	class ConstMemberFunctionType0 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) () const;
		
		ConstMemberFunctionType0 (FuncType function) : mFunction(function)
		{
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller0<ClassType, ReturnType>::call (
					instance, mFunction);
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
	};
	
	
	
	/**
	 * 1 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1>
	class ConstMemberFunctionType1 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1) const;
		
		ConstMemberFunctionType1 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller1<ClassType,
			              ReturnType,
			              Param1>::call (instance, mFunction,
					mParam1.unpack (params[0]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
	};
	
	
	
	/**
	 * 2 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2>
	class ConstMemberFunctionType2 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2) const;
		
		ConstMemberFunctionType2 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller2<ClassType,
			              ReturnType,
			              Param1,
			              Param2>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
	};
	
	
	
	/**
	 * 3 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3>
	class ConstMemberFunctionType3 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3) const;
		
		ConstMemberFunctionType3 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller3<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
	};
	
	
	
	/**
	 * 4 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4>
	class ConstMemberFunctionType4 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3,
		                                           Param4) const;
		
		ConstMemberFunctionType4 (FuncType function) : mFunction(function)
		{
			this->mParamTypes.push_back (TYPE(Param1));
			this->mParamTypes.push_back (TYPE(Param2));
			this->mParamTypes.push_back (TYPE(Param3));
			this->mParamTypes.push_back (TYPE(Param4));
			this->mReturnType = TYPE(ReturnType);
		}
		
		Value call (const List& params) const
		{
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller4<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
		FuncType mFunction;
		ParameterType <Param1> mParam1;
		ParameterType <Param2> mParam2;
		ParameterType <Param3> mParam3;
		ParameterType <Param4> mParam4;
	};
	
	
	
	/**
	 * 5 parameter member function.
	 */
	template <typename ClassType,
	          typename ReturnType,
	          typename Param1,
	          typename Param2,
	          typename Param3,
	          typename Param4,
	          typename Param5>
	class ConstMemberFunctionType5 : public FunctionType
	{
	public:
		typedef ReturnType (ClassType::*FuncType) (Param1,
		                                           Param2,
		                                           Param3,
		                                           Param4,
		                                           Param5) const;
		
		ConstMemberFunctionType5 (FuncType function) : mFunction(function)
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
			CHECK_INSTANCE (mInstance);
			ClassType* instance = UNPACK_INSTANCE (mInstance, ClassType);
			
			return ConstMemberCaller5<ClassType,
			              ReturnType,
			              Param1,
			              Param2,
			              Param3,
			              Param4,
			              Param5>::call (instance, mFunction,
					mParam1.unpack (params[0]),
					mParam2.unpack (params[1]),
					mParam3.unpack (params[2]),
					mParam4.unpack (params[3]),
					mParam5.unpack (params[4]));
		}
		
		void setInstance (const Value& instance) { mInstance = instance; }
		
	private:
		Value mInstance;
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
	
	template <typename ClassType>
	struct MemberCaller0<ClassType,void>
	{
		typedef void (ClassType::*FuncType)();
		static Value call (ClassType* instance, FuncType func) { (instance->*func)(); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1>
	struct MemberCaller1<ClassType, void, Param1>
	{
		typedef void (ClassType::*FuncType)(Param1);
		static Value call (ClassType* instance, FuncType func, Param1 param1) { (instance->*func)(param1); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2>
	struct MemberCaller2<ClassType, void, Param1, Param2>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2) { (instance->*func)(param1, param2); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3>
	struct MemberCaller3<ClassType, void, Param1, Param2, Param3>
	{
		typedef void (ClassType::*FuncType)(Param1,Param2,Param3);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3) { (instance->*func)(param1, param2, param3); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct MemberCaller4<ClassType, void, Param1, Param2, Param3, Param4>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2, Param3, Param4);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { (instance->*func)(param1, param2, param3, param4); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct MemberCaller5<ClassType, void, Param1, Param2, Param3, Param4, Param5>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { (instance->*func)(param1, param2, param3, param4, param5); return Value(); }
	};
	
	
	
	
	template <typename ClassType>
	struct ConstMemberCaller0<ClassType,void>
	{
		typedef void (ClassType::*FuncType)() const;
		static Value call (ClassType* instance, FuncType func) { (instance->*func)(); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1>
	struct ConstMemberCaller1<ClassType, void, Param1>
	{
		typedef void (ClassType::*FuncType)(Param1) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1) { (instance->*func)(param1); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2>
	struct ConstMemberCaller2<ClassType, void, Param1, Param2>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2) { (instance->*func)(param1, param2); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3>
	struct ConstMemberCaller3<ClassType, void, Param1, Param2, Param3>
	{
		typedef void (ClassType::*FuncType)(Param1,Param2,Param3) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3) { (instance->*func)(param1, param2, param3); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct ConstMemberCaller4<ClassType, void, Param1, Param2, Param3, Param4>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2, Param3, Param4) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { (instance->*func)(param1, param2, param3, param4); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct ConstMemberCaller5<ClassType, void, Param1, Param2, Param3, Param4, Param5>
	{
		typedef void (ClassType::*FuncType)(Param1, Param2, Param3, Param4, Param5) const;
		static Value call (ClassType* instance, FuncType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { (instance->*func)(param1, param2, param3, param4, param5); return Value(); }
	};

}


#endif /* MYELIN_MEMBER_FUNCTION_TYPE_H_ */

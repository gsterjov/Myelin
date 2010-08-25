
#ifndef MYELIN_FUNCTOR_H_
#define MYELIN_FUNCTOR_H_


#include <Myelin/Value.h>
#include <Myelin/List.h>


namespace Myelin
{

	/* function callback interface */
	struct Functor
	{
		virtual Value call (void* object, const List& params) = 0;
	};
	
	
	
	
	/* used for easy specialisation of void returns */
	template <typename ClassType, typename ReturnType>
	struct MemberCaller0
	{
		typedef ReturnType (ClassType::*FunctionType)();
		static Value call (ClassType* obj, FunctionType func){ return (obj->*func)(); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1>
	struct MemberCaller1
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1);
		static Value call (ClassType* obj, FunctionType func, Param1 param1) { return (obj->*func)(param1); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2>
	struct MemberCaller2
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2) { return (obj->*func)(param1, param2); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3>
	struct MemberCaller3
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3) { return (obj->*func)(param1, param2, param3); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct MemberCaller4
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3, Param4);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { return (obj->*func)(param1, param2, param3, param4); }
	};
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct MemberCaller5
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { return (obj->*func)(param1, param2, param3, param4, param5); }
	};
	
	
	
	
	/* member functors */
	template <typename ClassType, typename ReturnType>
	struct MemberFunctor0 : Functor
	{
		typedef ReturnType(ClassType::*FunctionType)();
		FunctionType function;
		
		MemberFunctor0 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object) { return (object->*function)(); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller0<ClassType, ReturnType>::call (
					static_cast<ClassType*>(object), function);
		}
	};
	
	
	
	template <typename ClassType, typename ReturnType, typename Param1>
	struct MemberFunctor1 : Functor
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1);
		FunctionType function;
		
		MemberFunctor1 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object, Param1 param1) { return (object->*function)(param1); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller1<ClassType, ReturnType, Param1>::call (
					static_cast<ClassType*>(object), function,
					value_cast<Param1>(params[0]));
		}
	};
	
	
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2>
	struct MemberFunctor2 : Functor
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2);
		FunctionType function;
		
		MemberFunctor2 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object, Param1 param1, Param2 param2) { return (object->*function)(param1, param2); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller2<ClassType, ReturnType, Param1, Param2>::call (
					static_cast<ClassType*>(object), function,
					value_cast<Param1>(params[0]),
					value_cast<Param2>(params[1]));
		}
	};
	
	
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3>
	struct MemberFunctor3 : Functor
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3);
		FunctionType function;
		
		MemberFunctor3 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object, Param1 param1, Param2 param2, Param3 param3) { return (object->*function)(param1, param2, param3); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller3<ClassType, ReturnType, Param1, Param2, Param3>::call (
					static_cast<ClassType*>(object), function,
					value_cast<Param1>(params[0]),
					value_cast<Param2>(params[1]),
					value_cast<Param3>(params[2]));
		}
	};
	
	
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct MemberFunctor4 : Functor
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3, Param4);
		FunctionType function;
		
		MemberFunctor4 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { return (object->*function)(param1, param2, param3, param4); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller4<ClassType, ReturnType, Param1, Param2, Param3, Param4>::call (
					static_cast<ClassType*>(object), function,
					value_cast<Param1>(params[0]),
					value_cast<Param2>(params[1]),
					value_cast<Param3>(params[2]),
					value_cast<Param4>(params[3]));
		}
	};
	
	
	
	template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct MemberFunctor5 : Functor
	{
		typedef ReturnType (ClassType::*FunctionType)(Param1, Param2, Param3, Param4, Param5);
		FunctionType function;
		
		MemberFunctor5 (FunctionType func) : function(func) {}
		
		ReturnType call (ClassType* object, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { return (object->*function)(param1, param2, param3, param4, param5); }
		
		Value call (void* object, const List& params)
		{
			return MemberCaller5<ClassType, ReturnType, Param1, Param2, Param3, Param4, Param5>::call (
					static_cast<ClassType*>(object), function, 
					value_cast<Param1>(params[0]),
					value_cast<Param2>(params[1]),
					value_cast<Param3>(params[2]),
					value_cast<Param4>(params[3]),
					value_cast<Param5>(params[4]));
		}
	};
	
	
	
	
	
	/****************************************
	 * specialisation of void return values *
	 ****************************************/
	
	template <typename ClassType>
	struct MemberCaller0<ClassType,void>
	{
		typedef void (ClassType::*FunctionType)();
		static Value call (ClassType* obj, FunctionType func) { (obj->*func)(); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1>
	struct MemberCaller1<ClassType, void, Param1>
	{
		typedef void (ClassType::*FunctionType)(Param1);
		static Value call (ClassType* obj, FunctionType func, Param1 param1) { (obj->*func)(param1); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2>
	struct MemberCaller2<ClassType, void, Param1, Param2>
	{
		typedef void (ClassType::*FunctionType)(Param1, Param2);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2) { (obj->*func)(param1, param2); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3>
	struct MemberCaller3<ClassType, void, Param1, Param2, Param3>
	{
		typedef void (ClassType::*FunctionType)(Param1,Param2,Param3);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3) { (obj->*func)(param1, param2, param3); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4>
	struct MemberCaller4<ClassType, void, Param1, Param2, Param3, Param4>
	{
		typedef void (ClassType::*FunctionType)(Param1, Param2, Param3, Param4);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4) { (obj->*func)(param1, param2, param3, param4); return Value(); }
	};
	
	
	template <typename ClassType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
	struct MemberCaller5<ClassType, void, Param1, Param2, Param3, Param4, Param5>
	{
		typedef void (ClassType::*FunctionType)(Param1, Param2, Param3, Param4, Param5);
		static Value call (ClassType* obj, FunctionType func, Param1 param1, Param2 param2, Param3 param3, Param4 param4, Param5 param5) { (obj->*func)(param1, param2, param3, param4, param5); return Value(); }
	};

}


#endif /* MYELIN_FUNCTOR_H_ */
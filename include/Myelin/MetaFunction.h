
#ifndef MYELIN_META_FUNCTION_H_
#define MYELIN_META_FUNCTION_H_


#include <Myelin/Value.h>

#include <vector>
#include <iostream>
#include <typeinfo>


namespace Myelin
{

	typedef std::vector<Value> ValueList;
	
	
	
	class MetaFunction
	{
	public:
		template <typename C, typename R>
		MetaFunction (const std::string& name, R(C::*function)())
		: mData (new MemberData0<C,R>(function)),
		  mName (name),
		  mArgCount (0)
		{}
		
		template <typename C, typename R, typename A1>
		MetaFunction (const std::string& name, R(C::*function)(A1))
		: mData (new MemberData1<C,R,A1>(function)),
		  mName (name),
		  mArgCount (1)
		{}
		
		template <typename C, typename R, typename A1, typename A2>
		MetaFunction (const std::string& name, R(C::*function)(A1,A2))
		: mData (new MemberData2<C,R,A1,A2>(function)),
		  mName (name),
		  mArgCount (2)
		{}
		
		template <typename C, typename R, typename A1, typename A2, typename A3>
		MetaFunction (const std::string& name, R(C::*function)(A1,A2,A3))
		: mData (new MemberData3<C,R,A1,A2,A3>(function)),
		  mName (name),
		  mArgCount (3)
		{}
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
		MetaFunction (const std::string& name, R(C::*function)(A1,A2,A3,A4))
		: mData (new MemberData4<C,R,A1,A2,A3,A4>(function)),
		  mName (name),
		  mArgCount (4)
		{}
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
		MetaFunction (const std::string& name, R(C::*function)(A1,A2,A3,A4,A5))
		: mData (new MemberData5<C,R,A1,A2,A3,A4,A5>(function)),
		  mName (name),
		  mArgCount (5)
		{}
		
		
		
		std::string getName() { return mName; }
		int getArgCount() { return mArgCount; }
		
		
		
		Value call (void* object, const ValueList& args)
		{
			return mData->call (object, args);
		}
		
		
		
		
		template <typename C, typename R>
		R call (C* object)
		{
			MemberData0<C,R>* data = static_cast<MemberData0<C,R>*> (mData);
			return data->call (object);
		}
		
		
		template <typename C, typename R, typename A1>
		R call (C* object, A1 arg1)
		{
			MemberData1<C,R,A1>* data = static_cast<MemberData1<C,R,A1>*> (mData);
			return data->call (object, arg1);
		}
		
		
		template <typename C, typename R, typename A1, typename A2>
		R call (C* object, A1 arg1, A2 arg2)
		{
			MemberData2<C,R,A1,A2>* data = static_cast<MemberData2<C,R,A1,A2>*> (mData);
			return data->call (object, arg1, arg2);
		}
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3>
		R call (C* object, A1 arg1, A2 arg2, A3 arg3)
		{
			MemberData3<C,R,A1,A2,A3>* data = static_cast<MemberData3<C,R,A1,A2,A3>*> (mData);
			return data->call (object, arg1, arg2, arg3);
		}
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
		R call (C* object, A1 arg1, A2 arg2, A3 arg3, A4 arg4)
		{
			MemberData4<C,R,A1,A2,A3,A4>* data = static_cast<MemberData4<C,R,A1,A2,A3,A4>*> (mData);
			return data->call (object, arg1, arg2, arg3, arg4);
		}
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
		R call (C* object, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5)
		{
			MemberData5<C,R,A1,A2,A3,A4,A5>* data = static_cast<MemberData5<C,R,A1,A2,A3,A4,A5>*> (mData);
			return data->call (object, arg1, arg2, arg3, arg4, arg5);
		}
		
		
		
	private:
		struct Data
		{
			virtual Value call (void* object, const ValueList& args) = 0;
		};
		
		
		Data* mData;
		std::string mName;
		int mArgCount;
		
		
		
		
		
		template <typename C, typename R>
		struct MemberFunction0
		{
			typedef R(C::*FunctionType)();
			static Value call (C* obj, FunctionType func) { return (obj->*func)(); }
		};
		
		template <typename C, typename R, typename A1>
		struct MemberFunction1
		{
			typedef R(C::*FunctionType)(A1);
			static Value call (C* obj, FunctionType func,A1 a1) { 
				
				std::cout << "calling" << std::endl;return (obj->*func)(a1); }
		};
		
		template <typename C, typename R, typename A1, typename A2>
		struct MemberFunction2
		{
			typedef R(C::*FunctionType)(A1,A2);
			static Value call (C* obj, FunctionType func,A1 a1,A2 a2) { return (obj->*func)(a1,a2); }
		};
		
		template <typename C, typename R, typename A1, typename A2, typename A3>
		struct MemberFunction3
		{
			typedef R(C::*FunctionType)(A1,A2,A3);
			static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3) { return (obj->*func)(a1,a2,a3); }
		};
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
		struct MemberFunction4
		{
			typedef R(C::*FunctionType)(A1,A2,A3,A4);
			static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3,A4 a4) { return (obj->*func)(a1,a2,a3,a4); }
		};
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
		struct MemberFunction5
		{
			typedef R(C::*FunctionType)(A1,A2,A3,A4,A5);
			static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3,A4 a4, A5 a5) { return (obj->*func)(a1,a2,a3,a4,a5); }
		};
		
		
		
		
		
		template <typename C, typename R>
		struct MemberData0 : Data
		{
			typedef R(C::*FunctionType)();
			FunctionType function;
			
			MemberData0 (FunctionType func) : function(func) {}
			
			R call (C* object) { return (object->*function)(); }
			
			Value call (void* object, const ValueList& args)
			{
				return MemberFunction0<C,R>::call (
						static_cast<C*>(object), function);
			}
		};
		
		
		
		template <typename C, typename R, typename A1>
		struct MemberData1 : Data
		{
			typedef R(C::*FunctionType)(A1);
			FunctionType function;
			
			MemberData1 (FunctionType func) : function(func) {}
			
			R call (C* object, A1 arg1) { return (object->*function)(arg1); }
			
			Value call (void* object, const ValueList& args)
			{
				A1 tmp = args[0].get<A1>();
				std::cout << tmp << std::endl;
				std::cout << "done" << std::endl;
				
				
				return MemberFunction1<C,R,A1>::call (
						static_cast<C*>(object), function, args[0].get<A1>());
			}
		};
		
		
		
		template <typename C, typename R, typename A1, typename A2>
		struct MemberData2 : Data
		{
			typedef R(C::*FunctionType)(A1,A2);
			FunctionType function;
			
			MemberData2 (FunctionType func) : function(func) {}
			
			R call (C* object, A1 arg1, A2 arg2) { return (object->*function)(arg1, arg2); }
			
			Value call (void* object, const ValueList& args)
			{
				return MemberFunction2<C,R,A1,A2>::call (
						static_cast<C*>(object), function, args[0].get<A1>(),
						                                   args[1].get<A2>());
			}
		};
		
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3>
		struct MemberData3 : Data
		{
			typedef R(C::*FunctionType)(A1,A2,A3);
			FunctionType function;
			
			MemberData3 (FunctionType func) : function(func) {}
			
			R call (C* object, A1 arg1, A2 arg2, A3 arg3) { return (object->*function)(arg1, arg2, arg3); }
			
			Value call (void* object, const ValueList& args)
			{
				return MemberFunction3<C,R,A1,A2,A3>::call (
						static_cast<C*>(object), function, args[0].get<A1>(),
						                                   args[1].get<A2>(),
						                                   args[2].get<A3>());
			}
		};
		
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
		struct MemberData4 : Data
		{
			typedef R(C::*FunctionType)(A1,A2,A3,A4);
			FunctionType function;
			
			MemberData4 (FunctionType func) : function(func) {}
			
			R call (C* object, A1 arg1, A2 arg2, A3 arg3, A4 arg4) { return (object->*function)(arg1, arg2, arg3, arg4); }
			
			Value call (void* object, const ValueList& args)
			{
				return MemberFunction4<C,R,A1,A2,A3,A4>::call (
						static_cast<C*>(object), function, args[0].get<A1>(),
						                                   args[1].get<A2>(),
						                                   args[2].get<A3>(),
						                                   args[3].get<A4>());
			}
		};
		
		
		
		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
		struct MemberData5 : Data
		{
			typedef R(C::*FunctionType)(A1,A2,A3,A4,A5);
			FunctionType function;
			
			MemberData5 (FunctionType func) : function(func) {}
			
			R call (C* object, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5) { return (object->*function)(arg1, arg2, arg3, arg4, arg5); }
			
			Value call (void* object, const ValueList& args)
			{
				return MemberFunction5<C,R,A1,A2,A3,A4,A5>::call (
						static_cast<C*>(object), function, args[0].get<A1>(),
						                                   args[1].get<A2>(),
						                                   args[2].get<A3>(),
						                                   args[3].get<A4>(),
						                                   args[4].get<A5>());
			}
		};
		
	};
	
	
	
	
	
	/****************************************
	 * specialisation of void return values *
	 ****************************************/
	
	template <typename C>
	struct MetaFunction::MemberFunction0<C,void>
	{
		typedef void(C::*FunctionType)();
		static Value call (C* obj, FunctionType func) { (obj->*func)(); return Value(); }
	};
	
	
	template <typename C, typename A1>
	struct MetaFunction::MemberFunction1<C,void,A1>
	{
		typedef void(C::*FunctionType)(A1);
		static Value call (C* obj, FunctionType func,A1 a1) { (obj->*func)(a1); return Value(); }
	};
	
	
	template <typename C, typename A1, typename A2>
	struct MetaFunction::MemberFunction2<C,void,A1,A2>
	{
		typedef void(C::*FunctionType)(A1,A2);
		static Value call (C* obj, FunctionType func,A1 a1,A2 a2) { (obj->*func)(a1,a2); return Value(); }
	};
	
	
	template <typename C, typename A1, typename A2, typename A3>
	struct MetaFunction::MemberFunction3<C,void,A1,A2,A3>
	{
		typedef void(C::*FunctionType)(A1,A2,A3);
		static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3) { (obj->*func)(a1,a2,a3); return Value(); }
	};
	
	
	template <typename C, typename A1, typename A2, typename A3, typename A4>
	struct MetaFunction::MemberFunction4<C,void,A1,A2,A3,A4>
	{
		typedef void(C::*FunctionType)(A1,A2,A3,A4);
		static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3,A4 a4) { (obj->*func)(a1,a2,a3,a4); return Value(); }
	};
	
	
	template <typename C, typename A1, typename A2, typename A3, typename A4, typename A5>
	struct MetaFunction::MemberFunction5<C,void,A1,A2,A3,A4,A5>
	{
		typedef void(C::*FunctionType)(A1,A2,A3,A4,A5);
		static Value call (C* obj, FunctionType func,A1 a1,A2 a2,A3 a3,A4 a4, A5 a5) { (obj->*func)(a1,a2,a3,a4,a5); return Value(); }
	};


}


#endif /* MYELIN_META_FUNCTION_H_ */

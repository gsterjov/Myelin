
#ifndef MYELIN_META_OBJECT_H_
#define MYELIN_META_OBJECT_H_


#include <map>
#include <Myelin/Value.h>
#include <Myelin/MetaClass.h>
#include <Myelin/MetaFunction.h>


namespace Myelin
{

	/**
	 * MetaObject.
	 */
	class MetaObject
	{
	public:
		MetaObject (const std::string& name, void* object) : mClass(0), mObject(object)
		{
			mClass = Classes[name];
		}
		
		
		
//		Value call (const std::string& name, const ValueList& args)
//		{
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		
//		
//		Value call (const std::string& name)
//		{
//			std::vector<Value> args;
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		Value call (const std::string& name, const Value& arg1)
//		{
//			std::vector<Value> args;
//			args.push_back (arg1);
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		Value call (const std::string& name, const Value& arg1, const Value& arg2)
//		{
//			std::vector<Value> args;
//			args.push_back (arg1);
//			args.push_back (arg2);
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		Value call (const std::string& name, const Value& arg1, const Value& arg2, const Value& arg3)
//		{
//			std::vector<Value> args;
//			args.push_back (arg1);
//			args.push_back (arg2);
//			args.push_back (arg3);
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		Value call (const std::string& name, const Value& arg1, const Value& arg2, const Value& arg3, const Value& arg4)
//		{
//			std::vector<Value> args;
//			args.push_back (arg1);
//			args.push_back (arg2);
//			args.push_back (arg3);
//			args.push_back (arg4);
//			return mClass->getFunction(name)->call (mObject, args);
//		}
//		
//		
//		Value call (const std::string& name, const Value& arg1, const Value& arg2, const Value& arg3, const Value& arg4, const Value& arg5)
//		{
//			std::vector<Value> args;
//			args.push_back (arg1);
//			args.push_back (arg2);
//			args.push_back (arg3);
//			args.push_back (arg4);
//			args.push_back (arg5);
//			return mClass->getFunction(name)->call (mObject, args);
//		}
		
		
		
		
		Value call (const std::string& name)
		{
			const MetaFunction* metafunc = mClass->getFunction (name);
			
			metafunc->getFunction();
		}
		
		
		
		template <typename C, typename R>
		R call (const std::string& name)
		{
			const MetaFunction* metafunc = mClass->getFunction (name);
			
			typedef R(C::*FuncType)();
			
			FuncType func = value_cast<FuncType> (metafunc->getFunction());
			(static_cast<C*>(mObject)->*func)();
			
//			return mClass->getFunction(name)->call<C,R>(
//					static_cast<C*>(mObject));
		}
		
		
//		template <typename C, typename R, typename A1>
//		R call (const std::string& name, A1 arg1)
//		{
//			return mClass->getFunction(name)->call<C,R,A1>(
//					static_cast<C*>(mObject), arg1);
//		}
//		
//		
//		template <typename C, typename R, typename A1, typename A2>
//		R call (const std::string& name, A1 arg1, A2 arg2)
//		{
//			return mClass->getFunction(name)->call<C,R,A1,A2>(
//					static_cast<C*>(mObject), arg1, arg2);
//		}
//		
//		
//		template <typename C, typename R, typename A1, typename A2, typename A3>
//		R call (const std::string& name, A1 arg1, A2 arg2, A3 arg3)
//		{
//			return mClass->getFunction(name)->call<C,R,A1,A2,A3>(
//					static_cast<C*>(mObject), arg1, arg2, arg3);
//		}
//		
//		
//		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4>
//		R call (const std::string& name, A1 arg1, A2 arg2, A3 arg3, A4 arg4)
//		{
//			return mClass->getFunction(name)->call<C,R,A1,A2,A3,A4>(
//					static_cast<C*>(mObject), arg1, arg2, arg3, arg4);
//		}
//		
//		
//		template <typename C, typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
//		R call (const std::string& name, A1 arg1, A2 arg2, A3 arg3, A4 arg4, A5 arg5)
//		{
//			return mClass->getFunction(name)->call<C,R,A1,A2,A3,A4,A5>(
//					static_cast<C*>(mObject), arg1, arg2, arg3, arg4, arg5);
//		}
		
		
		
		void* getObject () { return mObject; }
		
		
	private:
		MetaClass* mClass;
		void* mObject;
	};

}


#endif /* MYELIN_META_OBJECT_H_ */

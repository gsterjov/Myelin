
#ifndef MYELIN_META_OBJECT_H_
#define MYELIN_META_OBJECT_H_


#include <map>
#include <Myelin/MetaClass.h>
#include <vector>


namespace Myelin
{

	typedef std::vector<Value> ValueList;
	
	
	/**
	 * MetaObject.
	 */
	class MetaObject
	{
	public:
		MetaObject (const std::string& name) : mClass(0), mObject(0)
		{
			mClass = Classes[name];
			mObject = mClass->create();
		}
		
		
		
		template <typename Class, typename Return>
		Return call (const std::string& name)
		{
			MetaFunction* func = mClass->getFunction (name);
//			return func->call<Class, Return> (static_cast<Class*>(mObject));
		}
		
		
		
		template <typename Class, typename Return, typename Arg1>
		Return call (const std::string& name, Arg1 arg1)
		{
			MetaFunction* func = mClass->getFunction (name);
//			return func->call<Class, Return, Arg1> (static_cast<Class*>(mObject), arg1);
		}
		
		
		
		Value call (const std::string& name, const Value& arg1)
		{
			MetaFunction* func = mClass->getFunction (name);
			return func->call (mObject, arg1);
		}
		
		
		Value call (const std::string& name, const Value& arg1, const Value& arg2)
		{
			MetaFunction* func = mClass->getFunction (name);
			return func->call (mObject, arg1, arg2);
		}
		
		
		
		Value call (const std::string& name, const ValueList& args)
		{
			MetaFunction* func = mClass->getFunction (name);
			return func->call (mObject, args);
		}
		
		
		
		void* getObject () { return mObject; }
		
		
	private:
		BaseMetaClass* mClass;
		void* mObject;
	};

}


#endif /* MYELIN_META_OBJECT_H_ */

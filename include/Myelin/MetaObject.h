
#ifndef MYELIN_META_OBJECT_H_
#define MYELIN_META_OBJECT_H_


#include <map>
#include <Myelin/MetaClass.h>


namespace Myelin
{

	/**
	 * MetaObject.
	 */
	template <typename Class>
	class MetaObject
	{
	public:
		MetaObject (MetaClass<Class>* metaclass) : mClass(metaclass), mObject(new Class()) {}
		
		
		
		void call (const std::string& name)
		{
			MetaFunction* func = mClass->getFunction (name);
			func->call<Class, void> (mObject);
		}
		
		
		Class* getObject () { return mObject; }
		
		
	private:
		MetaClass<Class>* mClass;
		Class* mObject;
	};

}


#endif /* MYELIN_META_OBJECT_H_ */


#ifndef MYELIN_GENERIC_OBJECT_H_
#define MYELIN_GENERIC_OBJECT_H_


#include <stdexcept>

#include <Myelin/Class.h>
#include <Myelin/Object.h>
#include <Myelin/Function.h>


namespace Myelin
{

	template <typename ClassType>
	class GenericObject : public Object
	{
	public:
		/**
		 * Constructor.
		 */
		GenericObject () : mClass(0), mObject(0) {}
		
		/**
		 * Class constructor.
		 */
		explicit GenericObject (Class* klass) : mClass(klass) {}
		
		/**
		 * Class and object constructor.
		 */
		explicit GenericObject (Class* klass, ClassType* object)
		: mClass (klass),
		  mObject (object)
		{}
		
		
		
		/**
		 * Set meta class.
		 */
		void setClass (Class* klass) { mClass = klass; }
		
		
		/**
		 * Get meta class.
		 */
		Class* getClass () { return mClass; }
		
		
		
		/**
		 * Set object.
		 */
		void setObject (ClassType* object) { mObject = object; }
		
		
		/**
		 * Get object.
		 */
		Class* getObject () { return mObject; }
		
		
		
		/**
		 * Call the function on the object.
		 */
//		template <typename Return>
//		Return call (const std::string& name)
//		{
//			
//		}
		
		
		
	protected:
		/**
		 * Call the function on the object
		 */
		Value callImpl (const std::string& function, const ValueList& params)
		{
			const Function* func = mClass->getFunction (function);
			
			/* no function found */
			if (!func)
				throw std::runtime_error (
						"Cannot find the function '" + function + "' in the class '"
						+ mClass->getName() + "'.");
			
			/* execute the function */
			return func->call (mObject, params);
		}
		
		
		
	private:
		Class* mClass;
		ClassType* mObject;
	};

}


#endif /* MYELIN_GENERIC_OBJECT_H_ */


#ifndef MYELIN_GENERIC_OBJECT_H_
#define MYELIN_GENERIC_OBJECT_H_


#include <stdexcept>

#include <Myelin/Value.h>
#include <Myelin/List.h>
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
		GenericObject () : mClass(0), mInstance(0) {}
		
		/**
		 * Class constructor.
		 */
		explicit GenericObject (const Class* klass) : mClass(klass), mInstance(0) {}
		
		/**
		 * Class and object constructor.
		 */
		explicit GenericObject (const Class* klass, ClassType* object)
		: mClass (klass),
		  mInstance (object)
		{}
		
		
		
		/**
		 * Set meta class.
		 */
		void setClass (Class* klass) { mClass = klass; }
		
		
		/**
		 * Get meta class.
		 */
		Class* getClass () const { return mClass; }
		
		
		
		/**
		 * Set object instance.
		 */
		void setInstance (ClassType* instance) { mInstance = instance; }
		
		
		/**
		 * Set object instance from generic pointer.
		 */
		void setInstance (void* instance) { mInstance = static_cast<ClassType*> (instance); }
		
		
		
		/**
		 * Get object instance as generic pointer.
		 */
		void* getInstance () const { return mInstance; }
		
		
		
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
		Value callImpl (const std::string& function, const List& params) const
		{
			const Function* func = mClass->getFunction (function);
			
			/* no function found */
			if (!func)
				throw std::runtime_error (
						"Cannot find the function '" + function + "' in the class '"
						+ mClass->getName() + "'.");
			
			/* execute the function */
			return func->call (mInstance, params);
		}
		
		
		
	private:
		const Class* mClass;
		ClassType* mInstance;
	};

}


#endif /* MYELIN_GENERIC_OBJECT_H_ */

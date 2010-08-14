
#ifndef MYELIN_META_FUNCTION_H_
#define MYELIN_META_FUNCTION_H_


#include <Myelin/Value.h>


namespace Myelin
{

	/**
	 * MetaFunction.
	 */
	class MetaFunction
	{
	public:
		
		
		template <typename Class, typename R>
		void set (R(Class::*function)())
		{
			Value* value = new Value ();
			
			value->set (function);
			mValue = value;
		}
		
		
		template <typename Class, typename R>
		R call (Class* object)
		{
			R(Class::*func)() = mValue->get<R(Class::*)()>();
			
			return (object->*func)();
		}
		
		
		
	private:
		Value* mValue;
	};

}


#endif /* MYELIN_META_FUNCTION_H_ */

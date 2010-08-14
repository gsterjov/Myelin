
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
		
		
		template <typename Class, typename R, typename Arg1>
		void set (R(Class::*function)(Arg1))
		{
			Value* value = new Value ();
			
			value->set (function);
			mValue = value;
		}
		
		
		
		
		template <typename Class, typename Return>
		Return call (Class* object)
		{
			typedef Return (Class::*FunctionType) ();
			
			FunctionType func = mValue->get<FunctionType>();
			return (object->*func)();
		}
		
		
		template <typename Class, typename Return, typename Arg1>
		Return call (Class* object, Arg1 arg1)
		{
			typedef Return (Class::*FunctionType) (Arg1);
			
			FunctionType func = mValue->get<FunctionType>();
			return (object->*func)(arg1);
		}
		
		
		
	private:
		Value* mValue;
	};

}


#endif /* MYELIN_META_FUNCTION_H_ */

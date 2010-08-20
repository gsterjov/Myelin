
#ifndef MYELIN_FUNCTION_H_
#define MYELIN_FUNCTION_H_


#include <Myelin/Type.h>
#include <Myelin/Value.h>


namespace Myelin
{

	/* forward declarations */
	class Object;
	
	
	
	class Function
	{
	public:
		/**
		 * Function name.
		 */
		virtual const std::string getName() const = 0;
		
		/**
		 * Return type.
		 */
		virtual Type getReturnType() const = 0;
		
		/**
		 * Parameter count.
		 */
		virtual int getParamCount() const = 0;
		
		/**
		 * Parameter type.
		 */
		virtual Type getParamType(int index) const = 0;
		
		
		/**
		 * Call the function.
		 */
		virtual Value call (const void* object,
		                    const ValueList& params) const = 0;
	};

}


#endif /* MYELIN_FUNCTION_H_ */

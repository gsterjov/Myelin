
#ifndef MYELIN_OBJECT_H_
#define MYELIN_OBJECT_H_


#include <Myelin/Value.h>
#include <Myelin/MetaClass.h>


namespace Myelin
{

	class Object
	{
	public:
		/**
		 * Call the function on the object.
		 */
		virtual Value call (const std::string& function,
		                    const ValueList& params) = 0;
		
		
		Value call (const std::string& function);
		Value call (const std::string& function, const Value& param1);
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2);
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3);
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3,
											     const Value& param4);
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3,
											     const Value& param4,
											     const Value& param5);
	};

}


#endif /* MYELIN_OBJECT_H_ */

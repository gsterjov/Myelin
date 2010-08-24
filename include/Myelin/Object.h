
#ifndef MYELIN_OBJECT_H_
#define MYELIN_OBJECT_H_


#include <string>
#include <Myelin/Value.h>
#include <Myelin/List.h>


namespace Myelin
{

	class Object
	{
	public:
		/**
		 * Call the function on the object.
		 */
		Value call (const std::string& function, const List& params);
		
		
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
		
		
	protected:
		/**
		 * Call the function on the object.
		 */
		virtual Value callImpl (const std::string& function,
		                        const List& params) = 0;
	};

}




/* C api */
extern "C"
{

	Myelin::Value *myelin_object_call (Myelin::Object *object,
	                                   const char *function,
	                                   const Myelin::List *params);

}



#endif /* MYELIN_OBJECT_H_ */

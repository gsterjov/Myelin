

#include "Object.h"
#include "List.h"


namespace Myelin
{

	Value Object::call (const std::string& function,
	                    const List& params)
	{
		return callImpl (function, params);
	}
	
	
	Value Object::call (const std::string& function)
	{
		List params;
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1)
	{
		List params;
		params.push_back (param1);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2)
	{
		List params;
		params.push_back (param1);
		params.push_back (param2);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3)
	{
		List params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3,
	                                                 const Value& param4)
	{
		List params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		params.push_back (param4);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3,
	                                                 const Value& param4,
	                                                 const Value& param5)
	{
		List params;
		params.push_back (param1);
		params.push_back (param2);
		params.push_back (param3);
		params.push_back (param4);
		params.push_back (param5);
		return call (function, params);
	}

}





/* C api */
Myelin::Value *
myelin_object_call (Myelin::Object *object,
                    const char *function,
                    const Myelin::List *params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = object->call (function, *params);
	return value;
}




#include "Object.h"
#include "Value.h"
#include "List.h"
#include "Class.h"


namespace Myelin
{

	Value Object::call (const std::string& function,
	                    const List& params) const
	{
		return callImpl (function, params);
	}
	
	
	Value Object::call (const std::string& function) const
	{
		List params;
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1) const
	{
		List params;
		params.push_back (param1);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2) const
	{
		List params;
		params.push_back (param1);
		params.push_back (param2);
		return call (function, params);
	}
	
	
	Value Object::call (const std::string& function, const Value& param1,
	                                                 const Value& param2,
	                                                 const Value& param3) const
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
	                                                 const Value& param4) const
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
	                                                 const Value& param5) const
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
MYELIN_API Myelin::Object *
myelin_object_new (const Myelin::Class *klass, const Myelin::List *params)
{
	return klass->createObject (*params);
}


MYELIN_API Myelin::Object *myelin_object_new_instance (const Myelin::Class *klass,
                                                       void* instance)
{
	return klass->createObject (instance);
}



MYELIN_API void
myelin_object_free (Myelin::Object *object)
{
	delete object;
}



MYELIN_API Myelin::Value *
myelin_object_call (const Myelin::Object *object,
                    const char *function,
                    const Myelin::List *params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = object->call (function, *params);
	return value;
}



MYELIN_API void
myelin_object_set_instance (Myelin::Object *object, void *instance)
{
	object->setInstance (instance);
}



MYELIN_API void *
myelin_object_get_instance (const Myelin::Object *object)
{
	return object->getInstance();
}


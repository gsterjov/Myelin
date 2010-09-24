

#include "Object.h"

#include <stdexcept>

#include "Value.h"
#include "List.h"
#include "Class.h"
#include "Function.h"


namespace Myelin
{

	/* constructor */
	Object::Object () : mClass(0) {}
	
	
	/* class constructor */
	Object::Object (const Class* klass) : mClass(klass)
	{
		
	}
	
	
	/* class and instance constructor */
	Object::Object (const Class* klass, const Pointer& instance)
	: mClass (klass),
	  mInstance (instance)
	{
		
	}
	
	
	
	/* destructor */
	Object::~Object ()
	{
		
	}
	
	
	
	/* call function */
	Value Object::call (const std::string& function,
	                    const List& params) const
	{
		FunctionList list = mClass->getFunctions (function);
		
		/* no function found */
		if (list.empty())
			throw std::runtime_error (
					"Cannot find the function '" + function + "' in the class '"
					+ mClass->getName() + "'.");
		
		
		FunctionList::iterator iter;
		
		/* find a function which can handle the parameters */
		for (iter = list.begin(); iter != list.end(); ++iter)
		{
			Function* func = *iter;
			
			/* found match, execute the function */
			if (func->getType()->checkParamTypes (params))
				return func->call (params);
		}
		
		
		/* no capable function found */
		throw std::runtime_error (
				"Cannot find a function capable of handling the provided "
				"parameters");
	}
	
	
	
	
	/* convenience functions */
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






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Object *myelin_object_new () { return new Myelin::Object(); }

Myelin::Object *
myelin_object_new_with_class (const Myelin::Class *klass)
{
	return new Myelin::Object (klass);
}


Myelin::Object *
myelin_object_new_with_instance (const Myelin::Class *klass,
                                 const Myelin::Pointer *instance)
{
	return new Myelin::Object (klass, *instance);
}




void
myelin_object_free (Myelin::Object *object)
{
	delete object;
}



void
myelin_object_set_class (Myelin::Object *object, Myelin::Class *klass)
{
	object->setClass (klass);
}



const Myelin::Class *
myelin_object_get_class (const Myelin::Object *object)
{
	return object->getClass ();
}



void
myelin_object_set_instance (Myelin::Object *object, const Myelin::Pointer *instance)
{
	object->setInstance (*instance);
}



const Myelin::Pointer *
myelin_object_get_instance (const Myelin::Object *object)
{
	return &object->getInstance ();
}



Myelin::Value *
myelin_object_call (const Myelin::Object *object,
                    const char *function,
                    const Myelin::List *params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = object->call (function, *params);
	return value;
}


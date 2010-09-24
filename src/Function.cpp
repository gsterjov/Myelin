

#include "Function.h"

#include <sstream>
#include <stdexcept>

#include "Types/FunctionType.h"

#include "List.h"
#include "Class.h"
#include "Converter.h"


namespace Myelin
{

	/* constructor */
	Function::Function (const std::string& name, FunctionType* type)
	: mName (name),
	  mType (type)
	{
		
	}
	
	
	/* destructor */
	Function::~Function ()
	{
		
	}
	
	
	/* get function type */
	Value Function::call (const List& params) const
	{
		/* wrong number of parameters */
		if (params.size() != mType->getParamCount())
		{
			std::stringstream stream;
			stream << "The function '" + mName + "' takes exactly "
					<< mType->getParamCount() << " parameter(s) instead of "
					<< params.size() << ".";
			
			throw std::invalid_argument (stream.str());
		}
		
		
		/* parameter types dont match */
		if (!mType->checkParamTypes (params))
			throw std::invalid_argument ("The provided parameters do not"
					"match the types required by the function '" + mName + "'");
		
		
		/* call function */
		return mType->call (params);
	}
	
	
	
	/* bind instance */
	void Function::bind (const Pointer& instance)
	{
		mType->setInstance (instance);
	}
	
	
	
	
	
	/* check parameter types */
	bool FunctionType::checkParamTypes (const List& params) const
	{
		/* wrong number of parameters */
		if (params.size() != getParamCount())
			return false;
		
		
		/* check types */
		for (int i = 0; i < params.size(); ++i)
		{
			/* types to compare */
			const Type* param_type = params[i].getType();
			const Type* target_type = mParamTypes[i];
			
			/* types dont match */
			if (!param_type->equals (target_type))
			{
				const Class* klass = target_type->getAtom()->getClass();
				
				/* check if type can be converted */
				if (klass != 0)
				{
					bool match = false;
					
					ConverterList list = klass->getConverters();
					ConverterList::iterator iter;
					
					/* look for compatible type */
					for (iter = list.begin(); iter != list.end(); ++iter)
					{
						Converter* converter = *iter;
						
						/* type can be converted */
						if (converter->getInputType()->equals (param_type))
						{
							match = true;
							break;
						}
					}
					
					/* no conversion types found */
					if (!match) return false;
				}
				
				/* no conversion possible */
				else return false;
			}
		}
		
		
		return true;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
const char *
myelin_function_get_name (Myelin::Function *function)
{
	return function->getName().c_str();
}


const Myelin::FunctionType *
myelin_function_get_type (Myelin::Function *function)
{
	return function->getType ();
}


void
myelin_function_bind (Myelin::Function *function,
                      const Myelin::Pointer* instance)
{
	function->bind (*instance);
}


Myelin::Value *
myelin_function_call (Myelin::Function *function,
                      const Myelin::List* params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = function->call (*params);
	return value;
}





const Myelin::Type *
myelin_function_type_get_return_type (Myelin::FunctionType *type)
{
	return type->getReturnType();
}



int
myelin_function_type_get_param_count (Myelin::FunctionType *type)
{
	return type->getParamCount();
}



const Myelin::Type *
myelin_function_type_get_param_type (Myelin::FunctionType *type, int index)
{
	return type->getParamType (index);
}



Myelin::List *
myelin_function_type_get_param_types (Myelin::FunctionType *type)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::TypeList types = type->getParamTypes();
	Myelin::TypeList::iterator iter;
	
	/* add all functions into the list */
	for (iter = types.begin(); iter != types.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}



bool
myelin_function_type_check_param_types (Myelin::FunctionType *type,
                                        const Myelin::List* params)
{
	return type->checkParamTypes (*params);
}



void
myelin_function_type_set_instance (Myelin::FunctionType *type,
                                   const Myelin::Pointer* instance)
{
	type->setInstance (*instance);
}



Myelin::Value *
myelin_function_type_call (Myelin::FunctionType *type,
                           const Myelin::List* params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = type->call (*params);
	return value;
}


/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "Function.h"

#include <sstream>
#include <stdexcept>
#include <cassert>

#include "Types/FunctionType.h"

#include "List.h"
#include "Class.h"
#include "Converter.h"


namespace Myelin
{

	/* constructor */
	Function::Function (const std::string& name,
	                    FunctionType* type,
	                    int properties)
	: mName (name),
	  mType (type),
	  mProperties (properties)
	{
		
	}
	
	
	/* destructor */
	Function::~Function ()
	{
		
	}
	
	
	/* get function type */
	Value Function::call (const List& params) const
	{
		assert (mType);
		
		/* wrong number of parameters */
		if (params.size() != mType->getParamCount())
		{
			std::stringstream stream;
			stream << "The function '" + mName + "' takes exactly "
					<< mType->getParamCount() << " parameter(s) instead of "
					<< params.size() << ".";
			
			throw std::invalid_argument (stream.str());
		}
		
		
		/* call function */
		return mType->call (params);
	}
	
	
	
	/* bind instance */
	void Function::bind (const Value& instance)
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
	
	
	
	
	
	/* call custom function type */
	Value CustomFunctionType::call (const List& params) const
	{
		Value* val = mCallback (&params);
		Value ret (*val);
		
		val->unref();
		if (val->count() == 0) delete val;
		
		return ret;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Function *
myelin_function_new (const char *name, Myelin::FunctionType *type)
{
	return new Myelin::Function (name, type);
}


Myelin::Function *
myelin_function_ref (Myelin::Function *function)
{
	function->ref();
	return function;
}


void
myelin_function_unref (Myelin::Function *function)
{
	function->unref();
	if (function->count() == 0) delete function;
}



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



bool
myelin_function_is_constant (Myelin::Function *function)
{
	return function->isConstant();
}


bool
myelin_function_is_virtual (Myelin::Function *function)
{
	return function->isVirtual();
}


bool
myelin_function_is_pure (Myelin::Function *function)
{
	return function->isPure();
}



void
myelin_function_bind (Myelin::Function *function,
                      const Myelin::Value* instance)
{
	function->bind (*instance);
}


Myelin::Value *
myelin_function_call (Myelin::Function *function,
                      const Myelin::List* params)
{
	Myelin::Value* ret = new Myelin::Value (function->call (*params));
	
	/* throw away ownership */
	ret->unref();
	return ret;
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
	
	/* throw away ownership */
	list->unref();
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
                                   const Myelin::Value* instance)
{
	type->setInstance (*instance);
}



Myelin::Value *
myelin_function_type_call (Myelin::FunctionType *type,
                           const Myelin::List* params)
{
	Myelin::Value* ret = new Myelin::Value (type->call (*params));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}







Myelin::CustomFunctionType *
myelin_custom_function_type_new (Callback callback)
{
	return new Myelin::CustomFunctionType (callback);
}


Myelin::CustomFunctionType *
myelin_custom_function_type_ref (Myelin::CustomFunctionType *func)
{
	func->ref();
	return func;
}


void
myelin_custom_function_type_unref (Myelin::CustomFunctionType *func)
{
	func->unref();
	if (func->count() == 0) delete func;
}



void
myelin_custom_function_type_add_param_type (Myelin::CustomFunctionType *func,
                                            const Myelin::Type *type)
{
	func->addParamType (type);
}



void
myelin_custom_function_type_set_return_type (Myelin::CustomFunctionType *func,
                                             const Myelin::Type *type)
{
	func->setReturnType (type);
}



Myelin::Value *
myelin_custom_function_type_call (Myelin::CustomFunctionType *func,
                                  const Myelin::List *params)
{
	Myelin::Value* ret = new Myelin::Value (func->call (*params));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}



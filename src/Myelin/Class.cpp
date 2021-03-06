/*
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

#include "Class.h"

#include <stdexcept>

#include "Type.h"
#include "Value.h"
#include "List.h"
#include "Object.h"
#include "Constructor.h"
#include "Function.h"



namespace Myelin
{

	/* constructor */
	Class::Class (const std::string& name)
	: mName (name),
	  mType (TYPE(void)),
	  mTable (0)
	{}
	
	
	/* destructor */
	Class::~Class ()
	{
		
	}
	
	
	
	/* add base class */
	void Class::addBase (const Type* baseType)
	{
		mBases.push_back (baseType);
	}
	
	
	
	/* get base class list */
	const BaseList& Class::getBases () const
	{
		return mBases;
	}
	
	
	
	/* add constructor */
	void Class::addConstructor (Constructor* constructor)
	{
		mConstructors.push_back (constructor);
		constructor->ref();
	}
	
	
	
	/* get constructor list */
	const ConstructorList& Class::getConstructors () const
	{
		return mConstructors;
	}
	
	
	
	/* add converter */
	void Class::addConverter (Converter* converter)
	{
		mConverters.push_back (converter);
		converter->ref();
	}
	
	
	
	/* get converter list */
	const ConverterList& Class::getConverters () const
	{
		return mConverters;
	}
	
	
	
	/* add function */
	void Class::addFunction (Function* function)
	{
		std::string name = function->getName();
		
		/* add the function to the list, creating a new
		 * one if it doesn't exist */
		mFunctions[name].push_back (function);
		function->ref();
	}
	
	
	/* get function list */
	FunctionList Class::getFunctions () const
	{
		FunctionList list;
		FunctionMap::const_iterator iter;
		
		/* merge function lists from the map into a flat list */
		for (iter = mFunctions.begin(); iter != mFunctions.end(); ++iter)
			list.insert (list.end(), iter->second.begin(), iter->second.end());
		
		return list;
	}
	
	
	/* get functions by name */
	FunctionList Class::getFunctions (const std::string& name) const
	{
		FunctionMap::const_iterator iter;
		
		iter = mFunctions.find (name);
		return iter != mFunctions.end() ? iter->second : FunctionList();
	}
	
	
	
	/* create object instance */
	Value Class::createInstance (const List& params) const
	{
		ConstructorList::const_iterator iter;
		
		/* find the correct constructor */
		for (iter = mConstructors.begin(); iter != mConstructors.end(); ++iter)
		{
			const Constructor* ctor = *iter;
			
			/* basic size check */
			if (ctor->getParamCount() != params.size())
				continue;
			
			
			/* get parameter types */
			TypeList types = ctor->getParamTypes();
			
			int i;
			bool matched = true;
			
			/* see if parameters match */
			for (i = 0; i < params.size(); ++i)
			{
				matched = false;
				
				/* types to compare */
				const Type* param_type = params[i].getType();
				const Type* target_type = types[i];
				
				/* parameter type matches */
				if (param_type->compatible (target_type))
					matched = true;
				
				/* parameter type can be converted to target type */
				else if (param_type->findConverter (target_type))
					matched = true;
				
				/* parameters dont match for this constructor */
				if (!matched) break;
			}
			
			
			/* create instance */
			if (matched)
				return ctor->call (params);
		}
		
		
		/* return empty value */
		return Value();
	}
	
	
	/* create meta object */
	Object* Class::createObject (const List& params) const
	{
		Value instance = createInstance (params);
		
		if (!instance.isEmpty())
		{
			Object* ret = new Object (this, instance);
			
			ret->unref();
			return ret;
		}
		
		return 0;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/


Myelin::Class *
myelin_class_new (const char *name)
{
	return new Myelin::Class (name);
}


Myelin::Class *
myelin_class_ref (Myelin::Class *klass)
{
	klass->ref();
	return klass;
}


void
myelin_class_unref (Myelin::Class *klass)
{
	klass->unref();
	if (klass->count() == 0) delete klass;
}



const char *
myelin_class_get_name (Myelin::Class *klass)
{
	return klass->getName().c_str();
}



const Myelin::Type *
myelin_class_get_type (Myelin::Class *klass)
{
	return klass->getType();
}




void
myelin_class_add_base (Myelin::Class *klass, const Myelin::Type *type)
{
	klass->addBase (type);
}


Myelin::List *
myelin_class_get_bases (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	const Myelin::BaseList& bases = klass->getBases();
	Myelin::BaseList::const_iterator iter;
	
	/* add all bases into the list */
	for (iter = bases.begin(); iter != bases.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}




void
myelin_class_add_constructor (Myelin::Class *klass,
                              Myelin::Constructor *constructor)
{
	klass->addConstructor (constructor);
}


Myelin::List *
myelin_class_get_constructors (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	const Myelin::ConstructorList& funcs = klass->getConstructors();
	Myelin::ConstructorList::const_iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}




void
myelin_class_add_function (Myelin::Class *klass,
                           Myelin::Function *function)
{
	klass->addFunction (function);
}


Myelin::List *
myelin_class_get_functions (Myelin::Class *klass, const char *name)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::FunctionList funcs = klass->getFunctions (name);
	Myelin::FunctionList::iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}


Myelin::List *
myelin_class_get_all_functions (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::FunctionList funcs = klass->getFunctions();
	Myelin::FunctionList::iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}



Myelin::VTable *
myelin_class_get_vtable (Myelin::Class *klass)
{
	return klass->getVTable();
}


void
myelin_class_set_vtable (Myelin::Class *klass, Myelin::VTable *vtable)
{
	klass->setVTable (vtable);
}



Myelin::Value *
myelin_class_create_instance (const Myelin::Class *klass,
                              const Myelin::List *params)
{
	Myelin::Value* ret = new Myelin::Value (klass->createInstance (*params));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}



Myelin::Object *
myelin_class_create_object (const Myelin::Class *klass,
                            const Myelin::List *params)
{
	return klass->createObject (*params);
}


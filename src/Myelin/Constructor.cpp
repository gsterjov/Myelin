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

#include "Constructor.h"

#include <sstream>
#include <stdexcept>

#include "Value.h"
#include "List.h"
#include "Types/ConstructorType.h"


namespace Myelin
{

	/* constructor */
	Constructor::Constructor (const ConstructorType* type) : mCtorType(type) {}
	
	
	/* destructor */
	Constructor::~Constructor ()
	{
		
	}
	
	
	
	/* get parameter count */
	int Constructor::getParamCount() const
	{
		return mCtorType->getParamTypes().size();
	}
	
	
	/* get parameter type */
	const Type* Constructor::getParamType (int index) const
	{
		return mCtorType->getParamTypes()[index];
	}
	
	
	/* get parameter list */
	const TypeList& Constructor::getParamTypes() const
	{
		return mCtorType->getParamTypes();
	}
	
	
	
	/* call the constructor */
	Value Constructor::call (const List& params) const
	{
		/* wrong number of parameters */
		if (params.size() < getParamCount())
		{
			std::stringstream stream;
			stream << "The constructor takes exactly "
					<< getParamCount() << " parameter(s) instead of "
					<< params.size() << ".";
			
			throw std::runtime_error (stream.str());
		}
		
		/* call constructor */
		return mCtorType->create (params);
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
int
myelin_constructor_get_param_count (Myelin::Constructor *constructor)
{
	return constructor->getParamCount();
}



const Myelin::Type *
myelin_constructor_get_param_type (Myelin::Constructor *constructor, int index)
{
	return constructor->getParamType (index);
}



Myelin::List *
myelin_constructor_get_param_types (Myelin::Constructor *constructor)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::TypeList types = constructor->getParamTypes();
	Myelin::TypeList::iterator iter;
	
	/* add all functions into the list */
	for (iter = types.begin(); iter != types.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}



Myelin::Value *
myelin_constructor_call (Myelin::Constructor *constructor,
                         const Myelin::List* params)
{
	Myelin::Value* ret = new Myelin::Value (constructor->call (*params));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}


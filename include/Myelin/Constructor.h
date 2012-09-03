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

#ifndef MYELIN_CONSTRUCTOR_H_
#define MYELIN_CONSTRUCTOR_H_


#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Type.h>


namespace Myelin
{

	/* forward declaration */
	class Value;
	class List;
	class ConstructorType;
	
	
	
	class MYELIN_API Constructor : public RefCounter
	{
	public:
		/**
		 * Constructor.
		 */
		Constructor (const ConstructorType* type);
		
		/**
		 * Destructor.
		 */
		~Constructor ();
		
		
		/**
		 * Parameter count.
		 */
		int getParamCount() const;
		
		/**
		 * Parameter type.
		 */
		const Type* getParamType (int index) const;
		
		/**
		 * Parameter list.
		 */
		const TypeList& getParamTypes() const;
		
		
		/**
		 * Call the constructor.
		 */
		Value call (const List& params) const;
		
		
	private:
		const ConstructorType* mCtorType;
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
extern "C"
{

	/**
	 * Get the amount of parameters specified by the constructor.
	 */
	MYELIN_API int myelin_constructor_get_param_count (Myelin::Constructor *constructor);
	
	/**
	 * Get the parameter type at the specified index.
	 */
	MYELIN_API const Myelin::Type *myelin_constructor_get_param_type (Myelin::Constructor *constructor,
	                                                                  int index);
	
	/**
	 * Get a list of all the parameter types.
	 */
	MYELIN_API Myelin::List *myelin_constructor_get_param_types (Myelin::Constructor *constructor);

	
	/**
	 * Call the constructor.
	 */
	MYELIN_API Myelin::Value *myelin_constructor_call (Myelin::Constructor *constructor,
	                                                   const Myelin::List *params);

}



#endif /* MYELIN_CONSTRUCTOR_H_ */

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

#ifndef MYELIN_VTABLE_H_
#define MYELIN_VTABLE_H_


#include <string>
#include <map>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{

	/* forward declaration */
	class Function;
	
	
	
	/**
	 * VTable to store functions overriding virtual functions.
	 */
	class MYELIN_API VTable : public RefCounter
	{
	public:
		/**
		 * Get a function from the virtual function table.
		 */
		Function* get (const std::string& name) const;
		
		/**
		 * Set a function in the virtual function table.
		 */
		void set (Function* function);
		
		
	private:
		/* virtual function storage */
		typedef std::map<std::string, Function*> FunctionTable;
		FunctionTable mTable;
	};
	
	
	
	
	/**
	 * Allows access to call overriden virtual functions.
	 */
	template <typename ClassType>
	class MYELIN_API Overridable
	{
	public:
		/**
		 * Get the virtual function table.
		 */
		static VTable* getVTable () { return mTable; }
		
		
	protected:
		/**
		 * Get a virtual function from the virtual function table.
		 */
		Function* get (const std::string& name) const
		{
			return mTable->get (name);
		}
		
		
	private:
		static VTable* mTable;
	};
	
	
	/* static table declaration */
	template <typename ClassType>
	VTable* Overridable<ClassType>::mTable = new VTable();

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/


extern "C"
{

	/**
	 * Get a function from the virtual function table with the matching name.
	 */
	MYELIN_API Myelin::Function *myelin_vtable_get (const Myelin::VTable *vtable,
	                                                const char *name);
	
	/**
	 * Set a function in the virtual function table.
	 */
	MYELIN_API void myelin_vtable_set (Myelin::VTable *vtable,
	                                   Myelin::Function *function);

}



#endif /* MYELIN_VTABLE_H_ */

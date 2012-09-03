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

#include "VTable.h"
#include "Function.h"


namespace Myelin
{

	/* get a virtual function */
	Function* VTable::get (const std::string& name) const
	{
		FunctionTable::const_iterator iter = mTable.find (name);
		return iter != mTable.end() ? iter->second : 0;
	}
	
	
	
	/* set a virtual function */
	void VTable::set (Function* function)
	{
		mTable[function->getName()] = function;
		function->ref();
	}

}



/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Function *
myelin_vtable_get (const Myelin::VTable *vtable, const char *name)
{
	return vtable->get (name);
}


void
myelin_vtable_set (Myelin::VTable *vtable, Myelin::Function *function)
{
	vtable->set (function);
}



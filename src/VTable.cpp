

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



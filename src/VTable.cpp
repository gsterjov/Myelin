

#include "VTable.h"
#include "Function.h"



namespace Myelin
{

	/* get a virtual function */
	const Function* VTable::get (const std::string& name) const
	{
		FunctionTable::const_iterator iter = mTable.find (name);
		return iter != mTable.end() ? iter->second : 0;
	}
	
	
	
	/* set a virtual function */
	void VTable::set (const Function* function)
	{
		mTable[function->getName()] = function;
	}

}



/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
const Myelin::Function *
myelin_vtable_get (const Myelin::VTable *vtable, const char *name)
{
	return vtable->get (name);
}


void
myelin_vtable_set (Myelin::VTable *vtable, const Myelin::Function *function)
{
	vtable->set (function);
}



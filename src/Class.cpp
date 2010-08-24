

#include "Class.h"
#include "List.h"


/* C api */
const char *
myelin_class_get_name (Myelin::Class *klass)
{
	return klass->getName().c_str();
}


void
myelin_class_register_function (Myelin::Class *klass,
                                Myelin::Function *function)
{
	klass->registerFunction (function);
}


Myelin::Function *
myelin_class_get_function (Myelin::Class *klass, const char *name)
{
	return klass->getFunction (name);
}


Myelin::List *
myelin_class_get_function_list (Myelin::Class *klass)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::FunctionList funcs = klass->getFunctionList();
	Myelin::FunctionList::iterator iter;
	
	/* add all functions into the list */
	for (iter = funcs.begin(); iter != funcs.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}


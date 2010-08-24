

#include "Function.h"
#include "List.h"


/* C api */
const char *
myelin_function_get_name (Myelin::Function *function)
{
	return function->getName().c_str();
}



const Myelin::Type *
myelin_function_get_return_type (Myelin::Function *function)
{
	return function->getReturnType();
}



int
myelin_function_get_param_count (Myelin::Function *function)
{
	return function->getParamCount();
}



const Myelin::Type *
myelin_function_get_param_type (Myelin::Function *function, int index)
{
	return function->getParamType (index);
}



Myelin::List *
myelin_function_get_param_list (Myelin::Function *function)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::TypeList types = function->getParamList();
	Myelin::TypeList::iterator iter;
	
	/* add all functions into the list */
	for (iter = types.begin(); iter != types.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}



Myelin::Value *
myelin_function_call (Myelin::Function *function,
                      void *object,
                      const Myelin::List* params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = function->call (object, *params);
	return value;
}


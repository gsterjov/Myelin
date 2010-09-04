

#include "Constructor.h"
#include "List.h"


/* C api */
MYELIN_API int
myelin_constructor_get_param_count (Myelin::Constructor *constructor)
{
	return constructor->getParamCount();
}



MYELIN_API const Myelin::Type *
myelin_constructor_get_param_type (Myelin::Constructor *constructor, int index)
{
	return constructor->getParamType (index);
}



MYELIN_API Myelin::List *
myelin_constructor_get_param_list (Myelin::Constructor *constructor)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get a list of all functions */
	Myelin::TypeList types = constructor->getParamList();
	Myelin::TypeList::iterator iter;
	
	/* add all functions into the list */
	for (iter = types.begin(); iter != types.end(); ++iter)
		list->push_back (*iter);
	
	return list;
}



MYELIN_API Myelin::Value *
myelin_constructor_call (Myelin::Constructor *constructor,
                         const Myelin::List* params)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = constructor->call (*params);
	return value;
}


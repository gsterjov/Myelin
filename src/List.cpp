

#include "List.h"


/* C api */
MYELIN_API Myelin::List *
myelin_list_new ()
{
	return new Myelin::List ();
}


MYELIN_API void
myelin_list_free (Myelin::List *list)
{
	delete list;
}




MYELIN_API uint
myelin_list_size (const Myelin::List *list)
{
	return list->size();
}


MYELIN_API Myelin::Value *
myelin_list_index (const Myelin::List *list, uint index)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = list->at (index);
	return value;
}



MYELIN_API void
myelin_list_append (Myelin::List *list, Myelin::Value *value)
{
	list->push_back (*value);
}


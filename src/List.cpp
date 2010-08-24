

#include "List.h"


/* C api */
Myelin::List *
myelin_list_new ()
{
	return new Myelin::List ();
}


void
myelin_list_free (Myelin::List *list)
{
	delete list;
}




uint
myelin_list_size (const Myelin::List *list)
{
	return list->size();
}


Myelin::Value *
myelin_list_index (const Myelin::List *list, uint index)
{
	Myelin::Value *value = new Myelin::Value ();
	*value = list[index];
	return value;
}



#include "List.h"






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::List *
myelin_list_new ()
{
	return new Myelin::List ();
}


Myelin::List *
myelin_list_ref (Myelin::List *list)
{
	list->ref();
	return list;
}


void
myelin_list_unref (Myelin::List *list)
{
	list->unref();
	if (list->count() == 0) delete list;
}




uint
myelin_list_size (const Myelin::List *list)
{
	return list->size();
}


Myelin::Value *
myelin_list_index (const Myelin::List *list, uint index)
{
	Myelin::Value* ret = new Myelin::Value (list->at (index));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}



void
myelin_list_append (Myelin::List *list, Myelin::Value *value)
{
	list->push_back (*value);
}


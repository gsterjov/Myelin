
#include "Pointer.h"






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Pointer *
myelin_pointer_new ()
{
	return new Myelin::Pointer();
}


void
myelin_pointer_free (Myelin::Pointer *ptr)
{
	delete ptr;
}


const Myelin::Type *
myelin_pointer_get_type (const Myelin::Pointer *ptr)
{
	return ptr->getType();
}


bool 
myelin_pointer_is_empty (const Myelin::Pointer *ptr)
{
	return ptr->isEmpty();
}


void
myelin_pointer_clear (Myelin::Pointer *ptr)
{
	ptr->clear();
}



void *
myelin_pointer_get_raw (const Myelin::Pointer *ptr)
{
	return ptr->getRaw();
}



void
myelin_pointer_set (Myelin::Pointer *ptr,
                    void* pointer,
                    const Myelin::Type* type)
{
	ptr->set (pointer, type);
}


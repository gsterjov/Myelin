
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


Myelin::Pointer *
myelin_pointer_ref (Myelin::Pointer *ptr)
{
	ptr->ref();
	return ptr;
}


void
myelin_pointer_unref (Myelin::Pointer *ptr)
{
	ptr->unref();
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


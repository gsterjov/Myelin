
#include "Pointer.h"




/* C api */
MYELIN_API Myelin::Pointer *
myelin_pointer_new ()
{
	return new Myelin::Pointer();
}


MYELIN_API void
myelin_pointer_free (Myelin::Pointer *ptr)
{
	delete ptr;
}


MYELIN_API const Myelin::Type *
myelin_pointer_get_type (const Myelin::Pointer *ptr)
{
	return ptr->getType();
}


MYELIN_API bool 
myelin_pointer_is_empty (const Myelin::Pointer *ptr)
{
	return ptr->isEmpty();
}


MYELIN_API void
myelin_pointer_clear (Myelin::Pointer *ptr)
{
	ptr->clear();
}



MYELIN_API void *
myelin_pointer_get_raw (const Myelin::Pointer *ptr)
{
	return ptr->getRaw();
}



MYELIN_API void
myelin_pointer_set (Myelin::Pointer *ptr,
                    void* pointer,
                    const Myelin::Type::Atom* atom)
{
	Myelin::Type::Traits traits;
	traits.add_pointer ();
	
	Myelin::Type* type = new Myelin::Types::CustomType (atom, traits);
	
	ptr->set (pointer, type);
}


MYELIN_API void
myelin_pointer_set_const (Myelin::Pointer *ptr,
                          const void* pointer,
                          const Myelin::Type::Atom* atom)
{
	Myelin::Type::Traits traits;
	traits.add_pointer ();
	traits.add_constant ();
	
	Myelin::Type* type = new Myelin::Types::CustomType (atom, traits);
	
	ptr->set (const_cast<void*>(pointer), type);
}



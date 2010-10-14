
#include "Pointer.h"


namespace Myelin
{

	/* constructor */
	Pointer::Pointer () : mData(0), mType(0)
	{
		
	}
	
	
	/* custom type constructor */
	Pointer::Pointer (void* ptr, const Type* type)
	: mData (new GenericData <void*> (ptr)),
	  mType (type)
	{
		
	}
	
	
	
	/* data constructor */
	Pointer::Pointer (Data* data)
	: mData (data),
	  mType (0)
	{
		
	}
	
	
	
	/* get pointer type */
	const Type* Pointer::getType() const
	{
		if (mType) return mType;
		return mData ? mData->getType() : TYPE(void);
	}
	
	
	
	/* clear value */
	void Pointer::clear ()
	{
		if (mData)
		{
			mData->unref();
			
			if (mData->count() == 0)
				delete mData;
			
			mData = 0;
		}
		
		mType = 0;
	}
	
	
	
	/* set custom pointer */
	void Pointer::set (void* ptr, const Type* type)
	{
		clear();
		mData = new GenericData <void*> (ptr);
		mType = type;
	}
	
	
	
	/* get raw pointer */
	void* Pointer::getRaw() const
	{
		if (isEmpty()) return 0;
		return static_cast<GenericData<void*>*> (mData)->getData();
	}

}



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
	if (ptr->count() == 0) delete ptr;
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


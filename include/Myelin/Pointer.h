
#ifndef MYELIN_POINTER_H_
#define MYELIN_POINTER_H_


#include <stdexcept>
#include <cassert>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Type.h>
#include <Myelin/TypeTraits.h>
#include <Myelin/Data.h>
#include <Myelin/Class.h>
#include <Myelin/Converter.h>


namespace Myelin
{

	/**
	 * A type-safe generic pointer.
	 */
	class MYELIN_API Pointer : public RefCounter
	{
	public:
		/**
		 * Default constructor.
		 */
		Pointer();
		
		
		/**
		 * Custom type constructor.
		 */
		Pointer (void* ptr, const Type* type);
		
		
		/**
		 * Data constructor.
		 */
		Pointer (Data* data);
		
		
		/**
		 * Pointer constructor.
		 */
		template <typename T>
		explicit Pointer (T* ptr)
		: mData (new GenericData <T*> (ptr)),
		  mType (0)
		{}
		
		
		
		/**
		 * Get pointer type.
		 */
		const Type* getType() const;
		
		
		
		/**
		 * Has the pointer been set?
		 */
		bool isEmpty() const { return !mData; }
		
		
		/**
		 * Clear the pointer.
		 */
		void clear();
		
		
		/**
		 * Set custom type pointer.
		 */
		void set (void* ptr, const Type* type);
		
		
		/**
		 * Get raw pointer.
		 */
		void* getRaw() const;
		
		
		
		/**
		 * Set new pointer.
		 */
		template <typename T>
		void set (T* ptr)
		{
			clear();
			mData = new GenericData <T*> (ptr);
		}
		
		
		
		/**
		 * Get the pointer.
		 */
		template <typename T>
		T* get () const
		{
			/* output type */
			const Type* out_type = TYPE(T*);
			
			
			/* empty value */
			if (isEmpty())
				throw std::invalid_argument ("Cannot cast pointer type to "
						"the requested type '" + out_type->getName() + "' "
						"because the generic pointer is empty");
			
			
			/* pointer type */
			const Type* type = mType ? mType : mData->getType();
			
			
			/* pointers match */
			if (out_type->equals (type))
				return static_cast<GenericData<T*>*> (mData)->getData();
			
			
			/* try convert pointer TO the pointer type */
			else if (mType->getAtom()->getClass())
			{
				const Class* klass = type->getAtom()->getClass();
				
				
				/* get all converters */
				const ConverterList& list = klass->getConverters();
				ConverterList::const_iterator iter;
				
				/* look for a matching conversion context */
				for (iter = list.begin(); iter != list.end(); ++iter)
				{
					Converter* conv = *iter;
					
					/* can convert to type */
					if (conv->getOutputType()->equals (out_type))
						return static_cast<GenericData<T*>*> (mData)->getData();
				}
			}
			
			/* target type and value type dont match */
			else throw std::invalid_argument ("Cannot cast pointer type '" +
					type->getName() + "' to pointer type '" +
					out_type->getName() + "'");
		}
		
		
		
	private:
		Data* mData;
		const Type* mType;
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
extern "C"
{

	/**
	 * Create a new generic pointer.
	 */
	MYELIN_API Myelin::Pointer *myelin_pointer_new ();
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Pointer *myelin_pointer_ref (Myelin::Pointer *ptr);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_pointer_unref (Myelin::Pointer *ptr);
	
	/**
	 * Get the type of the generic pointer.
	 */
	MYELIN_API const Myelin::Type *myelin_pointer_get_type (const Myelin::Pointer *ptr);
	
	/**
	 * Is the generic pointer holding an address?
	 */
	MYELIN_API bool myelin_pointer_is_empty (const Myelin::Pointer *ptr);
	
	/**
	 * Clear the generic pointer.
	 */
	MYELIN_API void myelin_pointer_clear (Myelin::Pointer *ptr);
	
	/**
	 * Get the raw type-less pointer.
	 */
	MYELIN_API void *myelin_pointer_get_raw (const Myelin::Pointer *ptr);
	
	/**
	 * Set the generic pointer with the specified address and atomic type.
	 */
	MYELIN_API void myelin_pointer_set (Myelin::Pointer *ptr,
	                                    void* pointer,
	                                    const Myelin::Type *type);

}



#endif /* MYELIN_POINTER_H_ */

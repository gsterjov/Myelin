
#ifndef MYELIN_POINTER_H_
#define MYELIN_POINTER_H_


#include <stdexcept>
#include <cassert>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Type.h>
#include <Myelin/TypeTraits.h>
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
		Pointer() : mPointer(0), mType(0) {}
		
		
		/**
		 * Pointer constructor.
		 */
		template <typename T>
		explicit Pointer (T* ptr)
		: mPointer (ptr),
		  mType (TYPE(T*))
		{}
		
		
		/**
		 * Custom type constructor.
		 */
		Pointer (void* ptr, const Type* type) : mPointer(ptr), mType(type) {}
		
		
		
		/**
		 * Get pointer type.
		 */
		const Type* getType() const
		{
			return mType ? mType : TYPE(void);
		}
		
		
		
		/**
		 * Has the pointer been set?
		 */
		bool isEmpty() const { return !mType; }
		
		
		/**
		 * Clear the pointer.
		 */
		void clear() { mPointer = 0; mType = 0; }
		
		
		
		/**
		 * Set new pointer.
		 */
		template <typename T>
		void set (T* ptr)
		{
			clear();
			mType = TYPE(T*);
			mPointer = ptr;
		}
		
		
		/**
		 * Set custom type pointer.
		 */
		void set (void* ptr, const Type* type)
		{
			clear();
			mType = type;
			mPointer = ptr;
		}
		
		
		/**
		 * Get the pointer.
		 */
		template <typename T>
		T* get () const
		{
			assert (mType);
			
			/* output type */
			const Type* out_type = TYPE(T*);
			
			/* pointers match */
			if (TYPE(T*)->equals (mType))
				return static_cast<T*> (mPointer);
			
			/* try convert pointer TO the pointer type */
			else if (mType->getAtom()->getClass())
			{
				const Class* klass = mType->getAtom()->getClass();
				
				
				/* get all converters */
				const ConverterList& list = klass->getConverters();
				ConverterList::const_iterator iter;
				
				/* look for a matching conversion context */
				for (iter = list.begin(); iter != list.end(); ++iter)
				{
					Converter* conv = *iter;
					
					/* can convert to type */
					if (conv->getOutputType()->equals (out_type))
						return static_cast<T*> (mPointer);
				}
			}
			
			/* target type and value type dont match */
			else throw std::invalid_argument ("Cannot cast pointer type '" +
					mType->getName() + "' to pointer type '" +
					TYPE(T*)->getName() + "'");
		}
		
		
		/**
		 * Get raw pointer.
		 */
		void* getRaw() const { return mPointer; }
		
		
		
	private:
		void* mPointer;
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

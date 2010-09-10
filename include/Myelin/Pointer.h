
#ifndef MYELIN_POINTER_H_
#define MYELIN_POINTER_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/TypeTraits.h>


namespace Myelin
{

	/**
	 * A type-safe generic pointer.
	 */
	class MYELIN_API Pointer
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
		explicit Pointer (const T* ptr)
		: mPointer (const_cast<T*>(ptr)),
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
		void set (const T* ptr)
		{
			clear();
			mType = TYPE(T*);
			mPointer = const_cast<T*>(ptr);
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
			/* pointers match */
			if (TYPE(T*)->equals (mType))
				return static_cast<T*> (mPointer);
			
			/* target type and value type dont match */
			else throw std::invalid_argument ("Cannot cast pointer '" +
					mType->getName() + "' to pointer '" +
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



/* C api */
extern "C"
{

	MYELIN_API Myelin::Pointer *myelin_pointer_new ();
	
	MYELIN_API void myelin_pointer_free (Myelin::Pointer *ptr);
	
	
	MYELIN_API const Myelin::Type *myelin_pointer_get_type (const Myelin::Pointer *ptr);
	
	MYELIN_API bool myelin_pointer_is_empty (const Myelin::Pointer *ptr);
	MYELIN_API void myelin_pointer_clear (Myelin::Pointer *ptr);
	
	
	MYELIN_API void *myelin_pointer_get_raw (const Myelin::Pointer *ptr);
	
	
	MYELIN_API void myelin_pointer_set (Myelin::Pointer *ptr,
	                                    void* pointer,
	                                    const Myelin::Type::Atom* atom);
	
	MYELIN_API void myelin_pointer_set_const (Myelin::Pointer *ptr,
	                                          const void* pointer,
	                                          const Myelin::Type::Atom* atom);

}



#endif /* MYELIN_POINTER_H_ */

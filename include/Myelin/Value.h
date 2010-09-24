
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Pointer.h>


namespace Myelin
{

	/**
	 * Generic value.
	 */
	class MYELIN_API Value
	{
	public:
		/**
		 * Default constructor.
		 */
		Value () : mValue(0) {}
		
		
		/**
		 * Value constructor.
		 */
		template <typename T>
		Value (const T& value)
		: mValue (new GenericValue <T> (value))
		  {}
		
		
		/**
		 * Get value type.
		 */
		const Type* getType() const
		{
			return mValue ? mValue->getType() : TYPE(void);
		}
		
		
		/**
		 * Has the value been set?
		 */
		bool isEmpty() const { return !mValue; }
		
		
		/**
		 * Clear the value.
		 */
		void clear() { if (mValue) delete mValue; mValue = 0; }
		
		
		
		/**
		 * Set new value.
		 */
		template <typename T>
		void set (const T& value)
		{
			clear();
			mValue = new GenericValue <T> (value);
		}
		
		
		
		/**
		 * Get generic value.
		 */
		template <typename T>
		T& get () const
		{
			/* empty value */
			if (isEmpty())
				throw std::invalid_argument ("Cannot cast value type to "
						"the requested type '" + TYPE(T)->getName() + "' "
						"because the value is empty");
			
			
			/* cast to value type */
			else if (mValue->getType()->equals (TYPE(T)))
				return static_cast<GenericValue<T>*> (mValue)->data;
			
			
			/* target type and value type dont match */
			else throw std::invalid_argument ("Cannot cast value type '" +
					mValue->getType()->getName() + "' to requested type '" +
					TYPE(T)->getName() + "'");
		}
		
		
		Pointer* getPointer () const
		{
			/* empty value */
			if (isEmpty())
				throw std::invalid_argument ("Cannot cast value type to "
						"a generic pointer type because the value is empty");
			
			
			const Type* val_t = mValue->getType();
			
			/* we have a generic pointer */
			if (val_t->getAtom() == TYPE(Pointer)->getAtom())
			{
				if      (val_t->isPointer())   return get<Pointer*>();
				else if (val_t->isReference()) return &get<Pointer&>();
				else return &get<Pointer>();
			}
			
			/* not a generic pointer */
			else if (val_t->isPointer())
				return new Pointer (
						static_cast<Value::GenericValue<void*>*> (mValue)->data,
						val_t);
			
			
			/* value is not a pointer */
			else throw std::invalid_argument ("Cannot cast value type '" +
					val_t->getName() + "' to a generic pointer because it"
					"isn't a valid pointer type");
		}
		
		
		
	private:
		struct ValueData;
		ValueData* mValue;
		
		
		
		/* data storage interface */
		struct ValueData
		{
			virtual const Type* getType() const = 0;
		};
		
		
		/* value data storage */
		template <typename T>
		struct GenericValue : ValueData
		{
			T data;
			
			GenericValue (const T& value) : data (value) {}
			const Type* getType() const { return TYPE(T); }
		};
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
	 * Create a new generic value.
	 */
	MYELIN_API Myelin::Value *myelin_value_new ();
	
	/**
	 * Free the generic value pointer.
	 */
	MYELIN_API void myelin_value_free (Myelin::Value *value);
	
	
	/**
	 * Get the generic value type.
	 */
	MYELIN_API const Myelin::Type *myelin_value_get_type (const Myelin::Value *value);
	
	/**
	 * Is the generic value holding anything?
	 */
	MYELIN_API bool myelin_value_is_empty (const Myelin::Value *value);
	
	/**
	 * Clear the generic value.
	 */
	MYELIN_API void myelin_value_clear (Myelin::Value *value);
	
	
	
	/**
	 * Get the boolean inside the generic value.
	 */
	MYELIN_API bool myelin_value_get_bool (const Myelin::Value *value);
	
	/**
	 * Set the boolean inside the generic value.
	 */
	MYELIN_API void myelin_value_set_bool (Myelin::Value *value, bool val);
	
	/**
	 * Set the constant boolean inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_bool (Myelin::Value *value, const bool val);
	
	
	
	/**
	 * Get the char inside the generic value.
	 */
	MYELIN_API char myelin_value_get_char (const Myelin::Value *value);
	
	/**
	 * Set the char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_char (Myelin::Value *value, char val);
	
	/**
	 * Set the constant char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_char (Myelin::Value *value, const char val);
	
	
	/**
	 * Get the unsigned char inside the generic value.
	 */
	MYELIN_API uchar myelin_value_get_uchar (const Myelin::Value *value);
	
	/**
	 * Set the unsigned char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uchar (Myelin::Value *value, uchar val);
	
	/**
	 * Set the constant unsigned char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uchar (Myelin::Value *value, const uchar val);
	
	
	
	/**
	 * Get the integer inside the generic value.
	 */
	MYELIN_API int myelin_value_get_int (const Myelin::Value *value);
	
	/**
	 * Set the integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_int (Myelin::Value *value, int val);
	
	/**
	 * Set the constant integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_int (Myelin::Value *value, const int val);
	
	
	
	
	/**
	 * Get the unsigned integer inside the generic value.
	 */
	MYELIN_API uint myelin_value_get_uint (const Myelin::Value *value);
	
	/**
	 * Set the unsigned integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uint (Myelin::Value *value, uint val);
	
	/**
	 * Set the constant unsigned integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uint (Myelin::Value *value, const uint val);
	
	
	
	
	/**
	 * Get the long inside the generic value.
	 */
	MYELIN_API long myelin_value_get_long (const Myelin::Value *value);
	
	/**
	 * Set the long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_long (Myelin::Value *value, long val);
	
	/**
	 * Set the constant long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_long (Myelin::Value *value, const long val);
	
	
	
	
	/**
	 * Set the unsigned long inside the generic value.
	 */
	MYELIN_API ulong myelin_value_get_ulong (const Myelin::Value *value);
	
	/**
	 * Set the unsigned long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_ulong (Myelin::Value *value, ulong val);
	
	/**
	 * Set the constant unsigned long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_ulong (Myelin::Value *value, const ulong val);
	
	
	
	
	/**
	 * Get the int64 inside the generic value.
	 */
	MYELIN_API int64 myelin_value_get_int64 (const Myelin::Value *value);
	
	/**
	 * Set the int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_int64 (Myelin::Value *value, int64 val);
	
	/**
	 * Set the constant int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_int64 (Myelin::Value *value, const int64 val);
	
	
	
	
	/**
	 * Get the unsigned int64 inside the generic value.
	 */
	MYELIN_API uint64 myelin_value_get_uint64 (const Myelin::Value *value);
	
	/**
	 * Set the unsigned int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uint64 (Myelin::Value *value, uint64 val);
	
	/**
	 * Set the constant unsigned int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uint64 (Myelin::Value *value, const uint64 val);
	
	
	
	
	/**
	 * Get the float inside the generic value.
	 */
	MYELIN_API float myelin_value_get_float (const Myelin::Value *value);
	
	/**
	 * Set the float inside the generic value.
	 */
	MYELIN_API void myelin_value_set_float (Myelin::Value *value, float val);
	
	/**
	 * Set the constant float inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_float (Myelin::Value *value, const float val);
	
	
	
	
	/**
	 * Get the double inside the generic value.
	 */
	MYELIN_API double myelin_value_get_double (const Myelin::Value *value);
	
	/**
	 * Set the double inside the generic value.
	 */
	MYELIN_API void myelin_value_set_double (Myelin::Value *value, double val);
	
	/**
	 * Set the constant double inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_double (Myelin::Value *value, const double val);
	
	
	
	
	/**
	 * Get the string inside the generic value.
	 */
	MYELIN_API const char *myelin_value_get_string (const Myelin::Value *value);
	
	/**
	 * Set the string inside the generic value.
	 */
	MYELIN_API void myelin_value_set_string (Myelin::Value *value, const char *val);
	
	
	
	
	/**
	 * Get the generic pointer inside the generic value.
	 */
	MYELIN_API Myelin::Pointer *myelin_value_get_pointer (const Myelin::Value *value);
	
	/**
	 * Get the constant generic pointer inside the generic value.
	 */
	MYELIN_API const Myelin::Pointer *myelin_value_get_const_pointer (const Myelin::Value *value);
	
	/**
	 * Set the generic pointer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_pointer (Myelin::Value *value, Myelin::Pointer *ptr);
	
	/**
	 * Set the constant generic pointer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_pointer (Myelin::Value *value, const Myelin::Pointer *ptr);

}



#endif /* MYELIN_VALUE_H_ */

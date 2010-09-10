
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <stdexcept>
#include <cassert>
#include <vector>

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
			/* cast to value type */
			if (mValue->getType()->equals (TYPE(T)))
				return static_cast<GenericValue<T>*> (mValue)->data;
			
			
			/* target type and value type dont match */
			else throw std::invalid_argument ("Cannot cast value type '" +
					mValue->getType()->getName() + "' to requested type '" +
					TYPE(T)->getName() + "'");
		}
		
		
		Pointer* getPointer () const
		{
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




/* C api */
extern "C"
{

	MYELIN_API Myelin::Value *myelin_value_new ();
	
	MYELIN_API void myelin_value_free (Myelin::Value *value);
	
	
	MYELIN_API const Myelin::Type *myelin_value_get_type (const Myelin::Value *value);
	
	MYELIN_API bool myelin_value_is_empty (const Myelin::Value *value);
	MYELIN_API void myelin_value_clear (Myelin::Value *value);
	
	
	
	/* boolean */
	MYELIN_API       bool myelin_value_get_bool       (const Myelin::Value *value);
	MYELIN_API const bool myelin_value_get_const_bool (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_bool       (Myelin::Value *value,       bool val);
	MYELIN_API void myelin_value_set_const_bool (Myelin::Value *value, const bool val);
	
	
	/* char */
	MYELIN_API       char myelin_value_get_char       (const Myelin::Value *value);
	MYELIN_API const char myelin_value_get_const_char (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_char       (Myelin::Value *value,       char val);
	MYELIN_API void myelin_value_set_const_char (Myelin::Value *value, const char val);
	
	
	MYELIN_API       uchar myelin_value_get_uchar       (const Myelin::Value *value);
	MYELIN_API const uchar myelin_value_get_const_uchar (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_uchar       (Myelin::Value *value,       uchar val);
	MYELIN_API void myelin_value_set_const_uchar (Myelin::Value *value, const uchar val);
	
	
	/* integer */
	MYELIN_API       int myelin_value_get_int       (const Myelin::Value *value);
	MYELIN_API const int myelin_value_get_const_int (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_int       (Myelin::Value *value,       int val);
	MYELIN_API void myelin_value_set_const_int (Myelin::Value *value, const int val);
	
	
	MYELIN_API       uint myelin_value_get_uint       (const Myelin::Value *value);
	MYELIN_API const uint myelin_value_get_const_uint (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_uint       (Myelin::Value *value,       uint val);
	MYELIN_API void myelin_value_set_const_uint (Myelin::Value *value, const uint val);
	
	
	/* long */
	MYELIN_API       long myelin_value_get_long       (const Myelin::Value *value);
	MYELIN_API const long myelin_value_get_const_long (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_long       (Myelin::Value *value,       long val);
	MYELIN_API void myelin_value_set_const_long (Myelin::Value *value, const long val);
	
	
	MYELIN_API       ulong myelin_value_get_ulong       (const Myelin::Value *value);
	MYELIN_API const ulong myelin_value_get_const_ulong (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_ulong       (Myelin::Value *value,       ulong val);
	MYELIN_API void myelin_value_set_const_ulong (Myelin::Value *value, const ulong val);
	
	
	/* 64bit integer */
	MYELIN_API       int64 myelin_value_get_int64       (const Myelin::Value *value);
	MYELIN_API const int64 myelin_value_get_const_int64 (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_int64       (Myelin::Value *value,       int64 val);
	MYELIN_API void myelin_value_set_const_int64 (Myelin::Value *value, const int64 val);
	
	
	MYELIN_API       uint64 myelin_value_get_uint64       (const Myelin::Value *value);
	MYELIN_API const uint64 myelin_value_get_const_uint64 (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_uint64       (Myelin::Value *value,       uint64 val);
	MYELIN_API void myelin_value_set_const_uint64 (Myelin::Value *value, const uint64 val);
	
	
	/* float */
	MYELIN_API       float myelin_value_get_float       (const Myelin::Value *value);
	MYELIN_API const float myelin_value_get_const_float (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_float       (Myelin::Value *value,       float val);
	MYELIN_API void myelin_value_set_const_float (Myelin::Value *value, const float val);
	
	
	/* double */
	MYELIN_API       double myelin_value_get_double       (const Myelin::Value *value);
	MYELIN_API const double myelin_value_get_const_double (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_double       (Myelin::Value *value,       double val);
	MYELIN_API void myelin_value_set_const_double (Myelin::Value *value, const double val);
	
	
	/* string */
	MYELIN_API const char *myelin_value_get_string (const Myelin::Value *value);
	MYELIN_API void        myelin_value_set_string (Myelin::Value *value, const char *val);
	
	
	/* pointer */
	MYELIN_API       Myelin::Pointer *myelin_value_get_pointer       (const Myelin::Value *value);
	MYELIN_API const Myelin::Pointer *myelin_value_get_const_pointer (const Myelin::Value *value);
	
	MYELIN_API void myelin_value_set_pointer       (Myelin::Value *value,       Myelin::Pointer *ptr);
	MYELIN_API void myelin_value_set_const_pointer (Myelin::Value *value, const Myelin::Pointer *ptr);

}



#endif /* MYELIN_VALUE_H_ */

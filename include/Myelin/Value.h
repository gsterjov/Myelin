
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <exception>
#include <vector>

#include <Myelin/Config.h>
#include <Myelin/TypeInfo.h>


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
		Value (const T& value) : mValue(new GenericValue<T>(value)), mIsPointer(false) {}
		
		
		/**
		 * Value pointer constructor.
		 */
		template <typename T>
		Value (T* value) : mValue(new GenericValue<T*>(value)), mIsPointer(true) {}
		
		
		/**
		 * Get value type.
		 */
		const TypeInfo* getTypeInfo() const
		{
			return mValue ? mValue->getTypeInfo() : TYPE_INFO(void);
		}
		
		
		
		/**
		 * Is the value a pointer?
		 */
		bool isPointer() const { return mIsPointer; }
		
		
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
		void setValue (const T& value)
		{
			if (mValue) delete mValue;
			mValue = new GenericValue<T>(value);
			mIsPointer = false;
		}
		
		
		template <typename T>
		void setValue (T* value)
		{
			if (mValue) delete mValue;
			mValue = new GenericValue<T*>(value);
			mIsPointer = true;
		}
		
		
		
		
	private:
		struct ValueData;
		
		ValueData* mValue;
		bool mIsPointer;
		
		
		
		/* data storage interface */
		struct ValueData
		{
			virtual const TypeInfo* getTypeInfo() const = 0;
		};
		
		
		/* value data storage */
		template <typename T>
		struct GenericValue : ValueData
		{
			T data;
			const TypeInfo* type;
			
			GenericValue (const T& value) : data (value), type (TYPE_INFO(T)) {}
			const TypeInfo* getTypeInfo() const { return type; }
		};
		
		
		
		/* allow global casting */
	    template <typename T>
	    friend T* value_cast (Value*);
	    
	    /* allow global const casting */
	    template <typename T>
	    friend const T* value_cast (const Value*);
	};
	
	
	
	
	/**
	 * Cast to the specified value pointer.
	 */
	template <typename T>
	T* value_cast (Value* value)
	{
		/* sanity check */
		if (!value) return 0;
		
		/* cast to value type */
		if (value->getTypeInfo() == TYPE_INFO(T))
			return &static_cast<Value::GenericValue<T>*> (value->mValue)->data;
		
		/* cast to generic pointer */
		else if (value->isPointer() && TYPE_INFO(T) == TYPE_INFO(void*))
			return &static_cast<Value::GenericValue<T>*> (value->mValue)->data;
		
		
		return 0;
	}
	
	
	/**
	 * Cast to the specified const value pointer.
	 */
	template <typename T>
	const T* value_cast (const Value* value)
	{
		return value_cast<T> (const_cast<Value*> (value));
	}
	
	
	
	/**
	 * Cast to the specified value.
	 */
	template <typename T>
	T value_cast (Value& value)
	{
		T* ret = value_cast<T> (&value);
		if (!ret) throw std::bad_cast();
		return *ret;
	}
	
	
	/**
	 * Cast to the specified const value.
	 */
	template <typename T>
	const T value_cast (const Value& value)
	{
		const T* ret = value_cast<T> (&value);
		if (!ret) throw std::bad_cast();
		return *ret;
	}

}



/* C api */
extern "C"
{

	MYELIN_API Myelin::Value *myelin_value_new ();
	
	MYELIN_API void myelin_value_free (Myelin::Value *value);
	
	
	MYELIN_API const Myelin::TypeInfo *myelin_value_get_type_info (Myelin::Value *value);
	
	MYELIN_API bool myelin_value_is_pointer (Myelin::Value *value);
	MYELIN_API bool myelin_value_is_empty (Myelin::Value *value);
	MYELIN_API void myelin_value_clear (Myelin::Value *value);
	
	
	
	/* boolean */
	MYELIN_API bool myelin_value_get_bool (const Myelin::Value *value);
	MYELIN_API void myelin_value_set_bool (Myelin::Value *value, bool val);
	
	
	/* char */
	MYELIN_API char myelin_value_get_char (const Myelin::Value *value);
	MYELIN_API void myelin_value_set_char (Myelin::Value *value, char val);
	
	MYELIN_API uchar myelin_value_get_uchar (const Myelin::Value *value);
	MYELIN_API void  myelin_value_set_uchar (Myelin::Value *value, uchar val);
	
	
	/* integer */
	MYELIN_API int  myelin_value_get_int (const Myelin::Value *value);
	MYELIN_API void myelin_value_set_int (Myelin::Value *value, int val);
	
	MYELIN_API uint myelin_value_get_uint (const Myelin::Value *value);
	MYELIN_API void myelin_value_set_uint (Myelin::Value *value, uint val);
	
	
	/* long */
	MYELIN_API long myelin_value_get_long (const Myelin::Value *value);
	MYELIN_API void myelin_value_set_long (Myelin::Value *value, long val);
	
	MYELIN_API ulong myelin_value_get_ulong (const Myelin::Value *value);
	MYELIN_API void  myelin_value_set_ulong (Myelin::Value *value, ulong val);
	
	
	/* 64bit integer */
	MYELIN_API int64 myelin_value_get_int64 (const Myelin::Value *value);
	MYELIN_API void  myelin_value_set_int64 (Myelin::Value *value, int64 val);
	
	MYELIN_API uint64 myelin_value_get_uint64 (const Myelin::Value *value);
	MYELIN_API void   myelin_value_set_uint64 (Myelin::Value *value, uint64 val);
	
	
	/* float */
	MYELIN_API float myelin_value_get_float (const Myelin::Value *value);
	MYELIN_API void  myelin_value_set_float (Myelin::Value *value, float val);
	
	
	/* double */
	MYELIN_API double myelin_value_get_double (const Myelin::Value *value);
	MYELIN_API void   myelin_value_set_double (Myelin::Value *value, double val);
	
	
	/* string */
	MYELIN_API const char *myelin_value_get_string (const Myelin::Value *value);
	MYELIN_API void        myelin_value_set_string (Myelin::Value *value, const char *val);
	
	
	/* pointer */
	MYELIN_API void *myelin_value_get_pointer (const Myelin::Value *value);
	MYELIN_API void  myelin_value_set_pointer (Myelin::Value *value, void *val);

}



#endif /* MYELIN_VALUE_H_ */


#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <exception>
#include <vector>
#include <Myelin/Type.h>


namespace Myelin
{

	/**
	 * Generic value.
	 */
	class Value
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
		Value (const T& value) : mValue (new GenericValueData<T>(value)) {}
		
		
		/**
		 * Get value type.
		 */
		const Type& getType() const { return mValue ? mValue->getType() : typeid(void); }
		
		
		
		/**
		 * Get raw value data.
		 */
		void* getData() { return mValue->getData(); }
		
		
		
		/**
		 * Set new value.
		 */
		template <typename T>
		void setValue (const T& value)
		{
			delete mValue;
			mValue = new GenericValueData<T>(value);
		}
		
		
		
		
	private:
		struct ValueData;
		
		ValueData* mValue;
		
		
		/* data storage interface */
		struct ValueData
		{
			virtual const Type& getType() const = 0;
			virtual void* getData() = 0;
		};
		
		
		/* data storage */
		template <typename T>
		struct GenericValueData : ValueData
		{
			T data;
			
			GenericValueData (const T& value) : data(value) {}
			const Type& getType() const { return typeid(T); }
			
			void* getData() { return &data; }
		};
		
		
		
		/* allow static casting */
	    template <typename T>
	    friend T* value_cast (Value*);
	    
	    /* allow static const casting */
	    template <typename T>
	    friend const T* value_cast (const Value*);
	};
	
	
	
	
	/**
	 * A list of generic values.
	 */
	typedef std::vector<Value> ValueList;
	
	
	
	
	
	/**
	 * Cast to the specified value pointer.
	 */
	template <typename T>
	T* value_cast (Value* value)
	{
		return value && value->getType() == typeid(T)
				? &static_cast<Value::GenericValueData<T>*> (value->mValue)->data
				: 0;
	}
	
	/**
	 * Cast to the specified const value pointer.
	 */
	template <typename T>
	const T* value_cast (const Value* value)
	{
		return value && value->getType() == typeid(T)
				? &static_cast<Value::GenericValueData<T>*> (value->mValue)->data
				: 0;
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

	const Myelin::Type *myelin_value_get_type (Myelin::Value *value);
	
	void *myelin_value_get_data (Myelin::Value *value);
	
	
	/* boolean */
	bool myelin_value_get_bool (const Myelin::Value *value);
	void myelin_value_set_bool (Myelin::Value *value, bool val);
	
	
	/* char */
	char myelin_value_get_char (const Myelin::Value *value);
	void myelin_value_set_char (Myelin::Value *value, char val);
	
	uchar myelin_value_get_uchar (const Myelin::Value *value);
	void  myelin_value_set_uchar (Myelin::Value *value, uchar val);
	
	
	/* integer */
	int  myelin_value_get_int (const Myelin::Value *value);
	void myelin_value_set_int (Myelin::Value *value, int val);
	
	uint myelin_value_get_uint (const Myelin::Value *value);
	void myelin_value_set_uint (Myelin::Value *value, uint val);
	
	
	/* long */
	long myelin_value_get_long (const Myelin::Value *value);
	void myelin_value_set_long (Myelin::Value *value, long val);
	
	ulong myelin_value_get_ulong (const Myelin::Value *value);
	void  myelin_value_set_ulong (Myelin::Value *value, ulong val);
	
	
	/* 64bit integer */
	int64 myelin_value_get_int64 (const Myelin::Value *value);
	void  myelin_value_set_int64 (Myelin::Value *value, int64 val);
	
	uint64 myelin_value_get_uint64 (const Myelin::Value *value);
	void   myelin_value_set_uint64 (Myelin::Value *value, uint64 val);
	
	
	/* float */
	float myelin_value_get_float (const Myelin::Value *value);
	void  myelin_value_set_float (Myelin::Value *value, float val);
	
	
	/* double */
	double myelin_value_get_double (const Myelin::Value *value);
	void   myelin_value_set_double (Myelin::Value *value, double val);
	
	
	/* string */
	const char *myelin_value_get_string (const Myelin::Value *value);
	void        myelin_value_set_string (Myelin::Value *value, const char *val);
	
	
	/* pointer */
	void *myelin_value_get_pointer (const Myelin::Value *value);
	void  myelin_value_set_pointer (Myelin::Value *value, void *val);

}



#endif /* MYELIN_VALUE_H_ */

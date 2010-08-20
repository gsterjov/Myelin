
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <typeinfo>
#include <exception>
#include <vector>


namespace Myelin
{

	/**
	 * Generic value.
	 */
	class Value
	{
	public:
		Value () : mValue(0) {}
		
		
		template <typename T>
		Value (const T& value) : mValue (new GenericValueData<T>(value)) {}
		
		const std::type_info& getType() const { return mValue ? mValue->getType() : typeid(void); }
		
		
		
	private:
		struct ValueData
		{
			virtual ~ValueData() {}
			virtual const std::type_info& getType() const = 0;
		};
		
		
		
		
		template <typename T>
		struct GenericValueData : ValueData
		{
			GenericValueData (const T& value) : data(value) {}
			const std::type_info& getType() const { return typeid(T); }
			
			T data;
		};
		
		
		
	    template <typename T>
	    friend T* value_cast (Value*);
	    
	    template <typename T>
	    friend const T* value_cast (const Value*);
		
	    
		ValueData* mValue;
	};
	
	
	
	
	typedef std::vector<Value> ValueList;
	
	
	
	
	
	template <typename T>
	T* value_cast (Value* value)
	{
		return value && value->getType() == typeid(T)
				? &static_cast<Value::GenericValueData<T>*> (value->mValue)->data
				: 0;
	}
	
	template <typename T>
	const T* value_cast (const Value* value)
	{
		return value && value->getType() == typeid(T)
				? &static_cast<Value::GenericValueData<T>*> (value->mValue)->data
				: 0;
	}
	
	
	template <typename T>
	T value_cast (Value& value)
	{
		T* ret = value_cast<T> (&value);
		if (!ret) throw std::bad_cast();
		return *ret;
	}
	
	
	template <typename T>
	const T value_cast (const Value& value)
	{
		const T* ret = value_cast<T> (&value);
		if (!ret) throw std::bad_cast();
		return *ret;
	}

}


#endif /* MYELIN_VALUE_H_ */

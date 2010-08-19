
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_
#include <iostream>
#include <typeinfo>

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
		Value (const T& value) : mValue(new GenericValueData<T>(value)) {}
		
		template <typename T>
		Value (const T* value) : mValue(new GenericValueData<const T*>(value)) {}
		
		
		template <typename T>
		static Value create (const T& value) { return Value(value); }
		
		
		template <typename T>
		T& get() { return static_cast<GenericValueData<T>*>(mValue)->data; }
		
		template <typename T>
		const T& get() const {
			
			std::cout << "getting" << std::endl;
			std::cout << typeid(T).name() << std::endl;
			std::cout << mValue->getType().name() << std::endl;
			
			
			if (mValue->getType() != typeid(T))
			{
				std::cout << "NO MATCH" << std::endl;
				
				
				GenericValueData<T>* val = static_cast<GenericValueData<T>*>(mValue);
				
//				T newval = val->data;
				std::cout << val->getType().name() << std::endl;
				std::cout << typeid(val->data).name() << std::endl;
			}
			
			return static_cast<GenericValueData<T>*>(mValue)->data; }
		
		
		
		template <typename newType>
		operator newType& () { return get<newType>(); }
		
		
		
		template <typename T>
		friend bool operator== (const T lhs, const Value& rhs) { return lhs == rhs.get<T>(); }
		
		template <typename T>
		friend bool operator== (const Value& lhs, const T rhs) { return lhs.get<T>() == rhs; }
		
		
		template <typename T>
		friend bool operator!= (const T lhs, const Value& rhs) { return !(lhs == rhs); }
		
		template <typename T>
		friend bool operator!= (const Value& lhs, const T rhs) { return !(lhs == rhs); }
		
		
		
	private:
		struct ValueData
		{
			virtual ~ValueData() {}
			
			virtual const std::type_info& getType() = 0;
		};
		
		
		template <typename T>
		struct GenericValueData : ValueData
		{
			T data;
			const std::type_info& type;
			
			GenericValueData (const T& value) : data(value), type(typeid(value)) {}
			const std::type_info& getType() { return type; }
		};
		
		
		
		ValueData* mValue;
	};
	
	
	
	template<>
	struct Value::GenericValueData<const char*> : Value::ValueData
	{
		const char* data;
		const std::type_info& type;
		
		GenericValueData (const char* value) : data(value), type(typeid(value)) {}
		const std::type_info& getType() { return type; }
	};

}


#endif /* MYELIN_VALUE_H_ */

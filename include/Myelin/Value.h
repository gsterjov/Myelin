
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


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
		void set (const T& value)
		{
			if (mValue) delete mValue;
			mValue = new GenericValueData<T> (value);
		}
		
		
		
		template <typename T>
		T& get()
		{
			GenericValueData<T>* val = static_cast<GenericValueData<T>*> (mValue);
			return val->data;
		}
		
		
		template <typename T>
		const T& get() const
		{
			GenericValueData<T>* val = static_cast<GenericValueData<T>*> (mValue);
			return val->data;
		}
		
		
		
		template <typename newType>
		operator newType& ()
		{
			return get<newType>();
		}
		
		
		
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
		};
		
		
		template <typename T>
		struct GenericValueData : ValueData
		{
			GenericValueData (const T& value) : data(value) {}
			T data;
		};
		
		
		
		ValueData* mValue;
	};

}


#endif /* MYELIN_VALUE_H_ */

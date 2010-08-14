
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
		
		
		template <typename T>
		void set (T value)
		{
			GenericValueData<T>* val = new GenericValueData<T>;
			val->data = value;
			mValue = val;
		}
		
		
		template <typename T>
		T get()
		{
			GenericValueData<T>* val = static_cast<GenericValueData<T>*> (mValue);
			return val->data;
		}
		
		
		
	private:
		struct ValueData
		{
			virtual ~ValueData() {}
		};
		
		
		template <typename T>
		struct GenericValueData : ValueData
		{
			T data;
		};
		
		
		
		ValueData* mValue;
	};

}


#endif /* MYELIN_VALUE_H_ */

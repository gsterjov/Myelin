
#ifndef MYELIN_META_FUNCTION_H_
#define MYELIN_META_FUNCTION_H_


#include <Myelin/Value.h>


namespace Myelin
{

	class MetaFunction
	{
	public:
		std::string getName() { return mName; }
		
		
		virtual Value call (void* object, const Value& arg1)
		{
			return mData->call (object, arg1);
		}
		
		
		template <typename Class, typename Return, typename Arg1>
		void set (const std::string& name, Return(Class::*function)(Arg1))
		{
			MemberData<Class, Return, Arg1>* data = new MemberData<Class, Return, Arg1> ();
			data->set (function);
			
			mData = data;
			mName = name;
		}
		
		
		
	private:
		struct Data
		{
			virtual Value call (void* object, const Value& arg1) = 0;
		};
		
		
		template <typename Class, typename Return, typename Arg1>
		struct MemberData : Data
		{
			typedef Return (Class::*FunctionType) (Arg1);
			
			
			void set (FunctionType function)
			{
				Value* value = new Value ();
				
				value->set (function);
				mValue = value;
			}
			
			
			Return call (Class* object, Arg1 arg1)
			{
				FunctionType func = mValue->get<FunctionType>();
				return (object->*func)(arg1);
			}
			
			
			
			Value call (void* object, const Value& arg1)
			{
				FunctionType func = mValue->get<FunctionType>();
				
				Class* obj = static_cast<Class*> (object);
				Return ret = (obj->*func)(arg1.get<Arg1>());
				
				Value val;
				val.set (ret);
				return val;
			}
			
			
			
		private:
			Value* mValue;
		};
		
		
		Data* mData;
		std::string mName;
	};

}


#endif /* MYELIN_META_FUNCTION_H_ */

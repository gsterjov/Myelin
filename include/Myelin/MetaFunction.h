
#ifndef MYELIN_META_FUNCTION_H_
#define MYELIN_META_FUNCTION_H_


#include <Myelin/Value.h>

#include <vector>


namespace Myelin
{

	typedef std::vector<Value> ValueList;
	
	
	class MetaFunction
	{
	public:
		std::string getName() { return mName; }
		
		int getArgCount() { return mArgCount; }
		
		
		Value call (void* object, const ValueList& args)
		{
			return mData->call (object, args);
		}
		
		
		Value call (void* object, const Value& arg1)
		{
			return mData->call (object, arg1);
		}
		
		
		Value call (void* object, const Value& arg1, const Value& arg2)
		{
			ValueList list;
			list.push_back (arg1);
			list.push_back (arg2);
			
			return mData->call (object, list);
		}
		
		
		
		template <typename Class, typename Return, typename Arg1>
		void set (const std::string& name, Return(Class::*function)(Arg1))
		{
			MemberData1<Class, Return, Arg1>* data = new MemberData1<Class, Return, Arg1> ();
			data->set (function);
			
			mData = data;
			mName = name;
			
			mArgCount = 1;
		}
		
		
		template <typename Class, typename Return, typename Arg1, typename Arg2>
		void set (const std::string& name, Return(Class::*function)(Arg1, Arg2))
		{
			MemberData2<Class, Return, Arg1, Arg2>* data = new MemberData2<Class, Return, Arg1, Arg2> ();
			data->set (function);
			
			mData = data;
			mName = name;
			
			mArgCount = 2;
		}
		
		
		
	private:
		struct Data
		{
			virtual Value call (void* object, const Value& arg1) = 0;
			virtual Value call (void* object, const ValueList& args) = 0;
		};
		
		
		template <typename Class, typename Return, typename Arg1>
		struct MemberData1 : Data
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
			
			
			
			Value call (void* object, const ValueList& args)
			{
				FunctionType func = mValue->get<FunctionType>();
				
				Class* obj = static_cast<Class*> (object);
				Value val = (obj->*func)(args[0].get<Arg1>());
				
				return val;
			}
			
			
			
		private:
			Value* mValue;
		};
		
		
		
		template <typename Class, typename Return, typename Arg1, typename Arg2>
		struct MemberData2 : Data
		{
			typedef Return (Class::*FunctionType) (Arg1, Arg2);
			
			
			void set (FunctionType function)
			{
				Value* value = new Value ();
				
				value->set (function);
				mValue = value;
			}
			
			
			Return call (Class* object, Arg1 arg1, Arg2 arg2)
			{
				FunctionType func = mValue->get<FunctionType>();
				return (object->*func)(arg1, arg2);
			}
			
			
			
			Value call (void* object, const Value& arg1)
			{
				
			}
			
			
			
			Value call (void* object, const ValueList& args)
			{
				FunctionType func = mValue->get<FunctionType>();
				
				Class* obj = static_cast<Class*> (object);
				Value val = (obj->*func)(args[0].get<Arg1>(), args[1].get<Arg2>());
				
				return val;
			}
			
			
			
		private:
			Value* mValue;
		};
		
		
		Data* mData;
		std::string mName;
		
		int mArgCount;
	};

}


#endif /* MYELIN_META_FUNCTION_H_ */

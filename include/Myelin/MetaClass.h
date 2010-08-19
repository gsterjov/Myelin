
#ifndef MYELIN_META_CLASS_H_
#define MYELIN_META_CLASS_H_


#include <string>
#include <map>
#include <vector>
#include <Myelin/MetaFunction.h>


namespace Myelin
{

	class BaseMetaClass
	{
	public:
		virtual const std::string getName() const = 0;
		virtual MetaFunction* getFunction (const std::string& name) = 0;
		
		virtual std::vector<MetaFunction*> getFunctionList () = 0;
		
		virtual void* create() = 0;
	};
	
	
	
	static std::map<std::string, BaseMetaClass*> Classes;
	
	
	
	/**
	 * MetaClass.
	 */
	template <typename Class>
	class MetaClass : public BaseMetaClass
	{
	public:
		/**
		 * Constructor.
		 */
		MetaClass (const std::string& name) : mName(name)
		{
			Classes[name] = this;
		}
		
		/**
		 * Destructor.
		 */
		virtual ~MetaClass () {}
		
		
		/**
		 * Get the class name.
		 */
		const std::string getName() const { return mName; }
		
		
		/**
		 * Add a function.
		 */
		template <typename R>
		void addFunction (const std::string& name, R(Class::*function)())
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		template <typename R, typename A1>
		void addFunction (const std::string& name, R(Class::*function)(A1))
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		template <typename R, typename A1, typename A2>
		void addFunction (const std::string& name, R(Class::*function)(A1,A2))
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		template <typename R, typename A1, typename A2, typename A3>
		void addFunction (const std::string& name, R(Class::*function)(A1,A2,A3))
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		template <typename R, typename A1, typename A2, typename A3, typename A4>
		void addFunction (const std::string& name, R(Class::*function)(A1,A2,A3,A4))
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		template <typename R, typename A1, typename A2, typename A3, typename A4, typename A5>
		void addFunction (const std::string& name, R(Class::*function)(A1,A2,A3,A4,A5))
		{
			mFunctions[name] = new MetaFunction (name, function);
		}
		
		
		
		
		MetaFunction* getFunction (const std::string& name)
		{
			return mFunctions[name];
		}
		
		
		std::vector<MetaFunction*> getFunctionList ()
		{
			std::vector<MetaFunction*> list;
			std::map<std::string, MetaFunction*>::iterator iter;
			
			list.reserve (mFunctions.size());
			
			for (iter = mFunctions.begin(); iter != mFunctions.end(); iter++)
				list.push_back (iter->second);
			
			return list;
		}
		
		
		
		void* create ()
		{
			return new Class();
		}
		
		
		
		
	private:
		std::string mName;
		
		std::map<std::string, MetaFunction*> mFunctions;
	};

}


#endif /* MYELIN_META_CLASS_H_ */

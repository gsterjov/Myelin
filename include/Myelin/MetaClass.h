
#ifndef MYELIN_META_CLASS_H_
#define MYELIN_META_CLASS_H_


#include <string>
#include <map>
#include <Myelin/MetaFunction.h>


namespace Myelin
{

	class BaseMetaClass
	{
	public:
		virtual const std::string getName() const = 0;
		virtual MetaFunction* getFunction (const std::string& name) = 0;
		
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
		template <typename Return>
		void addFunction (const std::string& name, Return(Class::*function)())
		{
			MetaFunction* func = new MetaFunction();
			func->set (function);
			mFunctions[name] = func;
		}
		
		
		template <typename Return, typename Arg1>
		void addFunction (const std::string& name, Return(Class::*function)(Arg1))
		{
			MetaFunction* func = new MetaFunction();
			func->set (function);
			mFunctions[name] = func;
		}
		
		
		
		MetaFunction* getFunction (const std::string& name)
		{
			return mFunctions[name];
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

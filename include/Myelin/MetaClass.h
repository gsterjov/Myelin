
#ifndef MYELIN_META_CLASS_H_
#define MYELIN_META_CLASS_H_


#include <string>
#include <map>
#include <Myelin/MetaFunction.h>


namespace Myelin
{

	/**
	 * MetaClass.
	 */
	template <typename Class>
	class MetaClass
	{
	public:
		/**
		 * Constructor.
		 */
		MetaClass (const std::string& name) : mName(name) {}
		
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
		void addFunction (const std::string& name, void(Class::*function)())
		{
			MetaFunction* func = new MetaFunction();
			func->set (function);
			mFunctions[name] = func;
		}
		
		
		
		MetaFunction* getFunction (const std::string& name)
		{
			return mFunctions[name];
		}
		
		
		
		
	private:
		std::string mName;
		
		std::map<std::string, MetaFunction*> mFunctions;
	};

}


#endif /* MYELIN_META_CLASS_H_ */

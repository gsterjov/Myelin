
#ifndef MYELIN_GENERIC_CLASS_H_
#define MYELIN_GENERIC_CLASS_H_


#include <map>
#include <stdexcept>

#include <Myelin/Class.h>
#include <Myelin/Function.h>


namespace Myelin
{

	template <typename ClassType>
	class GenericClass : public Class
	{
	public:
		/**
		 * Constructor.
		 */
		explicit GenericClass (const std::string& name) : mName(name) {}
		
		
		/**
		 * Get meta class.
		 */
		const std::string& getName () const { return mName; }
		
		
		/**
		 * Register a function with the class.
		 */
		void registerFunction (Function* function)
		{
			std::map<std::string, Function*>::const_iterator iter;
			
			iter = mFunctionMap.find (function->getName());
			
			/* function already exists */
			if (iter != mFunctionMap.end())
				throw std::runtime_error (
					"A function by the name '" + function->getName() + "' "
					"already exists in the class '" + mName + "'.");
			
			/* add the function to the map */
			mFunctionMap[function->getName()] = function;
		}
		
		
		/**
		 * Get a function from the class.
		 */
		const Function* getFunction (const std::string& name) const
		{
			std::map<std::string, Function*>::const_iterator iter;
			
			iter = mFunctionMap.find (name);
			return iter != mFunctionMap.end() ? iter->second : 0;
		}
		
		
		
	private:
		std::string mName;
		std::map<std::string, Function*> mFunctionMap;
	};

}


#endif /* MYELIN_GENERIC_CLASS_H_ */

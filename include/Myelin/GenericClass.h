
#ifndef MYELIN_GENERIC_CLASS_H_
#define MYELIN_GENERIC_CLASS_H_


#include <map>
#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/List.h>
#include <Myelin/Class.h>
#include <Myelin/Function.h>

#include <Myelin/GenericObject.h>
#include <Myelin/Repository.h>


namespace Myelin
{

	/* function storage */
	typedef std::map<std::string, Function*> FunctionMap;
	
	
	
	template <typename ClassType>
	class MYELIN_API GenericClass : public Class
	{
	public:
		/**
		 * Constructor.
		 */
		explicit GenericClass (const std::string& name) : mName(name)
		{
			REGISTER_TYPE (ClassType, name);
		}
		
		
		/**
		 * Get meta class.
		 */
		const std::string& getName () const { return mName; }
		
		
		/**
		 * Register a function with the class.
		 */
		void registerFunction (Function* function)
		{
			FunctionMap::iterator iter;
			
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
		Function* getFunction (const std::string& name) const
		{
			FunctionMap::const_iterator iter;
			
			iter = mFunctionMap.find (name);
			return iter != mFunctionMap.end() ? iter->second : 0;
		}
		
		
		/**
		 * Get a list of functions from the class.
		 */
		FunctionList getFunctionList () const
		{
			FunctionList list;
			FunctionMap::const_iterator iter;
			
			for (iter = mFunctionMap.begin(); iter != mFunctionMap.end(); ++iter)
				list.push_back (iter->second);
			
			return list;
		}
		
		
		
		/**
		 * Create an object instance from the class.
		 */
		void* createInstance (const List& params) const
		{
			return new ClassType ();
		}
		
		
		/**
		 * Creates a meta object from the class.
		 */
		Object* createObject (const List& params) const
		{
			return new GenericObject<ClassType> (this, new ClassType());
		}
		
		
		
	private:
		std::string mName;
		FunctionMap mFunctionMap;
	};

}


#endif /* MYELIN_GENERIC_CLASS_H_ */

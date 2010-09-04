
#ifndef MYELIN_TYPE_CREATOR_H_
#define MYELIN_TYPE_CREATOR_H_


#include <Myelin/Config.h>
#include <Myelin/Repository.h>
#include <Myelin/GenericClass.h>
#include <Myelin/GenericConstructor.h>
#include <Myelin/GenericFunction.h>


namespace Myelin
{

	/**
	 * Class type creator.
	 */
	template <typename T>
	class ClassType
	{
	public:
		/**
		 * Constructor.
		 */
		ClassType (Repository* repo,
		           const std::string& name,
		           const std::string& name_space = "")
		: mRepo (repo),
		  mClass (new GenericClass<T>(name, name_space))
		{
			mRepo->registerClass (mClass);
		}
		
		
		
		/**
		 * Create the class type.
		 */
		static ClassType create (Repository* repo,
		                         const std::string& name,
		                         const std::string& name_space = "")
		{
			return ClassType (repo, name, name_space);
		}
		
		
		
		/**
		 * Declare a class constructor.
		 */
		ClassType& constructor ()
		{
			mClass->registerConstructor (new GenericConstructor<T> ());
			return *this;
		}
		
		
		
		
		/**
		 * Declare a class function.
		 */
		ClassType& function (const std::string &name, Function* function)
		{
			mClass->registerFunction (function);
			return *this;
		}
		
		
		/**
		 * Declare a class function.
		 */
		template <typename Class, typename Return>
		ClassType& function (const std::string& name, Return(Class::*function)())
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		template <typename Class, typename Return, typename Param1>
		ClassType& function (const std::string& name, Return(Class::*function)(Param1))
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		template <typename Class, typename Return, typename Param1, typename Param2>
		ClassType& function (const std::string& name, Return(Class::*function)(Param1, Param2))
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		template <typename Class, typename Return, typename Param1, typename Param2, typename Param3>
		ClassType& function (const std::string& name, Return(Class::*function)(Param1, Param2, Param3))
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		template <typename Class, typename Return, typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& function (const std::string& name, Return(Class::*function)(Param1, Param2, Param4, Param4))
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		template <typename Class, typename Return, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& function (const std::string& name, Return(Class::*function)(Param1, Param2, Param3, Param4, Param5))
		{
			mClass->registerFunction (new GenericFunction (name, function));
			return *this;
		}
		
		
		
	private:
		Repository* mRepo;
		GenericClass<T>* mClass;
	};

}


#endif /* MYELIN_TYPE_CREATOR_H_ */

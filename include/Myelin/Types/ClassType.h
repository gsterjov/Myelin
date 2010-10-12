
#ifndef MYELIN_CLASS_TYPE_H_
#define MYELIN_CLASS_TYPE_H_


#include <string>
#include <cassert>

#include <Myelin/Config.h>
#include <Myelin/Class.h>
#include <Myelin/Namespace.h>
#include <Myelin/Repository.h>
#include <Myelin/RepositoryFactory.h>
#include <Myelin/Constructor.h>
#include <Myelin/Function.h>
#include <Myelin/VTable.h>

#include <Myelin/Types/FunctionType.h>
#include <Myelin/Types/ConstructorType.h>
#include <Myelin/Types/MemberFunctionType.h>
#include <Myelin/Types/ConverterType.h>


namespace Myelin
{

	/**
	 * Class type.
	 */
	template <typename T>
	class ClassType
	{
	public:
		/**
		 * Constructor.
		 */
		explicit ClassType (const std::string& name) : mClass(new Class (name))
		{
			REGISTER_CLASS (T, mClass);
			mClass->setType (TYPE(T));
		}
		
		
		
		/**
		 * Create a new class type.
		 */
		static ClassType create (const std::string& name)
		{
			return ClassType (name);
		}
		
		
		
		/**
		 * Assign the class to the specified namespace.
		 */
		ClassType& name_space (Namespace* nspace)
		{
			assert (nspace);
			nspace->addClass (mClass);
			return *this;
		}
		
		
		ClassType& name_space (Repository* repository,
		                       const std::string& name)
		{
			assert (repository);
			Namespace* nspace = repository->getNamespace (name);
			
			/* create a new namespace */
			if (!nspace)
			{
				nspace = new Namespace (name);
				repository->addNamespace (nspace);
			}
			
			return name_space (nspace);
		}
		
		
		ClassType& name_space (const std::string& repository,
		                       const std::string& name)
		{
			return name_space (RepositoryFactory::get (repository), name);
		}
		
		
		
		
		template <typename BaseType>
		ClassType& inherits ()
		{
			Converter* converter = new Converter (new ImplicitConverter <T*, BaseType*> ());
			mClass->addConverter (converter);
			return *this;
		}
		
		
		template <typename InputType>
		ClassType& converter ()
		{
			Converter* converter = new Converter (new ImplicitConverter <InputType, T> ());
			mClass->addConverter (converter);
			return *this;
		}
		
		
		
		
		/**
		 * Declare a class constructor.
		 */
		ClassType& constructor (Constructor* constructor)
		{
			mClass->addConstructor (constructor);
			return *this;
		}
		
		
		
		/**
		 * Declare a class constructor.
		 */
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType0 <T> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		template <typename Param1>
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType1 <T, Param1> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		template <typename Param1, typename Param2>
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType2 <T, Param1, Param2> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		template <typename Param1, typename Param2, typename Param3>
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType3 <T, Param1, Param2, Param3> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		template <typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType4 <T, Param1, Param2, Param3, Param4> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		template <typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& constructor ()
		{
			ConstructorType* type = new ConstructorType5 <T, Param1, Param2, Param3, Param4, Param5> ();
			mClass->addConstructor (new Constructor (type));
			return *this;
		}
		
		
		
		
		
		
		/**
		 * Declare a class function.
		 */
		ClassType& function (Function* function)
		{
			mClass->addFunction (function);
			return *this;
		}
		
		
		ClassType& function (const std::string& name, FunctionType* type)
		{
			return function (new Function (name, type));
		}
		
		
		
		
		/**
		 * Declare a pure virtual class function.
		 */
		ClassType& pure (Function* function)
		{
			if (!mClass->getVTable())
				mClass->setVTable (T::getVTable());
			
			mClass->addFunction (function);
			return *this;
		}
		
		
		ClassType& pure (const std::string& name, FunctionType* type)
		{
			return pure (new Function (name, type, Function::VIRTUAL |
			                                       Function::PURE));
		}
		
		
		
		
		/**
		 * Declare a class function.
		 */
		template <typename Class, typename ReturnType>
		ClassType& function (const std::string& name, ReturnType (Class::*func)())
		{
			return function (name, new MemberFunctionType0 <Class, ReturnType> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1))
		{
			return function (name, new MemberFunctionType1 <Class, ReturnType, Param1> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2))
		{
			return function (name, new MemberFunctionType2 <Class, ReturnType, Param1, Param2> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3))
		{
			return function (name, new MemberFunctionType3 <Class, ReturnType, Param1, Param2, Param3> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4))
		{
			return function (name, new MemberFunctionType4 <Class, ReturnType, Param1, Param2, Param3, Param4> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4, Param5))
		{
			return function (name, new MemberFunctionType5 <Class, ReturnType, Param1, Param2, Param3, Param4, Param5> (func));
		}
		
		
		
		
		
		template <typename Class, typename ReturnType>
		ClassType& function (const std::string& name, ReturnType (Class::*func)() const)
		{
			return function (name, new ConstMemberFunctionType0 <Class, ReturnType> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1) const)
		{
			return function (name, new ConstMemberFunctionType1 <Class, ReturnType, Param1> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2) const)
		{
			return function (name, new ConstMemberFunctionType2 <Class, ReturnType, Param1, Param2> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3) const)
		{
			return function (name, new ConstMemberFunctionType3 <Class, ReturnType, Param1, Param2, Param3> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4) const)
		{
			return function (name, new ConstMemberFunctionType4 <Class, ReturnType, Param1, Param2, Param3, Param4> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& function (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4, Param5) const)
		{
			return function (name, new ConstMemberFunctionType5 <Class, ReturnType, Param1, Param2, Param3, Param4, Param5> (func));
		}
		
		
		
		
		

		/**
		 * Declare a pure virtual class function.
		 */
		template <typename Class, typename ReturnType>
		ClassType& pure (const std::string& name, ReturnType (Class::*func)())
		{
			return pure (name, new MemberFunctionType0 <Class, ReturnType> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1))
		{
			return pure (name, new MemberFunctionType1 <Class, ReturnType, Param1> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2))
		{
			return pure (name, new MemberFunctionType2 <Class, ReturnType, Param1, Param2> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3))
		{
			return pure (name, new MemberFunctionType3 <Class, ReturnType, Param1, Param2, Param3> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4))
		{
			return pure (name, new MemberFunctionType4 <Class, ReturnType, Param1, Param2, Param3, Param4> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4, Param5))
		{
			return pure (name, new MemberFunctionType5 <Class, ReturnType, Param1, Param2, Param3, Param4, Param5> (func));
		}
		
		
		
		
		
		template <typename Class, typename ReturnType>
		ClassType& pure (const std::string& name, ReturnType (Class::*func)() const)
		{
			return pure (name, new ConstMemberFunctionType0 <Class, ReturnType> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1) const)
		{
			return pure (name, new ConstMemberFunctionType1 <Class, ReturnType, Param1> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2) const)
		{
			return pure (name, new ConstMemberFunctionType2 <Class, ReturnType, Param1, Param2> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3) const)
		{
			return pure (name, new ConstMemberFunctionType3 <Class, ReturnType, Param1, Param2, Param3> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4) const)
		{
			return pure (name, new ConstMemberFunctionType4 <Class, ReturnType, Param1, Param2, Param3, Param4> (func));
		}
		
		
		template <typename Class, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		ClassType& pure (const std::string& name, ReturnType (Class::*func) (Param1, Param2, Param3, Param4, Param5) const)
		{
			return pure (name, new ConstMemberFunctionType5 <Class, ReturnType, Param1, Param2, Param3, Param4, Param5> (func));
		}
		
		
		
		
		
		
//		template <typename ReturnType>
//		ClassType& function (const std::string& name,
//		                     const function_type<ReturnType>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
//		
//		
//		template <typename ReturnType,
//		          typename Param1>
//		ClassType& function (const std::string& name,
//		                     const Function<ReturnType,
//		                                    Param1>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
//		
//		
//		template <typename ReturnType,
//		          typename Param1,
//		          typename Param2>
//		ClassType& function (const std::string& name,
//		                     const Function<ReturnType,
//		                                    Param1,
//		                                    Param2>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
//		
//		
//		template <typename ReturnType,
//		          typename Param1,
//		          typename Param2,
//		          typename Param3>
//		ClassType& function (const std::string& name,
//		                     const Function<ReturnType,
//		                                    Param1,
//		                                    Param2,
//		                                    Param3>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
//		
//		
//		template <typename ReturnType,
//		          typename Param1,
//		          typename Param2,
//		          typename Param3,
//		          typename Param4>
//		ClassType& function (const std::string& name,
//		                     const Function<ReturnType,
//		                                    Param1,
//		                                    Param2,
//		                                    Param3,
//		                                    Param4>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
//		
//		
//		template <typename ReturnType,
//		          typename Param1,
//		          typename Param2,
//		          typename Param3,
//		          typename Param4,
//		          typename Param5>
//		ClassType& function (const std::string& name,
//		                     const Function<ReturnType,
//		                                    Param1,
//		                                    Param2,
//		                                    Param3,
//		                                    Param4,
//		                                    Param5>& function)
//		{
//			mClass->addFunction (new MemberFunction (name, function.type));
//			return *this;
//		}
		
		
		
	private:
		Class* mClass;
	};

}


#endif /* MYELIN_CLASS_TYPE_H_ */

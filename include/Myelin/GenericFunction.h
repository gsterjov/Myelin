
#ifndef MYELIN_GENERIC_FUNCTION_H_
#define MYELIN_GENERIC_FUNCTION_H_


#include <stdexcept>
#include <sstream>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Function.h>
#include <Myelin/Functor.h>


namespace Myelin
{

	class MYELIN_API GenericFunction : public Function
	{
	public:
		/**
		 * Constructor.
		 */
		template <typename ClassType, typename ReturnType>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)())
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor0<ClassType, ReturnType>(function))
		{
			
		}
		
		
		template <typename ClassType, typename ReturnType, typename Param1>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)(Param1))
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor1<ClassType, ReturnType, Param1>(function))
		{
			mParamTypes.push_back (TYPE(Param1));
		}
		
		
		template <typename ClassType, typename ReturnType, typename Param1, typename Param2>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)(Param1, Param2))
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor2<ClassType, ReturnType, Param1, Param2>(function))
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
		}
		
		
		template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)(Param1, Param2, Param3))
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor3<ClassType, ReturnType, Param1, Param2, Param3>(function))
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
		}
		
		
		template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)(Param1, Param2, Param3, Param4))
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor4<ClassType, ReturnType, Param1, Param2, Param3, Param4>(function))
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
		}
		
		
		template <typename ClassType, typename ReturnType, typename Param1, typename Param2, typename Param3, typename Param4, typename Param5>
		GenericFunction (const std::string& name, ReturnType (ClassType::*function)(Param1, Param2, Param3, Param4, Param5))
		: mName (name),
		  mReturnType (TYPE(ReturnType)),
		  mFunction (new MemberFunctor5<ClassType, ReturnType, Param1, Param2, Param3, Param4, Param5>(function))
		{
			mParamTypes.push_back (TYPE(Param1));
			mParamTypes.push_back (TYPE(Param2));
			mParamTypes.push_back (TYPE(Param3));
			mParamTypes.push_back (TYPE(Param4));
			mParamTypes.push_back (TYPE(Param5));
		}
		
		
		
		
		
		const std::string& getName() const { return mName; }
		
		const Type* getReturnType() const { return mReturnType; }
		
		int getParamCount() const { return mParamTypes.size(); }
		
		const Type* getParamType (int index) const { return mParamTypes[index]; }
		
		const TypeList getParamList () const { return mParamTypes; }
		
		
		
		Value call (void* object, const List& params) const
		{
			/* wrong number of parameters */
			if (params.size() < mParamTypes.size())
			{
				std::stringstream stream;
				stream << "The function '" + mName + "' takes exactly "
						<< mParamTypes.size() << " parameter(s) instead of "
						<< params.size() << ".";
				
				throw std::runtime_error (stream.str());
			}
			
			/* call function */
			return mFunction->call (object, params);
		}
		
		
		
	protected:
		std::string mName;
		const Type* mReturnType;
		TypeList mParamTypes;
		
		Functor* mFunction;
	};

}


#endif /* MYELIN_GENERIC_FUNCTION_H_ */

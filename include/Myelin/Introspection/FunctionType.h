
#ifndef MYELIN_INTROSPECTION_MEMBER_FUNCTION_H_
#define MYELIN_INTROSPECTION_MEMBER_FUNCTION_H_


#include "Function.h"
#include "Types/ClassType.h"
#include "Types/FunctionType.h"


namespace Myelin {
namespace Introspection {


	/* wrap function type virtuals */
	class FunctionTypeWrapper : public FunctionType,
								public Overridable <FunctionTypeWrapper>
	{
	public:
		Value call (const List& params) const
		{
			List list;
			list.push_back (params);
			
			get("call")->call (list);
		}
	};
	
	
	/**
	 * Create function introspection type.
	 */
	void create_function_type ()
	{
		ClassType<Function>::create ("Function")
			.name_space ("Myelin", "")
			.constructor <const std::string&, FunctionType*> ()
			
			.function ("getName", &Function::getName)
			.function ("getType", &Function::getType)
			.function ("call",    &Function::call)
			.function ("bind",    &Function::bind);
		
		
		ClassType<FunctionTypeWrapper>::create ("FunctionType")
			.name_space ("Myelin", "")
			.function ("getReturnType",   &FunctionType::getReturnType)
			.function ("getParamType",    &FunctionType::getParamType)
			.function ("getParamTypes",   &FunctionType::getParamTypes)
			.function ("getParamCount",   &FunctionType::getParamCount)
			.function ("checkParamTypes", &FunctionType::checkParamTypes)
			.function ("setInstance",     &FunctionType::setInstance)
			.pure     ("call",            &FunctionType::call);
	}

}}


#endif /* MYELIN_INTROSPECTION_MEMBER_FUNCTION_H_ */

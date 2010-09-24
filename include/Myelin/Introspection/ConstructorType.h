
#ifndef MYELIN_INTROSPECTION_CONSTRUCTOR_H_
#define MYELIN_INTROSPECTION_CONSTRUCTOR_H_


#include "Constructor.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create constructor introspection type.
	 */
	void create_constructor_type ()
	{
		ClassType<Constructor>::create ("Constructor")
			.name_space ("Myelin", "")
			.constructor <const ConstructorType*> ()
			
			.function ("getParamCount", &Constructor::getParamCount)
			.function ("getParaType",   &Constructor::getParamType)
			.function ("getParamTypes", &Constructor::getParamTypes)
			.function ("call",          &Constructor::call);
	}

}}


#endif /* MYELIN_INTROSPECTION_CONSTRUCTOR_H_ */

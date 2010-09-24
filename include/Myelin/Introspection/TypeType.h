
#ifndef MYELIN_INTROSPECTION_TYPE_H_
#define MYELIN_INTROSPECTION_TYPE_H_


#include "Type.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create type introspection type.
	 */
	void create_type_type ()
	{
		/* TODO: Nested classes */
		
		ClassType<Type>::create ("Type")
			.name_space ("Myelin", "")
			
			.function ("getAtom",     &Type::getAtom)
			.function ("getTraits",   &Type::getTraits)
			
			.function ("isConstant",  &Type::isConstant)
			.function ("isReference", &Type::isReference)
			.function ("isPointer",   &Type::isPointer)
			.function ("isVolatile",  &Type::isVolatile)
			
			.function ("equals",      &Type::equals);
	}

}}


#endif /* MYELIN_INTROSPECTION_TYPE_H_ */

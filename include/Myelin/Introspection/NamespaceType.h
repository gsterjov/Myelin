
#ifndef MYELIN_INTROSPECTION_NAMESPACE_H_
#define MYELIN_INTROSPECTION_NAMESPACE_H_


#include "Namespace.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create namespace introspection type.
	 */
	void create_namespace_type ()
	{
		ClassType<Namespace>::create ("Namespace")
			.name_space ("Myelin", "")
			.constructor <const std::string&> ()
			
			.function ("getname",    &Namespace::getName)
			.function ("addClass",   &Namespace::addClass)
			.function ("getClass",   &Namespace::getClass)
			.function ("getClasses", &Namespace::getClasses);
	}

}}


#endif /* MYELIN_INTROSPECTION_NAMESPACE_H_ */

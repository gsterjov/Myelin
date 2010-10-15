
#ifndef MYELIN_INTROSPECTION_OBJECT_H_
#define MYELIN_INTROSPECTION_OBJECT_H_


#include "Object.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create object introspection type.
	 */
	void create_object_type ()
	{
		ClassType<Object>::create ("Object")
			.name_space ("Myelin", "")
			.constructor ()
			.constructor <const Class*> ()
			
			.function ("setClass",    &Object::setClass)
			.function ("getClass",    &Object::getClass)
			.function ("setInstance", &Object::setInstance)
			.function ("getInstance", &Object::getInstance)
			
			.function <Object, Value, const std::string&, const List&> ("call", &Object::call);
	}

}}


#endif /* MYELIN_INTROSPECTION_OBJECT_H_ */

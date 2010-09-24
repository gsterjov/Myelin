
#ifndef MYELIN_INTROSPECTION_CLASS_H_
#define MYELIN_INTROSPECTION_CLASS_H_


#include "Class.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create class introspection type.
	 */
	void create_class_type ()
	{
		ClassType<Class>::create ("Class")
			.name_space ("Myelin", "")
			.constructor <const std::string&> ()
			
			.function ("getName",         &Class::getName)
			.function ("addConstructor",  &Class::addConstructor)
			.function ("getConstructors", &Class::getConstructors)
			.function ("addFunction",     &Class::addFunction)
			.function ("createInstance",  &Class::createInstance)
			
//			.function ("getFunctions", function_type<FunctionList() const> (&Class::getFunctions))
//			.function <FunctionList, const std::string&> ("getFunctions", &Class::getFunctions)
			
			.function ("createObject", &Class::createObject);
	}

}}


#endif /* MYELIN_INTROSPECTION_CLASS_H_ */

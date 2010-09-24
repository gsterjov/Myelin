
#ifndef MYELIN_INTROSPECTION_REPOSITORY_H_
#define MYELIN_INTROSPECTION_REPOSITORY_H_


#include "Repository.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create repository introspection type.
	 */
	void create_repository_type ()
	{
		ClassType<Repository>::create ("Repository")
			.name_space ("Myelin", "")
			.constructor <const std::string&> ()
			
			.function ("getName",       &Repository::getName)
			.function ("addNamespace",  &Repository::addNamespace)
			.function ("getNamespace",  &Repository::getNamespace)
			.function ("getNamespaces", &Repository::getNamespaces);
	}

}}


#endif /* MYELIN_INTROSPECTION_REPOSITORY_H_ */

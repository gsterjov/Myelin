
#ifndef MYELIN_INTROSPECTION_REPOSITORY_FACTORY_H_
#define MYELIN_INTROSPECTION_REPOSITORY_FACTORY_H_


#include "RepositoryFactory.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create repository factory introspection type.
	 */
	void create_repository_factory_type ()
	{
		/* TODO: Static and free functions */
		
		ClassType<RepositoryFactory>::create ("RepositoryFactory")
			.name_space ("Myelin", "");
	}

}}


#endif /* MYELIN_INTROSPECTION_REPOSITORY_FACTORY_H_ */

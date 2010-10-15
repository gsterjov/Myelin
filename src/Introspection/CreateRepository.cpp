

#include "Introspection/ClassType.h"
#include "Introspection/ConstructorType.h"
#include "Introspection/ListType.h"
#include "Introspection/FunctionType.h"
#include "Introspection/NamespaceType.h"
#include "Introspection/ObjectType.h"
#include "Introspection/RepositoryFactoryType.h"
#include "Introspection/RepositoryType.h"
#include "Introspection/TypeType.h"
#include "Introspection/ValueType.h"


extern "C"
{
	MYELIN_API void create_repository ()
	{
		using namespace Myelin;
		using namespace Introspection;
		
		/* create repository */
		RepositoryFactory::create ("Myelin");
		
		/* create class types */
		create_class_type();
		create_constructor_type();
		create_list_type();
		create_function_type();
		create_namespace_type();
		create_object_type();
		create_repository_factory_type();
		create_repository_type();
		create_type_type();
		create_value_type();
	}
}

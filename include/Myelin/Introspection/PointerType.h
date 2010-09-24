
#ifndef MYELIN_INTROSPECTION_POINTER_H_
#define MYELIN_INTROSPECTION_POINTER_H_


#include "Pointer.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create pointer introspection type.
	 */
	void create_pointer_type ()
	{
		ClassType<Pointer>::create ("Pointer")
			.name_space ("Myelin", "")
			.constructor ()
			.constructor <void*, const Type*> ()
			
			.function ("getType", &Pointer::getType)
			.function ("isEmpty", &Pointer::isEmpty)
			.function ("clear",   &Pointer::clear)
			.function ("getRaw",  &Pointer::getRaw)
			
			.function <Pointer, void, void*, const Type*> ("set", &Pointer::set);
	}

}}


#endif /* MYELIN_INTROSPECTION_POINTER_H_ */

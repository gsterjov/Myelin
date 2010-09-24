
#ifndef MYELIN_INTROSPECTION_VALUE_H_
#define MYELIN_INTROSPECTION_VALUE_H_


#include "Value.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create value introspection type.
	 */
	void create_value_type ()
	{
		ClassType<Value>::create ("Value")
			.name_space ("Myelin", "")
			.constructor ()
			
			.function ("getType",    &Value::getType)
			.function ("isEmpty",    &Value::isEmpty)
			.function ("clear",      &Value::clear)
			.function ("getPointer", &Value::getPointer);
	}

}}


#endif /* MYELIN_INTROSPECTION_VALUE_H_ */

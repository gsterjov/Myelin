
#ifndef MYELIN_INTROSPECTION_LIST_H_
#define MYELIN_INTROSPECTION_LIST_H_


#include "List.h"
#include "Types/ClassType.h"


namespace Myelin {
namespace Introspection {

	/**
	 * Create list introspection type.
	 */
	void create_list_type ()
	{
		ClassType<List>::create ("List")
			.name_space ("Myelin", "")
			.constructor ()
			
			.function <List, List::iterator>       ("begin", &List::begin)
			.function <List, List::const_iterator> ("begin", &List::begin)
			.function <List, List::iterator>       ("end", &List::end)
			.function <List, List::const_iterator> ("end", &List::end)
			
			.function <List, List::reverse_iterator>       ("rbegin", &List::rbegin)
			.function <List, List::const_reverse_iterator> ("rbegin", &List::rbegin)
			.function <List, List::reverse_iterator>       ("rend", &List::rend)
			.function <List, List::const_reverse_iterator> ("rend", &List::rend)
			
			.function <List, void, const Value&> ("push_back", &List::push_back)
			.function ("pop_back", &List::pop_back)
			
			.function <List, List::iterator, List::iterator, const Value&> ("insert", &List::insert)
			.function <List, void, List::iterator, uint, const Value&>     ("insert", &List::insert)
			
			.function ("erase", static_cast<List::iterator (List::*)(List::iterator)> (&List::erase))
			.function ("erase", static_cast<List::iterator (List::*)(List::iterator, List::iterator)> (&List::erase))
			
			.function ("clear", &List::clear)
			.function ("size",  &List::size)
			.function ("empty", &List::empty)
			
			.function ("front", static_cast<      Value& (List::*)()>       (&List::front))
			.function ("front", static_cast<const Value& (List::*)() const> (&List::front))
			
			.function ("back", static_cast<      Value& (List::*)()>       (&List::back))
			.function ("back", static_cast<const Value& (List::*)() const> (&List::back))
			
			.function ("at", static_cast<      Value& (List::*)(uint)>       (&List::at))
			.function ("at", static_cast<const Value& (List::*)(uint) const> (&List::at))
			
			.function ("operator[]", static_cast<      Value& (List::*)(uint)>       (&List::operator[]))
			.function ("operator[]", static_cast<const Value& (List::*)(uint) const> (&List::operator[]));
	}

}}


#endif /* MYELIN_INTROSPECTION_LIST_H_ */



#include "Type.h"
#include "Class.h"
#include "Converter.h"
#include <iostream>

namespace Myelin
{

	/* type atom constructor */
	Type::Atom::Atom (const Class* klass)
	: mName (klass->getName()),
	  mClass (klass)
	{}
	
	
	/* set atom class */
	void Type::Atom::setClass (const Class* klass)
	{
		mName = klass->getName();
		mClass = klass;
	}
	
	
	
	
	/* is type compatible */
	bool Type::compatible (const Type* type) const
	{
		/* perfect match */
		if (equals (type))
			return true;
		
		/* integral types match */
		else if (getAtom() == type->getAtom())
		{
			/* check for value/pointer to reference conversion */
			if (type->isReference())
			{
				/* upgrade to const */
				if (!isConstant() && type->isConstant()) return true;
				else return isConstant() == type->isConstant();
			}
			
			/* upgrade to const if necessary */
			else return (getTraits().getFlags() | Traits::Constant) == type->getTraits().getFlags();
		}
		
		return false;
	}
	
	
	
	/* find type converter */
	const Converter* Type::findConverter (const Type* outputType) const
	{
		const Class* klass = getAtom()->getClass();
		
		/* check if type can be converted */
		if (klass != 0)
		{
			ConverterList list = klass->getConverters();
			ConverterList::iterator iter;
			
			/* look for compatible type */
			for (iter = list.begin(); iter != list.end(); ++iter)
			{
				Converter* converter = *iter;
				
				/* type can be converted */
				if (equals (converter->getInputType()))
					return converter;
			}
			
		}
		
		return 0;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Type::Traits *
myelin_type_traits_new ()
{
	return new Myelin::Type::Traits();
}


Myelin::Type::Traits *
myelin_type_traits_ref (Myelin::Type::Traits *traits)
{
	traits->ref();
	return traits;
}

void
myelin_type_traits_unref (Myelin::Type::Traits *traits)
{
	traits->unref();
	if (traits->count() == 0) delete traits;
}


void myelin_type_traits_add_constant  (Myelin::Type::Traits *traits) { traits->add_constant(); }
void myelin_type_traits_add_reference (Myelin::Type::Traits *traits) { traits->add_reference(); }
void myelin_type_traits_add_pointer   (Myelin::Type::Traits *traits) { traits->add_pointer(); }
void myelin_type_traits_add_volatile  (Myelin::Type::Traits *traits) { traits->add_volatile(); }

bool myelin_type_traits_is_constant  (Myelin::Type::Traits *traits) { return traits->is_constant(); }
bool myelin_type_traits_is_reference (Myelin::Type::Traits *traits) { return traits->is_reference(); }
bool myelin_type_traits_is_pointer   (Myelin::Type::Traits *traits) { return traits->is_pointer(); }
bool myelin_type_traits_is_volatile  (Myelin::Type::Traits *traits) { return traits->is_volatile(); }



Myelin::Type *
myelin_type_ref (Myelin::Type *type)
{
	type->ref();
	return type;
}


void
myelin_type_unref (Myelin::Type *type)
{
	type->unref();
	if (type->count() == 0) delete type;
}



const char *myelin_type_get_name (const Myelin::Type *type)
{
	return type->getName().c_str();
}


const char *myelin_type_atom_get_name (const Myelin::Type::Atom *atom)
{
	return atom->getName().c_str();
}


const Myelin::Type::Atom *
myelin_type_get_atom (const Myelin::Type *type)
{
	return type->getAtom();
}


const Myelin::Type::Traits *
myelin_type_get_traits (const Myelin::Type *type)
{
	return &type->getTraits();
}


bool
myelin_type_equals (const Myelin::Type *lhs, const Myelin::Type *rhs)
{
	return lhs->equals (rhs);
}



bool myelin_type_is_constant  (const Myelin::Type *type) { return type->isConstant(); }
bool myelin_type_is_reference (const Myelin::Type *type) { return type->isReference(); }
bool myelin_type_is_pointer   (const Myelin::Type *type) { return type->isPointer(); }
bool myelin_type_is_volatile  (const Myelin::Type *type) { return type->isVolatile(); }


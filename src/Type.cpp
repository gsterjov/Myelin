

#include "Type.h"
#include "Class.h"
#include "Converter.h"
#include "Types/ConverterType.h"



namespace Myelin {

	/* type atom constructor */
	Type::Atom::Atom (const Class* klass)
	: mName (klass->getName()),
	  mClass (klass)
	{}
	


namespace Types {

	/* fundamental types */
	const Type::Atom* void_t    = 0;
	const Type::Atom* bool_t    = 0;
	const Type::Atom* char_t    = 0;
	const Type::Atom* uchar_t   = 0;
	const Type::Atom* int_t     = 0;
	const Type::Atom* uint_t    = 0;
	const Type::Atom* long_t    = 0;
	const Type::Atom* ulong_t   = 0;
	const Type::Atom* int64_t   = 0;
	const Type::Atom* uint64_t  = 0;
	const Type::Atom* float_t   = 0;
	const Type::Atom* double_t  = 0;
	const Type::Atom* pointer_t = 0;
	
	const Type::Atom* string_t = 0;
	
	
	
	/* initialise fundamental types */
	void init_types ()
	{
		static bool initialised = false;
		if (initialised) return;
		
		
		void_t    = new Type::Atom ("void");
		bool_t    = new Type::Atom ("bool");
		char_t    = new Type::Atom ("char");
		uchar_t   = new Type::Atom ("uchar");
		int_t     = new Type::Atom ("int");
		uint_t    = new Type::Atom ("uint");
		long_t    = new Type::Atom ("long");
		ulong_t   = new Type::Atom ("ulong");
		int64_t   = new Type::Atom ("int64");
		uint64_t  = new Type::Atom ("uint64");
		float_t   = new Type::Atom ("float");
		double_t  = new Type::Atom ("double");
		pointer_t = new Type::Atom ("Myelin::Pointer");
		
		
		Class* string_class = new Class ("std::string");
		
		Converter* converter = new Converter (new ImplicitConverter<const char*, std::string>());
		string_class->addConverter (converter);
		
		string_t = new Type::Atom (string_class);
		
		
		initialised = true;
	}


}}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
void myelin_type_init () { Myelin::Types::init_types(); }



Myelin::Type::Traits * myelin_type_traits_new () { return new Myelin::Type::Traits(); }


Myelin::Type::Traits *myelin_type_traits_ref (Myelin::Type::Traits *traits) { traits->ref(); return traits; }
void myelin_type_traits_unref (Myelin::Type::Traits *traits) { traits->unref(); }


void myelin_type_traits_add_constant  (Myelin::Type::Traits *traits) { traits->add_constant(); }
void myelin_type_traits_add_reference (Myelin::Type::Traits *traits) { traits->add_reference(); }
void myelin_type_traits_add_pointer   (Myelin::Type::Traits *traits) { traits->add_pointer(); }
void myelin_type_traits_add_volatile  (Myelin::Type::Traits *traits) { traits->add_volatile(); }

bool myelin_type_traits_is_constant  (Myelin::Type::Traits *traits) { return traits->is_constant(); }
bool myelin_type_traits_is_reference (Myelin::Type::Traits *traits) { return traits->is_reference(); }
bool myelin_type_traits_is_pointer   (Myelin::Type::Traits *traits) { return traits->is_pointer(); }
bool myelin_type_traits_is_volatile  (Myelin::Type::Traits *traits) { return traits->is_volatile(); }


const Myelin::Type*
myelin_type_new (const Myelin::Type::Atom *atom,
                 const Myelin::Type::Traits *traits)
{
	return new Myelin::Types::CustomType (atom, *traits);
}


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


const Myelin::Type::Atom *myelin_type_bool ()    { return Myelin::Types::bool_t; }
const Myelin::Type::Atom *myelin_type_char ()    { return Myelin::Types::char_t; }
const Myelin::Type::Atom *myelin_type_uchar ()   { return Myelin::Types::uchar_t; }
const Myelin::Type::Atom *myelin_type_int ()     { return Myelin::Types::int_t; }
const Myelin::Type::Atom *myelin_type_uint ()    { return Myelin::Types::uint_t; }
const Myelin::Type::Atom *myelin_type_long ()    { return Myelin::Types::long_t; }
const Myelin::Type::Atom *myelin_type_ulong ()   { return Myelin::Types::ulong_t; }
const Myelin::Type::Atom *myelin_type_int64 ()   { return Myelin::Types::int64_t; }
const Myelin::Type::Atom *myelin_type_uint64 ()  { return Myelin::Types::uint64_t; }
const Myelin::Type::Atom *myelin_type_float ()   { return Myelin::Types::float_t; }
const Myelin::Type::Atom *myelin_type_double ()  { return Myelin::Types::double_t; }
const Myelin::Type::Atom *myelin_type_pointer () { return Myelin::Types::pointer_t; }

const Myelin::Type::Atom *myelin_type_string () { return Myelin::Types::string_t; }

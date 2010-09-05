

#include "Type.h"



namespace Myelin {
namespace Types {

	/* fundamental types */
	MYELIN_API const Type::Atom* void_t    = 0;
	MYELIN_API const Type::Atom* bool_t    = 0;
	MYELIN_API const Type::Atom* char_t    = 0;
	MYELIN_API const Type::Atom* uchar_t   = 0;
	MYELIN_API const Type::Atom* int_t     = 0;
	MYELIN_API const Type::Atom* uint_t    = 0;
	MYELIN_API const Type::Atom* long_t    = 0;
	MYELIN_API const Type::Atom* ulong_t   = 0;
	MYELIN_API const Type::Atom* int64_t   = 0;
	MYELIN_API const Type::Atom* uint64_t  = 0;
	MYELIN_API const Type::Atom* float_t   = 0;
	MYELIN_API const Type::Atom* double_t  = 0;
	MYELIN_API const Type::Atom* string_t  = 0;
	MYELIN_API const Type::Atom* pointer_t = 0;
	
	
	
	/* initialise fundamental types */
	MYELIN_API void init_types ()
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
		string_t  = new Type::Atom ("const char*");
		pointer_t = new Type::Atom ("void*");
		
		
		initialised = true;
	}


}}





/* C api */
MYELIN_API void myelin_type_init () { Myelin::Types::init_types(); }


MYELIN_API const char *myelin_type_get_name (const Myelin::Type *type)
{
	return type->getName().c_str();
}


MYELIN_API const char *myelin_type_atom_get_name (const Myelin::Type::Atom *atom)
{
	return atom->getName().c_str();
}


MYELIN_API const Myelin::Type::Atom *
myelin_type_get_atom (const Myelin::Type *type)
{
	return type->getAtom();
}


MYELIN_API Myelin::Type::TraitFlags
myelin_type_get_traits (const Myelin::Type *type)
{
	return type->getTraits();
}


MYELIN_API bool
myelin_type_equals (const Myelin::Type *lhs, const Myelin::Type *rhs)
{
	return lhs->equals (rhs);
}



MYELIN_API bool myelin_type_is_constant  (const Myelin::Type *type) { return type->isConstant(); }
MYELIN_API bool myelin_type_is_reference (const Myelin::Type *type) { return type->isReference(); }
MYELIN_API bool myelin_type_is_pointer   (const Myelin::Type *type) { return type->isPointer(); }
MYELIN_API bool myelin_type_is_volatile  (const Myelin::Type *type) { return type->isVolatile(); }


MYELIN_API const Myelin::Type::Atom *myelin_type_bool ()    { return Myelin::Types::bool_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_char ()    { return Myelin::Types::char_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_uchar ()   { return Myelin::Types::uchar_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_int ()     { return Myelin::Types::int_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_uint ()    { return Myelin::Types::uint_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_long ()    { return Myelin::Types::long_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_ulong ()   { return Myelin::Types::ulong_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_int64 ()   { return Myelin::Types::int64_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_uint64 ()  { return Myelin::Types::uint64_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_float ()   { return Myelin::Types::float_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_double ()  { return Myelin::Types::double_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_string ()  { return Myelin::Types::string_t; }
MYELIN_API const Myelin::Type::Atom *myelin_type_pointer () { return Myelin::Types::pointer_t; }



#include "TypeUtils.h"
#include "Class.h"
#include "Converter.h"
#include "Types/ConverterType.h"


namespace Myelin
{

	/* fundamental types */
	Type::Atom* void_t    = 0;
	Type::Atom* bool_t    = 0;
	Type::Atom* char_t    = 0;
	Type::Atom* uchar_t   = 0;
	Type::Atom* int_t     = 0;
	Type::Atom* uint_t    = 0;
	Type::Atom* long_t    = 0;
	Type::Atom* ulong_t   = 0;
	Type::Atom* int64_t   = 0;
	Type::Atom* uint64_t  = 0;
	Type::Atom* float_t   = 0;
	Type::Atom* double_t  = 0;
	
	Type::Atom* string_t = 0;
	
	
	
	/* initialise fundamental types */
	bool init_types ()
	{
		static bool initialised = false;
		if (initialised) return true;
		
		
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
		
		
		Class* string_class = new Class ("std::string");
		
		Converter* converter = new Converter (new ImplicitConverter<const char*, std::string>());
		string_class->addConverter (converter);
		
		string_t = new Type::Atom (string_class);
		
		
		initialised = true;
		return true;
	}


}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
bool myelin_type_init () { return Myelin::init_types(); }



const Myelin::Type*
myelin_type_new (const Myelin::Type::Atom *atom,
                 const Myelin::Type::Traits *traits)
{
	return new Myelin::CustomType (atom, *traits);
}



const Myelin::Type::Atom *myelin_type_bool ()    { return Myelin::bool_t; }
const Myelin::Type::Atom *myelin_type_char ()    { return Myelin::char_t; }
const Myelin::Type::Atom *myelin_type_uchar ()   { return Myelin::uchar_t; }
const Myelin::Type::Atom *myelin_type_int ()     { return Myelin::int_t; }
const Myelin::Type::Atom *myelin_type_uint ()    { return Myelin::uint_t; }
const Myelin::Type::Atom *myelin_type_long ()    { return Myelin::long_t; }
const Myelin::Type::Atom *myelin_type_ulong ()   { return Myelin::ulong_t; }
const Myelin::Type::Atom *myelin_type_int64 ()   { return Myelin::int64_t; }
const Myelin::Type::Atom *myelin_type_uint64 ()  { return Myelin::uint64_t; }
const Myelin::Type::Atom *myelin_type_float ()   { return Myelin::float_t; }
const Myelin::Type::Atom *myelin_type_double ()  { return Myelin::double_t; }

const Myelin::Type::Atom *myelin_type_string () { return Myelin::string_t; }


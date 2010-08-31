

#include "Type.h"



namespace Myelin {
namespace Types {


	namespace
	{
		MYELIN_API const Type* void_t    = 0;
		MYELIN_API const Type* bool_t    = 0;
		MYELIN_API const Type* char_t    = 0;
		MYELIN_API const Type* uchar_t   = 0;
		MYELIN_API const Type* int_t     = 0;
		MYELIN_API const Type* uint_t    = 0;
		MYELIN_API const Type* long_t    = 0;
		MYELIN_API const Type* ulong_t   = 0;
		MYELIN_API const Type* int64_t   = 0;
		MYELIN_API const Type* uint64_t  = 0;
		MYELIN_API const Type* float_t   = 0;
		MYELIN_API const Type* double_t  = 0;
		MYELIN_API const Type* string_t  = 0;
		MYELIN_API const Type* pointer_t = 0;
	}
	
	
	
	MYELIN_API const Type* void_type() { return void_t; }
	MYELIN_API const Type* bool_type() { return bool_t; }
	MYELIN_API const Type* char_type() { return char_t; }
	MYELIN_API const Type* uchar_type() { return uchar_t; }
	MYELIN_API const Type* int_type() { return int_t; }
	MYELIN_API const Type* uint_type() { return uint_t; }
	MYELIN_API const Type* long_type() { return long_t; }
	MYELIN_API const Type* ulong_type() { return ulong_t; }
	MYELIN_API const Type* int64_type() { return int64_t; }
	MYELIN_API const Type* uint64_type() { return uint64_t; }
	MYELIN_API const Type* float_type() { return float_t; }
	MYELIN_API const Type* double_type() { return double_t; }
	MYELIN_API const Type* string_type() { return string_t; }
	MYELIN_API const Type* pointer_type() { return pointer_t; }
	
	
	
	MYELIN_API void init_types ()
	{
		static bool initialised = false;
		if (initialised) return;
		
		
		void_t    = new Type ("void");
		bool_t    = new Type ("bool");
		char_t    = new Type ("char");
		uchar_t   = new Type ("uchar");
		int_t     = new Type ("int");
		uint_t    = new Type ("uint");
		long_t    = new Type ("long");
		ulong_t   = new Type ("ulong");
		int64_t   = new Type ("int64");
		uint64_t  = new Type ("uint64");
		float_t   = new Type ("float");
		double_t  = new Type ("double");
		string_t  = new Type ("const char*");
		pointer_t = new Type ("void*");
		
		
		initialised = true;
	}


}}





/* C api */
MYELIN_API void myelin_type_init () { Myelin::Types::init_types(); }
MYELIN_API const char *myelin_type_get_name (const Myelin::Type *type) { return type->getName().c_str(); }

MYELIN_API const Myelin::Type *myelin_type_bool ()    { return Myelin::Types::bool_t; }
MYELIN_API const Myelin::Type *myelin_type_char ()    { return Myelin::Types::char_t; }
MYELIN_API const Myelin::Type *myelin_type_uchar ()   { return Myelin::Types::uchar_t; }
MYELIN_API const Myelin::Type *myelin_type_int ()     { return Myelin::Types::int_t; }
MYELIN_API const Myelin::Type *myelin_type_uint ()    { return Myelin::Types::uint_t; }
MYELIN_API const Myelin::Type *myelin_type_long ()    { return Myelin::Types::long_t; }
MYELIN_API const Myelin::Type *myelin_type_ulong ()   { return Myelin::Types::ulong_t; }
MYELIN_API const Myelin::Type *myelin_type_int64 ()   { return Myelin::Types::int64_t; }
MYELIN_API const Myelin::Type *myelin_type_uint64 ()  { return Myelin::Types::uint64_t; }
MYELIN_API const Myelin::Type *myelin_type_float ()   { return Myelin::Types::float_t; }
MYELIN_API const Myelin::Type *myelin_type_double ()  { return Myelin::Types::double_t; }
MYELIN_API const Myelin::Type *myelin_type_string ()  { return Myelin::Types::string_t; }
MYELIN_API const Myelin::Type *myelin_type_pointer () { return Myelin::Types::pointer_t; }

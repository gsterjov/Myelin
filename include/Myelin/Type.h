
#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <typeinfo>
#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <iostream>


typedef long long int64;

/* unsigned numbers */
typedef unsigned char  uchar;
typedef unsigned short ushort;
typedef unsigned int   uint;
typedef unsigned long  ulong;
typedef unsigned long long  uint64;



namespace Myelin
{

	/**
	 * Convenience macro to register a type and its pointer type.
	 */
	#define REGISTER_TYPE(type,name) \
		Types::register_type<type>(name); \
		Types::register_type<type*>(name + "*")
	
	
	/**
	 * Convenience macro to get types.
	 */
	#define TYPE(type) Types::get_type<type>()
	
	
	/**
	 * Information on a specific type.
	 */
	struct MYELIN_API Type
	{
		Type (const std::string& name) : name(name) {}
		const std::string getName() const { return name; }
		
	private:
		const std::string name;
	};
	
	
	/**
	 * A list of types.
	 */
	typedef std::vector<const Type*> TypeList;
	
	
	
	namespace Types
	{
	
		/**
		 * Initaite fundamental types.
		 */
		void init_types ();
		
		
		
		/**
		 * Register type information.
		 */
		template <typename T>
		const Type* register_type (const std::string& name = "")
		{
			/* static type info */
			static const Type* info = 0;
			
			
			/* type info hasn't been created yet */
			if (info == 0)
			{
				/* generate name */
				if (name.empty())
					info = new Type (typeid(T).name());
				
				/* use given name */
				else info = new Type (name);
			}
			
			return info;
		}
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		const Type* get_type ()
		{
			return register_type<T>();
		}
		
		
		
		/* fundamental types */
		extern MYELIN_API const Type* void_type();
		extern MYELIN_API const Type* bool_type();
		extern MYELIN_API const Type* char_type();
		extern MYELIN_API const Type* uchar_type();
		extern MYELIN_API const Type* int_type();
		extern MYELIN_API const Type* uint_type();
		extern MYELIN_API const Type* long_type();
		extern MYELIN_API const Type* ulong_type();
		extern MYELIN_API const Type* int64_type();
		extern MYELIN_API const Type* uint64_type();
		extern MYELIN_API const Type* float_type();
		extern MYELIN_API const Type* double_type();
		extern MYELIN_API const Type* string_type();
		extern MYELIN_API const Type* pointer_type();
		
		
		
		/* specialised types */
		template<> inline const Type* get_type<void>   () { return void_type(); }
		template<> inline const Type* get_type<bool>   () { return bool_type(); }
		template<> inline const Type* get_type<char>   () { return char_type(); }
		template<> inline const Type* get_type<uchar>  () { return uchar_type(); }
		template<> inline const Type* get_type<int>    () { return int_type(); }
		template<> inline const Type* get_type<uint>   () { return uint_type(); }
		template<> inline const Type* get_type<long>   () { return long_type(); }
		template<> inline const Type* get_type<ulong>  () { return ulong_type(); }
		template<> inline const Type* get_type<int64>  () { return int64_type(); }
		template<> inline const Type* get_type<uint64> () { return uint64_type(); }
		template<> inline const Type* get_type<float>  () { return float_type(); }
		template<> inline const Type* get_type<double> () { return double_type(); }
		template<> inline const Type* get_type<void*>  () { return pointer_type(); }
		template<> inline const Type* get_type<const char*> () { return string_type(); }
	}

}





/* C api */
extern "C"
{

	MYELIN_API void myelin_type_init ();
	MYELIN_API const char *myelin_type_get_name (const Myelin::Type *type);
	
	MYELIN_API const Myelin::Type *myelin_type_bool ();
	MYELIN_API const Myelin::Type *myelin_type_char ();
	MYELIN_API const Myelin::Type *myelin_type_uchar ();
	MYELIN_API const Myelin::Type *myelin_type_int ();
	MYELIN_API const Myelin::Type *myelin_type_uint ();
	MYELIN_API const Myelin::Type *myelin_type_long ();
	MYELIN_API const Myelin::Type *myelin_type_ulong ();
	MYELIN_API const Myelin::Type *myelin_type_int64 ();
	MYELIN_API const Myelin::Type *myelin_type_uint64 ();
	MYELIN_API const Myelin::Type *myelin_type_float ();
	MYELIN_API const Myelin::Type *myelin_type_double ();
	MYELIN_API const Myelin::Type *myelin_type_string ();
	MYELIN_API const Myelin::Type *myelin_type_pointer ();

}






#endif /* MYELIN_TYPE_H_ */

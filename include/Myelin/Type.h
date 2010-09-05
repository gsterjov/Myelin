
#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <typeinfo>
#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/TypeTraits.h>
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
	#define REGISTER_TYPE(type,name) Types::register_type<type>(name)
	
	
	/**
	 * Convenience macro to get types.
	 */
	#define TYPE(type) Types::get_type<type>()
	
	
	
	/**
	 * A list of types.
	 */
	class Type; typedef std::vector<const Type*> TypeList;
	
	
	

	/**
	 * Core type data. Used to identify types ignoring qualifiers.
	 */
	struct MYELIN_API Type
	{
		/**
		 * The raw type.
		 */
		struct MYELIN_API Atom
		{
			explicit Atom (const std::string& name) : mName(name) {}
			const std::string getName() const { return mName; }
			
		private:
			const std::string mName;
		};
		
		
		
		/**
		 * Qualifier types.
		 */
		enum Trait { Constant = 1<<0, Reference = 1<<1, Pointer = 1<<2, Volatile = 1<<3 };
		typedef int TraitFlags;
		
		
		const std::string getName() const
		{
			std::string name = getAtom()->getName();
			TraitFlags traits = getTraits();
			
			if (traits & Volatile)  name = "volatile " + name;
			if (traits & Constant)  name = "const " + name;
			if (traits & Reference) name = name + "&";
			if (traits & Pointer)   name = name + "*";
			
			return name;
		}
		
		
		virtual const Atom* getAtom() const = 0;
		virtual TraitFlags getTraits() const = 0;
		
		
		bool isConstant()  const { return getTraits() & Constant; }
		bool isReference() const { return getTraits() & Reference; }
		bool isPointer()   const { return getTraits() & Pointer; }
		bool isVolatile()  const { return getTraits() & Volatile; }
		
		
		bool equals (const Type* info) const
		{
			return getAtom() == info->getAtom() &&
			       getTraits() == info->getTraits();
		}
		
		
		/* equality comparison operator */
		friend bool operator== (const Type& lhs, const Type& rhs) { return lhs.equals (&rhs); }
		friend bool operator!= (const Type& lhs, const Type& rhs) { return !(lhs == rhs); }
	};
	
	
	
	
	namespace Types
	{
		/**
		 * Initiate fundamental types.
		 */
		void init_types ();
		
		
		
		
		/**
		 * Used by generic types to access a single type across classes.
		 */
		template <typename RawType> struct StaticType { static const Type::Atom* atom; };
		template <typename RawType> const Type::Atom* StaticType<RawType>::atom = 0;
		
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		const Type::Atom* get_type_atom()
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			return StaticType<raw_type>::atom;
		}
		
		
		
		/**
		 * Register type information.
		 */
		template <typename T>
		const Type::Atom* register_type (const std::string& name = "")
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			
			/* get existing atom first. this prevents
			 * duplicate type atoms across library boundaries */
			if (get_type_atom <raw_type> ())
				return get_type_atom <raw_type> ();
			
			
			/* type atom hasn't been created yet */
			if (StaticType<raw_type>::atom == 0)
			{
				/* generate name */
				if (name.empty())
					StaticType<raw_type>::atom = new Type::Atom (typeid(T).name());
				
				/* use given name */
				else StaticType<raw_type>::atom = new Type::Atom (name);
			}
			
			return StaticType<T>::atom;
		}
		
		
		
		
		/**
		 * Generic type which can wrap anything.
		 */
		template <typename T>
		struct GenericType : Type
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			
			
			GenericType () : mTraits(0)
			{
				/* no raw type found */
				if (StaticType<raw_type>::atom == 0)
					StaticType<raw_type>::atom = register_type <raw_type> ();
				
				/* determine traits */
				if (is_constant  <T>::value) mTraits = mTraits | Constant;
				if (is_reference <T>::value) mTraits = mTraits | Reference;
				if (is_pointer   <T>::value) mTraits = mTraits | Pointer;
				if (is_volatile  <T>::value) mTraits = mTraits | Volatile;
			}
			
			
			const Atom* getAtom() const { return StaticType<raw_type>::atom; }
			TraitFlags getTraits() const { return mTraits; }
			
			
			
		private:
			TraitFlags mTraits;
		};
		
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		const Type* get_type()
		{
			static const GenericType<T>* type = new GenericType<T>();
			return type;
		}
		
		
		
		
		
		/* fundamental types */
		extern MYELIN_API const Type::Atom* void_t;
		extern MYELIN_API const Type::Atom* bool_t;
		extern MYELIN_API const Type::Atom* char_t;
		extern MYELIN_API const Type::Atom* uchar_t;
		extern MYELIN_API const Type::Atom* int_t;
		extern MYELIN_API const Type::Atom* uint_t;
		extern MYELIN_API const Type::Atom* long_t;
		extern MYELIN_API const Type::Atom* ulong_t;
		extern MYELIN_API const Type::Atom* int64_t;
		extern MYELIN_API const Type::Atom* uint64_t;
		extern MYELIN_API const Type::Atom* float_t;
		extern MYELIN_API const Type::Atom* double_t;
		extern MYELIN_API const Type::Atom* string_t;
		extern MYELIN_API const Type::Atom* pointer_t;
		
		
		
		/* specialised types */
		template<> inline const Type::Atom* get_type_atom <void>   () { return void_t; }
		template<> inline const Type::Atom* get_type_atom <bool>   () { return bool_t; }
		template<> inline const Type::Atom* get_type_atom <char>   () { return char_t; }
		template<> inline const Type::Atom* get_type_atom <uchar>  () { return uchar_t; }
		template<> inline const Type::Atom* get_type_atom <int>    () { return int_t; }
		template<> inline const Type::Atom* get_type_atom <uint>   () { return uint_t; }
		template<> inline const Type::Atom* get_type_atom <long>   () { return long_t; }
		template<> inline const Type::Atom* get_type_atom <ulong>  () { return ulong_t; }
		template<> inline const Type::Atom* get_type_atom <int64>  () { return int64_t; }
		template<> inline const Type::Atom* get_type_atom <uint64> () { return uint64_t; }
		template<> inline const Type::Atom* get_type_atom <float>  () { return float_t; }
		template<> inline const Type::Atom* get_type_atom <double> () { return double_t; }
		template<> inline const Type::Atom* get_type_atom <void*>  () { return pointer_t; }
		template<> inline const Type::Atom* get_type_atom <const char*> () { return string_t; }
	}

}





/* C api */
extern "C"
{

	MYELIN_API void myelin_type_init ();

	MYELIN_API const char *myelin_type_get_name (const Myelin::Type *type);
	MYELIN_API const char *myelin_type_atom_get_name (const Myelin::Type::Atom *atom);
	
	MYELIN_API const Myelin::Type::Atom *myelin_type_get_atom (const Myelin::Type *type);
	MYELIN_API Myelin::Type::TraitFlags myelin_type_get_traits (const Myelin::Type *type);
	
	
	MYELIN_API bool myelin_type_is_constant  (const Myelin::Type *type);
	MYELIN_API bool myelin_type_is_reference (const Myelin::Type *type);
	MYELIN_API bool myelin_type_is_pointer   (const Myelin::Type *type);
	MYELIN_API bool myelin_type_is_volatile  (const Myelin::Type *type);
	
	MYELIN_API bool myelin_type_equals (const Myelin::Type *lhs,
	                                    const Myelin::Type *rhs);
	
	
	MYELIN_API const Myelin::Type::Atom *myelin_type_bool ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_char ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_uchar ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_int ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_uint ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_long ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_ulong ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_int64 ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_uint64 ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_float ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_double ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_string ();
	MYELIN_API const Myelin::Type::Atom *myelin_type_pointer ();

}



#endif /* MYELIN_TYPE_H_ */

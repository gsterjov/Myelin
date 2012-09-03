/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MYELIN_TYPE_UTILS_H_
#define MYELIN_TYPE_UTILS_H_


#include <string>
#include <iostream>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/TypeTraits.h>


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
	 * Convenience macro to register an atomic type.
	 */
	#define REGISTER_TYPE(type,name) register_type <type> (name)
	
	
	/**
	 * Convenience macro to register a class type.
	 */
	#define REGISTER_CLASS(type,klass) register_class <type> (klass)
	
	
	/**
	 * Convenience macro to get types.
	 */
	#define TYPE(type) get_type <type> ()
	
	
	
	/**
	 * Initiate fundamental types.
	 * 
	 * This will initiate and create atomic types for the fundamental types
	 * such as int, double, void and so on. In this way we can have
	 * the Myelin library be in charge of core types and as such can
	 * pass values between introspected libraries without having type
	 * incompatibilities due to both libraries declaring the same
	 * fundamental types while having diferrent instances for them.
	 * 
	 * @return True if initialised, false otherwise.
	 */
	MYELIN_API bool init_types ();
	
	

	template <typename RawType> Type* test_type<RawType>;
	
	/**
	 * A static type declarator.
	 * 
	 * This class is used by generic types to access a single atomic type
	 * instance across classes and boundaries.
	 */
	template <typename RawType> struct MYELIN_LOCAL StaticType
	{
		/**
		 * The atomic type instance.
		 */
		static Type::Atom* atom;
	};
	
	/**
	 * Default atomic type instance.
	 */
	template <typename RawType> MYELIN_LOCAL Type::Atom* StaticType<RawType>::atom = 0;
	
	
	
	/**
	 * Get atomic type.
	 * 
	 * Returns the atomic type of the templated type. This will strip
	 * any modifiers and qualifiers on the type so as to consistently
	 * return the same atomic type instance.
	 * If the templated type has not been registered it will return the
	 * default atomic type instance, which is NULL.
	 * 
	 * @return The atomic type instance.
	 */
	template <typename T>
	MYELIN_API Type::Atom* get_type_atom()
	{
		/* get raw type */
		typedef typename remove_qualifiers<T>::type raw_type;
		return StaticType<raw_type>::atom;
	}
	
	
	
	/**
	 * Register type information.
	 * 
	 * This will register the templated type with the optional name by
	 * creating an atomic type instance to associate with. If no name
	 * is specified it will automatically be given an 'unknown name' as
	 * a place holder.
	 * 
	 * @param name The name to register the type as.
	 * @return The created atomic type instance.
	 */
	template <typename T>
	MYELIN_API Type::Atom* register_type (const std::string& name = "")
	{
		bool createName = name.empty();
		
		
		/* get raw type */
		typedef typename remove_qualifiers<T>::type raw_type;
		
		/* get existing atom first. this prevents
		 * duplicate type atoms across library boundaries */
		if (get_type_atom <raw_type> ())
		{
			/* set new name */
			if (!createName)
				StaticType<raw_type>::atom->setName (name);
			
			return get_type_atom <raw_type> ();
		}
		
		
		/* type atom hasn't been created yet */
		if (StaticType<raw_type>::atom == 0)
		{
			if (createName)
				StaticType<raw_type>::atom = new Type::Atom ("[Unknown Type]");
			else
				StaticType<raw_type>::atom = new Type::Atom (name);
		}
		
		return StaticType<raw_type>::atom;
	}
	
	
	
	
	/**
	 * Register class type information.
	 * 
	 * This will register the templated class type with the specified
	 * class metadata. It's not unlike register_class() in that it
	 * creates an atomic type for the class, except that it associates
	 * the class with the atom rather than a simple name. This allows
	 * for more functionality allowing advanced features such as
	 * polymorphism.
	 * 
	 * @param klass The class metadata to  register the type as.
	 * @return The created atomic type instance.
	 */
	template <typename T>
	MYELIN_API Type::Atom* register_class (const Class* klass)
	{
		/* get raw type */
		typedef typename remove_qualifiers<T>::type raw_type;
		
		Type::Atom* atom = get_type_atom <raw_type> ();
		
		/* get existing atom first. this prevents
		 * duplicate type atoms across library boundaries */
		if (get_type_atom <raw_type> ())
		{
			StaticType<raw_type>::atom->setClass (klass);
			return get_type_atom <raw_type> ();
		}
		
		
		/* type atom hasn't been created yet */
		if (StaticType<raw_type>::atom == 0)
			StaticType<raw_type>::atom = new Type::Atom (klass);
		
		return StaticType<raw_type>::atom;
	}
	
	
	
	
	/**
	 * Generic type which can wrap anything.
	 * 
	 * A generic type is a specialisation of Type which can take any kind
	 * of type specified in the templated type parameter. It will register
	 * the type upon creation and construct the necessary traits for it.
	 * More often than not a GenericType will be used to describe most, if
	 * not all, types within the introspected library.
	 */
	template <typename T>
	class MYELIN_LOCAL GenericType : public Type
	{
	public:
		/* get raw type */
		typedef typename remove_qualifiers<T>::type raw_type;
		
		
		/**
		 * Constructor.
		 * 
		 * Just by creating the generic type it will be registered and
		 * appropriately interpreted. It can be used straight away after
		 * construction.
		 */
		GenericType ()
		{
			/* no raw type found */
			if (StaticType<raw_type>::atom == 0)
				StaticType<raw_type>::atom = register_type <raw_type> ();
			
			/* determine traits */
			if (is_constant  <T>::value) mTraits.add_constant();
			if (is_reference <T>::value) mTraits.add_reference();
			if (is_pointer   <T>::value) mTraits.add_pointer();
			if (is_volatile  <T>::value) mTraits.add_volatile();
		}
		
		
		/**
		 * Destructor.
		 */
		virtual ~GenericType () {}
		
		
		/* Type implementation */
		const Atom* getAtom() const { return StaticType<raw_type>::atom; }
		const Traits& getTraits() const { return mTraits; }
		
		
	private:
		Traits mTraits;
	};
	
	
	
	/**
	 * Custom type which can be created by passing a type atom.
	 * 
	 * A custom type is usefull for when you only have a type atom and its
	 * traits rather than the actual type. It is used heavily, for example,
	 * in other programming languages that want to pass a value to an
	 * introspected function but obviously cannot register its own types
	 * and so it must construct a custom one.
	 * 
	 * By passing in an atom and traits we can create any kind of type
	 * we want at runtime without worrying about compile time type
	 * checks.
	 */
	class MYELIN_API CustomType : public Type
	{
	public:
		/**
		 * Constructor.
		 * Creates a type with the provided atom and traits.
		 * 
		 * @param atom The atomic type describing the type.
		 * @param traits The type traits the define the type.
		 */
		CustomType (const Atom* atom, const Traits& traits)
		: mAtom (atom),
		  mTraits (traits)
		{}
		
		
		/**
		 * Destructor.
		 */
		virtual ~CustomType () {}
		
		
		/* Type implementation */
		const Atom* getAtom() const { return mAtom; }
		const Traits& getTraits() const { return mTraits; }
		
		
	private:
		const Atom* mAtom;
		Traits mTraits;
	};
	
	
	
	/**
	 * Get type information.
	 * 
	 * Retrieves the type class associated with the templated type
	 * parameter. Although a type can be retrieved simply by creating a
	 * GenericType each time, this provides a convenient way to retrieve
	 * the type class without creating duplicate GenericType references.
	 * 
	 * By returning a static instance of the type, and since type
	 * doesn't really care about instantiations, we can shave off redundant
	 * memory usage simply by using this function instead.
	 * 
	 * @return The type class associated with the templated type parameter.
	 */
	template <typename T>
	MYELIN_API const Type* get_type()
	{
		static const GenericType<T>* type = new GenericType<T>();
		return type;
	}
	
	
	
	
	
	/* fundamental types */
	extern MYELIN_API Type::Atom* void_t;
	extern MYELIN_API Type::Atom* bool_t;
	extern MYELIN_API Type::Atom* char_t;
	extern MYELIN_API Type::Atom* uchar_t;
	extern MYELIN_API Type::Atom* int_t;
	extern MYELIN_API Type::Atom* uint_t;
	extern MYELIN_API Type::Atom* long_t;
	extern MYELIN_API Type::Atom* ulong_t;
	extern MYELIN_API Type::Atom* int64_t;
	extern MYELIN_API Type::Atom* uint64_t;
	extern MYELIN_API Type::Atom* float_t;
	extern MYELIN_API Type::Atom* double_t;
	
	extern MYELIN_API Type::Atom* string_t;
	
	
	
	/* specialised types */
	template<> MYELIN_API inline Type::Atom* get_type_atom <void>   () { return void_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <bool>   () { return bool_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <char>   () { return char_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <uchar>  () { return uchar_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <int>    () { return int_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <uint>   () { return uint_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <long>   () { return long_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <ulong>  () { return ulong_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <int64>  () { return int64_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <uint64> () { return uint64_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <float>  () { return float_t; }
	template<> MYELIN_API inline Type::Atom* get_type_atom <double> () { return double_t; }
	
	template<> MYELIN_API inline Type::Atom* get_type_atom <std::string>() { return string_t; }

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
extern "C"
{

	/**
	 * Initialise fundamental types.
	 */
	MYELIN_API bool myelin_type_init ();
	
	
	/**
	 * Create a custom type with the specified atom and traits.
	 */
	MYELIN_API const Myelin::Type* myelin_type_new (const Myelin::Type::Atom *atom,
	                                                const Myelin::Type::Traits *traits);
	
	
	/* fundamental types */
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

}



#endif /* MYELIN_TYPE_UTILS_H_ */

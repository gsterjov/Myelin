
#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
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
	#define REGISTER_TYPE(type,name) Types::register_type <type> (name)
	
	
	/**
	 * Convenience macro to register a class type.
	 */
	#define REGISTER_CLASS(type,klass) Types::register_class <type> (klass)
	
	
	/**
	 * Convenience macro to get types.
	 */
	#define TYPE(type) Types::get_type <type> ()
	
	
	
	/**
	 * A list of types.
	 */
	class Type; class Class;
	typedef std::vector<const Type*> TypeList;
	
	
	/**
	 * Core type data. Used to identify types ignoring qualifiers.
	 */
	struct MYELIN_API Type : public RefCounter
	{
		/**
		 * The raw type.
		 */
		struct MYELIN_API Atom
		{
			explicit Atom (const std::string& name) : mName(name), mClass(0) {}
			explicit Atom (const Class* klass);
			
			const std::string& getName() const { return mName; }
			const Class* getClass() const { return mClass; }
			
		private:
			const std::string mName;
			const Class* mClass;
		};
		
		
		/**
		 * Type traits.
		 */
		struct MYELIN_API Traits : public RefCounter
		{
			Traits() : mFlags(0) {}
			
			/**
			 * Qualifier types.
			 */
			enum Flags
			{
				Constant  = 1 << 0,
				Reference = 1 << 1,
				Pointer   = 1 << 2,
				Volatile  = 1 << 3
			};
			
			int getFlags() const { return mFlags; }
			
			
			/* change style to mimic trait modifiers */
			void add_constant()  { mFlags |= Constant; }
			void add_reference() { mFlags |= Reference; }
			void add_pointer()   { mFlags |= Pointer; }
			void add_volatile()  { mFlags |= Volatile; }
			
			bool is_constant()  const { return mFlags & Constant; }
			bool is_reference() const { return mFlags & Reference; }
			bool is_pointer()   const { return mFlags & Pointer; }
			bool is_volatile()  const { return mFlags & Volatile; }
			
			
		private:
			int mFlags;
		};
		
		
		
		
		const std::string getName() const
		{
			std::string name = getAtom()->getName();
			const Traits& traits = getTraits();
			
			if (traits.is_volatile())  name = "volatile " + name;
			if (traits.is_constant())  name = "const " + name;
			if (traits.is_reference()) name = name + "&";
			if (traits.is_pointer())   name = name + "*";
			
			return name;
		}
		
		
		virtual const Atom* getAtom() const = 0;
		virtual const Traits& getTraits() const = 0;
		
		
		/* convenience functions for getting type traits */
		bool isConstant()  const { return getTraits().is_constant(); }
		bool isReference() const { return getTraits().is_reference(); }
		bool isPointer()   const { return getTraits().is_pointer(); }
		bool isVolatile()  const { return getTraits().is_volatile(); }
		
		
		bool equals (const Type* info) const
		{
			return getAtom() == info->getAtom() &&
			       getTraits().getFlags() == info->getTraits().getFlags();
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
		MYELIN_API void init_types ();
		
		
		
		
		/**
		 * Used by generic types to access a single type across classes.
		 */
		template <typename RawType> struct MYELIN_LOCAL StaticType { static const Type::Atom* atom; };
		template <typename RawType> MYELIN_LOCAL const Type::Atom* StaticType<RawType>::atom = 0;
		
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		MYELIN_API const Type::Atom* get_type_atom()
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			return StaticType<raw_type>::atom;
		}
		
		
		
		/**
		 * Register type information.
		 */
		template <typename T>
		MYELIN_API const Type::Atom* register_type (const std::string& name = "[Unknown Type]")
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			
			/* get existing atom first. this prevents
			 * duplicate type atoms across library boundaries */
			if (get_type_atom <raw_type> ())
				return get_type_atom <raw_type> ();
			
			
			/* type atom hasn't been created yet */
			if (StaticType<raw_type>::atom == 0)
				StaticType<raw_type>::atom = new Type::Atom (name);
			
			return StaticType<raw_type>::atom;
		}
		
		
		
		
		/**
		 * Register class type information.
		 */
		template <typename T>
		MYELIN_API const Type::Atom* register_class (const Class* klass)
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			
			/* get existing atom first. this prevents
			 * duplicate type atoms across library boundaries */
			if (get_type_atom <raw_type> ())
				return get_type_atom <raw_type> ();
			
			
			/* type atom hasn't been created yet */
			if (StaticType<raw_type>::atom == 0)
				StaticType<raw_type>::atom = new Type::Atom (klass);
			
			return StaticType<raw_type>::atom;
		}
		
		
		
		
		/**
		 * Generic type which can wrap anything.
		 */
		template <typename T>
		struct MYELIN_LOCAL GenericType : Type
		{
			/* get raw type */
			typedef typename remove_qualifiers<T>::type raw_type;
			
			
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
			
			
			const Atom* getAtom() const { return StaticType<raw_type>::atom; }
			const Traits& getTraits() const { return mTraits; }
			
			
			
		private:
			Traits mTraits;
		};
		
		
		
		/**
		 * Custom type which can be created by passing a type atom.
		 */
		struct MYELIN_API CustomType : Type
		{
			CustomType (const Atom* atom, const Traits& traits)
			: mAtom (atom),
			  mTraits (traits)
			{}
			
			const Atom* getAtom() const { return mAtom; }
			const Traits& getTraits() const { return mTraits; }
			
		private:
			const Atom* mAtom;
			Traits mTraits;
		};
		
		
		
		
		/**
		 * Get type information.
		 */
		template <typename T>
		MYELIN_API const Type* get_type()
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
		
		
		
		/* specialised types */
		template<> MYELIN_API inline const Type::Atom* get_type_atom <void>   () { return void_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <bool>   () { return bool_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <char>   () { return char_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <uchar>  () { return uchar_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <int>    () { return int_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <uint>   () { return uint_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <long>   () { return long_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <ulong>  () { return ulong_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <int64>  () { return int64_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <uint64> () { return uint64_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <float>  () { return float_t; }
		template<> MYELIN_API inline const Type::Atom* get_type_atom <double> () { return double_t; }
		
		template<> MYELIN_API inline const Type::Atom* get_type_atom <std::string>() { return string_t; }
	}

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
	MYELIN_API void myelin_type_init ();
	
	
	/**
	 * Create a custom type traits definition.
	 */
	MYELIN_API Myelin::Type::Traits *myelin_type_traits_new ();
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Type::Traits *myelin_type_traits_ref (Myelin::Type::Traits *traits);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_type_traits_unref (Myelin::Type::Traits *traits);
	
	/**
	 * Add a constant trait.
	 */
	MYELIN_API void myelin_type_traits_add_constant (Myelin::Type::Traits *traits);
	
	/**
	 * Add a reference trait.
	 */
	MYELIN_API void myelin_type_traits_add_reference (Myelin::Type::Traits *traits);
	
	/**
	 * Add a pointer trait.
	 */
	MYELIN_API void myelin_type_traits_add_pointer (Myelin::Type::Traits *traits);
	
	/**
	 * Add a volatile trait.
	 */
	MYELIN_API void myelin_type_traits_add_volatile (Myelin::Type::Traits *traits);
	
	
	/**
	 * Is constant defined as a trait?
	 */
	MYELIN_API bool myelin_type_traits_is_constant (Myelin::Type::Traits *traits);
	
	/**
	 * Is reference defined as a trait?
	 */
	MYELIN_API bool myelin_type_traits_is_reference (Myelin::Type::Traits *traits);
	
	/**
	 * Is pointer defined as a trait?
	 */
	MYELIN_API bool myelin_type_traits_is_pointer (Myelin::Type::Traits *traits);
	
	/**
	 * Is volatile defined as a trait?
	 */
	MYELIN_API bool myelin_type_traits_is_volatile (Myelin::Type::Traits *traits);
	
	
	
	
	/**
	 * Create a custom type with the specified atom and traits.
	 */
	MYELIN_API const Myelin::Type* myelin_type_new (const Myelin::Type::Atom *atom,
	                                                const Myelin::Type::Traits *traits);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Type *myelin_type_ref (Myelin::Type *type);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_type_unref (Myelin::Type *type);
	
	
	/**
	 * Get the name of the type.
	 */
	MYELIN_API const char *myelin_type_get_name (const Myelin::Type *type);
	
	/**
	 * Get the name of the type atom.
	 */
	MYELIN_API const char *myelin_type_atom_get_name (const Myelin::Type::Atom *atom);
	
	/**
	 * Get the type's atom.
	 */
	MYELIN_API const Myelin::Type::Atom *myelin_type_get_atom (const Myelin::Type *type);
	
	/**
	 * Get the type's traits.
	 */
	MYELIN_API const Myelin::Type::Traits *myelin_type_get_traits (const Myelin::Type *type);
	
	
	
	/**
	 * Is the type a constant?
	 */
	MYELIN_API bool myelin_type_is_constant (const Myelin::Type *type);
	
	/**
	 * Is the type a reference?
	 */
	MYELIN_API bool myelin_type_is_reference (const Myelin::Type *type);
	
	/**
	 * Is the type a pointer?
	 */
	MYELIN_API bool myelin_type_is_pointer (const Myelin::Type *type);
	
	/**
	 * Is the type volatile?
	 */
	MYELIN_API bool myelin_type_is_volatile (const Myelin::Type *type);
	
	
	/**
	 * Compares the type atom and traits for equality.
	 */
	MYELIN_API bool myelin_type_equals (const Myelin::Type *lhs, const Myelin::Type *rhs);
	
	
	
	
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



#endif /* MYELIN_TYPE_H_ */

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

#ifndef MYELIN_TYPE_H_
#define MYELIN_TYPE_H_


#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{
	/* forward declarations */
	class Type; class Class; class Converter;
	
	/**
	 * A list of immutable types.
	 */
	typedef std::vector<const Type*> TypeList;
	
	
	
	/**
	 * A type class.
	 * 
	 * The type class defines any particular type within the C++ language. It
	 * is composed of an atomic type identifying the raw type, and traits
	 * which explain the current qualifiers and modifiers being applied to
	 * the type.
	 * 
	 * In this way the type 'const int*' is not the same as 'int' as the
	 * traits differ even though the raw type is the same.
	 */
	class MYELIN_API Type : public RefCounter
	{
	public:
		/**
		 * The raw type.
		 * 
		 * An atomic type is the core element of all types. It identifies
		 * what the type is without qualifiers or modifiers. This is what
		 * makes a type unique.
		 * 
		 * As such there is no such thing as a 'const int*', instead this is
		 * interpreted as an atomic type of 'int'.
		 */
		class MYELIN_API Atom
		{
		public:
			/**
			 * Name constructor.
			 * 
			 * This will create an atomic type with the specified name but
			 * without a class. Usefull for primitive or opaque types.
			 * 
			 * @param name The name of the atomic type.
			 */
			explicit Atom (const std::string& name) : mName(name), mClass(0) {}
			
			/**
			 * Class constructor.
			 * 
			 * Create an atomic type defined by the specified class metadata.
			 * This is usefull for when we are dealing with class types while
			 * introspecting as it provides extra functionality for types such
			 * as inheritance, implicit conversions and explicit conversions.
			 * 
			 * @param klass The class the atomic type defines.
			 */
			explicit Atom (const Class* klass);
			
			
			/**
			 * The name of the atomic type.
			 * @return A string representing the name of the atomic type
			 */
			const std::string& getName() const { return mName; }
			
			/**
			 * The class defined by the atomic type.
			 * @return The class being defined, otherwise NULL if no class is
			 * defined.
			 */
			const Class* getClass() const { return mClass; }
			
			
			/**
			 * Set the name of the atomic type.
			 * @param name The new name of the atomic type.
			 */
			void setName (const std::string& name) { mName = name; }
			
			/**
			 * Set the class defined by the atomic type.
			 * @param klass The new class the atomic type defines.
			 */
			void setClass (const Class* klass);
			
			
		private:
			std::string mName;
			const Class* mClass;
		};
		
		
		/**
		 * Type traits.
		 * 
		 * Traits define the extra metadata associated with types such as
		 * whether it is constant or volatile and whether it is a reference
		 * or a pointer. These are collectively called qualifiers and modifiers.
		 * By supporting traits within the type system we can maintain
		 * const-correctness and correctly handle more complex functions and
		 * types.
		 */
		class MYELIN_API Traits : public RefCounter
		{
		public:
			/**
			 * Trait types.
			 * The bitmask flags used to identify which traits are defined.
			 */
			enum Flags
			{
				Constant  = 1 << 0,	/**< The type is constant. */
				Reference = 1 << 1,	/**< The type is a reference. */
				Pointer   = 1 << 2,	/**< The type is a pointer. */
				Volatile  = 1 << 3	/**< The type is volatile. */
			};
			
			
			/**
			 * Default constructor.
			 * By default types contain no traits.
			 */
			Traits() : mFlags(0) {}
			
			
			/**
			 * Get the trait flags defining the traits currently used.
			 * @return A bitmask flag using values from the enum Flags.
			 */
			int getFlags() const { return mFlags; }
			
			
			/* Add the appropriate flags to the trait */
			void add_constant()  { mFlags |= Constant; }
			void add_reference() { mFlags |= Reference; }
			void add_pointer()   { mFlags |= Pointer; }
			void add_volatile()  { mFlags |= Volatile; }
			
			/* See if the traits contain a specific flag */
			bool is_constant()  const { return mFlags & Constant; }
			bool is_reference() const { return mFlags & Reference; }
			bool is_pointer()   const { return mFlags & Pointer; }
			bool is_volatile()  const { return mFlags & Volatile; }
			
			
		private:
			int mFlags;
		};
		
		
		
		
		/**
		 * Destructor.
		 */
		virtual ~Type() {}
		
		
		
		/**
		 * Get the fully qualified name of the type.
		 * 
		 * This will take into account the defined traits of the type and
		 * use them with the atomic type to create the full name of the type.
		 * 
		 * @return The fully qualified type name.
		 */
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
		
		
		/**
		 * Get the atomic type.
		 * @return The atomic type defining the type.
		 */
		virtual const Atom* getAtom() const = 0;
		
		/**
		 * Get the type traits.
		 * @return The type traits defining the type.
		 */
		virtual const Traits& getTraits() const = 0;
		
		
		/* convenience functions for getting type traits */
		bool isConstant()  const { return getTraits().is_constant(); }
		bool isReference() const { return getTraits().is_reference(); }
		bool isPointer()   const { return getTraits().is_pointer(); }
		bool isVolatile()  const { return getTraits().is_volatile(); }
		
		
		/**
		 * Compares two types for equality.
		 * 
		 * Since Types can be instantiated in various contexts, including
		 * across library boundaries, we have to compare if two types are the
		 * same by comparing its atomic type and its traits.
		 * 
		 * @param type The type to compare this one with.
		 * @return True if types are the same, False otherwise.
		 */
		bool equals (const Type* type) const
		{
			return getAtom() == type->getAtom() &&
			       getTraits().getFlags() == type->getTraits().getFlags();
		}
		
		
		/**
		 * Determines if the specified type is compatible with this one.
		 * 
		 * Since classes provide inheritance we need to know if one class
		 * is compatible with the other by means of implicit casting.
		 * 
		 * @param The type to check compatibility with.
		 * @return True if the type is compatibile, False otherwise.
		 */
		bool compatible (const Type* type) const;
		
		
		/**
		 * Find a type converter.
		 * 
		 * Finds a converter that can transform this type into the specified
		 * output type. This can be achieved with implicit casting terms such
		 * as upcasting or through explicit casting means such as casting
		 * operators.
		 * 
		 * @outputType The desired output type.
		 * @return The converter which can perform the transformation.
		 */
		const Converter* findConverter (const Type* outputType) const;
		
		
		/* equality comparison operator */
		friend bool operator== (const Type& lhs, const Type& rhs) { return lhs.equals (&rhs); }
		friend bool operator!= (const Type& lhs, const Type& rhs) { return !(lhs == rhs); }
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
extern "C"
{

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

}



#endif /* MYELIN_TYPE_H_ */

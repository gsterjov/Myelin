
#ifndef MYELIN_VALUE_H_
#define MYELIN_VALUE_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Type.h>

#include <Myelin/Class.h>
#include <Myelin/Converter.h>
#include <iostream>

namespace Myelin
{

	/**
	 * Generic value.
	 */
	class MYELIN_API Value : public RefCounter
	{
	public:
		/**
		 * Default constructor.
		 */
		Value ();
		
		
		/**
		 * Copy constructor.
		 */
		Value (const Value& ref);
		
		
		/**
		 * Value constructor.
		 */
		template <typename T>
		Value (T value) : mData(new GenericData<T>(value)) {}
		
		
		/**
		 * Destructor.
		 */
		~Value();
		
		
		/**
		 * Assignment operator.
		 */
		const Value& operator= (const Value& ref);
		
		
		/**
		 * Get value type.
		 */
		const Type* getType() const;
		
		
		/**
		 * Has the value been set?
		 */
		bool isEmpty() const { return !mData; }
		
		
		/**
		 * Clear the value.
		 */
		void clear();
		
		
		/**
		 * Get the value as a generic pointer.
		 * 
		 * If the value is already a pointer then it is returned otherwise
		 * a pointer is created holding the address of the value.
		 * 
		 * If a pointer is created then it is valid for as long as the value
		 * is alive, or if the value holds a reference then for as long as the
		 * referent is alive. If however, the value holds a pointer then the
		 * semantics are the same as a regular pointer.
		 */
		void* asPointer () const;
		
		
		
		/**
		 * Set new value.
		 */
		template <typename T>
		void set (T value)
		{
			clear();
			mData = new GenericData <T> (value);
		}
		
		
		/**
		 * Set custom type value.
		 */
		template <typename T>
		void set (const Type* type, T value)
		{
			clear();
			mData = new GenericData <T> (type, value);
		}
		
		
		
		/**
		 * Get generic value.
		 */
		template <typename T>
		T& get () const
		{
			/* output type */
			const Type* outType = TYPE(T);
			
			
			/* empty value */
			if (isEmpty())
				throw std::invalid_argument ("Cannot cast value type to "
						"the requested type '" + outType->getName() + "' "
						"because the value is empty");
			
			
			/* data type */
			const Type* type = mData->getType();
			
			
			/* cast to value type */
			if (type->equals (outType))
				return static_cast<GenericData<T>*> (mData)->getData();
			
			
			/* try convert value TO the output type */
			else if (type->getAtom()->getClass())
			{
				const Class* klass = type->getAtom()->getClass();
				
				
				/* get all converters */
				const ConverterList& list = klass->getConverters();
				ConverterList::const_iterator iter;
				
				/* look for a matching conversion context */
				for (iter = list.begin(); iter != list.end(); ++iter)
				{
					Converter* conv = *iter;
					
					/* can convert to type */
					if (conv->getOutputType()->equals (outType))
						return static_cast<GenericData<T>*> (mData)->getData();
				}
			}
			
			
			
			/* target type and value type dont match */
			throw std::invalid_argument ("Cannot cast value type '" +
					type->getName() + "' to requested type '" +
					outType->getName() + "'");
		}
		
		
		
	private:
		struct Data;
		Data* mData;
		
		bool mReference;
		
		
		/**
		 * Data storage interface.
		 */
		struct Data
		{
			virtual Data* clone() const = 0;
			virtual const Type* getType() const = 0;
			virtual void* getPointer() = 0;
			virtual const void* getPointer() const = 0;
		};
		
		
		
		/**
		 * Generic data storage.
		 */
		template <typename T>
		struct GenericData : Data
		{
			/**
			 * Value constructor.
			 */
			GenericData (T value) : mData(value), mType(TYPE(T)) {}
			
			/**
			 * Custom type constructor.
			 */
			GenericData (const Type* type, T value) : mData(value), mType(type) {}
			
			
			/**
			 * Return a copy of the data.
			 */
			Data* clone() const { return new GenericData<T> (mType, mData); }
			
			
			/**
			 * Get the held data.
			 */
			T& getData() { return mData; }
			
			/**
			 * Get the data type.
			 */
			const Type* getType() const { return mType; }
			
			/**
			 * Get the data as a pointer.
			 */
			void* getPointer()
			{
				typedef typename Types::remove_constant<
						typename Types::remove_reference<T>::type>::type raw_type;
				return const_cast<raw_type*> (&mData);
			}
			
			/**
			 * Get the data as a constant pointer.
			 */
			const void* getPointer() const { return &mData; }
			
			
		private:
			T mData;
			const Type* mType;
		};
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
	 * Create a new generic value.
	 */
	MYELIN_API Myelin::Value *myelin_value_new ();
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Value *myelin_value_ref (Myelin::Value *value);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_value_unref (Myelin::Value *value);
	
	
	/**
	 * Get the generic value type.
	 */
	MYELIN_API const Myelin::Type *myelin_value_get_type (const Myelin::Value *value);
	
	/**
	 * Is the generic value holding anything?
	 */
	MYELIN_API bool myelin_value_is_empty (const Myelin::Value *value);
	
	/**
	 * Clear the generic value.
	 */
	MYELIN_API void myelin_value_clear (Myelin::Value *value);
	
	
	
	/**
	 * Get the boolean inside the generic value.
	 */
	MYELIN_API bool myelin_value_get_bool (const Myelin::Value *value);
	
	/**
	 * Set the boolean inside the generic value.
	 */
	MYELIN_API void myelin_value_set_bool (Myelin::Value *value, bool val);
	
	/**
	 * Set the constant boolean inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_bool (Myelin::Value *value, const bool val);
	
	
	
	/**
	 * Get the char inside the generic value.
	 */
	MYELIN_API char myelin_value_get_char (const Myelin::Value *value);
	
	/**
	 * Set the char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_char (Myelin::Value *value, char val);
	
	/**
	 * Set the constant char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_char (Myelin::Value *value, const char val);
	
	
	/**
	 * Get the unsigned char inside the generic value.
	 */
	MYELIN_API uchar myelin_value_get_uchar (const Myelin::Value *value);
	
	/**
	 * Set the unsigned char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uchar (Myelin::Value *value, uchar val);
	
	/**
	 * Set the constant unsigned char inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uchar (Myelin::Value *value, const uchar val);
	
	
	
	/**
	 * Get the integer inside the generic value.
	 */
	MYELIN_API int myelin_value_get_int (const Myelin::Value *value);
	
	/**
	 * Set the integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_int (Myelin::Value *value, int val);
	
	/**
	 * Set the constant integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_int (Myelin::Value *value, const int val);
	
	
	
	
	/**
	 * Get the unsigned integer inside the generic value.
	 */
	MYELIN_API uint myelin_value_get_uint (const Myelin::Value *value);
	
	/**
	 * Set the unsigned integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uint (Myelin::Value *value, uint val);
	
	/**
	 * Set the constant unsigned integer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uint (Myelin::Value *value, const uint val);
	
	
	
	
	/**
	 * Get the long inside the generic value.
	 */
	MYELIN_API long myelin_value_get_long (const Myelin::Value *value);
	
	/**
	 * Set the long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_long (Myelin::Value *value, long val);
	
	/**
	 * Set the constant long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_long (Myelin::Value *value, const long val);
	
	
	
	
	/**
	 * Set the unsigned long inside the generic value.
	 */
	MYELIN_API ulong myelin_value_get_ulong (const Myelin::Value *value);
	
	/**
	 * Set the unsigned long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_ulong (Myelin::Value *value, ulong val);
	
	/**
	 * Set the constant unsigned long inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_ulong (Myelin::Value *value, const ulong val);
	
	
	
	
	/**
	 * Get the int64 inside the generic value.
	 */
	MYELIN_API int64 myelin_value_get_int64 (const Myelin::Value *value);
	
	/**
	 * Set the int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_int64 (Myelin::Value *value, int64 val);
	
	/**
	 * Set the constant int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_int64 (Myelin::Value *value, const int64 val);
	
	
	
	
	/**
	 * Get the unsigned int64 inside the generic value.
	 */
	MYELIN_API uint64 myelin_value_get_uint64 (const Myelin::Value *value);
	
	/**
	 * Set the unsigned int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_uint64 (Myelin::Value *value, uint64 val);
	
	/**
	 * Set the constant unsigned int64 inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_uint64 (Myelin::Value *value, const uint64 val);
	
	
	
	
	/**
	 * Get the float inside the generic value.
	 */
	MYELIN_API float myelin_value_get_float (const Myelin::Value *value);
	
	/**
	 * Set the float inside the generic value.
	 */
	MYELIN_API void myelin_value_set_float (Myelin::Value *value, float val);
	
	/**
	 * Set the constant float inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_float (Myelin::Value *value, const float val);
	
	
	
	
	/**
	 * Get the double inside the generic value.
	 */
	MYELIN_API double myelin_value_get_double (const Myelin::Value *value);
	
	/**
	 * Set the double inside the generic value.
	 */
	MYELIN_API void myelin_value_set_double (Myelin::Value *value, double val);
	
	/**
	 * Set the constant double inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_double (Myelin::Value *value, const double val);
	
	
	
	
	/**
	 * Get the string inside the generic value.
	 */
	MYELIN_API const char *myelin_value_get_string (const Myelin::Value *value);
	
	/**
	 * Set the string inside the generic value.
	 */
	MYELIN_API void myelin_value_set_string (Myelin::Value *value, const char *val);
	
	
	
	
	/**
	 * Get the generic pointer inside the generic value.
	 */
	MYELIN_API void *myelin_value_get_pointer (const Myelin::Value *value);
	
	/**
	 * Get the constant generic pointer inside the generic value.
	 */
	MYELIN_API const void *myelin_value_get_const_pointer (const Myelin::Value *value);
	
	/**
	 * Set the generic pointer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_pointer (Myelin::Value *value,
                                              const Myelin::Type *type,
	                                          void *ptr);
	
	/**
	 * Set the constant generic pointer inside the generic value.
	 */
	MYELIN_API void myelin_value_set_const_pointer (Myelin::Value *value,
	                                                const Myelin::Type *type,
	                                                const void *ptr);

}



#endif /* MYELIN_VALUE_H_ */

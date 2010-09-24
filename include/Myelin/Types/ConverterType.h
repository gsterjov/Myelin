
#ifndef MYELIN_CONVERTER_TYPE_H_
#define MYELIN_CONVERTER_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Value.h>
#include <Myelin/Pointer.h>


namespace Myelin
{

	/**
	 * Converter type interface.
	 */
	struct ConverterType
	{
		/**
		 * Convert the value into the appropriate output type.
		 */
		virtual Value convert (const Value& value) const = 0;
		
		/**
		 * Convert the pointer into the appropriate output type.
		 */
		virtual Value convert (const Pointer& value) const = 0;
		
		/**
		 * The type to convert from.
		 */
		virtual const Type* getInputType() const = 0;
		
		/**
		 * The type to convert into.
		 */
		virtual const Type* getOutputType() const = 0;
	};
	
	
	
	/**
	 * Implicit conversion type.
	 */
	template <typename InputType, typename OutputType>
	struct ImplicitConverter : ConverterType
	{
		Value convert (const Value& value) const
		{
			Value val;
			val.set <OutputType> (value.get <InputType> ());
			return val;
		}
		
		
		Value convert (const Pointer& ptr) const
		{
			typedef typename Types::remove_pointer<InputType>::type input_type;
			
			Value val;
			val.set <OutputType> (ptr.get <input_type> ());
			return val;
		}
		
		
		const Type* getInputType  () const { return TYPE(InputType); }
		const Type* getOutputType () const { return TYPE(OutputType); }
	};

}


#endif /* MYELIN_CONVERTER_TYPE_H_ */

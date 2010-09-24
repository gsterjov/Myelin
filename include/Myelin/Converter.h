
#ifndef MYELIN_CONVERTER_H_
#define MYELIN_CONVERTER_H_


#include <Myelin/Config.h>


namespace Myelin
{

	/* forward declarations */
	class Type;
	class Value;
	class Pointer;
	class ConverterType;
	
	
	/**
	 * Class type converter.
	 */
	class MYELIN_API Converter
	{
	public:
		/**
		 * Constructor.
		 */
		Converter (const ConverterType* type);
		
		/**
		 * Destructor.
		 */
		virtual ~Converter ();
		
		
		/**
		 * The type to convert from.
		 */
		const Type* getInputType() const;
		
		/**
		 * The type to convert into.
		 */
		const Type* getOutputType() const;
		
		
		
		/**
		 * Convert the value into the appropriate output type.
		 */
		Value convert (const Value& value) const;
		
		/**
		 * Convert the pointer into the appropriate output type.
		 */
		Value convert (const Pointer& ptr) const;
		
		
	private:
		const ConverterType* mConvType;
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
	 * Get the input type to be convertered.
	 */
	MYELIN_API const Myelin::Type *myelin_converter_get_input_type (const Myelin::Converter *converter);
	
	/**
	 * Get the output type to convert to.
	 */
	MYELIN_API const Myelin::Type *myelin_converter_get_output_type (const Myelin::Converter *converter);
	
	
	/**
	 * Convert the value to the output value type.
	 */
	MYELIN_API Myelin::Value *myelin_converter_convert_value (const Myelin::Converter *converter,
	                                                          const Myelin::Value *value);
	
	/**
	 * Convert the pointer to the output value type.
	 */
	MYELIN_API Myelin::Value *myelin_converter_convert_pointer (const Myelin::Converter *converter,
	                                                            const Myelin::Pointer *pointer);

}



#endif /* MYELIN_CONVERTER_H_ */

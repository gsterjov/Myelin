
#include "Converter.h"

#include "Type.h"
#include "Value.h"

#include "Types/ConverterType.h"


namespace Myelin
{

	/* constructor */
	Converter::Converter (const ConverterType* type) : mConvType(type) {}
	
	
	/* destructor */
	Converter::~Converter ()
	{
		
	}
	
	
	
	/* get input type */
	const Type* Converter::getInputType() const
	{
		return mConvType->getInputType();
	}
	
	
	/* get output type */
	const Type* Converter::getOutputType() const
	{
		return mConvType->getOutputType();
	}
	
	
	/* convert value */
	Value Converter::convert (const Value& value) const
	{
		return mConvType->convert (value);
	}

}



/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/

const Myelin::Type *
myelin_converter_get_input_type (const Myelin::Converter *converter)
{
	return converter->getInputType();
}


const Myelin::Type *
myelin_converter_get_output_type (const Myelin::Converter *converter)
{
	return converter->getOutputType();
}



Myelin::Value *
myelin_converter_convert_value (const Myelin::Converter *converter,
                                const Myelin::Value *value)
{
	Myelin::Value* ret = new Myelin::Value (converter->convert (*value));
	
	/* throw away ownership */
	ret->unref();
	return ret;
}


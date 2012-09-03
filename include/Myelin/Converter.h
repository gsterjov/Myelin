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

#ifndef MYELIN_CONVERTER_H_
#define MYELIN_CONVERTER_H_


#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{

	/* forward declarations */
	class Type;
	class Value;
	class ConverterType;
	
	
	/**
	 * Class type converter.
	 */
	class MYELIN_API Converter : public RefCounter
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

}



#endif /* MYELIN_CONVERTER_H_ */

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

#ifndef MYELIN_CONVERTER_TYPE_H_
#define MYELIN_CONVERTER_TYPE_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Value.h>


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
		virtual ~ImplicitConverter() {}
		
		
		Value convert (const Value& value) const
		{
			Value val;
			val.set <OutputType> (value.get <InputType> ());
			return val;
		}
		
		
		const Type* getInputType  () const { return TYPE(InputType); }
		const Type* getOutputType () const { return TYPE(OutputType); }
	};

}


#endif /* MYELIN_CONVERTER_TYPE_H_ */

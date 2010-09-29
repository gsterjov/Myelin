
#ifndef MYELIN_PARAMETER_TYPE_H_
#define MYELIN_PARAMETER_TYPE_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Class.h>
#include <Myelin/Converter.h>
#include <iostream>

namespace Myelin
{

	/**
	 * Convert a parameter pointer into the appropriate type.
	 */
	static Value convert_parameter (const Pointer& ptr, const Type* param_type)
	{
		/* TODO: qualifier upgrades from non-const to const. etc. */
		
		/* convert FROM pointer */
		const Class* klass = param_type->getAtom()->getClass();
		
		/* type is a class */
		if (klass != 0)
		{
			/* get all converters */
			const ConverterList& list = klass->getConverters();
			ConverterList::const_iterator iter;
			
			/* look for a matching conversion context */
			for (iter = list.begin(); iter != list.end(); ++iter)
			{
				Converter* conv = *iter;
				
				/* can convert to type */
				if (conv->getInputType()->equals (ptr.getType()))
					return conv->convert (ptr);
			}
		}
		
		
		
		/* convert TO parameter */
		klass = ptr.getType()->getAtom()->getClass();
		
		/* type is a class */
		if (klass != 0)
		{
			/* get all converters */
			const ConverterList& list = klass->getConverters();
			ConverterList::const_iterator iter;
			
			/* look for a matching conversion context */
			for (iter = list.begin(); iter != list.end(); ++iter)
			{
				Converter* conv = *iter;
				
				/* can convert to type */
				if (conv->getOutputType()->equals (param_type))
					return conv->convert (ptr);
			}
		}
		
		
		/* conversion failed */
		throw std::invalid_argument ("Cannot convert the given value type '" +
				ptr.getType()->getName() + "' to the required parameter "
				"type '" + param_type->getName() + "'. No conversion possible");
	}
	
	
	
	/**
	 * Stores a parameter type and handles type transformation.
	 */
	template <typename T>
	struct ParameterType
	{
		T& unpack (const Value& value) const
		{
			/* adding a const qualifier is done automatically */
			typedef typename Types::remove_constant<T>::type raw_type;
			return value.get<raw_type>();
		}
	};
	
	
	
	template <typename T>
	struct ParameterType <T&>
	{
		T unpack (const Value& value) const
		{
			/* adding a const qualifier is done automatically */
			typedef typename Types::remove_constant<T>::type raw_type;
			
			
			const Type* val_t = value.getType();
			
			/* value is a generic pointer.
			 * generic pointers are needed so that all references can be
			 * treated as pointers outside C++ */
			if (val_t->getAtom() == TYPE(Pointer)->getAtom())
			{
				Pointer* ptr = 0;
				
				/* pointer to generic pointer structure */
				if (val_t->isPointer())
					ptr = value.get<Pointer*>();
				
				/* reference to generic pointer structure */
				else if (val_t->isReference())
					ptr = &value.get<Pointer&>();
				
				/* generic pointer structure value */
				else ptr = &value.get<Pointer>();
				
				
				if (ptr != 0)
				{
					/* pointer value matches parameter */
					if (ptr->getType()->equals (TYPE(raw_type*)))
						return *ptr->get<raw_type>();
					
					/* convert the parameter */
					else
					{
						Value val = convert_parameter (*ptr, TYPE(raw_type));
						return val.get<raw_type>();
					}
				}
			}
			
			
			/* do a standard cast */
			return value.get<raw_type>();
		}
	};
	
	
	
	
	template <typename T>
	struct ParameterType <T*>
	{
		T* unpack (const Value& value) const
		{
			/* adding a const qualifier is done automatically */
			typedef typename Types::remove_constant<T>::type raw_type;
			
			
			const Type* val_t = value.getType();
			
			/* value is a generic pointer.
			 * generic pointers are needed so that all references can be
			 * treated as pointers outside C++ */
			if (val_t->getAtom() == TYPE(Pointer)->getAtom())
			{
				Pointer* ptr = 0;
				
				/* pointer to generic pointer structure */
				if (val_t->isPointer())
					ptr = value.get<Pointer*>();
				
				/* reference to generic pointer structure */
				else if (val_t->isReference())
					ptr = &value.get<Pointer&>();
				
				/* generic pointer structure value */
				else ptr = &value.get<Pointer>();
				
				
				if (ptr != 0)
				{
					/* pointer value matches parameter */
					if (ptr->getType()->equals (TYPE(raw_type*)))
						return ptr->get<raw_type>();
					
					/* convert the parameter */
					else
					{
						Value val = convert_parameter (*ptr, TYPE(raw_type*));
						return val.get<raw_type*>();
					}
				}
			}
			
			
			/* do a standard cast */
			return value.get<raw_type*>();
		}
	};

}


#endif /* MYELIN_PARAMETER_TYPE_H_ */

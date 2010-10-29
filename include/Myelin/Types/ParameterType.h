
#ifndef MYELIN_PARAMETER_TYPE_H_
#define MYELIN_PARAMETER_TYPE_H_


#include <stdexcept>

#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Value.h>
#include <Myelin/Class.h>
#include <Myelin/Converter.h>
#include <iostream>

namespace Myelin
{

	/**
	 * Convert a parameter pointer into the appropriate type.
	 */
	static Value convert_parameter (const Value& ptr, const Type* param_type)
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
			return value.get <T> ();
		}
	};
	
	
	
	template <typename T>
	struct ParameterType <T&>
	{
		T& unpack (const Value& value) const
		{
			const Type* val_t = value.getType();
			
			
			/* get the type of the parameter without a const */
			typedef typename Types::remove_constant<T>::type no_const_type;
			
			
			/* we can upgrade the value to const implicitly */
			if (val_t->equals (TYPE(no_const_type&)))
				return value.get <no_const_type&> ();
			
			
			/* TODO: get value to reference conversion working.
			 * As it is now abstract classes stop it from working due
			 * to the fact that the abstract class is declared here in this
			 * template function. */
			
			/* pass value as a reference */
//			else if (val_t->equals (TYPE(T)))
//				return value.get <T> ();
//			
//			else if (val_t->equals (TYPE(no_const_type)))
//				return value.get <no_const_type> ();
			
			
			/* value is a pointer.
			 * pointer-reference conversions are needed so that all references
			 * can be treated as pointers outside C++ */
			else if (val_t->isPointer())
			{
				/* pointer value matches parameter */
				if (val_t->equals (TYPE(T*)))
					return *value.get <T*> ();
				
				/* upgrade pointer to a const */
				else if (val_t->equals (TYPE(no_const_type*)))
					return *value.get <no_const_type*> ();
				
				/* convert the parameter */
				else
				{
					Value val = convert_parameter (value, TYPE(T*));
					return *val.get <T*> ();
				}
			}
			
			
			/* do a standard cast */
			return value.get <T&> ();
		}
	};
	
	
	
	
	template <typename T>
	struct ParameterType <T*>
	{
		T* unpack (const Value& value) const
		{
			const Type* val_t = value.getType();
			
			
			/* get the type of the parameter without a const */
			typedef typename Types::remove_constant<T>::type no_const_type;
			const Type* no_const_t = TYPE(no_const_type*);
			
			
			/* we can upgrade the value to const implicitly */
			if (val_t->equals (no_const_t))
				return value.get <no_const_type*> ();
			
			
			/* convert the parameter */
			else if (!val_t->equals (TYPE(T*)))
			{
				Value val = convert_parameter (value, TYPE(T*));
				return val.get <T*> ();
			}
			
			
			/* do a standard cast */
			return value.get <T*> ();
		}
	};

}


#endif /* MYELIN_PARAMETER_TYPE_H_ */

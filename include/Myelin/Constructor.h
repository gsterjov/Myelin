
#ifndef MYELIN_CONSTRUCTOR_H_
#define MYELIN_CONSTRUCTOR_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>


namespace Myelin
{

	/* forward declaration */
	class Value;
	class List;
	class Pointer;
	class ConstructorType;
	
	
	
	class MYELIN_API Constructor
	{
	public:
		/**
		 * Constructor.
		 */
		Constructor (const ConstructorType* type);
		
		/**
		 * Destructor.
		 */
		~Constructor ();
		
		
		/**
		 * Parameter count.
		 */
		int getParamCount() const;
		
		/**
		 * Parameter type.
		 */
		const Type* getParamType (int index) const;
		
		/**
		 * Parameter list.
		 */
		const TypeList& getParamTypes() const;
		
		
		/**
		 * Call the constructor.
		 */
		Pointer call (const List& params) const;
		
		
	private:
		const ConstructorType* mCtorType;
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
	 * Get the amount of parameters specified by the constructor.
	 */
	MYELIN_API int myelin_constructor_get_param_count (Myelin::Constructor *constructor);
	
	/**
	 * Get the parameter type at the specified index.
	 */
	MYELIN_API const Myelin::Type *myelin_constructor_get_param_type (Myelin::Constructor *constructor,
	                                                                  int index);
	
	/**
	 * Get a list of all the parameter types.
	 */
	MYELIN_API Myelin::List *myelin_constructor_get_param_types (Myelin::Constructor *constructor);

	
	/**
	 * Call the constructor.
	 */
	MYELIN_API Myelin::Pointer *myelin_constructor_call (Myelin::Constructor *constructor,
	                                                     const Myelin::List *params);

}



#endif /* MYELIN_CONSTRUCTOR_H_ */


#ifndef MYELIN_CONSTRUCTOR_H_
#define MYELIN_CONSTRUCTOR_H_


#include <Myelin/Config.h>
#include <Myelin/Type.h>
#include <Myelin/Pointer.h>
#include <Myelin/List.h>


namespace Myelin
{

	class MYELIN_API Constructor
	{
	public:
		/**
		 * Parameter count.
		 */
		virtual int getParamCount() const = 0;
		
		/**
		 * Parameter type.
		 */
		virtual const Type* getParamType(int index) const = 0;
		
		/**
		 * Parameter list.
		 */
		virtual const TypeList getParamList() const = 0;
		
		
		/**
		 * Call the function.
		 */
		virtual Pointer call (const List& params) const = 0;
	};

}




/* C api */
extern "C"
{

	MYELIN_API int myelin_constructor_get_param_count (Myelin::Constructor *constructor);
	
	MYELIN_API const Myelin::Type *myelin_constructor_get_param_type (Myelin::Constructor *constructor,
	                                                                  int index);
	
	
	MYELIN_API Myelin::List *myelin_constructor_get_param_list (Myelin::Constructor *constructor);
	
	
	MYELIN_API Myelin::Pointer *myelin_constructor_call (Myelin::Constructor *constructor,
	                                                     const Myelin::List *params);

}



#endif /* MYELIN_CONSTRUCTOR_H_ */

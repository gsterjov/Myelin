
#ifndef MYELIN_FUNCTION_H_
#define MYELIN_FUNCTION_H_


#include <string>
#include <Myelin/Type.h>
#include <Myelin/Value.h>
#include <Myelin/List.h>


namespace Myelin
{

	/* forward declarations */
	class Object;
	
	
	
	class Function
	{
	public:
		/**
		 * Function name.
		 */
		virtual const std::string& getName() const = 0;
		
		/**
		 * Return type.
		 */
		virtual const Type* getReturnType() const = 0;
		
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
		virtual Value call (void* object, const List& params) const = 0;
	};

}




/* C api */
extern "C"
{

	const char *myelin_function_get_name (Myelin::Function *function);
	
	const Myelin::Type *myelin_function_get_return_type (Myelin::Function *function);
	
	int myelin_function_get_param_count (Myelin::Function *function);
	
	const Myelin::Type *myelin_function_get_param_type (Myelin::Function *function,
	                                                    int index);
	
	
	Myelin::List *myelin_function_get_param_list (Myelin::Function *function);
	
	
	Myelin::Value *myelin_function_call (Myelin::Function *function,
	                                     void *object,
	                                     const Myelin::List *params);

}



#endif /* MYELIN_FUNCTION_H_ */

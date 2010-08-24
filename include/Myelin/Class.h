
#ifndef MYELIN_CLASS_H_
#define MYELIN_CLASS_H_


#include <string>
#include <vector>


namespace Myelin
{

	/* forward declaration */
	class Function;
	
	
	/* function storage */
	typedef std::vector<Function*> FunctionList;
	
	
	
	class Class
	{
	public:
		/**
		 * Get class name.
		 */
		virtual const std::string& getName() const = 0;
		
		
		/**
		 * Register function with class.
		 */
		virtual void registerFunction (Function* function) = 0;
		
		
		/**
		 * Get function.
		 */
		virtual Function* getFunction (const std::string& name) const = 0;
		
		
		/**
		 * Get all functions.
		 */
		virtual FunctionList getFunctionList () const = 0;
	};

}



/* C api forward declaration */
namespace Myelin { class List; }



/* C api */
extern "C"
{

	const char *myelin_class_get_name (Myelin::Class *klass);
	
	void myelin_class_register_function (Myelin::Class *klass,
	                                     Myelin::Function *function);
	
	Myelin::Function *myelin_class_get_function (Myelin::Class *klass,
	                                             const char *name);
	
	
	Myelin::List *myelin_class_get_function_list (Myelin::Class *klass);

}



#endif /* MYELIN_CLASS_H_ */


#ifndef MYELIN_CLASS_H_
#define MYELIN_CLASS_H_


#include <string>


namespace Myelin
{

	/* forward declaration */
	class Function;
	
	
	
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
		virtual const Function* getFunction (const std::string& name) const = 0;
	};

}



/* C api */
extern "C"
{

	Myelin::Class *myelin_class_get (const char *class_name);
	
	const char *myelin_class_get_name (Myelin::Class *klass);
	
	void myelin_class_register_function (Myelin::Class *klass,
	                                     Myelin::Function *function);
	
	const Myelin::Function *myelin_class_get_function (Myelin::Class *klass,
	                                                   const char *name);

}



#endif /* MYELIN_CLASS_H_ */


#ifndef MYELIN_CLASS_H_
#define MYELIN_CLASS_H_


#include <string>
#include <vector>

#include <Myelin/Config.h>


namespace Myelin
{

	/* forward declaration */
	class List;
	class Object;
	class Constructor;
	class Function;
	class Pointer;
	
	
	/* storage */
	typedef std::vector<Constructor*> ConstructorList;
	typedef std::vector<Function*> FunctionList;
	
	
	
	class MYELIN_API Class
	{
	public:
		/**
		 * Get class name.
		 */
		virtual const std::string& getName() const = 0;
		
		
		/**
		 * Get class name.
		 */
		virtual const std::vector<std::string>& getNamespace() const = 0;
		
		
		/**
		 * Register constructor with class.
		 */
		virtual void registerConstructor (Constructor* constructor) = 0;
		
		
		/**
		 * Get all constructors.
		 */
		virtual const ConstructorList& getConstructorList () const = 0;
		
		
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
		
		
		
		/**
		 * Creates an object instance from the class.
		 */
		virtual Pointer createInstance (const List& params) const = 0;
		
		
		/**
		 * Creates a meta object from the class.
		 */
		virtual Object* createObject (const List& params) const = 0;
		
		
		/**
		 * Creates a meta object with the supplied instance.
		 */
		virtual Object* createObject (void* instance) const = 0;
	};

}



/* C api forward declaration */
namespace Myelin { class List; }



/* C api */
extern "C"
{

	MYELIN_API const char *myelin_class_get_name (Myelin::Class *klass);
	
	MYELIN_API Myelin::List *myelin_class_get_namespace (Myelin::Class *klass);
	
	
	MYELIN_API void myelin_class_register_constructor (Myelin::Class *klass,
	                                                   Myelin::Constructor *constructor);
	
	MYELIN_API Myelin::List *myelin_class_get_constructor_list (Myelin::Class *klass);
	
	
	MYELIN_API void myelin_class_register_function (Myelin::Class *klass,
	                                                Myelin::Function *function);
	
	MYELIN_API Myelin::Function *myelin_class_get_function (Myelin::Class *klass,
	                                                        const char *name);
	
	
	MYELIN_API Myelin::List *myelin_class_get_function_list (Myelin::Class *klass);
	
	
	
	MYELIN_API Myelin::Pointer *myelin_class_create_instance (const Myelin::Class *klass,
	                                                          const Myelin::List *params);
	
	
	MYELIN_API Myelin::Object *myelin_class_create_object (const Myelin::Class *klass,
	                                                       const Myelin::List *params);
	
	
	MYELIN_API Myelin::Object *myelin_class_create_object_instance (const Myelin::Class *klass,
	                                                                void* instance);

}



#endif /* MYELIN_CLASS_H_ */

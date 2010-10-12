
#ifndef MYELIN_CLASS_H_
#define MYELIN_CLASS_H_


#include <map>
#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{

	/* forward declaration */
	class Type;
	class List;
	class Object;
	class Constructor;
	class Converter;
	class Function;
	class Pointer;
	class VTable;
	
	
	/* storage */
	typedef std::vector<Constructor*> ConstructorList;
	typedef std::vector<Converter*> ConverterList;
	typedef std::vector<Function*> FunctionList;
	
	
	
	class MYELIN_API Class : public RefCounter
	{
	public:
		/**
		 * Constructor.
		 */
		explicit Class (const std::string& name);
		
		/**
		 * Destructor.
		 */
		virtual ~Class ();
		
		
		
		/**
		 * Get class name.
		 */
		const std::string& getName() const { return mName; }
		
		/**
		 * Get class type.
		 */
		const Type* getType() const { return mType; }
		
		/**
		 * Set class type.
		 */
		void setType (const Type* type) { mType = type; }
		
		
		/**
		 * Add constructor to the class.
		 */
		void addConstructor (Constructor* constructor);
		
		
		/**
		 * Get all constructors.
		 */
		const ConstructorList& getConstructors () const;
		
		
		/**
		 * Add a converter to the class.
		 */
		void addConverter (Converter* converter);
		
		
		/**
		 * Get all converters.
		 */
		const ConverterList& getConverters () const;
		
		
		/**
		 * Add function to the class.
		 */
		void addFunction (Function* function);
		
		
		/**
		 * Get all functions.
		 */
		FunctionList getFunctions () const;
		
		
		/**
		 * Get all functions with the specified name.
		 */
		FunctionList getFunctions (const std::string& name) const;
		
		
		/**
		 * Get the virtual function table.
		 */
		VTable* getVTable () const { return mTable; }
		
		
		/**
		 * Set the virtual function table.
		 */
		void setVTable (VTable* vtable) { mTable = vtable; }
		
		
		/**
		 * Create an object instance from the class.
		 */
		Pointer createInstance (const List& params) const;
		
		
		/**
		 * Create a meta object from the class.
		 */
		Object* createObject (const List& params) const;
		
		
	private:
		std::string mName;
		const Type* mType;
		
		ConstructorList mConstructors;
		ConverterList mConverters;
		
		typedef std::map<std::string, FunctionList> FunctionMap;
		FunctionMap mFunctions;
		
		VTable* mTable;
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/

/* forward declaration */
namespace Myelin { class List; }


extern "C"
{

	/**
	 * Create a new meta class.
	 */
	MYELIN_API Myelin::Class *myelin_class_new (const char *name);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Class *myelin_class_ref (Myelin::Class *klass);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_class_unref (Myelin::Class *klass);
	
	/**
	 * Get the name of the meta class.
	 */
	MYELIN_API const char *myelin_class_get_name (Myelin::Class *klass);
	
	/**
	 * Get the type of the meta class.
	 */
	MYELIN_API const Myelin::Type *myelin_class_get_type (Myelin::Class *klass);
	
	/**
	 * Add a constructor to the meta class.
	 */
	MYELIN_API void myelin_class_add_constructor (Myelin::Class *klass,
	                                              Myelin::Constructor *constructor);
	
	/**
	 * Get a list of all the constructors in the meta class.
	 */
	MYELIN_API Myelin::List *myelin_class_get_constructors (Myelin::Class *klass);
	
	/**
	 * Add a function to the meta class.
	 */
	MYELIN_API void myelin_class_add_function (Myelin::Class *klass,
	                                           Myelin::Function *function);
	
	/**
	 * Get a list of all the functions in the meta class.
	 */
	MYELIN_API Myelin::List *myelin_class_get_all_functions (Myelin::Class *klass);
	
	/**
	 * Get a list of functions with the given name.
	 */
	MYELIN_API Myelin::List *myelin_class_get_functions (Myelin::Class *klass,
	                                                     const char *name);
	
	/**
	 * Get the virtual function table being used by the class.
	 */
	MYELIN_API Myelin::VTable *myelin_class_get_vtable (Myelin::Class *klass);
	
	/**
	 * Set the virtual function table being used by the class.
	 */
	MYELIN_API void myelin_class_set_vtable (Myelin::Class *klass,
	                                         Myelin::VTable *vtable);
	
	
	/**
	 * Create an instance of the class defined by the meta class.
	 */
	MYELIN_API Myelin::Pointer *myelin_class_create_instance (const Myelin::Class *klass,
	                                                          const Myelin::List *params);
	
	/**
	 * Create a meta object of the class defined by the meta class.
	 */
	MYELIN_API Myelin::Object *myelin_class_create_object (const Myelin::Class *klass,
	                                                       const Myelin::List *params);

}



#endif /* MYELIN_CLASS_H_ */

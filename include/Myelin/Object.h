
#ifndef MYELIN_OBJECT_H_
#define MYELIN_OBJECT_H_


#include <string>

#include <Myelin/Config.h>
#include <Myelin/Pointer.h>


namespace Myelin
{

	/* forward declaration */
	class Value;
	class List;
	class Class;
	
	
	
	class MYELIN_API Object
	{
	public:
		/**
		 * Constructor.
		 */
		Object ();
		
		/**
		 * Class Constructor.
		 */
		explicit Object (const Class* klass);
		
		
		/**
		 * Class and instance constructor.
		 */
		Object (const Class* klass, const Pointer& instance);
		
		
		/**
		 * Destructor.
		 */
		virtual ~Object ();
		
		
		
		/*
		 * Set the object's meta class.
		 */
		void setClass (const Class* klass) { mClass = klass; }
		
		/*
		 * Get the object's meta class.
		 */
		const Class* getClass () const { return mClass; }
		
		
		/*
		 * Set the object instance to use.
		 */
		void setInstance (const Pointer& instance) { mInstance = instance; }
		
		/*
		 * Get the object instance being used.
		 */
		const Pointer& getInstance () const { return mInstance; }
		
		
		
		
		/**
		 * Call the function on the object.
		 */
		Value call (const std::string& function, const List& params) const;
		
		
		Value call (const std::string& function) const;
		Value call (const std::string& function, const Value& param1) const;
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2) const;
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3) const;
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3,
											     const Value& param4) const;
		
		Value call (const std::string& function, const Value& param1,
											     const Value& param2,
											     const Value& param3,
											     const Value& param4,
											     const Value& param5) const;
		
		
	private:
		const Class* mClass;
		Pointer mInstance;
	};

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/

/* forward declaration */
namespace Myelin { class Class; }


extern "C"
{

	/**
	 * Create a meta object.
	 */
	MYELIN_API Myelin::Object *myelin_object_new ();
	
	/**
	 * Create a meta object with the given class.
	 */
	MYELIN_API Myelin::Object *myelin_object_new_with_class (const Myelin::Class *klass);
	
	/**
	 * Create a meta object with the given instance.
	 */
	MYELIN_API Myelin::Object *myelin_object_new_with_instance (const Myelin::Class *klass,
	                                                            const Myelin::Pointer *instance);
	
	/**
	 * Free the meta object.
	 */
	MYELIN_API void myelin_object_free (Myelin::Object *object);
	
	/**
	 * Set the meta class being used by the meta object.
	 */
	MYELIN_API void myelin_object_set_class (Myelin::Object *object, Myelin::Class *klass);
	
	/**
	 * Get the meta class being used by the meta object.
	 */
	MYELIN_API const Myelin::Class *myelin_object_get_class (const Myelin::Object *object);
	
	/**
	 * Set the instance being used by the meta object.
	 */
	MYELIN_API void myelin_object_set_instance (Myelin::Object *object, const Myelin::Pointer *instance);
	
	/**
	 * Get the instance being used by the meta object.
	 */
	MYELIN_API const Myelin::Pointer *myelin_object_get_instance (const Myelin::Object *object);
	
	/**
	 * Call the named function on the meta object instance.
	 */
	MYELIN_API Myelin::Value *myelin_object_call (const Myelin::Object *object,
	                                              const char *function,
	                                              const Myelin::List *params);

}



#endif /* MYELIN_OBJECT_H_ */

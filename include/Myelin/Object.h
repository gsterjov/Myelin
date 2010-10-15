
#ifndef MYELIN_OBJECT_H_
#define MYELIN_OBJECT_H_


#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>
#include <Myelin/Value.h>


namespace Myelin
{

	/* forward declaration */
	class List;
	class Class;
	
	
	
	class MYELIN_API Object : public RefCounter
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
		Object (const Class* klass, const Value& instance);
		
		
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
		void setInstance (const Value& instance) { mInstance = instance; }
		
		/*
		 * Get the object instance being used.
		 */
		const Value& getInstance () const { return mInstance; }
		
		
		
		
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
		Value mInstance;
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
	                                                            const Myelin::Value *instance);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Object *myelin_object_ref (Myelin::Object *object);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_object_unref (Myelin::Object *object);
	
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
	MYELIN_API void myelin_object_set_instance (Myelin::Object *object, const Myelin::Value *instance);
	
	/**
	 * Get the instance being used by the meta object.
	 */
	MYELIN_API const Myelin::Value *myelin_object_get_instance (const Myelin::Object *object);
	
	/**
	 * Call the named function on the meta object instance.
	 */
	MYELIN_API Myelin::Value *myelin_object_call (const Myelin::Object *object,
	                                              const char *function,
	                                              const Myelin::List *params);

}



#endif /* MYELIN_OBJECT_H_ */

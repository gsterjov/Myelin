
#ifndef MYELIN_OBJECT_H_
#define MYELIN_OBJECT_H_


#include <string>


namespace Myelin
{

	/* forward declaration */
	class Value;
	class List;
	
	
	
	class Object
	{
	public:
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
		
		
		/*
		 * Set the object instance to use.
		 */
		virtual void setInstance (void* instance) = 0;
		
		/*
		 * Set the object instance being used.
		 */
		virtual void* getInstance () const = 0;
		
		
		
	protected:
		/**
		 * Call the function on the object.
		 */
		virtual Value callImpl (const std::string& function,
		                        const List& params) const = 0;
	};

}



/* C api forward declaration */
namespace Myelin { class Class; }



/* C api */
extern "C"
{

	Myelin::Object *myelin_object_new (const Myelin::Class *klass,
	                                   const Myelin::List *params);
	
	void myelin_object_free (Myelin::Object *object);
	
	
	Myelin::Value *myelin_object_call (const Myelin::Object *object,
	                                   const char *function,
	                                   const Myelin::List *params);
	
	
	void myelin_object_set_instance (Myelin::Object *object, void *instance);
	
	void *myelin_object_get_instance (const Myelin::Object *object);

}



#endif /* MYELIN_OBJECT_H_ */

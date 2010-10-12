
#ifndef MYELIN_NAMESPACE_H_
#define MYELIN_NAMESPACE_H_


#include <map>
#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{

	/* forward declaration */
	class Class;
	
	
	/* storage */
	typedef std::vector<Class*> ClassList;
	
	/* FIXME: Implement nested namespaces */
	/**
	 * Namespace
	 */
	class MYELIN_API Namespace : public RefCounter
	{
	public:
		/**
		 * Constructor.
		 */
		Namespace (const std::string& name);
		
		/**
		 * Destructor.
		 */
		virtual ~Namespace ();
		
		
		/**
		 * Get namespace name.
		 */
		const std::string& getName() const { return mName; }
		
		
		/**
		 * Add a class to the namespace.
		 */
		void addClass (Class* klass);
		
		
		/**
		 * Get class by name.
		 */
		Class* getClass (const std::string& name) const;
		
		
		/**
		 * Get a list of classes.
		 */
		ClassList getClasses() const;
		
		
	private:
		typedef std::map <std::string, Class*> ClassMap;
		
		std::string mName;
		ClassMap mClasses;
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
	 * Create a new namespace.
	 */
	MYELIN_API Myelin::Namespace *myelin_namespace_new (const char *name);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Namespace *myelin_namespace_ref (Myelin::Namespace *nspace);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_namespace_unref (Myelin::Namespace *nspace);
	
	/**
	 * Get the name of the namespace.
	 */
	MYELIN_API const char *myelin_namespace_get_name (Myelin::Namespace *nspace);
	
	/**
	 * Add the given class to the namespace.
	 */
	MYELIN_API void myelin_namespace_add_class (Myelin::Namespace *nspace,
	                                            Myelin::Class *klass);
	
	/**
	 * Get the named class from the namespace.
	 */
	MYELIN_API Myelin::Class *myelin_namespace_get_class (Myelin::Namespace *nspace,
	                                                      const char *name);
	
	/**
	 * Get a list of all the classes in the namespace.
	 */
	MYELIN_API Myelin::List *myelin_namespace_get_classes (Myelin::Namespace *nspace);

}



#endif /* MYELIN_NAMESPACE_H_ */

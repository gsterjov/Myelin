
#ifndef MYELIN_REPOSITORY_H_
#define MYELIN_REPOSITORY_H_


#include <map>
#include <vector>

#include <Myelin/Config.h>
#include <Myelin/Class.h>


namespace Myelin
{

	/* class storage */
	typedef std::vector<Class*> ClassList;
	typedef std::map<std::string, Class*> ClassMap;
	
	
	
	/**
	 * Repository.
	 */
	class MYELIN_API Repository
	{
	public:
		/**
		 * Constructor.
		 */
		Repository (const std::string& name);
		
		/**
		 * Destructor.
		 */
		virtual ~Repository ();
		
		
		/**
		 * Get repository name.
		 */
		const std::string& getName () const { return mName; }
		
		
		
		/**
		 * Register a class with the repository.
		 */
		void registerClass (Class* klass);
		
		
		/**
		 * Get class by name.
		 */
		Class* getClass (const std::string& name) const;
		
		
		/**
		 * Get a list of classes.
		 */
		ClassList getClassList() const;
		
		
		/**
		 * Get the underlying class mapping.
		 */
		const ClassMap getClassMap() const { return mClassMap; }
		
		
	private:
		std::string mName;
		ClassMap mClassMap;
	};

}



/* C api forward declaration */
namespace Myelin { class List; }



/* C api */
extern "C"
{

	MYELIN_API Myelin::Repository *myelin_repository_new (const char *name);
	
	MYELIN_API void myelin_repository_free (Myelin::Repository *repo);
	
	
	MYELIN_API const char *myelin_repository_get_name (Myelin::Repository *repo);
	
	MYELIN_API Myelin::Class *myelin_repository_get_class (Myelin::Repository *repo,
	                                                       const char *name);
	
	MYELIN_API void myelin_repository_register_class (Myelin::Repository *repo,
	                                                  Myelin::Class *klass);
	
	
	MYELIN_API Myelin::List *myelin_repository_get_class_list (Myelin::Repository *repo);

}



#endif /* MYELIN_REPOSITORY_H_ */

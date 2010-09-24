
#ifndef MYELIN_REPOSITORY_FACTORY_H_
#define MYELIN_REPOSITORY_FACTORY_H_


#include <map>
#include <vector>
#include <string>

#include <Myelin/Config.h>


namespace Myelin
{

	/* forward declarations */
	class Repository;
	
	
	/* repository storage */
	typedef std::vector<Repository*> RepositoryList;
	
	
	/**
	 * Repository factory.
	 */
	class MYELIN_API RepositoryFactory
	{
	public:
		/**
		 * Create a new repository.
		 */
		static Repository* create (const std::string& name);
		
		
		/**
		 * Add a repository to the factory list.
		 */
		static void add (Repository* repo);
		
		
		/**
		 * Get the repository.
		 */
		static Repository* get (const std::string& name);
		
		
		/**
		 * Get a list of repositories.
		 */
		static RepositoryList get();
		
		
	private:
		RepositoryFactory() {}
		
		typedef std::map<std::string, Repository*> RepositoryMap;
		static RepositoryMap mRepoMap;
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
	 * Create a repository and add it to the factory registry.
	 */
	MYELIN_API Myelin::Repository *myelin_repository_factory_create (const char *name);
	
	/**
	 * Get the named repository from the factory registry.
	 */
	MYELIN_API Myelin::Repository *myelin_repository_factory_get (const char *name);
	
	/**
	 * Add a repository to the factory registry.
	 */
	MYELIN_API void myelin_repository_factory_add (Myelin::Repository *repo);
	
	/**
	 * Get a list of all the repositories in the factory registry.
	 */
	MYELIN_API Myelin::List *myelin_repository_factory_get_all ();

}



#endif /* MYELIN_REPOSITORY_FACTORY_H_ */


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
	typedef std::map<std::string, Repository*> RepositoryMap;
	
	
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
		static RepositoryList getRepositoryList();
		
		
		/**
		 * Get the underlying repository mapping.
		 */
		static const RepositoryMap getRepositoryMap() { return mRepoMap; }
		
		
	private:
		RepositoryFactory() {}
		
		static RepositoryMap mRepoMap;
	};

}



/* C api forward declaration */
namespace Myelin { class List; }



/* C api */
extern "C"
{

	MYELIN_API Myelin::Repository *myelin_repository_factory_create (const char *name);
	MYELIN_API Myelin::Repository *myelin_repository_factory_get (const char *name);
	
	MYELIN_API void myelin_repository_factory_add (Myelin::Repository *repo);
	
	MYELIN_API Myelin::List *myelin_repository_factory_get_repository_list ();

}



#endif /* MYELIN_REPOSITORY_FACTORY_H_ */

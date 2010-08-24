
#ifndef MYELIN_REPOSITORY_H_
#define MYELIN_REPOSITORY_H_


#include <map>
#include <vector>
#include <Myelin/Class.h>


namespace Myelin
{

	/* class storage */
	typedef std::vector<Class*> ClassList;
	typedef std::map<std::string, Class*> ClassMap;
	
	
	
	/**
	 * Repository.
	 */
	class Repository
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
	
	
	
	
	/* repository storage */
	typedef std::vector<Repository*> RepositoryList;
	typedef std::map<std::string, Repository*> RepositoryMap;
	
	
	/**
	 * Repository factory.
	 */
	class RepositoryFactory
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

	/* repository */
	Myelin::Repository *myelin_repository_new (const char *name);
	
	void myelin_repository_free (Myelin::Repository *repo);
	
	
	const char *myelin_repository_get_name (Myelin::Repository *repo);
	
	Myelin::Class *myelin_repository_get_class (Myelin::Repository *repo,
	                                            const char *name);
	
	void myelin_repository_register_class (Myelin::Repository *repo,
	                                       Myelin::Class *klass);
	
	
	Myelin::List *myelin_repository_get_class_list (Myelin::Repository *repo);
	
	
	
	/* repository factory */
	Myelin::Repository *myelin_repository_factory_create (const char *name);
	Myelin::Repository *myelin_repository_factory_get (const char *name);
	
	void myelin_repository_factory_add (Myelin::Repository *repo);
	
	Myelin::List *myelin_repository_factory_get_repository_list ();

}



#endif /* MYELIN_REPOSITORY_H_ */

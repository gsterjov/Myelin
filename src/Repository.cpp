

#include "Repository.h"
#include <stdexcept>
#include "List.h"


namespace Myelin
{

	/* repository factory map */
	std::map<std::string, Repository*> RepositoryFactory::mRepoMap;
	
	
	
	/* constructor */
	Repository::Repository (const std::string& name) : mName (name) {}
	
	
	/* destructor */
	Repository::~Repository ()
	{
		ClassMap::iterator iter;
		
		/* free all classes */
		for (iter = mClassMap.begin(); iter != mClassMap.end(); ++iter)
			delete iter->second;
	}
	
	
	
	
	/* register specified class */
	void Repository::registerClass (Class* klass)
	{
		ClassMap::iterator iter;
		
		iter = mClassMap.find (klass->getName());
		
		/* class already exists */
		if (iter != mClassMap.end())
			throw std::runtime_error (
				"A class by the name '" + klass->getName() + "' "
				"already exists in the repository.");
		
		/* add the function to the map */
		mClassMap[klass->getName()] = klass;
	}
	
	
	
	/* get specified class */
	Class* Repository::getClass (const std::string& name) const
	{
		ClassMap::const_iterator iter;
		
		iter = mClassMap.find (name);
		return iter != mClassMap.end() ? iter->second : 0;
	}
	
	
	
	/* get a list of all registered classes */
	ClassList Repository::getClassList() const
	{
		ClassList list;
		ClassMap::const_iterator iter;
		
		/* add all classes in the map */
		for (iter = mClassMap.begin(); iter != mClassMap.end(); ++iter)
			list.push_back (iter->second);
		
		return list;
	}
	
	
	
	/**********************************************
	 * Repository Factory                         *
	 **********************************************/
	
	
	/* create a new repository */
	Repository* RepositoryFactory::create (const std::string& name)
	{
		/* create repo */
		Repository* repo = new Repository (name);
		add (repo);
		
		return repo;
	}
	
	
	
	/* add a repository */
	void RepositoryFactory::add (Repository* repo)
	{
		RepositoryMap::iterator iter;
		
		iter = mRepoMap.find (repo->getName());
		
		/* repo already exists */
		if (iter != mRepoMap.end())
			throw std::runtime_error (
				"A repository by the name '" + repo->getName() + "' "
				"already exists.");
		
		/* add repo */
		mRepoMap[repo->getName()] = repo;
	}
	
	
	
	/* get the specified repository */
	Repository* RepositoryFactory::get (const std::string& name)
	{
		RepositoryMap::iterator iter;
		
		iter = mRepoMap.find (name);
		return iter != mRepoMap.end() ? iter->second : 0;
	}
	
	
	
	/* get a list of all registered repositories */
	RepositoryList RepositoryFactory::getRepositoryList()
	{
		RepositoryList list;
		RepositoryMap::const_iterator iter;
		
		/* add all classes in the map */
		for (iter = mRepoMap.begin(); iter != mRepoMap.end(); ++iter)
			list.push_back (iter->second);
		
		return list;
	}

}





/* C api */
Myelin::Repository *
myelin_repository_new (const char *name)
{
	return new Myelin::Repository (name);
}


void
myelin_repository_free (Myelin::Repository *repo)
{
	delete repo;
}



const char *
myelin_repository_get_name (Myelin::Repository *repo)
{
	return repo->getName().c_str();
}



Myelin::Class *
myelin_repository_get_class (Myelin::Repository *repo, const char *name)
{
	return repo->getClass (name);
}


void
myelin_repository_register_class (Myelin::Repository *repo,
                                  Myelin::Class *klass)
{
	repo->registerClass (klass);
}



Myelin::List *
myelin_repository_get_class_list (Myelin::Repository *repo)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get underlying factory map */
	const Myelin::ClassMap map = repo->getClassMap();
	Myelin::ClassMap::const_iterator iter;
	
	/* add all repos into the list */
	for (iter = map.begin(); iter != map.end(); ++iter)
		list->push_back (iter->second);
	
	return list;
}




/* repository factory C api */
Myelin::Repository *
myelin_repository_factory_create (const char *name)
{
	return Myelin::RepositoryFactory::create (name);
}


Myelin::Repository *
myelin_repository_factory_get (const char *name)
{
	return Myelin::RepositoryFactory::get (name);
}



void
myelin_repository_factory_add (Myelin::Repository *repo)
{
	return Myelin::RepositoryFactory::add (repo);
}



Myelin::List *
myelin_repository_factory_get_repository_list ()
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get underlying factory map */
	const Myelin::RepositoryMap map = Myelin::RepositoryFactory::getRepositoryMap();
	Myelin::RepositoryMap::const_iterator iter;
	
	/* add all repos into the list */
	for (iter = map.begin(); iter != map.end(); ++iter)
		list->push_back (iter->second);
	
	return list;
}



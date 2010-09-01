

#include "RepositoryFactory.h"

#include <stdexcept>
#include "List.h"
#include "Repository.h"
#include <iostream>

namespace Myelin
{

	/* repository factory map */
	std::map<std::string, Repository*> RepositoryFactory::mRepoMap;
	
	
	
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
MYELIN_API Myelin::Repository *
myelin_repository_factory_create (const char *name)
{
	return Myelin::RepositoryFactory::create (name);
}


MYELIN_API Myelin::Repository *
myelin_repository_factory_get (const char *name)
{
	return Myelin::RepositoryFactory::get (name);
}



MYELIN_API void
myelin_repository_factory_add (Myelin::Repository *repo)
{
	return Myelin::RepositoryFactory::add (repo);
}



MYELIN_API Myelin::List *
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



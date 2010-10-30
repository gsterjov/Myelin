

#include "Repository.h"

#include <stdexcept>

#include "List.h"
#include "Namespace.h"


namespace Myelin
{

	/* constructor */
	Repository::Repository (const std::string& name) : mName(name)
	{
		Namespace* root = new Namespace (name);
		mNamespaces[""] = root;
		mNamespaces[name] = root;
	}
	
	
	/* destructor */
	Repository::~Repository ()
	{
		
	}
	
	
	
	/* add namespace to the repository */
	void Repository::addNamespace (Namespace* nspace)
	{
		std::string name = nspace->getName();
		NamespaceMap::iterator iter;
		
		/* look for namespace */
		iter = mNamespaces.find (name);
		
		/* namespace already exists */
		if (iter != mNamespaces.end())
			throw std::runtime_error (
				"A namespace by the name '" + name + "' "
				"already exists in the repository.");
		
		/* add namespace to the map */
		mNamespaces[name] = nspace;
	}
	
	
	
	/* get namespace by name */
	Namespace* Repository::getNamespace (const std::string& name)
	{
		NamespaceMap::iterator iter = mNamespaces.find (name);
		
		/* no namespace found. create it */
		if (iter == mNamespaces.end())
		{
			Namespace* nspace = new Namespace (name);
			mNamespaces[name] = nspace;
			return nspace;
		}
		
		/* existing namespace found */
		else return iter->second;
	}
	
	
	
	/* get namespace list */
	NamespaceList Repository::getNamespaces () const
	{
		NamespaceList list;
		NamespaceMap::const_iterator iter;
		
		/* add all namespace names */
		for (iter = mNamespaces.begin(); iter != mNamespaces.end(); ++iter)
			list.push_back (iter->second);
		
		return list;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Repository *
myelin_repository_new (const char *name)
{
	return new Myelin::Repository (name);
}


Myelin::Repository *
myelin_repository_ref (Myelin::Repository *repo)
{
	repo->ref();
	return repo;
}


void
myelin_repository_unref (Myelin::Repository *repo)
{
	repo->unref();
	if (repo->count() == 0) delete repo;
}



const char *
myelin_repository_get_name (Myelin::Repository *repo)
{
	return repo->getName().c_str();
}


void
myelin_repository_add_namespace (Myelin::Repository *repo,
                                 Myelin::Namespace *nspace)
{
	repo->addNamespace (nspace);
}



Myelin::Namespace *
myelin_repository_get_namespace (Myelin::Repository *repo, const char *name)
{
	return repo->getNamespace (name);
}



Myelin::List *
myelin_repository_get_namespaces (Myelin::Repository *repo)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get all namespaces */
	const Myelin::NamespaceList namespaces = repo->getNamespaces();
	Myelin::NamespaceList::const_iterator iter;
	
	/* add all namespaces into the list */
	for (iter = namespaces.begin(); iter != namespaces.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}



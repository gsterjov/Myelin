

#include "Repository.h"

#include <stdexcept>
#include "List.h"


namespace Myelin
{

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

}





/* C api */
MYELIN_API Myelin::Repository *
myelin_repository_new (const char *name)
{
	return new Myelin::Repository (name);
}


MYELIN_API void
myelin_repository_free (Myelin::Repository *repo)
{
	delete repo;
}



MYELIN_API const char *
myelin_repository_get_name (Myelin::Repository *repo)
{
	return repo->getName().c_str();
}



MYELIN_API Myelin::Class *
myelin_repository_get_class (Myelin::Repository *repo, const char *name)
{
	return repo->getClass (name);
}


MYELIN_API void
myelin_repository_register_class (Myelin::Repository *repo,
                                  Myelin::Class *klass)
{
	repo->registerClass (klass);
}



MYELIN_API Myelin::List *
myelin_repository_get_class_list (Myelin::Repository *repo)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get underlying factory map */
	const Myelin::ClassMap map = repo->getClassMap();
	Myelin::ClassMap::const_iterator iter;
	
	/* add all classes into the list */
	for (iter = map.begin(); iter != map.end(); ++iter)
		list->push_back (iter->second);
	
	return list;
}



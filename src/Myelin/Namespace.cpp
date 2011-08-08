
#include "Namespace.h"

#include <stdexcept>

#include "Class.h"
#include "List.h"


namespace Myelin
{

	/* constructor */
	Namespace::Namespace (const std::string& name) : mName(name) {}
	
	
	/* destructor */
	Namespace::~Namespace ()
	{
		
	}
	
	
	
	/* add specified class */
	void Namespace::addClass (Class* klass)
	{
		std::string name = klass->getName();
		ClassMap::iterator iter;
		
		/* look for class */
		iter = mClasses.find (name);
		
		/* class already exists */
		if (iter != mClasses.end())
			throw std::runtime_error (
				"A class by the name '" + name + "' "
				"already exists in the repository.");
		
		/* add the class to the map */
		mClasses[name] = klass;
		klass->ref();
	}
	
	
	
	/* get specified class */
	Class* Namespace::getClass (const std::string& name) const
	{
		ClassMap::const_iterator iter;
		
		iter = mClasses.find (name);
		return iter != mClasses.end() ? iter->second : 0;
	}
	
	
	
	/* get a list of all registered classes */
	ClassList Namespace::getClasses() const
	{
		ClassList list;
		ClassMap::const_iterator iter;
		
		/* add all classes in the map */
		for (iter = mClasses.begin(); iter != mClasses.end(); ++iter)
			list.push_back (iter->second);
		
		return list;
	}

}






/*****************************************************************************
 **                                                                         **
 **                              C API                                      **
 **                                                                         **
 *****************************************************************************/
Myelin::Namespace *
myelin_namespace_new (const char *name)
{
	return new Myelin::Namespace (name);
}


Myelin::Namespace *
myelin_namespace_ref (Myelin::Namespace *nspace)
{
	nspace->ref();
	return nspace;
}


void
myelin_namespace_unref (Myelin::Namespace *nspace)
{
	nspace->unref();
	if (nspace->count() == 0) delete nspace;
}



const char *
myelin_namespace_get_name (Myelin::Namespace *nspace)
{
	return nspace->getName().c_str();
}


void
myelin_namespace_add_class (Myelin::Namespace *nspace, Myelin::Class *klass)
{
	nspace->addClass (klass);
}


Myelin::Class *
myelin_namespace_get_class (Myelin::Namespace *nspace, const char *name)
{
	return nspace->getClass (name);
}


Myelin::List *
myelin_namespace_get_classes (Myelin::Namespace *nspace)
{
	/* create a new generic list */
	Myelin::List *list = new Myelin::List ();
	
	
	/* get all classes */
	const Myelin::ClassList classes = nspace->getClasses();
	Myelin::ClassList::const_iterator iter;
	
	/* add all repos into the list */
	for (iter = classes.begin(); iter != classes.end(); ++iter)
		list->push_back (*iter);
	
	/* throw away ownership */
	list->unref();
	return list;
}



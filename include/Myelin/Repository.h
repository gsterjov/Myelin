/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MYELIN_REPOSITORY_H_
#define MYELIN_REPOSITORY_H_


#include <map>
#include <vector>
#include <string>

#include <Myelin/Config.h>
#include <Myelin/RefCounter.h>


namespace Myelin
{

	/* forward declaration */
	class Namespace;
	
	
	/* class storage */
	typedef std::vector<Namespace*> NamespaceList;
	
	
	/**
	 * Repository.
	 */
	class MYELIN_API Repository : public RefCounter
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
		 * Add a namespace to the repository.
		 */
		void addNamespace (Namespace* nspace);
		
		
		/**
		 * Get namespace by name.
		 */
		Namespace* getNamespace (const std::string& name);
		
		
		/**
		 * Get a list of namespaces.
		 */
		NamespaceList getNamespaces () const;
		
		
	private:
		std::string mName;
		
		/* repo namespaces */
		typedef std::map<std::string, Namespace*> NamespaceMap;
		NamespaceMap mNamespaces;
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
	 * Create a new repository.
	 */
	MYELIN_API Myelin::Repository *myelin_repository_new (const char *name);
	
	/**
	 * Increase the reference count.
	 */
	MYELIN_API Myelin::Repository *myelin_repository_ref (Myelin::Repository *repo);
	
	/**
	 * Decrease the reference count.
	 */
	MYELIN_API void myelin_repository_unref (Myelin::Repository *repo);
	
	/**
	 * Get the name of the repository.
	 */
	MYELIN_API const char *myelin_repository_get_name (Myelin::Repository *repo);
	
	/**
	 * Add the given namespace to the repository.
	 */
	MYELIN_API void myelin_repository_add_namespace (Myelin::Repository *repo,
	                                      Myelin::Namespace *nspace);
	
	/**
	 * Get the named namespace from the repository.
	 */
	MYELIN_API Myelin::Namespace *myelin_repository_get_namespace (Myelin::Repository *repo,
	                                                    const char *name);
	
	/**
	 * Get a list of all the namespaces in the repository.
	 */
	MYELIN_API Myelin::List *myelin_repository_get_namespaces (Myelin::Repository *repo);

}



#endif /* MYELIN_REPOSITORY_H_ */

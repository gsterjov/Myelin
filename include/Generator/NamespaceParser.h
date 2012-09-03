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

#ifndef NAMESPACEPARSER_H_
#define NAMESPACEPARSER_H_


#include <map>
#include <string>

#include <ClassParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


/* forward declarations */
class NamespaceParser;


/**
 * A map of namespaces.
 */
typedef std::map<std::string, const NamespaceParser*> NamespaceMap;



class NamespaceParser
{
public:
	/**
	 * Constructor.
	 */
	NamespaceParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~NamespaceParser ();
	
	
	/**
	 * Get the namespace name.
	 */
	const std::string& getName() const { return mName; }
	
	
	/**
	 * Get a specific nested namespace.
	 */
	//const NamespaceParser* getNamespace (const std::string& name) const;
	
	/**
	 * Get a specific class in this namespace scope.
	 */
	const ClassParser* getClass (const std::string& name) const;
	
	
	/**
	 * Get a list of all nested namespaces.
	 */
	const NamespaceMap& getNamespaces() const { return mNamespaces; }
	
	/**
	 * Get a list of all classes in this namespace scope.
	 */
	const ClassMap& getClasses() const { return mClasses; }
	
	
private:
	std::string mName;
	
	/* children */
	NamespaceMap mNamespaces;
	ClassMap mClasses;
};


#endif /* NAMESPACEPARSER_H_ */

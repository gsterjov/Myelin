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

#ifndef CLASSPARSER_H_
#define CLASSPARSER_H_


#include <map>
#include <string>

#include <TypedefParser.h>
#include <FunctionParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


/* forward declarations */
class ClassParser;


/**
 * A map of typedefs.
 */
typedef std::map<std::string, const TypedefParser*> TypedefMap;

/**
 * A map of classes.
 */
typedef std::map<std::string, const ClassParser*> ClassMap;

/**
 * A map of functions.
 */
typedef std::map<std::string, const FunctionParser*> FunctionMap;



class ClassParser
{
public:
	/**
	 * Constructor.
	 */
	ClassParser (pANTLR3_BASE_TREE tree);
	
	/**
	 * Destructor.
	 */
	~ClassParser ();
	
	
	/**
	 * Get the class name.
	 */
	const std::string& getName() const { return mName; }
	
	
	/**
	 * Get a specific typedef defined in this class.
	 */
	const TypedefParser* getTypedef (const std::string& name) const;
	
	/**
	 * Get a specific nested class.
	 */
	const ClassParser* getClass (const std::string& name) const;
	
	/**
	 * Get a specific member function.
	 */
	const FunctionParser* getFunction (const std::string& name) const;
	
	
	/**
	 * Get a list of all typedefs in this class.
	 */
	const ClassMap& getTypedefs() const { return mClasses; }
	
	/**
	 * Get a list of all classes in this class.
	 */
	const ClassMap& getClasses() const { return mClasses; }
	
	/**
	 * Get a list of member functions.
	 */
	const FunctionMap& getFunctions() const { return mFunctions; }
	
	
private:
	std::string mName;
	
	/* children */
	TypedefMap mTypedefs;
	ClassMap mClasses;
	FunctionMap mFunctions;
};


#endif /* CLASSPARSER_H_ */

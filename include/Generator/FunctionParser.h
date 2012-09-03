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

#ifndef FUNCTIONPARSER_H_
#define FUNCTIONPARSER_H_


#include <string>
#include <vector>

#include <TypeParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


/**
 * A list of types.
 */
typedef std::vector<const TypeParser*> TypeList;



class FunctionParser
{
public:
	/**
	 * Constructor.
	 */
	FunctionParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~FunctionParser ();
	
	
	/**
	 * Get the function name.
	 */
	const std::string& getName() const { return mName; }
	
	
	/**
	 * Get the return type of the function.
	 */
	const TypeParser* getReturnType() const { return mReturnType; }
	
	
	/**
	 * Is the function a constant?
	 * This is only really helpfull for member functions.
	 */
	bool isConstant() const { return mConstant; }
	
	
	/**
	 * Get a list of all parameter types for the function.
	 */
	const TypeList& getParameters() const { return mParameters; }
	
	
private:
	std::string mName;
	TypeParser* mReturnType;
	bool mConstant;
	
	TypeList mParameters;
};


#endif /* FUNCTIONPARSER_H_ */

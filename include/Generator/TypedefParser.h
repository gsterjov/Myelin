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

#ifndef TYPEDEFPARSER_H_
#define TYPEDEFPARSER_H_


#include <string>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


class TypedefParser
{
public:
	/**
	 * Constructor.
	 */
	TypedefParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~TypedefParser ();
	
	
	/**
	 * Get the typedef name.
	 */
	const std::string& getName() const { return mName; }
	
	
private:
	std::string mName;
};


#endif /* TYPEDEFPARSER_H_ */

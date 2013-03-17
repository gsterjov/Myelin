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

#ifndef TYPEPARSER_H_
#define TYPEPARSER_H_


#include <string>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>


class TypeParser
{
public:
	/**
	 * Type flags.
	 */
	enum Flags
	{
		TYPE_NONE      = 1 << 0,
		TYPE_POINTER   = 1 << 1,
		TYPE_REFERENCE = 1 << 2,
		TYPE_CONSTANT  = 1 << 3,
		TYPE_VOLATILE  = 1 << 4
	};
	
	
	/**
	 * Constructor.
	 */
	TypeParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~TypeParser ();
	
	
	/**
	 * Get the type name.
	 */
	const std::string& getName() const { return mName; }
	
	
	bool isConstant() const { return mFlags & TYPE_CONSTANT; }
	bool isVolatile() const { return mFlags & TYPE_VOLATILE; }
	
	bool isPointer()         const { return mPointerFlags & TYPE_POINTER; }
	bool isConstantPointer() const { return mPointerFlags & TYPE_CONSTANT; }
	bool isVolatilePointer() const { return mPointerFlags & TYPE_VOLATILE; }
	
	bool isReference()         const { return mReferenceFlags & TYPE_REFERENCE; }
	bool isConstantReference() const { return mReferenceFlags & TYPE_CONSTANT; }
	bool isVolatileReference() const { return mReferenceFlags & TYPE_VOLATILE; }
	
	
private:
	std::string mName;
	
	Flags mFlags;
	Flags mPointerFlags;
	Flags mReferenceFlags;
	
	
	/* utility methods */
	Flags parse_qualifiers (pANTLR3_BASE_TREE tree);
	Flags parse_pointer    (pANTLR3_BASE_TREE tree);
	Flags parse_reference  (pANTLR3_BASE_TREE tree);
};


#endif /* TYPEPARSER_H_ */

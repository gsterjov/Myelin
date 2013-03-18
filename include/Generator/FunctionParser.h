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


/**
 * A list of types.
 */
typedef std::vector<const TypeParser*> TypeList;



class FunctionParser
{
public:
	/**
	 * Storage classes
	 */
	 enum StorageClass
	 {
	 	STORAGE_CLASS_NONE,
	 	STORAGE_CLASS_STATIC,
	 	STORAGE_CLASS_EXTERN,
	 	STORAGE_CLASS_REGISTER
	 };

	/**
	 * Storage qualifiers
	 */
	 enum StorageQualifiers
	 {
	 	STORAGE_QUALIFIER_NONE		= 0,
	 	STORAGE_QUALIFIER_CONSTANT	= 1 << 0,
	 	STORAGE_QUALIFIER_VOLATILE	= 1 << 1,
	 };


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
	 * Get the storage class of the function.
	 */
	StorageClass getStorageClass() const { return mStorageClass; }


	/**
	 * Get the storage qualifiers of the function.
	 */
	StorageQualifiers getStorageQualifiers() const { return static_cast<StorageQualifiers> (mStorageQualifiers); }


	/**
	 * Whether or not the function is a constant.
	 * This is just a convenience method to check the storage qualifier flags for the constant flag.
	 */
	bool isConstant() const { return mStorageQualifiers & STORAGE_QUALIFIER_CONSTANT == STORAGE_QUALIFIER_CONSTANT; }

	/**
	 * Whether or not the function is volatile.
	 * This is just a convenience method to check the storage qualifier flags for the volatile flag.
	 */
	bool isVolatile() const { return mStorageQualifiers & STORAGE_QUALIFIER_VOLATILE == STORAGE_QUALIFIER_VOLATILE; }
	
	
	/**
	 * Get a list of all parameter types for the function.
	 */
	const TypeList& getParameters() const { return mParameters; }
	
	
private:
	std::string mName;
	TypeParser* mReturnType;

	StorageClass mStorageClass;
	int mStorageQualifiers;
	
	TypeList mParameters;
};


#endif /* FUNCTIONPARSER_H_ */

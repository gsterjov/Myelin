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

#ifndef PARSER_H_
#define PARSER_H_


#include <string>

#include <NamespaceParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>


class Parser
{
public:
	/**
	 * Constructor.
	 */
	Parser ();
	
	/**
	 * Destructor.
	 */
	~Parser ();
	
	/**
	 * Open the header file to be parsed.
	 */
	bool open (const std::string& path);
	
	/**
	 * Load the specified string to be parsed.
	 */
	bool load (const std::string& input);
	
	/**
	 * Close the header file.
	 */
	void close ();
	
	
	/**
	 * Parse the opened header file.
	 */
	bool parse ();
	
	
	/**
	 * Get the root namespace of the header.
	 * 
	 * This would not be a named namespace but rather everything in the
	 * header file.
	 */
	const NamespaceParser* getRoot() const { return mRoot; }
	
	
	
private:
	std::string mPath;
	NamespaceParser* mRoot;
	
	
	pANTLR3_INPUT_STREAM            mInput;
	pANTLR3_COMMON_TOKEN_STREAM     mTokens;
	
	pCppHeaderLexer  mLexer;
	pCppHeaderParser mParser;
};


#endif /* PARSER_H_ */

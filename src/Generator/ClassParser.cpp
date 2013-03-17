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

#include "ClassParser.h"


/* constructor */
ClassParser::ClassParser (pANTLR3_BASE_TREE tree)
{
	/* iterate through all parsed children elements */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		/* get the child element */
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			/* got the actual class name */
			case ID:
			{
				mName = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
			}
			
			/* got a class member function */
			case NODE_FUNCTION:
			{
				FunctionParser* func = new FunctionParser (child);
				mFunctions[func->getName()] = func;
				break;
			}
			
			/* got a nested class */
			case NODE_CLASS:
			{
				ClassParser* klass = new ClassParser (child);
				mClasses[klass->getName()] = klass;
				break;
			}
			
			/* got a nested typedef */
			case NODE_TYPEDEF:
			{
				TypedefParser* type_def = new TypedefParser (child);
				mTypedefs[type_def->getName()] = type_def;
				break;
			}
		}
	}
}


/* destructor */
ClassParser::~ClassParser ()
{
	
}



/* get specific typedef */
const TypedefParser* ClassParser::getTypedef (const std::string& name) const
{
	TypedefMap::const_iterator iter = mTypedefs.find(name);
	return iter != mTypedefs.end() ? iter->second : NULL;
}


/* get specific class */
const ClassParser* ClassParser::getClass (const std::string& name) const
{
	ClassMap::const_iterator iter = mClasses.find(name);
	return iter != mClasses.end() ? iter->second : NULL;
}


/* get specific member function */
const FunctionParser* ClassParser::getFunction (const std::string& name) const
{
	FunctionMap::const_iterator iter = mFunctions.find(name);
	return iter != mFunctions.end() ? iter->second : NULL;
}

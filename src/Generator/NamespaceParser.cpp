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

#include "NamespaceParser.h"


/* constructor */
NamespaceParser::NamespaceParser (pANTLR3_BASE_TREE tree)
{
	/* iterate through all parsed children elements */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		/* get the child element */
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		/* note that we dont bother with typedefs. since the introspection
		 * wrapper is added to a nested namespace of this one it will inherit
		 * all typedefs and doesn't need to be fully qualified. this does
		 * lose value for any code analysis programs however */
		switch (child->getType (child))
		{
			/* got the actual namespace name */
			case ID:
			{
				mName = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
			}
			
			/* got a nested namespace */
			case NODE_NAMESPACE:
			{
				NamespaceParser* nspace = new NamespaceParser (child);
				mNamespaces[nspace->getName()] = nspace;
				break;
			}
			
			/* got a function within the namespace scope */
			case NODE_FUNCTION:
			{
				FunctionParser* func = new FunctionParser (child);
				mFunctions[func->getName()] = func;
				break;
			}
			
			/* got a class within the namespace scope */
			case NODE_CLASS:
			{
				ClassParser* klass = new ClassParser (child);
				mClasses[klass->getName()] = klass;
				break;
			}
		}
	}
}


/* destructor */
NamespaceParser::~NamespaceParser ()
{
	
}


/* get specific namespace */
const NamespaceParser* NamespaceParser::getNamespace (const std::string& name) const
{
	NamespaceMap::const_iterator iter = mNamespaces.find(name);
	return iter != mNamespaces.end() ? iter->second : NULL;
}


/* get specific class */
const ClassParser* NamespaceParser::getClass (const std::string& name) const
{
	ClassMap::const_iterator iter = mClasses.find(name);
	return iter != mClasses.end() ? iter->second : NULL;
}


/* get specific function */
const FunctionParser* NamespaceParser::getFunction (const std::string& name) const
{
	FunctionMap::const_iterator iter = mFunctions.find(name);
	return iter != mFunctions.end() ? iter->second : NULL;
}
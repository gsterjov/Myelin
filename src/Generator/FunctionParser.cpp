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

#include "FunctionParser.h"
#include <iostream>


/* constructor */
FunctionParser::FunctionParser (pANTLR3_BASE_TREE tree) : mStorageQualifiers(STORAGE_QUALIFIER_NONE), mStorageClass(STORAGE_CLASS_NONE)
{
	/* iterate through all parsed children elements */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		/* get the child element */
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			/* got the actual function name */
			case ID:
			{
				mName = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
			}
			
			/* got the return type */
			case NODE_TYPE:
			{
				mReturnType = new TypeParser (child);
				break;
			}
			
			/* got a parameter type */
			case NODE_PARAMETER:
			{
				pANTLR3_BASE_TREE param = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				mParameters.push_back (new TypeParser (param));
				break;
			}
			
			/* got a storage qualifier */
			case NODE_STORAGE_CLASS:
			{
				pANTLR3_BASE_TREE qual = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				std::string str = reinterpret_cast <const char*> (qual->getText(qual)->chars);

				if (str == "static") mStorageClass = STORAGE_CLASS_STATIC;
				else if (str == "extern") mStorageClass = STORAGE_CLASS_EXTERN;
				else if (str == "register") mStorageClass = STORAGE_CLASS_REGISTER;
				break;
			}
			
			/* got a cv qualifier */
			case NODE_STORAGE_QUALIFIER:
			{
				pANTLR3_BASE_TREE qual = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				std::string str = reinterpret_cast <const char*> (qual->getText(qual)->chars);

				if (str == "const") mStorageQualifiers |= STORAGE_QUALIFIER_CONSTANT;
				else if (str == "volatile") mStorageQualifiers |= STORAGE_QUALIFIER_VOLATILE;
				break;
			}
		}
	}
}


/* destructor */
FunctionParser::~FunctionParser ()
{
	
}

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


/* constructor */
FunctionParser::FunctionParser (pANTLR3_BASE_TREE tree) : mConstant(false)
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
			case TYPE:
			{
				mReturnType = new TypeParser (child);
				break;
			}
			
			/* got a parameter type */
			case PARAMETER:
			{
				pANTLR3_BASE_TREE param = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				mParameters.push_back (new TypeParser (param));
				break;
			}
			
			/* got a qualifier */
			case QUALIFIERS:
			{
				/* get all qualifiers */
				for (int j=0; j < child->getChildCount(child); ++j)
				{
					pANTLR3_BASE_TREE qual = (pANTLR3_BASE_TREE)child->getChild (child, j);
					std::string str = reinterpret_cast <const char*> (qual->getText(qual)->chars);
					
					/* function is constant */
					if (str == "const") mConstant = true;
				}
				break;
			}
		}
	}
}


/* destructor */
FunctionParser::~FunctionParser ()
{
	
}

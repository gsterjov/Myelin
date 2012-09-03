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
TypedefParser::TypedefParser (pANTLR3_BASE_TREE tree)
{
	/* iterate through all parsed children elements */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		/* get the child element */
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			/* got the actual typedef name */
			case ID:
			{
				mName = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
			}
		}
	}
}


/* destructor */
TypedefParser::~TypedefParser ()
{
	
}

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

#include "TypeParser.h"

/* constructor */
TypeParser::TypeParser (pANTLR3_BASE_TREE tree)
: mFlags          (TYPE_NONE),
  mPointerFlags   (TYPE_NONE),
  mReferenceFlags (TYPE_NONE)
{
	/* iterate through all parsed children elements */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		/* get the child element */
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);

		switch (child->getType (child))
		{
			/* got a type name. we can have my typenames which form a scoped
			 * type. as such they are in order and each extra type name will
			 * be added to the fully qualified name */
			case NODE_TYPE_NAME:
			{
				/* append the name to the scope */
				if (mName.size() > 0)
					mName += "::";
				
				/* the child of the type name is the non-scoped identifier */
				pANTLR3_BASE_TREE type_child = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				mName += reinterpret_cast <const char*> (type_child->getText(type_child)->chars);
				break;
			}

			/* got a primitive type */
			case NODE_PRIMITIVE:
			{
				pANTLR3_BASE_TREE primitive = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				mName = reinterpret_cast <const char*> (primitive->getText(primitive)->chars);
				break;
			}
			
			/* we got a type qualifier */
			case NODE_STORAGE_QUALIFIER:
			{
				int val = static_cast<int> (mFlags) | parse_qualifiers (child);
				mFlags = static_cast<Flags> (val);
				break;
			}
			
			/* the type is a pointer */
			case NODE_POINTER:
			{
				mPointerFlags = parse_pointer (child);
				break;
			}
			
			/* the type is a reference */
			case NODE_REFERENCE:
			{
				mReferenceFlags = parse_reference (child);
				break;
			}
		}
	}
}


/* destructor */
TypeParser::~TypeParser ()
{
	
}



/* parse type qualifiers */
TypeParser::Flags TypeParser::parse_qualifiers (pANTLR3_BASE_TREE tree)
{
	pANTLR3_BASE_TREE qual = (pANTLR3_BASE_TREE)tree->getChild (tree, 0);
	std::string str = reinterpret_cast <const char*> (qual->getText(qual)->chars);		

	if      (str == "const")    return TYPE_CONSTANT;
	else if (str == "volatile") return TYPE_VOLATILE;

	return TYPE_NONE;
}


/* parse pointer types */
TypeParser::Flags TypeParser::parse_pointer (pANTLR3_BASE_TREE tree)
{
	int flags = 0;
	
	/* get all qualifiers for the pointer */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			/* got a qualifier for the pointer */
			case NODE_STORAGE_QUALIFIER:
				flags |= parse_qualifiers (child);
				break;
		}
	}
	
	flags |= TYPE_POINTER;
	return static_cast<Flags> (flags);
}


/* parse reference types */
TypeParser::Flags TypeParser::parse_reference (pANTLR3_BASE_TREE tree)
{
	int flags = 0;
	
	/* get all qualifiers for the reference */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			/* got a qualifier for the reference */
			case NODE_STORAGE_QUALIFIER:
				flags |=  parse_qualifiers (child);
				break;
		}
	}
	
	flags |= TYPE_REFERENCE;
	return static_cast<Flags> (flags);
}


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
			case TYPE_NAME:
			{
				/* append the name to the scope */
				if (mName.size() > 0)
					mName += "::";
				
				/* the child of the type name is the non-scoped identifier */
				pANTLR3_BASE_TREE type_child = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				mName += reinterpret_cast <const char*> (type_child->getText(type_child)->chars);
				break;
			}
			
			/* we got a type qualifier */
			case QUALIFIERS:
			{
				mFlags = parse_qualifiers (child);
				break;
			}
			
			/* the type is a pointer */
			case POINTER:
			{
				mPointerFlags = parse_pointer (child);
				break;
			}
			
			/* the type is a reference */
			case REFERENCE:
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
	int flags = 0;
	
	/* get all qualifiers for the component */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		std::string str = reinterpret_cast <const char*> (child->getText(child)->chars);
		
		if      (str == "const")    flags |= TYPE_CONSTANT;
		else if (str == "volatile") flags |= TYPE_VOLATILE;
	}
	
	return static_cast<Flags> (flags);
}


/* parse pointer types */
TypeParser::Flags TypeParser::parse_pointer (pANTLR3_BASE_TREE tree)
{
	int flags = 0;
	
	/* get all qualifiers for the pointer */
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (tree))
		{
			/* got a qualifier for the pointer */
			case QUALIFIERS:
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
		
		switch (child->getType (tree))
		{
			/* got a qualifier for the reference */
			case QUALIFIERS:
				flags |=  parse_qualifiers (child);
				break;
		}
	}
	
	flags |= TYPE_REFERENCE;
	return static_cast<Flags> (flags);
}

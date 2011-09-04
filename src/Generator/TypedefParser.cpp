
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

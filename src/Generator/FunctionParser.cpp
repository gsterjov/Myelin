
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


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
			case NAMESPACE:
			{
				NamespaceParser* nspace = new NamespaceParser (child);
				mNamespaces[nspace->getName()] = nspace;
				break;
			}
			
			/* got a function within the namespace scope */
			case FUNCTION:
			{
				break;
			}
			
			/* got a class within the namespace scope */
			case CLASS:
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


/* get specific class */
const ClassParser* NamespaceParser::getClass (const std::string& name) const
{
	ClassMap::const_iterator iter = mClasses.find(name);
	return iter != mClasses.end() ? iter->second : NULL;
}

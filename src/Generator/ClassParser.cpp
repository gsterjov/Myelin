
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
			case FUNCTION:
			{
				FunctionParser* func = new FunctionParser (child);
				mFunctions[func->getName()] = func;
				break;
			}
			
			/* got a nested class */
			case CLASS:
			{
				ClassParser* klass = new ClassParser (child);
				mClasses[klass->getName()] = klass;
				break;
			}
			
			/* got a nested typedef */
			case TYPEDEF:
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

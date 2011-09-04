
#include "Parser.h"

#include <iostream>


/* constructor */
Parser::Parser () : mRoot(NULL)
{
	
}


/* destructor */
Parser::~Parser ()
{
	
}



/* open the header file */
bool Parser::open (const std::string& path)
{
	mPath = path;
	
	/* load input */
	mInput = antlr3AsciiFileStreamNew ((pANTLR3_UINT8)path.c_str());
	
	if (!mInput)
	{
		std::cerr << "Failed to open file: " << path << std::endl;
		return false;
	}
	
	
	/* create lexer and parser */
	mLexer = CppHeaderLexerNew (mInput);
	mTokens = antlr3CommonTokenStreamSourceNew (ANTLR3_SIZE_HINT, TOKENSOURCE(mLexer));
	mParser = CppHeaderParserNew (mTokens);
	
	return true;
}



/* close the header file */
void Parser::close ()
{
	mTree->free (mTree);
	mNodes->free (mNodes);
	
	mParser->free (mParser);
	mTokens->free (mTokens);
	
	mLexer->free (mLexer);
	mInput->close (mInput);
}




/* parse the opened header file */
bool Parser::parse ()
{
	/* parse the file into an AST */
	CppHeaderParser_source_return ast = mParser->source (mParser);
	
	/* parsing failed */
	if (!ast.tree)
	{
		std::cerr << "Failed to create an AST from the file '" << mPath << "'" << std::endl;
		return false;
	}
	
	
	/* dump AST tree */
	//std::cout << "Tree: " << ast.tree->toStringTree(ast.tree)->chars << std::endl;
	
	
	/* create a tree from the AST */
	mNodes = antlr3CommonTreeNodeStreamNewTree (ast.tree, ANTLR3_SIZE_HINT);
	mTree = CppHeaderTreeNew (mNodes);
	
	
	/* parse tree */
	CppHeaderTree_source_return source = mTree->source (mTree);
	
	
	/* dump parsed tree */
	//std::cout << "Tree: " << source.tree->toStringTree(source.tree)->chars << std::endl;
	
	
	mRoot = new NamespaceParser (source.tree);
	return true;
}




#if 0

std::string Parser::parseQualifiers (pANTLR3_BASE_TREE tree)
{
	std::string str;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		str += reinterpret_cast <const char*> (child->getText(child)->chars);
	}
	
	return str;
}


std::string Parser::parsePointer (pANTLR3_BASE_TREE tree)
{
	std::string str;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (tree))
		{
			case QUALIFIERS:
				str += parseQualifiers (child);
				str += " ";
				break;
				
			default:
				str += reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
		}
	}
	
	return str;
}


std::string Parser::parseReference (pANTLR3_BASE_TREE tree)
{
	std::string str;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (tree))
		{
			case QUALIFIERS:
				str += parseQualifiers (child);
				str += " ";
				break;
				
			default:
				str += reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
		}
	}
	
	return str;
}





Header::Type Parser::parseType (pANTLR3_BASE_TREE tree)
{
	Header::Type type;
	
	std::string name;
	std::string qualifiers;
	std::string ending;
	
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case TYPE_NAME:
			{
				if (name.size() > 0)
					name += "::";
				
				pANTLR3_BASE_TREE type_child = (pANTLR3_BASE_TREE)child->getChild (child, 0);
				name += reinterpret_cast <const char*> (type_child->getText(type_child)->chars);
				break;
			}
			case QUALIFIERS:
				qualifiers += parseQualifiers (child);
				break;
			
			case POINTER:
				ending += parsePointer (child);
				break;
			
			case REFERENCE:
				ending += parseReference (child);
				break;
		}
	}
	
	if (qualifiers.size() > 0)
		qualifiers += " ";
	
	if (ending.size() > 0)
		name += " ";
	
	type.name = qualifiers + name + ending;
	return type;
}



Header::Typedef Parser::parseTypedef (pANTLR3_BASE_TREE tree)
{
	Header::Typedef type_def;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case ID:
				type_def.name = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
		}
	}
	
	return type_def;
}



Header::Type Parser::parseParameter (pANTLR3_BASE_TREE tree)
{
	Header::Type type;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case TYPE:
				type = parseType (child);
				break;
		}
	}
	
	
	return type;
}



Header::Function Parser::parseFunction (pANTLR3_BASE_TREE tree)
{
	Header::Function func;
	func.isConst = false;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case TYPE:
				func.return_type = parseType (child);
				break;

			case PARAMETER:
				func.parameters.push_back (parseParameter (child));
				break;
				
			case ID:
				func.name = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
				
			case QUALIFIERS:
				func.isConst = parseQualifiers(child) == "const";
				break;
		}
	}
	
	
	return func;
}



Header::Class Parser::parseClass (pANTLR3_BASE_TREE tree)
{
	Header::Class klass;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case FUNCTION:
				klass.functions.push_back (parseFunction (child));
				break;
				
			case CLASS:
				klass.classes.push_back (parseClass (child));
				break;
				
			case TYPEDEF:
				klass.typedefs.push_back (parseTypedef (child));
				break;
				
			case ID:
				klass.name = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
		}
	}
	
	return klass;
}



Header::Namespace Parser::parseNamespace (pANTLR3_BASE_TREE tree)
{
	Header::Namespace nspace;
	
	for (int i=0; i < tree->getChildCount(tree); ++i)
	{
		pANTLR3_BASE_TREE child = (pANTLR3_BASE_TREE)tree->getChild (tree, i);
		
		switch (child->getType (child))
		{
			case FUNCTION:
				nspace.functions.push_back (parseFunction (child));
				break;

			case CLASS:
				nspace.classes.push_back (parseClass (child));
				break;
				
			case ID:
				nspace.name = reinterpret_cast <const char*> (child->getText(child)->chars);
				break;
		}
	}
	
	return nspace;
}

#endif

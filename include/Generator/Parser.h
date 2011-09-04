
#ifndef PARSER_H_
#define PARSER_H_


#include <string>

#include <NamespaceParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


class Parser
{
public:
	/**
	 * Constructor.
	 */
	Parser ();
	
	/**
	 * Destructor.
	 */
	~Parser ();
	
	/**
	 * Open the header file to be parsed.
	 */
	bool open (const std::string& path);
	
	/**
	 * Close the header file.
	 */
	void close ();
	
	
	/**
	 * Parse the opened header file.
	 */
	bool parse ();
	
	
	/**
	 * Get the root namespace of the header.
	 * 
	 * This would not be a named namespace but rather everything in the
	 * header file.
	 */
	const NamespaceParser* getRoot() const { return mRoot; }
	
	
	
private:
	std::string mPath;
	NamespaceParser* mRoot;
	
	
	pANTLR3_INPUT_STREAM            mInput;
	pANTLR3_COMMON_TOKEN_STREAM     mTokens;
	pANTLR3_COMMON_TREE_NODE_STREAM mNodes;
	
	pCppHeaderLexer  mLexer;
	pCppHeaderParser mParser;
	pCppHeaderTree   mTree;
};


#endif /* PARSER_H_ */

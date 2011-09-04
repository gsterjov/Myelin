
#ifndef TYPEDEFPARSER_H_
#define TYPEDEFPARSER_H_


#include <string>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


class TypedefParser
{
public:
	/**
	 * Constructor.
	 */
	TypedefParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~TypedefParser ();
	
	
	/**
	 * Get the typedef name.
	 */
	const std::string& getName() const { return mName; }
	
	
private:
	std::string mName;
};


#endif /* TYPEDEFPARSER_H_ */

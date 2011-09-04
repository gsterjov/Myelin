
#ifndef FUNCTIONPARSER_H_
#define FUNCTIONPARSER_H_


#include <string>
#include <vector>

#include <TypeParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


/**
 * A list of types.
 */
typedef std::vector<const TypeParser*> TypeList;



class FunctionParser
{
public:
	/**
	 * Constructor.
	 */
	FunctionParser (pANTLR3_BASE_TREE);
	
	/**
	 * Destructor.
	 */
	~FunctionParser ();
	
	
	/**
	 * Get the function name.
	 */
	const std::string& getName() const { return mName; }
	
	
	/**
	 * Get the return type of the function.
	 */
	const TypeParser* getReturnType() const { return mReturnType; }
	
	
	/**
	 * Is the function a constant?
	 * This is only really helpfull for member functions.
	 */
	bool isConstant() const { return mConstant; }
	
	
	/**
	 * Get a list of all parameter types for the function.
	 */
	const TypeList& getParameters() const { return mParameters; }
	
	
private:
	std::string mName;
	TypeParser* mReturnType;
	bool mConstant;
	
	TypeList mParameters;
};


#endif /* FUNCTIONPARSER_H_ */

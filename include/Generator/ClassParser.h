
#ifndef CLASSPARSER_H_
#define CLASSPARSER_H_


#include <map>
#include <string>

#include <TypedefParser.h>
#include <FunctionParser.h>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>


/* forward declarations */
class ClassParser;


/**
 * A map of typedefs.
 */
typedef std::map<std::string, const TypedefParser*> TypedefMap;

/**
 * A map of classes.
 */
typedef std::map<std::string, const ClassParser*> ClassMap;

/**
 * A map of functions.
 */
typedef std::map<std::string, const FunctionParser*> FunctionMap;



class ClassParser
{
public:
	/**
	 * Constructor.
	 */
	ClassParser (pANTLR3_BASE_TREE tree);
	
	/**
	 * Destructor.
	 */
	~ClassParser ();
	
	
	/**
	 * Get the class name.
	 */
	const std::string& getName() const { return mName; }
	
	
	/**
	 * Get a specific typedef defined in this class.
	 */
	const TypedefParser* getTypedef (const std::string& name) const;
	
	/**
	 * Get a specific nested class.
	 */
	const ClassParser* getClass (const std::string& name) const;
	
	/**
	 * Get a specific member function.
	 */
	const FunctionParser* getFunction (const std::string& name) const;
	
	
	/**
	 * Get a list of all typedefs in this class.
	 */
	const ClassMap& getTypedefs() const { return mClasses; }
	
	/**
	 * Get a list of all classes in this class.
	 */
	const ClassMap& getClasses() const { return mClasses; }
	
	/**
	 * Get a list of member functions.
	 */
	const FunctionMap& getFunctions() const { return mFunctions; }
	
	
private:
	std::string mName;
	
	/* children */
	TypedefMap mTypedefs;
	ClassMap mClasses;
	FunctionMap mFunctions;
};


#endif /* CLASSPARSER_H_ */

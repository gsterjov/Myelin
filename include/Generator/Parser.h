
#ifndef PARSER_H_
#define PARSER_H_


#include <string>
#include <vector>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <CppHeaderTree.h>



class Header
{
public:
	struct Type
	{
		std::string name;
	};
	
	struct Typedef
	{
		std::string name;
	};
	
	struct Function
	{
		std::string name;
		Type return_type;
		std::vector<Type> parameters;
		bool isConst;
	};
	
	struct Class
	{
		std::string name;
		std::vector<Function> functions;
		std::vector<Typedef> typedefs;
	};
	
	struct Namespace
	{
		std::string name;
		std::vector<Class> classes;
		std::vector<Function> functions;
		std::vector<Typedef> typedefs;
	};
	
	
	const std::vector<Function>&  getFunctions()  const { return mFunctions; }
	const std::vector<Class>&     getClasses()    const { return mClasses; }
	const std::vector<Namespace>& getNamespaces() const { return mNamespaces; }
	const std::vector<Typedef>&   getTypedefs()   const { return mTypedefs; }
	
	
	void addFunction  (Function func)    { mFunctions.push_back  (func); }
	void addClass     (Class klass)      { mClasses.push_back    (klass); }
	void addNamespace (Namespace nspace) { mNamespaces.push_back (nspace); }
	void addTypedef   (Typedef type_def) { mTypedefs.push_back   (type_def); }
	
	
private:
	std::vector<Function>  mFunctions;
	std::vector<Class>     mClasses;
	std::vector<Namespace> mNamespaces;
	std::vector<Typedef>   mTypedefs;
};



class Parser
{
public:
	Parser ();
	~Parser ();
	
	bool open (const std::string& path);
	void close ();
	
	
	Header parse ();
	
	
	
private:
	std::string mPath;
	
	pANTLR3_INPUT_STREAM            mInput;
	pANTLR3_COMMON_TOKEN_STREAM     mTokens;
	pANTLR3_COMMON_TREE_NODE_STREAM mNodes;
	
	pCppHeaderLexer  mLexer;
	pCppHeaderParser mParser;
	pCppHeaderTree   mTree;
	
	
	std::string parseQualifiers (pANTLR3_BASE_TREE tree);
	std::string parsePointer    (pANTLR3_BASE_TREE tree);
	std::string parseReference  (pANTLR3_BASE_TREE tree);
	
	Header::Type      parseType      (pANTLR3_BASE_TREE tree);
	Header::Typedef   parseTypedef   (pANTLR3_BASE_TREE tree);
	Header::Type      parseParameter (pANTLR3_BASE_TREE tree);
	Header::Function  parseFunction  (pANTLR3_BASE_TREE tree);
	Header::Class     parseClass     (pANTLR3_BASE_TREE tree);
	Header::Namespace parseNamespace (pANTLR3_BASE_TREE tree);
};


#endif /* PARSER_H_ */

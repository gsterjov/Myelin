
#ifndef MYELIN_GENERATOR_PARSER_H_
#define MYELIN_GENERATOR_PARSER_H_


#include <string>
#include <map>
#include <vector>


namespace Myelin {
namespace Generator {

	/**
	 * Tokens.
	 */
	enum Token
	{
		OPEN_COMMENT,
		CLOSE_COMMENT,
		
		OPEN_CURLY_BRACKET,
		CLOSE_CURLY_BRACKET,
		
		OPEN_BRACKET,
		CLOSE_BRACKET,
		
		COLON,
		SEMI_COLON,
		COMMA,
		
		ASTERIX,
		AMPERSAND
	};
	
	
	/**
	 * Keywords.
	 */
	enum Keyword
	{
		NOTHING,
		
		NAMESPACE,
		CLASS,
		FUNCTION,
		
		ENUMERATION,
		TEMPLATE,
		TYPEDEF
	};
	
	
	
	/**
	 * C++ header parser.
	 */
	class Parser
	{
	public:
		
		/**
		 * Function structure.
		 */
		struct Function
		{
			std::string name;
			std::string ret;
			
			std::vector<std::string> params;
			
			bool isConstructor;
			bool isVirtual;
			bool isConstant;
			
			Function (std::string name) : name(name) {}
		};
		
		
		/**
		 * Class structure.
		 */
		struct Class
		{
			std::string name;
			Class* parent;
			
			std::vector<std::string> bases;
			std::vector<std::string> enums;
			std::vector<std::string> typedefs;
			
			std::vector<Class*> children;
			std::vector<Function*> functions;
			
			bool hasVirtuals;
			
			Class (std::string name, Class* parent) : name(name), parent(parent) {}
		};
		
		
		/**
		 * Namespace structure.
		 */
		struct Namespace
		{
			std::string name;
			Namespace* parent;
			
			std::map<std::string, Namespace*> children;
			std::vector<Class*> classes;
			
			Namespace (std::string name, Namespace* parent) : name(name), parent(parent) {}
		};
		
		
		
		/**
		 * Constructor.
		 */
		Parser ();
		
		/**
		 * Destructor.
		 */
		~Parser ();
		
		
		/**
		 * Parse a single file.
		 */
		void parse (const std::string& file);
		
		
		/**
		 * Get root namespace.
		 */
		Namespace* getRoot() { return mRoot; }
		
		
	private:
		Namespace* mRoot;
		
		
		std::map<Token, std::string> mTokens;
		
		
		std::string getScope (const std::string& type);
		
		std::vector<std::string> tokenize (char* buffer, int length);
		
		
		Namespace* mCurrentNamespace;		
		Class* mCurrentClass;
		
		void parseNamespace (const std::vector<std::string>& frame);
		void parseClass     (const std::vector<std::string>& frame);
		void parseFunction  (const std::vector<std::string>& frame);
	};

}}


#endif /* MYELIN_GENERATOR_PARSER_H_ */

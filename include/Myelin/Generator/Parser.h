
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
		FUNCTION
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
			std::vector<Class*> children;
			std::vector<Function*> functions;
			
			Class (std::string name, Class* parent) : name(name), parent(parent) {}
		};
		
		
		/**
		 * Namespace structure.
		 */
		struct Namespace
		{
			std::string name;
			Namespace* parent;
			
			std::vector<Namespace*> children;
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
		std::vector<Namespace*>& getNamespaces() { return mRoot->children; }
		
		
	private:
		Namespace* mRoot;
		
		
		std::map<Token, std::string> mTokens;
		std::vector<std::string> mKeywords;
		
		
		std::vector<std::string> tokenize (char* buffer, int length);
		
		Namespace* mCurrentNamespace;		
		Class* mCurrentClass;
		
		void parseNamespace (const std::vector<std::string>& frame);
		void parseClass     (const std::vector<std::string>& frame);
		void parseFunction  (const std::vector<std::string>& frame);
	};

}}


#endif /* MYELIN_GENERATOR_PARSER_H_ */


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
		
		NAMESPACE,
		CLASS,
		
		OPEN_BRACKET,
		CLOSE_BRACKET
	};
	
	
	
	/**
	 * C++ header parser.
	 */
	class Parser
	{
	public:
		
		/**
		 * Class structure.
		 */
		struct Class
		{
			std::string name;
			
			Class (std::string name) : name(name) {}
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
		const std::vector<Namespace*>& getNamespaces() { return mRoot->children; }
		
		
	private:
		Namespace* mRoot;
		
		std::map<Token, std::string> mTokenMap;
		
		int parseNamespace (char* buffer, int length, int index);
		int parseClass (char* buffer, int length, int index);
		
		void tokenize (char* buffer, int length);
		
		
		Namespace* mCurrentNamespace;		
		Class* mCurrentClass;
	};

}}


#endif /* MYELIN_GENERATOR_PARSER_H_ */

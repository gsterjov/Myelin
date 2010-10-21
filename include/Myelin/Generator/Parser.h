
#ifndef MYELIN_GENERATOR_PARSER_H_
#define MYELIN_GENERATOR_PARSER_H_


#include <string>
#include <vector>


namespace Myelin {
namespace Generator {

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
	};

}}


#endif /* MYELIN_GENERATOR_PARSER_H_ */

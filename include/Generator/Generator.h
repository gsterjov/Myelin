
#ifndef GENERATOR_H_
#define GENERATOR_H_


#include <string>
#include <vector>
#include <ostream>

#include <ctemplate/template.h>

#include <Parser.h>



typedef std::vector<std::string> StringList;



class Generator
{
public:
	Generator (const std::string& repo);
	~Generator ();
	
	
	/**
	 * Generate the output for all the provided header files.
	 * This first parses the headers and then walks the generated abstract
	 * syntax tree to ensure dependencies, and then finally generates
	 * the final introspection source file.
	 * 
	 * @param headers A list of headers to parse and wrap.
	 * @param stream The stream to write the introspection source to.
	 */
	void generate (const StringList& headers, std::ostream& stream);
	
	
private:
	std::string mRepo;
	Parser mParser;
	
	
	/* specific generators */
	void add_namespace (const NamespaceParser* nspace, ctemplate::TemplateDictionary* dict);
	void add_class     (const ClassParser*     klass,  ctemplate::TemplateDictionary* dict);
	
	void add_function  (const ClassParser* parent,
	                    const FunctionParser* func,
	                    ctemplate::TemplateDictionary* dict);
	
	std::string get_scoped_type (const ClassParser* parent, const TypeParser* type);
};


#endif /* GENERATOR_H_ */

/*
    Copyright 2009-2010 Goran Sterjov
    This file is part of Myelin.

    Myelin is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Myelin is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Myelin.  If not, see <http://www.gnu.org/licenses/>.
*/

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

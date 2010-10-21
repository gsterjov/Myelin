

#include <iostream>

#include "Parser.h"



int main (int argc, char** argv)
{
	using namespace Myelin::Generator;
	
	
	std::cout << "Parsing: " << argv[1] << std::endl;
	
	Parser parser;
	parser.parse (argv[1]);
	
	
	std::vector<Parser::Namespace*>::iterator iter;
	std::vector<Parser::Namespace*> list = parser.getNamespaces();
	
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		Parser::Namespace* nspace = *iter;
//		std::cout << nspace->name << std::endl;
		
		
		std::vector<Parser::Class*>::iterator it;
		std::vector<Parser::Class*> classes = nspace->classes;
		
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
//			std::cout << klass->name << std::endl;
		}
	}
}


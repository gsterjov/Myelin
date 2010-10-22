

#include <iostream>

#include "Parser.h"


using namespace Myelin::Generator;



void display (const std::vector<Parser::Namespace*>& list)
{
	std::vector<Parser::Namespace*>::const_iterator iter;
	
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		Parser::Namespace* nspace = *iter;
		std::cout << nspace->name << std::endl;
		
		
		std::vector<Parser::Class*>::iterator it;
		std::vector<Parser::Class*> classes = nspace->classes;
		
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
			std::cout << klass->name << std::endl;
		}
		
		
		display (nspace->children);
	}
}



int main (int argc, char** argv)
{
	std::cout << "Parsing: " << argv[1] << std::endl;
	
	Parser parser;
	parser.parse (argv[1]);
	
	display (parser.getNamespaces());
}


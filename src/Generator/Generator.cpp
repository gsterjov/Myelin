

#include <iostream>
#include <fstream>

#include "tclap/CmdLine.h"

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
			std::cout << " " << klass->name << " : ";
			
			for (int i = 0; i < klass->bases.size(); ++i)
				std::cout << klass->bases[i] << ", ";
			
			std::cout << std::endl;
			
			
			std::vector<Parser::Function*>::iterator i;
			std::vector<Parser::Function*> functions = klass->functions;
			
			
			for (i = functions.begin(); i != functions.end(); ++i)
			{
				Parser::Function* function = *i;
				std::cout << "  " << function->ret << " ";
				std::cout << function->name << " (";
				
				for (int j = 0; j < function->params.size(); ++j)
				{
					std::cout << function->params[j];
					
					if (j < function->params.size() - 1)
						std::cout << ", ";
				}
				
				std::cout << ")";
				std::cout << std::endl;
			}
		}
		
		
		display (nspace->children);
	}
}




void generate (const std::string& repo, const std::string& output, Parser& parser)
{
	std::fstream out (output.c_str(), std::fstream::out | std::fstream::trunc);
	
	
	/* introspection header */
	out << "#include <Myelin/Myelin.h>" << "\n\n";
	
	/* instrospection library entry */
	out << "extern \"C\" void create_repository ()" << "\n";
	out << "{" << "\n";
	
	
	/* place holders */
	out << "\t" << "Myelin::Namespace* nspace = 0;" << "\n";
	out << "\t" << "Myelin::Class* klass = 0;" << "\n";
	
	/* create repository */
	out << "\t" << "Myelin::Repository* repo = Myelin::RepositoryFactory::create (\"" << repo << "\");" << "\n";
	
	
	
	std::vector<Parser::Namespace*>::iterator iter;
	std::vector<Parser::Namespace*>& list = parser.getNamespaces();
	
	
	/* add all namespaces */
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		Parser::Namespace* nspace = *iter;
		
		/* add namespace */
		out << "\n\n";
		out << "\t" << "/* register namespace */" << "\n";
		out << "\t" << "nspace = repo->getNamespace (\"" << nspace->name << "\");" << "\n\n";
		out << "\t" << "if (!nspace)" << "\n";
		out << "\t" << "{" << "\n";
		out << "\t\t" << "nspace = new Myelin::Namespace (\"" << nspace->name << "\");" << "\n";
		out << "\t\t" << "repo->addNamespace (nspace);" << "\n";
		out << "\t" << "}" << "\n";
		
		
		std::vector<Parser::Class*>::iterator it;
		std::vector<Parser::Class*> classes = nspace->classes;
		
		/* add classes to namespace */
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
			
			/* add class */
			out << "\n\n";
			out << "\t" << "/* register class type */" << "\n";
			out << "\t" << "klass = new Myelin::Class (\"" << klass->name << "\");" << "\n";
			out << "\t" << "Myelin::REGISTER_CLASS (" << klass->name << ", klass);" << "\n";
			out << "\t" << "klass->setType (Myelin::TYPE(" << klass->name << "));" << "\n";
			out << "\t" << "nspace->addClass (klass);" << "\n\n";
			
			out << "\t" << "/* register class function types */" << "\n";
			
			
			std::vector<Parser::Function*>::iterator i;
			std::vector<Parser::Function*> functions = klass->functions;
			
			/* add functions to class */
			for (i = functions.begin(); i != functions.end(); ++i)
			{
				Parser::Function* func = *i;
				
				/* max 5 parameters */
				if (func->params.size() > 5) continue;
				
				std::string params;
				
				/* format parameters */
				for (int j = 0; j < func->params.size(); ++j)
					params += ", " + func->params[j];
				
				
				/* add function */
				out << "\t" << "klass->addFunction (new Myelin::Function (\"" << func->name
				    << "\", new MemberFunctionType" << func->params.size()
				    << " <" << klass->name << ", " << func->ret
				    << params
				    << "> (&" << klass->name << "::" << func->name << ")));"
				    << "\n";
				
			} /* end function */
		} /* end class */
	} /* end namespace */
	
	
	/* end library entry */
	out << "}" << "\n";
}




int main (int argc, char** argv)
{
	/* options */
	std::string name;
	std::string outdir;
	std::vector<std::string> paths;
	
	bool verbose;
	bool pretend;
	
	
	/* set up command line */
	try
	{
		using namespace TCLAP;
		
		
		/* create command line interface */
		CmdLine cmd ("Myelin introspection file generator.", ' ', "0.1");
		
		
		/* command line options */
		ValueArg<std::string> outdir_arg ("o", "outdir", "The output directory to store the generated files in", false, "", "path", cmd);
		
		SwitchArg verbose_arg ("v","verbose","Print out the parsed elements within each input file", cmd, false);
		SwitchArg pretend_arg ("p","pretend","Process each file but dont generate anything", cmd, false);
		
		UnlabeledValueArg<std::string> name_arg ("name", "The name of the introspection repository to create", true, "", "repository name", cmd);
		UnlabeledMultiArg<std::string> headers_arg ("headers", "The header files to generate introspection files for", true, "headers", cmd);
		
		
		/* parse command line */
		cmd.parse (argc, argv);
		
		
		outdir = outdir_arg.getValue();
		verbose = verbose_arg.getValue();
		pretend = pretend_arg.getValue();
		name = name_arg.getValue();
		paths = headers_arg.getValue();
	}
	
	/* command line error */
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return EXIT_FAILURE;
	}
	
	
	
	/* make sure we have a trailing slash */
	if (outdir.size() > 0 && outdir[outdir.size()-1] != '/') outdir += '/';
	
	
	/* summary */
	std::cout << "Repository name: " << name << std::endl;
	std::cout << "Output directory: " << outdir << std::endl;
	
	
	std::vector<std::string>::iterator iter;
	
	/* parse and generate each file */
	for (iter = paths.begin(); iter != paths.end(); ++iter)
	{
		std::string path = *iter;
		std::cout << "Parsing header: " << path << std::endl;
		
		
		/* get file name */
		int pos = path.find_last_of ("/");
		pos = pos == std::string::npos ? 0 : pos + 1;
		
		/* create output path */
		std::string outfile = outdir + path.substr(pos, path.find_last_of(".") - pos) + "_type.cpp";
		
		
		Parser parser;
		parser.parse (path);
		
		if (verbose) display (parser.getNamespaces());
		if (!pretend)
		{
			std::cout << "Generating file: " << outfile << std::endl;
			generate (name, outfile, parser);
		}
	}
	
	
	return EXIT_SUCCESS;
}


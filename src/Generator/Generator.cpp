

#include <iostream>
#include <fstream>

#include "tclap/CmdLine.h"

#include "Parser.h"



using namespace Myelin::Generator;




void display (const std::map<std::string, Parser::Namespace*>& map, int indent = 0)
{
	std::map<std::string, Parser::Namespace*>::const_iterator iter;
	
	
	/* set indentation */
	std::string tab;
	for (int i = 0; i < indent; ++i) tab += "\t";
	
	
	/* dump all namespaces */
	for (iter = map.begin(); iter != map.end(); ++iter)
	{
		Parser::Namespace* nspace = iter->second;
		std::cout << tab << nspace->name << std::endl;
		
		
		
		/* typedef dump */
		std::cout << tab << "\t ----- ";
		
		std::map<std::string, std::string>::iterator type_iter;
		std::map<std::string, std::string> map = nspace->typedefs;
		
		for (type_iter = map.begin(); type_iter != map.end(); ++type_iter)
			std::cout << type_iter->first << " = " << type_iter->second << ", ";
		
		std::cout << std::endl;
		
		
		
		std::vector<Parser::Class*>::iterator it;
		std::vector<Parser::Class*> classes = nspace->classes;
		
		
		/* dump all classes */
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
			
			/* dump class name */
			std::cout << tab << "\t" << klass->name << " : ";
			
			/* dump inherited base classes */
			for (int i = 0; i < klass->bases.size(); ++i)
				std::cout << klass->bases[i] << ", ";
			
			std::cout << std::endl;
			
			
			std::vector<Parser::Function*>::iterator i;
			std::vector<Parser::Function*> functions = klass->functions;
			
			
			/* dump all class functions */
			for (i = functions.begin(); i != functions.end(); ++i)
			{
				Parser::Function* function = *i;
				std::cout << tab <<  "\t\t";
				if (function->isVirtual) std::cout << "virtual ";
				
				if (!function->isConstructor)
					std::cout << function->ret << " ";
				
				std::cout << function->name << " (";
				
				for (int j = 0; j < function->params.size(); ++j)
				{
					std::cout << function->params[j];
					
					if (j < function->params.size() - 1)
						std::cout << ", ";
				}
				
				std::cout << ")";
				
				if (function->isConstant) std::cout << " const";
				std::cout << std::endl;
			}
		}
		
		
		std::cout << std::endl;
		display (nspace->children, indent + 1);
	}
}



void write_wrapper (Parser::Class* klass, std::fstream& out)
{
	/* wrapper class */
	out << "class " << klass->name << "Wrapper : ";
	out << "public " << klass->name << ", ";
	out << "public Myelin::Overridable <" << klass->name << "Wrapper>" << "\n";
	out << "{" << "\n";
	
	
	std::vector<Parser::Function*>::iterator it;
	std::vector<Parser::Function*> functions = klass->functions;
	
	/* implement all virtual functions */
	for (it = functions.begin(); it != functions.end(); ++it)
	{
		Parser::Function* func = *it;
		
		/* wrap virtual function */
		if (func->isVirtual)
		{
			/* open prototype */
			out << "\t" << func->ret << " ";
			out << func->name << " (";
			
			/* write all parameters */
			for (int j = 0; j < func->params.size(); ++j)
			{
				out << func->params[j] << " param" << j+1;
				
				/* more parameters left */
				if (j < func->params.size() - 1)
					out << ", ";
			}
			
			/* close prototype */
			out << ")";
			if (func->isConstant) out << " const";
			out << "\n";
			
			
			/* implement function */
			out << "\t" << "{" << "\n";
			out << "\t\t" << "Myelin::List params;" << "\n";
			
			/* push params */
			for (int j = 0; j < func->params.size(); ++j)
			{
				out << "\t\t" << "params.push_back <";
				out << func->params[j];
				out << "> (param" << j+1 << ");" << "\n";
			}
			
			out << "\t\t";
			
			/* ignore void returns */
			if (func->ret != "void")
				out << "return ";
			
			out << "Myelin::Overridable<" << klass->name << "Wrapper>::";
			out << "get(\"" << func->name << "\")";
			out << "->call(params)";
			
			if (func->ret != "void")
				out << ".get<" << func->ret << ">()";
			
			out << ";" << "\n";
			
			/* end implementation */
			out << "\t" << "}" << "\n";
		}
	}
	
	
	/* end wrapper class */
	out << "};\n";
}



void write_class (Parser::Class* klass, std::fstream& out)
{
	std::string name = klass->name;
	
	/* use wrapper class name as the type */
	if (klass->hasVirtuals)
		name += "Wrapper";
	
	
	/* add class */
	out << "\n\n";
	out << "\t" << "/* register class type */" << "\n";
	out << "\t" << "klass = new Myelin::Class (\"" << klass->name << "\");" << "\n";
	out << "\t" << "nspace->addClass (klass);" << "\n\n";
	
	if (klass->hasVirtuals)
		out << "\t" << "klass->setVTable (" << name << "::getVTable());" << "\n\n";
	
	out << "\t" << "Myelin::REGISTER_CLASS (" << name << ", klass);" << "\n";
	out << "\t" << "klass->setType (Myelin::TYPE(" << name << "));" << "\n\n\n";
	
	
	if (klass->functions.size() != 0)
		out << "\t" << "/* register class function types */" << "\n";
	
	
	std::vector<Parser::Function*>::iterator it;
	std::vector<Parser::Function*> functions = klass->functions;
	
	/* add functions to class */
	for (it = functions.begin(); it != functions.end(); ++it)
	{
		Parser::Function* func = *it;
		
		/* max 5 parameters */
		if (func->params.size() > 5)
		{
			std::cout << "Skipping function with more than 5 arguments: " << func->name << std::endl;
			continue;
		}
		
		
		std::string params;
		
		/* format parameters */
		for (int j = 0; j < func->params.size(); ++j)
			params += ", " + func->params[j];
		
		
		/* add constructor */
		if (func->isConstructor)
		{
			out << "\t" << "klass->addConstructor (new Myelin::Constructor (";
			out << "new Myelin::ConstructorType" << func->params.size();
			
			out << " <" << klass->name;
			
			if (!params.empty())
				out << params;
			
			out << "> ()));";
			out << "\n";
		}
		
		/* add function */
		else
		{
			out << "\t" << "klass->addFunction (new Myelin::Function (";
			out << "\"" << func->name << "\"";
			out << ", new Myelin::";
			
			if (func->isConstant) out << "Const";
			out << "MemberFunctionType" << func->params.size();
			
			out << " <" << klass->name << ", " << func->ret;
			out << params;
			out << "> (&" << klass->name << "::" << func->name << ")));";
			out << "\n";
		}
	}
}




void write_namespace (Parser::Namespace* nspace, std::fstream& out, std::vector<std::string>& scopes)
{
	/* namespace has no content to introspect */
	if (nspace->classes.size() == 0 && nspace->children.size() == 0) return;
	
	
	/* only declare namespace when adding classes */
	if (nspace->classes.size() != 0)
	{
		/* get qualified namespace name */
		std::vector<std::string> tree;
		std::string full_name = nspace->name;
		
		Parser::Namespace* parent = nspace->parent;
		
		/* append all parents */
		while (parent && !parent->name.empty())
		{
			tree.push_back (parent->name);
			
			full_name = parent->name + "::" + full_name;
			parent = parent->parent;
		}
		
		/* add this namespace to the tree */
		tree.push_back (nspace->name);
		
		
		std::vector<std::string>::iterator iter;
		
		/* declare namespace for the function */
		for (iter = tree.begin(); iter != tree.end(); ++iter)
			out << "namespace " << *iter << " {" << "\n";
		
		out << "namespace MyelinIntrospection {" << "\n\n";
		
		
		/* add namespace scope to list */
		scopes.push_back (full_name);
		
		
		
		std::vector<Parser::Class*>::iterator it;
		std::vector<Parser::Class*> classes = nspace->classes;
		
		/* generate class wrapper for virtual functions */
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
			if (klass->hasVirtuals)
			{
				write_wrapper (klass, out);
				out << "\n\n";
			}
		}
		
		
		
		/* namespace function */
		out << "void declare_namespace (Myelin::Repository* repo)" << "\n";
		out << "{" << "\n";
		
		/* place holders */
		out << "\t" << "Myelin::Namespace* nspace = 0;" << "\n";
		out << "\t" << "Myelin::Class* klass = 0;" << "\n";
		
		
		/* add namespace */
		out << "\n\n";
		out << "\t" << "/* get namespace */" << "\n";
		out << "\t" << "nspace = repo->getNamespace (\"" << full_name << "\");" << "\n";
		
		
		/* add classes to namespace */
		for (it = classes.begin(); it != classes.end(); ++it)
			write_class (*it, out);
		
		
		/* end namespace function */
		out << "}" << "\n\n";
		
		
		/* close namespaces */
		for (int i = 0; i < tree.size(); ++i)
			out << "}";
		
		out << "}\n\n\n\n";
	}
	
	
	
	std::map<std::string, Parser::Namespace*>::iterator i;
	std::map<std::string, Parser::Namespace*> children = nspace->children;
	
	/* add all child namespaces */
	for (i = children.begin(); i != children.end(); ++i)
		write_namespace (i->second, out, scopes);
}




void generate (const std::string& name,
               const std::string& output,
               Parser& parser,
               std::vector<std::string>& headers)
{
	std::fstream out (output.c_str(), std::fstream::out | std::fstream::trunc);
	
	
	/* introspection header */
	out << "#include <Myelin/Myelin.h>" << "\n\n";
	
	std::vector<std::string>::iterator iter;
	
	/* introspected headers */
	for (iter = headers.begin(); iter != headers.end(); ++iter)
		out << "#include <" << *iter << ">" << "\n";
	
	out << "\n\n\n\n";
	
	
	std::vector<std::string> scopes;
	
	/* add all namespaces in root namespace */
	write_namespace (parser.getRoot(), out, scopes);
	
	
	
	/* export attribute for the myelin entry function */
	out << "#if defined _WIN32 || defined __CYGWIN__ " << "\n";
	out << "\t" << "#define MYELIN_ENTRY_EXPORT __declspec(dllexport)" << "\n";
	out << "#else" << "\n";
	out << "\t" << "#if __GNUC__ >= 4" << "\n";
	out << "\t\t" << "#define MYELIN_ENTRY_EXPORT __attribute__ ((visibility(\"default\")))" << "\n";
	out << "\t" << "#else" << "\n";
	out << "\t\t" << "#define MYELIN_ENTRY_EXPORT" << "\n";
	out << "\t" << "#endif" << "\n";
	out << "#endif" << "\n\n";
	
	
	/* instrospection library entry */
	out << "extern \"C\" MYELIN_ENTRY_EXPORT Myelin::Repository* myelin_create_repository ()" << "\n";
	out << "{" << "\n";
	
	/* create repository */
	out << "\t" << "Myelin::Repository* repo = new Myelin::Repository (\"" << name << "\");" << "\n";
	
	/* call namespace declaration functions */
	std::vector<std::string>::iterator it;
	
	for (it = scopes.begin(); it != scopes.end(); ++it)
		out << "\t" << *it << "::MyelinIntrospection::declare_namespace (repo);" << "\n";
	
	/* end library entry */
	out << "\t" << "return repo;" << "\n";
	out << "}" << "\n\n";
}




int main (int argc, char** argv)
{
	/* options */
	std::string name;
	std::string outdir;
	std::string outfile;
	std::vector<std::string> includes;
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
		MultiArg<std::string> include_arg ("I", "include", "The header directory to look for the specified headers in", false, "path", cmd);
		ValueArg<std::string> outdir_arg ("o", "outdir", "The output directory to store the generated files in", false, "", "path", cmd);
		ValueArg<std::string> outfile_arg ("f", "outfile", "The output file to write the generated introspection source file into", false, "Introspection.cpp", "filename", cmd);
		
		SwitchArg verbose_arg ("v","verbose","Print out the parsed elements within each input file", cmd, false);
		SwitchArg pretend_arg ("p","pretend","Process each file but dont generate anything", cmd, false);
		
		UnlabeledValueArg<std::string> name_arg ("name", "The name of the introspection repository to create", true, "", "repository name", cmd);
		UnlabeledMultiArg<std::string> headers_arg ("headers", "The header files to generate introspection files for", true, "headers", cmd);
		
		
		/* parse command line */
		cmd.parse (argc, argv);
		
		
		includes = include_arg.getValue();
		outdir = outdir_arg.getValue();
		outfile = outfile_arg.getValue();
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
	
	/* make sure all include dirs have a trailing slash */
	for (int i = 0; i < includes.size(); ++i)
	{
		std::string dir = includes[i];
		if (dir.size() > 0 && dir[dir.size()-1] != '/') includes[i] = dir + '/';
	}
	
	
	/* summary */
	std::cout << "Repository name: " << name << std::endl;
	std::cout << "Output directory: " << outdir << std::endl;
	std::cout << "Include directories: " << std::endl;
	
	for (int i = 0; i < includes.size(); ++i)
		std::cout << "\t - " << includes[i] << std::endl;
	
	std::cout << std::endl;
	
	
	/* the header parser */
	Parser parser;
	std::vector<std::string> headers;
	
	
	std::vector<std::string>::iterator iter;
	
	/* parse each header file */
	for (iter = paths.begin(); iter != paths.end(); ++iter)
	{
		std::string header = *iter;
		std::string full_path = *iter;
		
		
		std::vector<std::string>::iterator it;
		
		/* look for full path in the include dirs */
		for (it = includes.begin(); it != includes.end(); ++it)
		{
			std::string path = *it + *iter;
			
			/* found full path in include dir */
			if (std::ifstream (path.c_str()).is_open())
			{
				full_path = path;
				break;
			}
			
			/* remove include dir from header path */
			else if (header.find(*it) == 0)
				header = header.substr (it->size());
		}
		
		
		
		/* parse file if it can be opened */
		if (std::ifstream (full_path.c_str()).is_open())
		{
			std::cout << "Parsing header: " << full_path << std::endl;
			parser.parse (full_path);
			headers.push_back (header);
		}
	}
	
	
	/* dump parser output */
	if (verbose) display (parser.getRoot()->children);
	
	/* generate introspection source file */
	if (!pretend)
	{
		std::cout << "Generating source file: " << outdir + outfile << std::endl;
		generate (name, outdir + outfile, parser, headers);
	}
	
	
	return EXIT_SUCCESS;
}


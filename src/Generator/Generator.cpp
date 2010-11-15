

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
		std::vector<Parser::Class*> templates = nspace->templates;
		
		
		/* dump all template classes */
		for (it = templates.begin(); it != templates.end(); ++it)
		{
			Parser::Class* klass = *it;
			
			/* dump class name */
			std::cout << tab << "\t" << klass->name << " <";
			
			/* dump template parameters */
			for (int i = 0; i < klass->template_params.size(); ++i)
			{
				std::cout << klass->template_params[i];
				
				if (i < klass->template_params.size()-1)
					 std::cout << ", ";
			}
			
			std::cout << ">";
			
			if (!klass->bases.empty())
				std::cout << " : ";
			
			/* dump inherited base classes */
			for (int i = 0; i < klass->bases.size(); ++i)
			{
				std::cout << klass->bases[i];
				
				if (i < klass->bases.size()-1)
					 std::cout << ", ";
			}
			
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
		
		
		
		std::vector<Parser::Class*> classes = nspace->classes;
		
		
		/* dump all classes */
		for (it = classes.begin(); it != classes.end(); ++it)
		{
			Parser::Class* klass = *it;
			
			/* dump class name */
			std::cout << tab << "\t" << klass->name;
			
			if (!klass->bases.empty())
				std::cout << " : ";
			
			/* dump inherited base classes */
			for (int i = 0; i < klass->bases.size(); ++i)
			{
				std::cout << klass->bases[i];
				
				if (i < klass->bases.size()-1)
					 std::cout << ", ";
			}
			
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



void trim (std::string& str)
{
	str.erase (0, str.find_first_not_of (" \t\n"));
	str.erase (str.find_last_not_of (" \t\n") + 1);
}




void replace_param (std::string& str, std::map<std::string, std::string>& map)
{
	Parser parser;
	
	char arr[str.size()];
	
	for (int i = 0; i < str.size(); ++i)
		arr[i] = str[i];
	
	std::vector<std::string> tokens = parser.tokenize(arr, str.size());
	
	str = "";
	
	
	for (int i = 0; i < tokens.size(); ++i)
	{
		bool replaced = false;
		
		std::map<std::string, std::string>::iterator iter;
		
		for (iter = map.begin(); iter != map.end(); ++iter)
		{
			if (tokens[i] == iter->first)
			{
				str += iter->second;
				replaced = true;
				break;
			}
		}
		
		
		if (!replaced)
		{
			str += tokens[i];
			
			if (tokens[i] == "const")
				str += " ";
		}
	}
	
}



void write_wrapper (Parser::Class* klass, std::fstream& out)
{
	/* wrapper class */
	out << "class " << klass->name << "Wrapper : ";
	out << "public " << klass->name << ", ";
	out << "public Myelin::Overridable <" << klass->name << "Wrapper>" << "\n";
	out << "{" << "\n";
	out << "public:" << "\n";
	
	
	
	std::vector<Parser::Function*>::iterator it;
	std::vector<Parser::Function*> functions = klass->functions;
	
	/* implement all virtual functions */
	for (it = functions.begin(); it != functions.end(); ++it)
	{
		Parser::Function* func = *it;
		
		
		/* constructor pass-through */
		if (func->isConstructor)
		{
			/* open prototype */
			out << "\t" << klass->name << "Wrapper (";
			
			/* write all parameters */
			for (int j = 0; j < func->params.size(); ++j)
			{
				out << func->params[j] << " param" << j+1;
				
				/* more parameters left */
				if (j < func->params.size() - 1)
					out << ", ";
			}
			
			out << ") : " << func->name << "(";
			
			/* base initialiser */
			for (int j = 0; j < func->params.size(); ++j)
			{
				out << "param" << j+1;
				
				/* more parameters left */
				if (j < func->params.size() - 1)
					out << ", ";
			}
			
			out << ") {}" << "\n";
		}
		
		
		/* wrap virtual function */
		else if (func->isVirtual)
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



void write_class (Parser::Class* klass,
                  std::fstream& out,
                  std::string instance = "",
                  std::map<std::string, std::string> map = std::map<std::string, std::string>())
{
	std::string name = klass->name;
	
	/* use wrapper class name as the type */
	if (klass->hasVirtuals)
		name += "Wrapper";
	
	/* use instantiation name */
	if (klass->isTemplate)
		name = instance;
	
	
	/* add class */
	out << "\n\n";
	out << "\t" << "/* register class type */" << "\n";
	
	if (klass->isTemplate)
		out << "\t" << "klass = new Myelin::Class (\"" << name << "\");" << "\n";
	else
		out << "\t" << "klass = new Myelin::Class (\"" << klass->name << "\");" << "\n";
	
	out << "\t" << "nspace->addClass (klass);" << "\n\n";
	
	if (klass->hasVirtuals && !klass->isTemplate)
		out << "\t" << "klass->setVTable (" << name << "::getVTable());" << "\n\n";
	
	out << "\t" << "Myelin::REGISTER_CLASS (" << name << ", klass);" << "\n";
	out << "\t" << "klass->setType (Myelin::TYPE(" << name << "));" << "\n\n\n";
	
	
	
	/* register base classes */
	if (klass->bases.size() != 0)
		out << "\t" << "/* register base class types */" << "\n";
	
	
	/* add base classes */
	for (int i = 0; i < klass->bases.size(); ++i)
	{
		out << "\t" << "klass->addBase (Myelin::TYPE(" << klass->bases[i] << "));" << "\n";
		out << "\t" << "klass->addConverter (new Myelin::Converter (";
		out << "new Myelin::ImplicitConverter <";
		out << name << "*, " << klass->bases[i] << "*> ()));" << "\n";
	}
	
	
	
	if (klass->functions.size() != 0)
		out << "\t" << "/* register class function types */" << "\n";
	
	
	bool hasConstructor = false;
	
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
		{
			std::string str = func->params[j];
			replace_param (str, map);
			params += ", " + str;
		}
		
		
		/* add constructor */
		if (func->isConstructor)
		{
			out << "\t" << "klass->addConstructor (new Myelin::Constructor (";
			out << "new Myelin::ConstructorType" << func->params.size();
			
			out << " <" << name;
			out << params;
			out << "> ()));";
			out << "\n";
			
			hasConstructor = true;
		}
		
		/* add function */
		else
		{
			std::string ret = func->ret;
			replace_param (ret, map);
			
			out << "\t" << "klass->addFunction (new Myelin::Function (";
			out << "\"" << func->name << "\"";
			out << ", new Myelin::";
			
			if (func->isConstant) out << "Const";
			out << "MemberFunctionType" << func->params.size();
			
			out << " <" << name << ", " << ret;
			out << params;
			out << "> (&" << name << "::" << func->name << ")";
			
			/* set function properties */
			if (func->isConstant || func->isVirtual)
			{
				out << ", ";
				if (func->isConstant)
				{
					out << "Myelin::Function::CONSTANT";
					if (func->isVirtual) out << " | ";
				}
				if (func->isVirtual) out << "Myelin::Function::VIRTUAL";
			}
			
			/* finish declaring function */
			out << "));" << "\n";
		}
	}
	
	
	/* create default constructor */
	if (!hasConstructor)
	{
		out << "\t" << "klass->addConstructor (new Myelin::Constructor (";
		out << "new Myelin::ConstructorType0";
		
		out << " <" << name << "> ()));";
		out << "\n";
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
		
		
		
		std::map<std::string, std::string>::iterator map_iter;
		std::map<std::string, std::string> typedefs = nspace->typedefs;
		
		/* look through typedefs for template instantiations */
		for (map_iter = typedefs.begin(); map_iter != typedefs.end(); ++map_iter)
		{
			std::string type = map_iter->second;
			
			/* look for template type */
			int pos = type.find_first_of ('<');
			
			/* found template */
			if (pos != std::string::npos)
			{
				Parser::Class* klass = 0;
				std::string name = type.substr (0, pos);
				
				
				Parser::Namespace* ns = nspace;
				
				while (!klass && ns)
				{
					/* find template class */
					for (int i = 0; i < ns->templates.size(); ++i)
					{
						if (name == ns->templates[i]->name)
							klass = ns->templates[i];
					}
					
					ns = ns->parent;
				}
				
				/* found class */
				if (klass)
				{
					int i = 0;
					std::map<std::string, std::string> map;
					
					while (pos != std::string::npos)
					{
						int start = pos + 1;
						pos = type.find_first_of (',', start);
						
						if (pos != std::string::npos)
						{
							std::string param = type.substr (start, pos-start);
							map[klass->template_params[i]] = param;
						}
						
						else
						{
							pos = type.find_first_of ('>', start);
							
							if (pos != std::string::npos)
							{
								std::string param = type.substr (start, pos-start);
								map[klass->template_params[i]] = param;
							}
							
							break;
						}
					}
					
					
					map[name] = map_iter->first;
					write_class (klass, out, map_iter->first, map);
					++i;
				}
				
			}
		}
		
		
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
	
	
	std::cout << "Introspection file generated." << std::endl;
	
	return EXIT_SUCCESS;
}




#include <iostream>
#include <fstream>

#include "tclap/CmdLine.h"

#include "Parser.h"
#include "Generator.h"




int main (int argc, char** argv)
{
	/* options */
	std::string name;
	std::string outdir;
	std::string outfile;
	StringList includes;
	StringList paths;
	
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
	
	
	StringList::iterator iter;
	
	/* dump header paths to stdout */
	for (iter = includes.begin(); iter != includes.end(); ++iter)
		std::cout << "\t - " << *iter << std::endl;
	
	
	/* parse and generate introspection file */
	std::string path = outdir + outfile;
	std::fstream stream (path.c_str(), std::ios_base::out);
	
	Generator generator (name);
	generator.generate (paths, stream);
	
	stream.close();
	
	return 0;
}


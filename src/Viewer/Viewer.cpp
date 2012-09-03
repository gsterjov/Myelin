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

#include <iostream>
#include <stdexcept>
#include <dlfcn.h>

#include <Myelin/Myelin.h>

#include "tclap/CmdLine.h"




void dump_class (Myelin::Class* klass, const std::string& indent)
{
	std::cout << indent << "Class: " << klass->getName() << std::endl;


	std::string tab = indent + "\t";

	Myelin::ConstructorList::iterator iter;
	Myelin::ConstructorList ctors = klass->getConstructors();

	/* dump all constructors */
	for (iter = ctors.begin(); iter != ctors.end(); ++iter)
	{
		Myelin::Constructor* ctor = *iter;

		std::cout << tab << klass->getName() << " (";

		for (int i = 0; i < ctor->getParamCount(); ++i)
		{
			std::cout << ctor->getParamType(i)->getName();

			if (i < ctor->getParamCount()-1)
				std::cout << ", ";
		}

		std::cout << ")" << std::endl;
	}



	Myelin::FunctionList::iterator it;
	Myelin::FunctionList funcs = klass->getFunctions();

	/* dump all functions */
	for (it = funcs.begin(); it != funcs.end(); ++it)
	{
		Myelin::Function* func = *it;


		std::cout << tab;

		if (func->isVirtual())
			std::cout << "virtual ";


		std::cout << func->getType()->getReturnType()->getName();


		std::cout << " " << func->getName() << " (";

		for (int i = 0; i < func->getType()->getParamCount(); ++i)
		{
			std::cout << func->getType()->getParamType(i)->getName();

			if (i < func->getType()->getParamCount()-1)
				std::cout << ", ";
		}

		std::cout << ")";

		if (func->isConstant())
			std::cout << " const";

		if (func->isPure())
			std::cout << " = 0";

		std::cout << std::endl;
	}
}



void dump_namespace (Myelin::Namespace* nspace, const std::string& indent)
{
	std::cout << indent << "Namespace: " << nspace->getName() << std::endl;


	std::string tab = indent + "\t";

	Myelin::ClassList::iterator iter;
	Myelin::ClassList list = nspace->getClasses();

	/* dump all classes */
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		dump_class (*iter, tab);
	}
}



void dump_repository (Myelin::Repository* repo)
{
	std::cout << "Repository: " << repo->getName() << std::endl;


	std::string tab = "\t";


	Myelin::NamespaceList::iterator iter;
	Myelin::NamespaceList list = repo->getNamespaces();

	/* dump all namespaces */
	for (iter = list.begin(); iter != list.end(); ++iter)
	{
		dump_namespace (*iter, tab);
	}
}




Myelin::Repository* open_lib (const std::string& path)
{
	std::cout << "Opening library: " << path << std::endl;


	/* open library */
	void* handle = dlopen (path.c_str(), RTLD_LAZY);

	if (!handle)
		throw std::runtime_error ("Failed to open the library: " + path +
				". Error: " + dlerror());

	/* entry symbol */
	typedef Myelin::Repository* (*create_func)();

	/* get entry function */
	dlerror();
	create_func create = (create_func) dlsym (handle, "myelin_create_repository");

	/* check for errors */
	const char *err = dlerror();

	if (err)
	{
		dlclose (handle);
		throw std::runtime_error ("Failed to open the entry symbol: "
			"'myelin_create_repository()'. Error: " + std::string(err));
	}

	/* create repo */
	Myelin::init_types ();
	Myelin::Repository* repo = create ();

	return repo;
}



int main (int argc, char** argv)
{
	/* options */
	std::string name;
	std::string library;


	/* set up command line */
	try
	{
		using namespace TCLAP;


		/* create command line interface */
		CmdLine cmd ("Myelin introspection viewer.", ' ', "0.1");


		/* command line options */
		ValueArg<std::string> name_arg ("r", "repo", "The name of the introspection repository to view", false, "", "repository name", cmd);
		UnlabeledValueArg<std::string> library_arg ("library", "The path to the introspected library to view", true, "", "path", cmd);


		/* parse command line */
		cmd.parse (argc, argv);


		library = library_arg.getValue();
		name = name_arg.getValue();
	}

	/* command line error */
	catch (TCLAP::ArgException &e)
	{
		std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
		return EXIT_FAILURE;
	}



	/* get repository */
	Myelin::Repository* repo = open_lib (library);
	dump_repository (repo);


	return EXIT_SUCCESS;
}




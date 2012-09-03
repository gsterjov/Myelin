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

#include "Generator.h"

#include <map>
#include <iostream>
#include <sstream>

#include "TemplateVars.h"



Generator::Generator (const std::string& repo) : mRepo(repo)
{
	
}



Generator::~Generator ()
{
	
}



/* generate the introspection wrapping code */
void Generator::generate (const StringList& headers, std::ostream& stream)
{
	using namespace ctemplate;
	
	
	/* create the introspection source template */
	TemplateDictionary dict ("Introspection");
	dict.SetValue ("REPO", mRepo);
	
	/* namespace pool */
	std::map<std::string, TemplateDictionary*> scopes;
	
	
	StringList::const_iterator iter;
	
	/* generate introspection wrapping for all headers */
	for (iter = headers.begin(); iter != headers.end(); ++iter)
	{
		if (!mParser.open (*iter))
			continue;
		
		
		/* parse the header file */
		if (!mParser.parse ())
		{
			std::cerr << "Skipping '" << *iter << "' due to failed parse" << std::endl;
			continue;
		}
		
		
		/* get root namespace */
		const NamespaceParser* root = mParser.getRoot();
		
		
		/* get all namespaces in the header */
		NamespaceMap::const_iterator it;
		const NamespaceMap& nspaces = root->getNamespaces();
		
		
		/* add namespaces to the template */
		for (it = nspaces.begin(); it != nspaces.end(); ++it)
		{
			TemplateDictionary* nspace_dict = 0;
			std::string name = it->second->getName();
			
			/* look for an already created namespace */
			std::map<std::string, TemplateDictionary*>::const_iterator scope;
			scope = scopes.find (name);
			
			/* add to existing namespace */
			if (scope != scopes.end())
				nspace_dict = scope->second;
			
			/* create a new namespace */
			else
			{
				nspace_dict = dict.AddSectionDictionary ("NAMESPACES");
				nspace_dict->SetValue ("NAMESPACE", name);
				scopes[name] = nspace_dict;
			}
			
			/* generate class internals */
			add_namespace (it->second, nspace_dict);
		}
		
		
		mParser.close ();
		
		
		/* add the header to the include section */
		TemplateDictionary* sub_dict = dict.AddSectionDictionary ("HEADERS");
		sub_dict->SetValue ("HEADER", *iter);
	}
	
	
	/* generate the source code by filling out the template */
	std::string output;
	StringToTemplateCache ("template.tpl", TemplateVars, ctemplate::DO_NOT_STRIP);
	bool success = ExpandTemplate ("template.tpl", DO_NOT_STRIP, &dict, &output);
	
	
	/* write the expanded template to the output */
	if (success)
		stream << output;
	else
		std::cerr << "Failed to generate the introspection wrapper from the template" << std::endl;
	
}



/* add the namespace to the dictionary */
void Generator::add_namespace (const NamespaceParser* nspace, ctemplate::TemplateDictionary* dict)
{
	using namespace ctemplate;
	
	
	/* get all classes in the namespace */
	ClassMap::const_iterator it;
	const ClassMap& classes = nspace->getClasses();
	
	/* add each class to the template */
	for (it = classes.begin(); it != classes.end(); ++it)
	{
		/* add class section to the template */
		TemplateDictionary* class_dict = dict->AddSectionDictionary ("CLASSES");
		class_dict->SetValue ("CLASS", it->second->getName());
		
		/* generate class internals */
		add_class (it->second, class_dict);
	}
}



/* add the class to the dictionary */
void Generator::add_class (const ClassParser* klass, ctemplate::TemplateDictionary* dict)
{
	using namespace ctemplate;
	
	
	/* get all functions in the class */
	FunctionMap::const_iterator it;
	const FunctionMap& funcs = klass->getFunctions();
	
	/* add functions to the template */
	for (it = funcs.begin(); it != funcs.end(); ++it)
	{
		const FunctionParser* func = it->second;
		
		/* we only supports functions with 5 parameters or less */
		if (func->getParameters().size() > 5)
			continue;
		
		/* add function section to the template */
		TemplateDictionary* func_dict = dict->AddSectionDictionary ("FUNCTIONS");
		func_dict->SetValue ("NAME", func->getName());
		
		/* generate function internals */
		add_function (klass, func, func_dict);
	}
}



/* add the function to the dictionary */
void Generator::add_function (const ClassParser* parent,
                              const FunctionParser* func,
                              ctemplate::TemplateDictionary* dict)
{
	using namespace ctemplate;
	
	
	/* generate a constant function wrapper */
	if (func->isConstant())
		dict->ShowSection ("CONSTANT");
	
	
	/* determine parameter amount */
	std::stringstream st;
	st << func->getParameters().size();
	dict->SetValue ("PARAM_COUNT", st.str());
	
	
	/* get scoped return type */
	std::string return_type = get_scoped_type (parent, func->getReturnType());
	dict->SetValue ("RETURN", return_type);
	
	
	/* get all the parameters in the function */
	TypeList::const_iterator it;
	const TypeList& params = func->getParameters();
	
	/* add the parameter types to the function declaration */
	for (it = params.begin(); it != params.end(); ++it)
	{
		/* get scoped typename */
		std::string param_type = get_scoped_type (parent, *it);
		
		/* add parameter section to the template */
		TemplateDictionary* param_dict = dict->AddSectionDictionary ("PARAMS");
		param_dict->SetValue ("TYPE", param_type);
	}
}



/* get the fully qualified and scoped type name */
std::string Generator::get_scoped_type (const ClassParser* parent, const TypeParser* type)
{
	std::string scoped_name = type->getName();
	
	
	/* find scoped typedef */
	const TypedefParser* type_def = parent->getTypedef (scoped_name);
	if (type_def) scoped_name = parent->getName() + "::" + scoped_name;
	
	else
	{
		/* find scoped class */
		const ClassParser* klass = parent->getClass (scoped_name);
		if (klass) scoped_name = parent->getName() + "::" + scoped_name;
	}
	
	
	std::string type_name;
	
	/* construct qualified type name */
	if (type->isConstant()) type_name = "const ";
	if (type->isVolatile()) type_name += "volatile ";
	
	type_name += scoped_name;
	
	if (type->isConstantPointer()) type_name += " const";
	if (type->isVolatilePointer()) type_name += " volatile";
	if (type->isPointer()) type_name += "*";
	
	if (type->isConstantReference()) type_name += " const";
	if (type->isVolatileReference()) type_name += " volatile";
	if (type->isReference()) type_name += "&";
	
	return type_name;
}


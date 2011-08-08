
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
		Header header = mParser.parse ();
		
		
		/* get all namespaces in the header */
		std::vector<Header::Namespace>::const_iterator it;
		const std::vector<Header::Namespace>& nspaces = header.getNamespaces();
		
		/* add namespaces to the template */
		for (it = nspaces.begin(); it != nspaces.end(); ++it)
		{
			TemplateDictionary* nspace_dict = 0;
			
			/* look for an already created namespace */
			std::map<std::string, TemplateDictionary*>::const_iterator scope;
			scope = scopes.find (it->name);
			
			/* add to existing namespace */
			if (scope != scopes.end())
				nspace_dict = scope->second;
			
			/* create a new namespace */
			else
			{
				nspace_dict = dict.AddSectionDictionary ("NAMESPACES");
				nspace_dict->SetValue ("NAMESPACE", it->name);
				scopes[it->name] = nspace_dict;
			}
			
			/* generate class internals */
			generateNamespace (*it, nspace_dict);
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
	
	
	if (success)
		stream << output;
	else
		std::cerr << "Failed to generate the introspection wrapper from the template" << std::endl;
	
}




void Generator::generateNamespace (Header::Namespace nspace, ctemplate::TemplateDictionary* dict)
{
	using namespace ctemplate;
	
	
	/* get all classes in the namespace */
	std::vector<Header::Class>::const_iterator it;
	const std::vector<Header::Class>& classes = nspace.classes;
	
	/* add each class to the template */
	for (it = classes.begin(); it != classes.end(); ++it)
	{
		/* add class section to the template */
		TemplateDictionary* class_dict = dict->AddSectionDictionary ("CLASSES");
		class_dict->SetValue ("CLASS", it->name);
		
		/* generate class internals */
		generateClass (*it, class_dict);
	}
}



void Generator::generateClass (Header::Class klass, ctemplate::TemplateDictionary* dict)
{
	using namespace ctemplate;
	
	
	/* get all functions in the class */
	std::vector<Header::Function>::const_iterator it;
	const std::vector<Header::Function>& funcs = klass.functions;
	
	/* add functions to the template */
	for (it = funcs.begin(); it != funcs.end(); ++it)
	{
		std::stringstream st;
		st << it->parameters.size();
		
		/* add function section to the template */
		TemplateDictionary* func_dict = dict->AddSectionDictionary ("FUNCTIONS");
		func_dict->SetValue ("NAME", it->name);
		func_dict->SetValue ("PARAM_COUNT", st.str());
		func_dict->SetValue ("RETURN", it->return_type.name);
		
		
		/* get all the parameters in the function */
		std::vector<Header::Type>::const_iterator iter;
		const std::vector<Header::Type>& params = it->parameters;
		
		/* add the parameter types to the function declaration */
		for (iter = params.begin(); iter != params.end(); ++iter)
		{
			/* add parameter section to the template */
			TemplateDictionary* param_dict = func_dict->AddSectionDictionary ("PARAMS");
			param_dict->SetValue ("TYPE", iter->name);
		}
		
		/* generate a constant function wrapper */
		if (it->isConst)
			func_dict->ShowSection ("CONSTANT");
	}
}


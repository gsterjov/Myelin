
#include "Parser.h"

#include <fstream>
#include <iterator>
#include <iostream>



//#include <boost/spirit/core.hpp>
//#include <boost/spirit/symbols/symbols.hpp>
//#include <boost/spirit/utility/chset.hpp>
//#include <boost/spirit/utility/escape_char.hpp>
//#include <boost/spirit/utility/confix.hpp>

#include <spirit/include/qi.hpp>



namespace Myelin {
namespace Generator {


	namespace qi = boost::spirit::qi;
	
	
	
	struct Source
	{
		int test;
	};
	
	
	
	template <typename Iterator>
	struct cpp_grammar : qi::grammar <Iterator, std::string()>
	{
		cpp_grammar () : cpp_grammar::base_type (source)
		{
			using qi::space;
			using qi::lit;
			using qi::eol;
			using qi::alnum;
			using qi::alpha;
			
			
			source
				=   *(  nspace [qi::_val += qi::_1]
					 |  comment [qi::_val += qi::_1]
					 |  klass [qi::_val += qi::_1]
					 )
				;
			
			
			comment
				=   (  ("//" >> (*alnum - eol) >> eol)
					|  ("/*" >> (*alnum - "*/") >> "*/"))
				;
			
			
			klass = "class" >> alpha >> *alnum >> "{";
			
			
			nspace = "namespace" >> alpha >> *alnum >> "{";
		}
		
		
		
		qi::rule <Iterator, std::string()> source, comment, klass, nspace;
		
	};
	
	
	
	
	
	
	/* constructor */
	Parser::Parser () : mRoot(new Namespace("", 0))
	{
		
	}
	
	
	/* destructor */
	Parser::~Parser ()
	{
		
	}
	
	
	
	/* parse file */
	void Parser::parse (const std::string& file)
	{
		/* file stream */
		std::fstream stream (file.c_str(), std::fstream::in);
		
		
		std::istream_iterator<char> iter (stream);
		std::istream_iterator<char> eos;
		
		
		std::vector<char> source (iter, eos);
		std::cout << source.size() << std::endl;
		
		
		std::vector<char>::iterator start = source.begin();
		std::vector<char>::iterator end = source.end();
		
		
		cpp_grammar<std::vector<char>::iterator> cpp_parser;
		
		
		std::string result;
		
		
		bool ret = qi::parse (start, end, cpp_parser, result);
		
		
		std::cout << result << std::endl;
		
		if (ret) std::cout << "Parsing successful" << std::endl;
		else     std::cout << "Parsing failed" << std::endl;
		
		
//		Namespace* current_nspace = mRoot;
//		Class* current_class = 0;
//		
//		
//		bool comment = false;
//		
//		
//		std::string token;
//		
//		/* read the entire file */
//		while (!stream.eof())
//		{
//			/* get next token */
//			stream >> token;
//			
//			/* ignore comments */
//			if (comment) continue;
//			
//			
//			if (token == "};") current_class = 0;
//			
//			else if (token == "}" && !current_class)
//				current_nspace = current_nspace->parent;
//			
//			
//			else if (token.find ("/*") != std::string::npos)
//				comment = true;
//			
//			else if (token.find ("*/") != std::string::npos)
//				comment = false;
//			
//			
//			else if (token == "namespace")
//			{
//				stream >> token;
//				
//				Namespace* nspace = new Namespace (token, current_nspace);
//				current_nspace->children.push_back (nspace);
//				current_nspace = nspace;
//			}
//			
//			
//			else if (token == "class" && !current_class)
//			{
//				std::string name;
//				stream >> name;
//				
//				std::cout << name << std::endl;
//				
//				if (name.find(";", 0) != std::string::npos)
//					continue;
//				
//				while (!stream.eof())
//				{
//					stream >> token;
//					
//					/* found class */
//					if (token == "{" || token == ":")
//					{
//						Class* klass = new Class (name);
//						current_nspace->classes.push_back (klass);
//						current_class = klass;
//						break;
//					}
//					
//					/* forward class */
//					else if (token == ";")
//						break;
//					
//					name = token;
//				}
//			}
//			
//			
//		} /* while */
	}


}}

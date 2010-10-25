
#include "Parser.h"

#include <queue>
#include <fstream>
#include <iostream>


namespace Myelin {
namespace Generator {


	/* constructor */
	Parser::Parser () : mRoot(new Namespace("", 0)), mCurrentClass (0)
	{
		mCurrentNamespace = mRoot;
		
		mTokens[OPEN_COMMENT] = "/*";
		mTokens[CLOSE_COMMENT] = "*/";
		
		mTokens[OPEN_CURLY_BRACKET] = "{";
		mTokens[CLOSE_CURLY_BRACKET] = "}";
		
		mTokens[OPEN_BRACKET] = "(";
		mTokens[CLOSE_BRACKET] = ")";
		
		mTokens[COLON] = ":";
		mTokens[SEMI_COLON] = ";";
		
		
		mKeywords.push_back ("namespace");
		mKeywords.push_back ("class");
	}
	
	
	/* destructor */
	Parser::~Parser ()
	{
		
	}
	
	
	
	
	void dump (char* buffer, int start, int end)
	{
		for (int i = start; i <= end; ++i)
			std::cout << buffer[i];
		std::cout << std::endl;
	}
	
	
	
	bool isAlpha (const char& c)
	{
		return ((c >= 'a' && c <= 'z') ||
		        (c >= 'A' && c <= 'Z') ||
		        c == '_');
	}
	
	
	bool isAlphaNum (const char& c)
	{
		return ((c >= 'a' && c <= 'z') ||
		        (c >= 'A' && c <= 'Z') ||
		        c == '_' ||
		        (c >= '0' && c <= '9'));
	}
	
	
	bool isWhiteSpace (const char& c)
	{
		return (c==' ' || c=='\n' || c=='\t' || c=='\r' || c=='\v');
	}
	
	
	
	
	
	
	/* split buffer into tokens */
	std::vector<std::string> Parser::tokenize (char* buffer, int length)
	{
		std::vector<std::string> tokens;
		
		
		int start = -1;
		int token_start = -1;
		bool ignore = false;
		
		
		/* process each character */
		for (int i = 0; i < length; ++i)
		{
			
			/* whitespace is a token break */
			if (isWhiteSpace (buffer[i]))
			{
				/* got valid data between tokens */
				if (!ignore && start != -1)
				{
					std::string str (&buffer[start], i-start);
					tokens.push_back (str);
				}
				
				/* reset index */
				start = -1;
				token_start = -1;
			}
			
			
			/* process character */
			else
			{
				/* set index */
				if (start == -1) start = i;
				if (token_start == -1) token_start = i;
				
				
				
				bool match = false;
				std::map<Token, std::string>::iterator iter;
				
				
				/* look for matching token */
				for (iter = mTokens.begin(); iter != mTokens.end(); ++iter)
				{
					/* ignore comment data */
					if (ignore && iter->first != CLOSE_COMMENT)
						continue;
					
					
					/* get token compare length */
					int len = i + 1 - token_start;
					
					
					/* found either partial or full token match */
					if (len <= iter->second.size() &&
					    iter->second.compare (0, len, &buffer[token_start], len) == 0)
					{
						/* found full token match */
						if (len == iter->second.size())
						{
							std::string str (&buffer[token_start], len);
							tokens.push_back (str);
							
							/* reset index */
							start = -1;
							token_start = -1;
							
							/* ignore anything between comment tokens */
							if (iter->first == OPEN_COMMENT) ignore = true;
							else if (iter->first == CLOSE_COMMENT) ignore = false;
							
							break;
						}
						
						/* got a partial match */
						match = true;
					}
				}
				
				
				/* no token match found */
				if (!match) token_start = -1;
			}
			
		}
		
		
		return tokens;
	}
	
	
	
	
	/* parse file */
	void Parser::parse (const std::string& file)
	{
		/* file stream */
		std::ifstream stream (file.c_str());
		
		
		int length;
		char* buffer;
		
		/* get file length in bytes */
		stream.seekg (0, std::fstream::end);
		length = stream.tellg ();
		stream.seekg (0, std::fstream::beg);
		
		/* allocate buffer */
		buffer = new char[length];
		
		/* read file into buffer */
		stream.read (buffer, length);
		stream.close();
		
		
		/* split contents into tokens */
		std::vector<std::string> tokens = tokenize (buffer, length);
		
		
		std::string identifier;
		std::vector<Keyword> stack;
		
		
		bool inheriting = false;
		std::vector<std::string>::iterator iter;
		
		
		/* find keywords in the list of tokens */
		for (iter = tokens.begin(); iter != tokens.end(); ++iter)
		{
			/* found namespace */
			if (*iter == "namespace")
				stack.push_back (NAMESPACE);
			
			
			/* found class */
			else if (*iter == "class")
				stack.push_back (CLASS);
			
			
			/* found colon */
			else if (*iter == ":")
			{
				/* create class */
				if (stack.back() == CLASS)
					inheriting = true;
			}
			
			
			/* found semi colon */
			else if (*iter == ";")
			{
				/* pop class */
				if (stack.back() == CLASS)
					stack.pop_back();
			}
			
			
			
			/* found opening bracket */
			else if (*iter == "{")
			{
				/* open namespace */
				if (stack.back() == NAMESPACE)
				{
					Namespace* nspace = new Namespace (identifier, mCurrentNamespace);
					
					mCurrentNamespace->children.push_back (nspace);
					mCurrentNamespace = nspace;
				}
				
				/* open class */
				else if (stack.back() == CLASS)
				{
					Class* klass = new Class (identifier, mCurrentClass);
					
					if (mCurrentClass)
						mCurrentClass->children.push_back (klass);
					else
						mCurrentNamespace->classes.push_back (klass);
					
					mCurrentClass = klass;
					inheriting = false;
				}
				
				
				/* add an empty keyword to the stack so that we
				 * can still have '}' unwinding but wont nest unknown
				 * keywords as the parent type. */
				stack.push_back (NOTHING);
			}
			
			
			/* found closing bracket */
			else if (*iter == "}")
			{
				/* remove the padded keyword from stack */
				stack.pop_back();
				
				
				/* close namespace */
				if (stack.back() == NAMESPACE)
				{
					mCurrentNamespace = mCurrentNamespace->parent;
					stack.pop_back();
				}
				
				/* close class */
				else if (stack.back() == CLASS)
				{
					mCurrentClass = mCurrentClass->parent;
					stack.pop_back();
				}
			}
			
			
			/* no keyword found so store as an identifier */
			else if (!inheriting) identifier = *iter;
		}
		
		
		
		/* free buffer */
		delete[] buffer;
	}


}}

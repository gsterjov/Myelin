
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
		mTokens[COMMA] = ",";
		
		mTokens[ASTERIX] = "*";
		mTokens[AMPERSAND] = "&";
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
	
	
	
	void trim (std::string& str)
	{
		str.erase (0, str.find_first_not_of (" \t\n"));
		str.erase (str.find_last_not_of (" \t\n") + 1);
	}
	
	
	
	std::string Parser::getScope (const std::string& type)
	{
		std::string full_type = type;
		
		
		/* determine type scope */
		if (mCurrentClass)
		{
			std::string name = type.substr (0, type.find_first_of(':'));
			std::vector<Class*>::iterator iter;
			
			/* look for nested class */
			for (iter = mCurrentClass->children.begin();
			     iter != mCurrentClass->children.end();
			     ++iter)
			{
				Class* klass = *iter;
				if (name == klass->name)
					full_type = mCurrentClass->name + "::" + type;
			}
			
			
			std::vector<std::string>::iterator it;
			
			/* look for nested enum */
			for (it = mCurrentClass->enums.begin();
			     it != mCurrentClass->enums.end();
			     ++it)
			{
				if (type == *it)
					full_type = mCurrentClass->name + "::" + type;
			}
		}
		
		
		return full_type;
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
							/* add anything before the token */
							if (start != -1 && token_start > start)
							{
								std::string before (&buffer[start], token_start-start);
								tokens.push_back (before);
							}
							
							/* add matched token */
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
	
	
	
	
	void Parser::parseNamespace (const std::vector<std::string>& frame)
	{
		std::map<std::string, Namespace*>::iterator iter;
		iter = mCurrentNamespace->children.find (frame.back());
		
		
		/* no namespace found. create a new one */
		if (iter == mCurrentNamespace->children.end())
		{
			Namespace* nspace = new Namespace (frame.back(), mCurrentNamespace);
			
			mCurrentNamespace->children[nspace->name] = nspace;
			mCurrentNamespace = nspace;
		}
		
		/* existing namespace found */
		else mCurrentNamespace = iter->second;
	}
	
	
	
	void Parser::parseClass (const std::vector<std::string>& frame)
	{
		bool subclass = false;
		
		std::string name = frame.back();
		std::vector<std::string> bases;
		
		
		/* find the real class identifier */
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i] == ":")
			{
				name = frame[i-1];
				subclass = true;
			}
			
			else if (subclass)
			{
				if (frame[i] == "public")
					bases.push_back (frame[i + 1]);
			}
		}
		
		
		/* create class */
		Class* klass = new Class (name, mCurrentClass);
		klass->bases = bases;
		klass->hasVirtuals = false;
		
		if (mCurrentClass) mCurrentClass->children.push_back (klass);
		else mCurrentNamespace->classes.push_back (klass);
		
		mCurrentClass = klass;
	}
	
	
	
	void Parser::parseFunction (const std::vector<std::string>& frame)
	{
		std::string name;
		std::string ret;
		std::vector<std::string> params;
		bool isVirtual = false;
		bool isConstant = false;
		bool isStatic = false;
		
		bool parsed = false;
		bool isParam = false;
		bool isType = true;
		
		std::string param;
		std::string prefix;
		std::string postfix;
		
		
		
		/* find the real function identifier */
		for (int i = 0; i < frame.size(); ++i)
		{
			if (frame[i] == "(")
			{
				name = frame[i-1];
				
				/* found constructor */
				if (mCurrentClass && name == mCurrentClass->name)
					return;
				
				/* ignore destructors */
				else if (name.find('~') != std::string::npos)
					return;
				
				
				bool gotType = false;
				
				/* get return type */
				for (int j = i-2; j >= 0; --j)
				{
					/* pointer or reference return type */
					if (frame[j] == "*" || frame[j] == "&")
						postfix = frame[j] + postfix;
					
					/* constant return type */
					else if (frame[j] == "const")
					{
						if (gotType) prefix = " const " + prefix;
						else postfix = " const " + postfix;
					}
					
					/* qualified return type */
					else if (frame[j] == ":")
					{
						ret = frame[j] + ret;
						gotType = false;
					}
					
					/* return type */
					else
					{
						if (!gotType)
						{
							ret = frame[j] + ret;
							gotType = true;
						}
						else break;
					}
				}
				
				ret = getScope (ret);
				ret = prefix + ret + postfix;
				
				/* trim return */
				trim (ret);
				
				prefix.clear();
				postfix.clear();
				
				isParam = true;
			}
			
			
			
			/* parse parameter */
			else if (isParam)
			{
				/* no more parameters */
				if (frame[i] == ")")
				{
					parsed = true;
					isParam = false;
					
					param = getScope (param);
					param = prefix + param + postfix;
					
					trim (param);
					if (!param.empty()) params.push_back (param);
					
					param.clear();
					prefix.clear();
					postfix.clear();
				}
				
				
				/* next parameter */
				else if (frame[i] == ",")
				{
					param = getScope (param);
					param = prefix + param + postfix;
					
					trim (param);
					if (!param.empty()) params.push_back (param);
					
					param.clear();
					prefix.clear();
					postfix.clear();
					
					isType = true;
				}
				
				
				/* qualified parameter type */
				else if (frame[i] == ":")
				{
					param += frame[i];
					isType = true;
				}
				
				
				/* parameter is a pointer or reference */
				else if (frame[i] == "*" || frame[i] == "&")
					postfix += frame[i];
				
				
				/* constant paramter */
				else if (frame[i] == "const")
					if (isType) prefix += " const ";
					else postfix += " const ";
				
				
				/* parameter type */
				else if (isParam)
				{
					/* we dont want the identifier */
					if (isType)
					{
						param += frame[i];
						isType = false;
					}
				}
			}
			
			
			/* virtual function */
			else if (frame[i] == "virtual")
				isVirtual = true;
			
			/* static function */
			else if (frame[i] == "static")
				isStatic = true;
			
			/* const function */
			else if (parsed && frame[i] == "const")
				isConstant = true;
		}
		
		
		
		/* create function */
		if (!name.empty() && !isStatic)
		{
			Function* function = new Function (name);
			function->ret = ret;
			function->params = params;
			function->isVirtual = isVirtual;
			function->isConstant = isConstant;
			
			if (mCurrentClass)
			{
				mCurrentClass->functions.push_back (function);
				if (isVirtual) mCurrentClass->hasVirtuals = true;
			}
		}
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
		std::vector<Keyword> scope;
		std::vector<std::string> frame;
		
		
		bool isPublic = false;
		std::vector<std::string>::iterator iter;
		
		
		
		/* find keywords in the list of tokens */
		for (iter = tokens.begin(); iter != tokens.end(); ++iter)
		{
			/* found namespace */
			if (*iter == "namespace")
			{
				scope.push_back (NAMESPACE);
				frame.clear();
			}
			
			/* found class */
			else if (*iter == "class")
			{
				if (!scope.empty())
				{
					/* ignore template classes */
					if (scope.back() != TEMPLATE)
						scope.push_back (CLASS);
				}
				
				frame.clear();
			}
			
			/* found template keyword */
			else if (*iter == "template")
			{
				scope.push_back (TEMPLATE);
				frame.clear();
			}
			
			/* found enumeration */
			else if (*iter == "enum")
			{
				scope.push_back (ENUMERATION);
				frame.clear();
			}
			
			
			/* found function declaration */
			else if (*iter == "(")
			{
				if (!scope.empty())
				{
					/* ignore template functions */
					if (scope.back() != TEMPLATE)
					{
						/* make sure a class is the immediate parent scope */
						if (isPublic && scope[scope.size() - 2] == CLASS)
							scope.push_back (FUNCTION);
					}
				}
				
				frame.push_back (*iter);
			}
			
			
			/* found semi colon */
			else if (*iter == ";")
			{
				if (!scope.empty())
				{
					/* pop class since we dont want forwarded classes */
					if (scope.back() == CLASS)
						scope.pop_back();
					
					/* parse declared function */
					if (scope.back() == FUNCTION)
					{
						parseFunction (frame);
						scope.pop_back();
					}
					
					/* pop template declaration */
					if (scope.back() == TEMPLATE)
						scope.pop_back();
					
					/* pop enum declaration */
					if (scope.back() == ENUMERATION)
					{
						if (mCurrentClass)
							mCurrentClass->enums.push_back(frame.back());
						
						scope.pop_back();
					}
				}
				
				frame.clear ();
			}
			
			
			
			/* found opening bracket */
			else if (*iter == "{")
			{
				if (!scope.empty())
				{
					/* parse last keyword in the scope */
					if      (scope.back() == NAMESPACE) parseNamespace (frame);
					else if (scope.back() == CLASS)     parseClass     (frame);
					else if (scope.back() == FUNCTION)  parseFunction  (frame);
					
					else if (scope.back() == ENUMERATION)
					{
						if (mCurrentClass)
							mCurrentClass->enums.push_back(frame.back());
					}
				}
				
				
				/* add an empty keyword to the stack so that we
				 * can still have '}' unwinding but wont nest unknown
				 * keywords as the parent type. */
				scope.push_back (NOTHING);
				
				/* clear frame */
				frame.clear();
			}
			
			
			/* found closing bracket */
			else if (*iter == "}")
			{
				/* remove the padded keyword from stack */
				if (!scope.empty()) scope.pop_back();
				frame.clear();
				
				
				if (!scope.empty())
				{
					/* close namespace */
					if (scope.back() == NAMESPACE)
					{
						mCurrentNamespace = mCurrentNamespace->parent;
						scope.pop_back();
					}
					
					/* close class */
					else if (scope.back() == CLASS)
					{
						mCurrentClass = mCurrentClass->parent;
						scope.pop_back();
					}
					
					/* close function */
					else if (scope.back() == FUNCTION)
						scope.pop_back();
					
					
					/* close template */
					else if (scope.back() == TEMPLATE)
						scope.pop_back();
					
					
					/* close enum */
					else if (scope.back() == ENUMERATION)
						scope.pop_back();
				}
			}
			
			
			/* class accessors */
			else if (scope.size() >= 2 && scope[scope.size() - 2] == CLASS && *iter == "public")
				isPublic = true;
			
			else if (scope.size() >= 2 && scope[scope.size() - 2] == CLASS && (*iter == "protected" || *iter == "private"))
				isPublic = false;
			
			
			
			/* no keyword found so store as an identifier */
			else frame.push_back (*iter);
		}
		
		
		
		/* free buffer */
		delete[] buffer;
	}


}}


#include "Parser.h"

#include <queue>
#include <fstream>
#include <iostream>


namespace Myelin {
namespace Generator {


	/* constructor */
	Parser::Parser () : mRoot(new Namespace("", 0))
	{
		mCurrentNamespace = mRoot;
		
		mTokenMap[OPEN_COMMENT] = "/*";
		mTokenMap[CLOSE_COMMENT] = "*/";
		
		mTokenMap[NAMESPACE] = "namespace";
		mTokenMap[CLASS] = "class";
		
		mTokenMap[OPEN_BRACKET] = "{";
		mTokenMap[CLOSE_BRACKET] = "}";
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
	
	
	
	int Parser::parseNamespace (char* buffer, int length, int index)
	{
		std::string name;
		
		int start = 0;
		int end = 0;
		
		for (int i = index; i < length; ++i)
		{
			char c = buffer[i];
			
			/* ignore whitespace */
			if (start == 0 && isWhiteSpace (c)) continue;
			if (end != 0 &&  isWhiteSpace (c)) continue;
			
			/* found name */
			else if (start == 0 && isAlpha (c))
			{
				start = i;
			}
			
			/* continue name */
			else if (start != 0 && isAlphaNum (c))
			{
				end = i;
			}
			
			else if (end != 0 && c == '{')
			{
				std::string str (&buffer[start], (end-start)+1);
				Namespace* nspace = new Namespace (str, mCurrentNamespace);
				
				mCurrentNamespace->children.push_back (nspace);
				mCurrentNamespace = nspace;
				break;
			}
			
			else
			{
				break;
			}
			
			index = i;
		}
		
		return index;
	}
	
	
	
	int Parser::parseClass (char* buffer, int length, int index)
	{
		std::string name;
		
		int start = 0;
		int end = 0;
		
		for (int i = index; i < length; ++i)
		{
			char c = buffer[i];
			
			/* ignore whitespace */
			if (start == 0 && isWhiteSpace (c)) continue;
			if (end != 0 &&  isWhiteSpace (c)) continue;
			
			/* found name */
			else if (start == 0 && isAlpha (c))
			{
				start = i;
			}
			
			/* continue name */
			else if (start != 0 && isAlphaNum (c))
			{
				end = i;
			}
			
			else if (end != 0 && (c == '{' || c == ':'))
			{
				std::string str (&buffer[start], (end-start)+1);
				Class* klass = new Class (str);
				
				mCurrentNamespace->classes.push_back (klass);
				mCurrentClass = klass;
				break;
			}
			
			else
			{
				break;
			}
			
			index = i;
		}
		
		return index;
	}
	
	
	
	void Parser::tokenize (char* buffer, int length)
	{
		std::vector<Token> tokens;
		
		
		/* process each character */
		for (int i = 0; i < length; ++i)
		{
			int max = 0;
			
			
			std::vector<Token> matches;
			std::map<Token, std::string>::iterator iter;
			
			/* look for matching token */
			for (iter = mTokenMap.begin(); iter != mTokenMap.end(); ++iter)
			{
				bool match = true;
				
				for (int j = i; j < length; ++j)
				{
					std::string str (&buffer[i], j-i+1);
					std::cout << str << std::endl;
					
					if (j-i < iter->second.size())
						break;
					
					if (buffer[j] != iter->second[j-i])
					{
						match = false;
						break;
					}
				}
				
				if (match)
				{
					matches.push_back (iter->first);
					
					if (iter->second.size() > max)
						max = iter->second.size();
				}
			}
			
			
			i += max;
			
			
			
			/* only add complete matches */
			for (int j = 0; j < matches.size(); ++j)
			{
				tokens.push_back (matches[j]);
				std::cout << i << " - " << mTokenMap[matches[j]] << std::endl;
			}
		}
		
		
//		for (int i = 0; i < tokens.size(); ++i)
//			std::cout << mTokenMap[tokens[i]] << std::endl;
		
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
		
		
		tokenize (buffer, length);
		
		
		
//		std::vector<Token> stack;
////		int start = 0;
//		
//		
//		/* parse each character */
//		for (int i = 0; i < length; ++i)
//		{
//			if (buffer[i] == '{')
//			{
//				stack.push_back (OPEN_BRACKET);
//				continue;
//			}
//			
//			/* pop last token */
//			if (buffer[i] == '}')
//			{
//				if (stack.back() == NAMESPACE)
//					mCurrentNamespace = mCurrentNamespace->parent;
//				
//				stack.pop_back();
//				continue;
//			}
//			
//			
//			std::vector<Token> tmp;
//			
//			
//			std::map<Token, std::string>::iterator iter;
//			
//			for (iter = mTokenMap.begin(); iter != mTokenMap.end(); ++iter)
//			{
//				bool found = true;
//				
//				for (int j = start; j <= i; ++j)
//				{
//					if (iter->second[j-start] != buffer[j])
//						found = false;
//				}
//				
//				if (found)
//					tmp.push_back (iter->first);
//			}
//			
//			
//			if (tmp.size() == 0)
//				i = ++start;
//			
//			else if (tmp.size() == 1)
//			{
//				Token token = tmp[0];
//				
//				
//				/* check for complete match */
//				if (mTokenMap[token].size() != (i - start)+1)
//					continue;
//				
//				
//				if (token == NAMESPACE)
//				{
//					i = parseNamespace (buffer, length, i);
//				}
//				
//				
//				if (token == CLASS)
//				{
//					i = parseClass (buffer, length, i);
//				}
//				
//				
//				stack.push_back (token);
//				
//				
//				if (token == COMMENT_START)
//					comment_start (start);
//				
//				if (token == COMMENT_END)
//					comment_end (buffer, i);
				
				
//				if (stack.empty())
//					stack.push (token);
//				
//				else if (stack.back() == COMMENT_START && token == COMMENT_END)
//					stack.push (token);
//				
//				else if (stack.back() != COMMENT_START)
//					stack.push (token);
//				
//				
//				start = i + 1;
//			}
//		}
//		
		
//		while (!stack.empty())
//		{
//			Token token = stack.front();
//			stack.pop();
//			
//			if (token != COMMENT_START && token != COMMENT_END)
//				std::cout << mTokenMap[token] << std::endl;
//		}
		
		
		
		/* free buffer */
		delete[] buffer;
		
		
		
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

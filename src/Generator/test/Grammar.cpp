/*
    Copyright 2009-2013 Goran Sterjov
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

#include <gtest/gtest.h>

#include <string>
#include <stdexcept>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>


namespace MyelinGenerator {
namespace Test {


	/* function test fixture */
	class GrammarTest : public testing::Test
	{
	public:
		GrammarTest() : mInput(NULL), mTokens(NULL), mLexer(NULL), mParser(NULL)
		{

		}

		~GrammarTest()
		{
			freeParser();
		}


		void createParser (std::string input)
		{
			freeParser();

			/* load input */
			mInput = antlr3NewAsciiStringInPlaceStream ((pANTLR3_UINT8)input.c_str(), input.length(), NULL);
			
			if (!mInput)
				throw std::runtime_error ("Failed to stream with specified input");
			
			
			/* create lexer and parser */
			mLexer = CppHeaderLexerNew (mInput);
			mTokens = antlr3CommonTokenStreamSourceNew (ANTLR3_SIZE_HINT, TOKENSOURCE(mLexer));
			mParser = CppHeaderParserNew (mTokens);
		}


		void freeParser()
		{
			if (mParser) mParser->free (mParser);
			if (mTokens) mTokens->free (mTokens);
			
			if (mLexer) mLexer->free (mLexer);
			if (mInput) mInput->close (mInput);
		}
	
	
	protected:
		pANTLR3_INPUT_STREAM            mInput;
		pANTLR3_COMMON_TOKEN_STREAM     mTokens;
		
		pCppHeaderLexer  mLexer;
		pCppHeaderParser mParser;
	};
	
	
	
	/* test parser creation */
	TEST_F (GrammarTest, CreateParser)
	{
		EXPECT_NO_THROW ({ createParser (""); });
	}


	/* test parsing a function declaration */
	TEST_F (GrammarTest, ParseFunctions)
	{
		CppHeaderParser_func_return ret;

		// primitive functions
		createParser ("void test ();");
		ret = mParser->func (mParser);
		EXPECT_GT (ret.tree->getChildCount(ret.tree), 0);

		std::cout << ret.tree->getChildCount(ret.tree) << std::endl;
		std::cout << "AST: " << ret.tree->toStringTree(ret.tree)->chars << std::endl;

		// createParser ("void test (int val);");
		// ret = mParser->func (mParser);
		// EXPECT_GT (ret.tree->getChildCount(ret.tree), 0);

		// std::cout << ret.tree->getChildCount(ret.tree) << std::endl;
		// std::cout << "AST: " << ret.tree->toStringTree(ret.tree)->chars << std::endl;

		// createParser ("void test (int val1, int val2);");
		// ret = mParser->func (mParser);
		// EXPECT_GT (ret.tree->getChildCount(ret.tree), 0);

		// std::cout << ret.tree->getChildCount(ret.tree) << std::endl;
		// std::cout << "AST: " << ret.tree->toStringTree(ret.tree)->chars << std::endl;
	}


	/* test parsing a function declaration */
	TEST_F (GrammarTest, ParseComplexFunctions)
	{
		// CppHeaderParser_func_return ret;

		// // primitive functions
		// createParser ("SomeClass test ();");
		// ret = mParser->func (mParser);
		// EXPECT_GT (ret.tree->getChildCount(ret.tree), 0);

		// std::cout << ret.tree->getChildCount(ret.tree) << std::endl;
		// std::cout << "AST: " << ret.tree->toStringTree(ret.tree)->chars << std::endl;

		// createParser ("SomeClass test (int val);");
		// ret = mParser->func (mParser);
		// EXPECT_GT (ret.tree->getChildCount(ret.tree), 0);

		// createParser ("void test (int val1, int val2);");
		// ret = mParser->func (mParser);
		// EXPECT_TRUE (ret.tree);
	}

}}

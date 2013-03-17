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
#include <gmock/gmock.h>

#include <string>
#include <stdexcept>

#include <CppHeaderLexer.h>
#include <CppHeaderParser.h>
#include <FunctionParser.h>


using testing::Gt;
using testing::Eq;
using testing::StrEq;
using testing::NotNull;


namespace MyelinGenerator {
namespace Test {


	/* function test fixture */
	class FunctionParserTest : public testing::Test
	{
	public:
		FunctionParserTest() : mContent(NULL), mInput(NULL), mTokens(NULL), mLexer(NULL), mParser(NULL)
		{
			mInputName = (pANTLR3_UINT8)"input";
		}

		~FunctionParserTest()
		{
			freeParser();
		}


		void createParser (std::string input)
		{
			freeParser();

			/* load input */
			mContent = (pANTLR3_UINT8)strdup(input.c_str());
			mInput = antlr3StringStreamNew (mContent, ANTLR3_ENC_8BIT, input.length(), mInputName);
			
			if (!mInput)
				throw std::runtime_error ("Failed to stream with specified input");
			
			
			/* create lexer and parser */
			mLexer = CppHeaderLexerNew (mInput);
			mTokens = antlr3CommonTokenStreamSourceNew (ANTLR3_SIZE_HINT, TOKENSOURCE(mLexer));
			mParser = CppHeaderParserNew (mTokens);
		}


		void freeParser()
		{
			if (mContent) free (mContent);
			if (mParser) mParser->free (mParser);
			if (mTokens) mTokens->free (mTokens);
			
			if (mLexer) mLexer->free (mLexer);
			if (mInput) mInput->close (mInput);
		}
	
	
	protected:
		pANTLR3_UINT8 mContent;
		pANTLR3_UINT8 mInputName;

		pANTLR3_INPUT_STREAM		mInput;
		pANTLR3_COMMON_TOKEN_STREAM	mTokens;
		
		pCppHeaderLexer		mLexer;
		pCppHeaderParser	mParser;
	};
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, parse_primitive_no_params)
	{
		ASSERT_NO_THROW ({ createParser ("void test ();"); });

		// Parse tree
		CppHeaderParser_function_declaration_return ret = mParser->function_declaration (mParser);
		FunctionParser* parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		EXPECT_FALSE (parser->isConstant());
	}
	

	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, parse_primitive_with_params)
	{
		FunctionParser* parser = NULL;
		CppHeaderParser_function_declaration_return ret;


		// single parameter
		ASSERT_NO_THROW ({ createParser ("void test (int val);"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("int"));
		EXPECT_FALSE (parser->isConstant());


		// multiple parameters
		ASSERT_NO_THROW ({ createParser ("void test (int val1, int val2, int val3);"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(3));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("int"));
		EXPECT_THAT (parser->getParameters()[1]->getName(), StrEq("int"));
		EXPECT_THAT (parser->getParameters()[2]->getName(), StrEq("int"));
		EXPECT_FALSE (parser->isConstant());
	}


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, parse_complex_no_params)
	{
		FunctionParser* parser = NULL;
		CppHeaderParser_function_declaration_return ret;


		// non qualified
		ASSERT_NO_THROW ({ createParser ("SomeClass test ();"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		EXPECT_FALSE (parser->isConstant());


		// fully qualified
		ASSERT_NO_THROW ({ createParser ("SomeScope::SomeClass test ();"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeScope::SomeClass"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		EXPECT_FALSE (parser->isConstant());
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, parse_complex_with_params)
	{
		FunctionParser* parser = NULL;
		CppHeaderParser_function_declaration_return ret;


		// non qualified
		ASSERT_NO_THROW ({ createParser ("SomeClass test (OtherClass val);"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("OtherClass"));
		EXPECT_FALSE (parser->isConstant());


		// fully qualified
		ASSERT_NO_THROW ({ createParser ("SomeScope::SomeClass test (OtherScope::OtherClass val);"); });

		// Parse tree
		ret = mParser->function_declaration (mParser);
		parser = new FunctionParser (ret.tree);

		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType(), NotNull());
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeScope::SomeClass"));
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("OtherScope::OtherClass"));
		EXPECT_FALSE (parser->isConstant());
	}

}}

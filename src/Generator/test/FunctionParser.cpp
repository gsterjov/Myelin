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


		FunctionParser* parse (std::string input)
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

			CppHeaderParser_function_declaration_return ret = mParser->function_declaration (mParser);
			return new FunctionParser (ret.tree);
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
	TEST_F (FunctionParserTest, declared)
	{
		FunctionParser* parser = NULL;

		ASSERT_NO_THROW ({ parser = parse ("void test ();"); });
		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		delete parser;
	}



	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, defined)
	{
		FunctionParser* parser = NULL;

		ASSERT_NO_THROW ({ parser = parse ("void test () { var statement = 0; }"); });
		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		delete parser;
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, abstract)
	{
		FunctionParser* parser = NULL;

		ASSERT_NO_THROW ({ parser = parse ("void test () = 0;"); });
		EXPECT_THAT (parser->getName(), StrEq("test"));
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		EXPECT_THAT (parser->getParameters().size(), Eq(0));
		delete parser;
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, returns)
	{
		FunctionParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("void test ();"); });
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("void"));
		delete parser;


		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("SomeClass test ();"); });
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeClass"));
		delete parser;


		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("SomeScope::SomeClass test ();"); });
		EXPECT_THAT (parser->getReturnType()->getName(), StrEq("SomeScope::SomeClass"));
		delete parser;
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, parameters)
	{
		FunctionParser* parser = NULL;

		// single parameter
		ASSERT_NO_THROW ({ parser = parse ("void test (int val);"); });
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("int"));
		delete parser;


		// multiple parameters
		ASSERT_NO_THROW ({ parser = parse ("void test (int val1, int val2, int val3);"); });
		EXPECT_THAT (parser->getParameters().size(), Eq(3));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("int"));
		EXPECT_THAT (parser->getParameters()[1]->getName(), StrEq("int"));
		EXPECT_THAT (parser->getParameters()[2]->getName(), StrEq("int"));
		delete parser;


		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("void test (OtherClass val);"); });
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("OtherClass"));
		delete parser;


		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("void test (OtherScope::OtherClass val);"); });
		EXPECT_THAT (parser->getParameters().size(), Eq(1));
		EXPECT_THAT (parser->getParameters()[0]->getName(), StrEq("OtherScope::OtherClass"));
		delete parser;
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, storage_classes)
	{
		FunctionParser* parser = NULL;

		// nothing
		ASSERT_NO_THROW ({ parser = parse ("void test ();"); });
		EXPECT_EQ (parser->getStorageClass(), FunctionParser::STORAGE_CLASS_NONE);
		delete parser;

		// static
		ASSERT_NO_THROW ({ parser = parse ("static void test ();"); });
		EXPECT_EQ (parser->getStorageClass(), FunctionParser::STORAGE_CLASS_STATIC);
		delete parser;


		// extern
		ASSERT_NO_THROW ({ parser = parse ("extern void test ();"); });
		EXPECT_EQ (parser->getStorageClass(), FunctionParser::STORAGE_CLASS_EXTERN);
		delete parser;


		// register
		ASSERT_NO_THROW ({ parser = parse ("register void test ();"); });
		EXPECT_EQ (parser->getStorageClass(), FunctionParser::STORAGE_CLASS_REGISTER);
		delete parser;
	}
	


	/* test parsing a function declaration */
	TEST_F (FunctionParserTest, storage_qualifiers)
	{
		FunctionParser* parser = NULL;

		// none
		ASSERT_NO_THROW ({ parser = parse ("void test ();"); });
		EXPECT_EQ (parser->getStorageQualifiers(), FunctionParser::STORAGE_QUALIFIER_NONE);
		delete parser;


		// constant
		ASSERT_NO_THROW ({ parser = parse ("void test () const;"); });
		EXPECT_EQ (parser->getStorageQualifiers(), FunctionParser::STORAGE_QUALIFIER_CONSTANT);
		delete parser;


		// volatile
		ASSERT_NO_THROW ({ parser = parse ("void test () volatile;"); });
		EXPECT_EQ (parser->getStorageQualifiers(), FunctionParser::STORAGE_QUALIFIER_VOLATILE);
		delete parser;


		// both constant and volatile
		ASSERT_NO_THROW ({ parser = parse ("void test () const volatile;"); });
		EXPECT_EQ (parser->getStorageQualifiers(), FunctionParser::STORAGE_QUALIFIER_CONSTANT | FunctionParser::STORAGE_QUALIFIER_VOLATILE);
		delete parser;
	}

}}

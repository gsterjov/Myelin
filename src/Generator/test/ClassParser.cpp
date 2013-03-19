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
#include <ClassParser.h>


using testing::Gt;
using testing::Eq;
using testing::StrEq;


namespace MyelinGenerator {
namespace Test {


	/* function test fixture */
	class ClassParserTest : public testing::Test
	{
	public:
		ClassParserTest() : mContent(NULL), mInput(NULL), mTokens(NULL), mLexer(NULL), mParser(NULL)
		{
			mInputName = (pANTLR3_UINT8)"input";
		}

		~ClassParserTest()
		{
			freeParser();
		}


		ClassParser* parse (std::string input)
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

			CppHeaderParser_class_declaration_return ret = mParser->class_declaration (mParser);
			return new ClassParser (ret.tree);
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



	/* test parsing a class definition */
	TEST_F (ClassParserTest, defined)
	{
		ClassParser* parser = NULL;

		ASSERT_NO_THROW ({ parser = parse ("class SomeClass {};"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;
	}



	/* test parsing a class definition */
	TEST_F (ClassParserTest, inheritance)
	{
		ClassParser* parser = NULL;

		// public
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass : public SomeBase {};"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;

		// protected
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass : protected SomeBase {};"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;

		// private
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass : private SomeBase {};"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass : public SomeBase1, protected SomeBase2, private SomeBase3 {};"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;
	}



	/* test parsing a class definition */
	TEST_F (ClassParserTest, with_functions)
	{
		ClassParser* parser = NULL;

		// single
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass { void test(); };"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getFunctions().size(), Eq(1));

		EXPECT_THAT (parser->getFunction("test")->getName(), Eq("test"));
		EXPECT_THAT (parser->getFunction("test")->getReturnType()->getName(), Eq("void"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass { void test1(); int test2 (int param){} };"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getFunctions().size(), Eq(2));

		EXPECT_THAT (parser->getFunction("test1")->getName(), Eq("test1"));
		EXPECT_THAT (parser->getFunction("test1")->getReturnType()->getName(), Eq("void"));

		EXPECT_THAT (parser->getFunction("test2")->getName(), Eq("test2"));
		EXPECT_THAT (parser->getFunction("test2")->getReturnType()->getName(), Eq("int"));
		delete parser;
	}



	/* test parsing a class definition */
	TEST_F (ClassParserTest, with_nested_classes)
	{
		ClassParser* parser = NULL;

		// single
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass { class NestedClass{}; };"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getClasses().size(), Eq(1));
		EXPECT_THAT (parser->getClass("NestedClass")->getName(), Eq("NestedClass"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("class SomeClass { class NestedClass{}; class OtherClass : public Inherited {}; };"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		EXPECT_THAT (parser->getClasses().size(), Eq(2));
		EXPECT_THAT (parser->getClass("NestedClass")->getName(), Eq("NestedClass"));
		EXPECT_THAT (parser->getClass("OtherClass")->getName(), Eq("OtherClass"));
		delete parser;
	}

}}

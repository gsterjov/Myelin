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
#include <NamespaceParser.h>


using testing::Gt;
using testing::Eq;
using testing::StrEq;


namespace MyelinGenerator {
namespace Test {


	/* namespace test fixture */
	class NamespaceParserTest : public testing::Test
	{
	public:
		NamespaceParserTest() : mContent(NULL), mInput(NULL), mTokens(NULL), mLexer(NULL), mParser(NULL)
		{
			mInputName = (pANTLR3_UINT8)"input";
		}

		~NamespaceParserTest()
		{
			freeParser();
		}


		NamespaceParser* parse (std::string input)
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

			CppHeaderParser_namespace_declaration_return ret = mParser->namespace_declaration (mParser);
			return new NamespaceParser (ret.tree);
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



	/* test parsing a namespace definition */
	TEST_F (NamespaceParserTest, defined)
	{
		NamespaceParser* parser = NULL;

		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope {}"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		delete parser;
	}



	/* test parsing a namespace definition */
	TEST_F (NamespaceParserTest, with_functions)
	{
		NamespaceParser* parser = NULL;

		// single
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { void test(); }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getFunctions().size(), Eq(1));
		EXPECT_THAT (parser->getFunction("test")->getName(), StrEq("test"));
		delete parser;

		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { SomeScope2::SomeClass test(int param2, SomeClass param2) {} }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getFunctions().size(), Eq(1));
		EXPECT_THAT (parser->getFunction("test")->getName(), StrEq("test"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { void test1(); void test2(); }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getFunctions().size(), Eq(2));
		EXPECT_THAT (parser->getFunction("test1")->getName(), StrEq("test1"));
		EXPECT_THAT (parser->getFunction("test2")->getName(), StrEq("test2"));
		delete parser;
	}



	/* test parsing a namespace definition */
	TEST_F (NamespaceParserTest, with_classes)
	{
		NamespaceParser* parser = NULL;

		// single
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { class Test {}; }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getClasses().size(), Eq(1));
		EXPECT_THAT (parser->getClass("Test")->getName(), StrEq("Test"));
		delete parser;

		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { class Test : public Base1, private Base2 {}; }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getClasses().size(), Eq(1));
		EXPECT_THAT (parser->getClass("Test")->getName(), StrEq("Test"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { class Test1 {}; class Test2 {}; }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getClasses().size(), Eq(2));
		EXPECT_THAT (parser->getClass("Test1")->getName(), StrEq("Test1"));
		EXPECT_THAT (parser->getClass("Test2")->getName(), StrEq("Test2"));
		delete parser;
	}



	/* test parsing a namespace definition */
	TEST_F (NamespaceParserTest, nested_namespaces)
	{
		NamespaceParser* parser = NULL;

		// single
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { namespace NestedScope {} }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getNamespaces().size(), Eq(1));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getName(), StrEq("NestedScope"));
		delete parser;

		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { namespace NestedScope { class Test {}; void test(); } }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getNamespaces().size(), Eq(1));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getName(), StrEq("NestedScope"));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getClasses().size(), Eq(1));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getFunctions().size(), Eq(1));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getClass("Test")->getName(), StrEq("Test"));
		EXPECT_THAT (parser->getNamespace("NestedScope")->getFunction("test")->getName(), StrEq("test"));
		delete parser;

		// multiple
		ASSERT_NO_THROW ({ parser = parse ("namespace SomeScope { namespace NestedScope1 {} namespace NestedScope2 {} }"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope"));
		EXPECT_THAT (parser->getNamespaces().size(), Eq(2));
		EXPECT_THAT (parser->getNamespace("NestedScope1")->getName(), StrEq("NestedScope1"));
		EXPECT_THAT (parser->getNamespace("NestedScope2")->getName(), StrEq("NestedScope2"));
		delete parser;
	}

}}

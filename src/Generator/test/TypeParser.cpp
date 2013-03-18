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
#include <TypeParser.h>


using testing::Gt;
using testing::Eq;
using testing::StrEq;


namespace MyelinGenerator {
namespace Test {


	/* type test fixture */
	class TypeParserTest : public testing::Test
	{
	public:
		TypeParserTest() : mContent(NULL), mInput(NULL), mTokens(NULL), mLexer(NULL), mParser(NULL)
		{
			mInputName = (pANTLR3_UINT8)"input";
		}

		~TypeParserTest()
		{
			freeParser();
		}


		TypeParser* parse (std::string input)
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

			CppHeaderParser_type_return ret = mParser->type (mParser);
			return new TypeParser (ret.tree);
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



	/* test parsing a type */
	TEST_F (TypeParserTest, names)
	{
		TypeParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("int"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		delete parser;

		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("SomeClass"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeClass"));
		delete parser;

		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("SomeScope::SomeClass"); });
		EXPECT_THAT (parser->getName(), StrEq("SomeScope::SomeClass"));
		delete parser;
	}



	/* test parsing a type */
	TEST_F (TypeParserTest, storage_qualifiers)
	{
		TypeParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("const int"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isConstant());
		EXPECT_FALSE (parser->isVolatile());
		delete parser;

		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("volatile int"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_FALSE (parser->isConstant());
		EXPECT_TRUE (parser->isVolatile());
		delete parser;

		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("const volatile int"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isConstant());
		EXPECT_TRUE (parser->isVolatile());
		delete parser;
	}



	/* test parsing a type */
	TEST_F (TypeParserTest, pointers)
	{
		TypeParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("int*"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isPointer());
		delete parser;

		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("int const*"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isConstantPointer());
		delete parser;

		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("int volatile *"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isVolatilePointer());
		delete parser;
	}



	/* test parsing a type */
	TEST_F (TypeParserTest, references)
	{
		TypeParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("int&"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isReference());
		delete parser;

		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("int const&"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isConstantReference());
		delete parser;

		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("int volatile &"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isVolatileReference());
		delete parser;
	}



	/* test parsing a type */
	TEST_F (TypeParserTest, reference_to_pointer)
	{
		TypeParser* parser = NULL;

		// primitive
		ASSERT_NO_THROW ({ parser = parse ("int*&"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isPointer());
		EXPECT_TRUE (parser->isReference());
		delete parser;

		// non qualified
		ASSERT_NO_THROW ({ parser = parse ("int const* const&"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isConstantPointer());
		EXPECT_TRUE (parser->isConstantReference());
		delete parser;

		// fully qualified
		ASSERT_NO_THROW ({ parser = parse ("int volatile * volatile &"); });
		EXPECT_THAT (parser->getName(), StrEq("int"));
		EXPECT_TRUE (parser->isVolatilePointer());
		EXPECT_TRUE (parser->isVolatileReference());
		delete parser;
	}

}}

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

#include <Parser.h>


namespace MyelinGenerator {
namespace Test {


	/* function test fixture */
	class ParserTest : public testing::Test
	{
	public:
		ParserTest()
		{
			mParser = new Parser();
		}

		~ParserTest()
		{
			mParser->close();
			delete mParser;
		}
	
	
	protected:
		Parser mParser;
	};
	
	
	
	/* test parser creation */
	TEST_F (ParserTest, CreateParser)
	{
		EXPECT_NO_THROW ({ mParser->load (""); });
	}


	/* test parsing a function declaration */
	TEST_F (ParserTest, ParseFunctions)
	{
		EXPECT_NO_THROW ({ mParser->load ("void test ();"); });
		
	}

}}

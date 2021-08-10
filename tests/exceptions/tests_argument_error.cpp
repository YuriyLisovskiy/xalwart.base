/**
 * tests/exceptions/tests_dict_error.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/exceptions.h"

using namespace xw;


class ArgumentErrorTestCase : public ::testing::Test
{
public:
	const char* WhatErrorMessage = "Test error message from ArgumentErrorTestCase";
	const char* FullErrorMessage = "xw::ArgumentError: Test error message from ArgumentErrorTestCase";
	const char* ErrorFunction = "testFunc";
	const char* ErrorFile = "test_file.cpp";
	const size_t ErrorLine = 1;

	ArgumentError ConstCharConstructorError;
	ArgumentError StringConstructorError;

	explicit ArgumentErrorTestCase()
		: ConstCharConstructorError("Test error message from ArgumentErrorTestCase", this->ErrorLine, this->ErrorFunction, this->ErrorFile),
		  StringConstructorError(std::string("Test error message from ArgumentErrorTestCase"), this->ErrorLine, this->ErrorFunction, this->ErrorFile)
	{
	}
};

TEST_F(ArgumentErrorTestCase, TestWhat)
{
	ASSERT_STREQ(this->ConstCharConstructorError.what(), this->WhatErrorMessage);
	ASSERT_STREQ(this->StringConstructorError.what(), this->WhatErrorMessage);
}

TEST_F(ArgumentErrorTestCase, TestLine)
{
	ASSERT_EQ(this->ConstCharConstructorError.line(), this->ErrorLine);
	ASSERT_EQ(this->StringConstructorError.line(), this->ErrorLine);
}

TEST_F(ArgumentErrorTestCase, TestFunction)
{
	ASSERT_EQ(this->ConstCharConstructorError.function(), this->ErrorFunction);
	ASSERT_EQ(this->StringConstructorError.function(), this->ErrorFunction);
}

TEST_F(ArgumentErrorTestCase, TestFile)
{
	ASSERT_EQ(this->ConstCharConstructorError.file(), this->ErrorFile);
	ASSERT_EQ(this->StringConstructorError.file(), this->ErrorFile);
}

TEST_F(ArgumentErrorTestCase, TestGetMessage)
{
	ASSERT_EQ(this->ConstCharConstructorError.get_message(), this->FullErrorMessage);
	ASSERT_EQ(this->StringConstructorError.get_message(), this->FullErrorMessage);
}

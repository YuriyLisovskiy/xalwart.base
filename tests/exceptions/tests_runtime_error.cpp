/**
 * tests/exceptions/tests_runtime_error.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/exceptions.h"

using namespace xw;


class RuntimeErrorTestCase : public ::testing::Test
{
public:
	const char* WhatErrorMessage = "Test error message from RuntimeErrorTestCase";
	const char* FullErrorMessage = "RuntimeError: Test error message from RuntimeErrorTestCase";
	const char* ErrorFunction = "testFunc";
	const char* ErrorFile = "test_file.cpp";
	const size_t ErrorLine = 1;

	RuntimeError ConstCharConstructorError;
	RuntimeError StringConstructorError;

	explicit RuntimeErrorTestCase()
		: ConstCharConstructorError("Test error message from RuntimeErrorTestCase", this->ErrorLine, this->ErrorFunction, this->ErrorFile),
		  StringConstructorError(std::string("Test error message from RuntimeErrorTestCase"), this->ErrorLine, this->ErrorFunction, this->ErrorFile)
	{
	}
};

TEST_F(RuntimeErrorTestCase, TestWhat)
{
	ASSERT_STREQ(this->ConstCharConstructorError.what(), this->WhatErrorMessage);
	ASSERT_STREQ(this->StringConstructorError.what(), this->WhatErrorMessage);
}

TEST_F(RuntimeErrorTestCase, TestLine)
{
	ASSERT_EQ(this->ConstCharConstructorError.line(), this->ErrorLine);
	ASSERT_EQ(this->StringConstructorError.line(), this->ErrorLine);
}

TEST_F(RuntimeErrorTestCase, TestFunction)
{
	ASSERT_EQ(this->ConstCharConstructorError.function(), this->ErrorFunction);
	ASSERT_EQ(this->StringConstructorError.function(), this->ErrorFunction);
}

TEST_F(RuntimeErrorTestCase, TestFile)
{
	ASSERT_EQ(this->ConstCharConstructorError.file(), this->ErrorFile);
	ASSERT_EQ(this->StringConstructorError.file(), this->ErrorFile);
}

TEST_F(RuntimeErrorTestCase, TestGetMessage)
{
	ASSERT_EQ(this->ConstCharConstructorError.get_message(), this->FullErrorMessage);
	ASSERT_EQ(this->StringConstructorError.get_message(), this->FullErrorMessage);
}

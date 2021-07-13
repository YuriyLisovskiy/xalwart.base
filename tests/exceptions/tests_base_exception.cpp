/**
 * tests/exceptions/tests_base_exception.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/exceptions.h"

using namespace xw;


class BaseExceptionTestCase : public ::testing::Test
{
public:
	const char* WhatErrorMessage = "Test error message from BaseExceptionTestCase";
	const char* FullErrorMessage = "BaseException: Test error message from BaseExceptionTestCase";
	const char* ErrorFunction = "testFunc";
	const char* ErrorFile = "test_file.cpp";
	const size_t ErrorLine = 1;

	BaseException ConstCharConstructorError;

	explicit BaseExceptionTestCase()
		: ConstCharConstructorError("Test error message from BaseExceptionTestCase", this->ErrorLine, this->ErrorFunction, this->ErrorFile)
	{
	}
};

TEST_F(BaseExceptionTestCase, TestWhat)
{
	ASSERT_STREQ(this->ConstCharConstructorError.what(), this->WhatErrorMessage);
}

TEST_F(BaseExceptionTestCase, TestLine)
{
	ASSERT_EQ(this->ConstCharConstructorError.line(), this->ErrorLine);
}

TEST_F(BaseExceptionTestCase, TestFunction)
{
	ASSERT_EQ(this->ConstCharConstructorError.function(), this->ErrorFunction);
}

TEST_F(BaseExceptionTestCase, TestFile)
{
	ASSERT_EQ(this->ConstCharConstructorError.file(), this->ErrorFile);
}

TEST_F(BaseExceptionTestCase, TestGetMessage)
{
	ASSERT_EQ(this->ConstCharConstructorError.get_message(), this->FullErrorMessage);
}

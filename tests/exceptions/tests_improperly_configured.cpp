/**
 * tests/exceptions/tests_improperly_configured.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/exceptions.h"

using namespace xw;


class ImproperlyConfiguredTestCase : public ::testing::Test
{
public:
	const char* WhatErrorMessage = "Test error message from ImproperlyConfiguredTestCase";
	const char* FullErrorMessage = "xw::ImproperlyConfigured: Test error message from ImproperlyConfiguredTestCase";
	const char* ErrorFunction = "testFunc";
	const char* ErrorFile = "test_file.cpp";
	const size_t ErrorLine = 1;

	ImproperlyConfigured ConstCharConstructorError;
	ImproperlyConfigured StringConstructorError;

	explicit ImproperlyConfiguredTestCase()
		: ConstCharConstructorError("Test error message from ImproperlyConfiguredTestCase", this->ErrorLine, this->ErrorFunction, this->ErrorFile),
		  StringConstructorError(std::string("Test error message from ImproperlyConfiguredTestCase"), this->ErrorLine, this->ErrorFunction, this->ErrorFile)
	{
	}
};

TEST_F(ImproperlyConfiguredTestCase, TestWhat)
{
	ASSERT_STREQ(this->ConstCharConstructorError.what(), this->WhatErrorMessage);
	ASSERT_STREQ(this->StringConstructorError.what(), this->WhatErrorMessage);
}

TEST_F(ImproperlyConfiguredTestCase, TestLine)
{
	ASSERT_EQ(this->ConstCharConstructorError.line(), this->ErrorLine);
	ASSERT_EQ(this->StringConstructorError.line(), this->ErrorLine);
}

TEST_F(ImproperlyConfiguredTestCase, TestFunction)
{
	ASSERT_EQ(this->ConstCharConstructorError.function(), this->ErrorFunction);
	ASSERT_EQ(this->StringConstructorError.function(), this->ErrorFunction);
}

TEST_F(ImproperlyConfiguredTestCase, TestFile)
{
	ASSERT_EQ(this->ConstCharConstructorError.file(), this->ErrorFile);
	ASSERT_EQ(this->StringConstructorError.file(), this->ErrorFile);
}

TEST_F(ImproperlyConfiguredTestCase, TestGetMessage)
{
	ASSERT_EQ(this->ConstCharConstructorError.get_message(), this->FullErrorMessage);
	ASSERT_EQ(this->StringConstructorError.get_message(), this->FullErrorMessage);
}

/**
 * tests_error.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/error.h"


TEST(TestCase_Error, ConstructError)
{
	using xw::core::error_type;
	auto err = xw::core::Error(error_type::HttpError, "an error", 1, "main", "main.cpp");
	ASSERT_TRUE(err);
	ASSERT_EQ(err.type, error_type::HttpError);
	ASSERT_EQ(err.msg, "an error");
	ASSERT_EQ(err.line, 1);
	ASSERT_EQ(err.func, "main");
	ASSERT_EQ(err.file, "main.cpp");
}

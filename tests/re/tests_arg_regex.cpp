/**
 * re/tests_arg_regex.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/re/arg_regex.h"

using namespace xw;


TEST(TestCase_ArgRegex, TestDoubleSquareBracketsInPattern)
{
	auto expr = re::ArgRegex(R"(<<hello>>([\w\s]+))");
	ASSERT_TRUE(expr.match("<<hello>>Double square brackets check"));
	ASSERT_FALSE(expr.match("Double square brackets check"));
	ASSERT_EQ(expr.groups().size(), 0);
}

TEST(TestCase_ArgRegex, TestSingleSquareBracketsInPattern)
{
	auto expr = re::ArgRegex(R"(\w{2}\s{5}<hello>([\w\s]+))");
	ASSERT_FALSE(expr.match("<<hello>>Double square brackets check"));
	ASSERT_TRUE(expr.search("SS     Double square brackets check"));
	ASSERT_EQ(expr.groups().size(), 1);
	ASSERT_EQ(expr.group("hello"), "Double square brackets check");
}

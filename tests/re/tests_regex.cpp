/**
 * re/tests_regex.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/re/regex.h"

using namespace xw;


TEST(TestCase_Regex, TestETagPattern)
{
	auto expr = re::Regex(R"(((?:W\/)?"[^"]*"))");

	ASSERT_TRUE(expr.search(R"("bfc13a64729c4290ef5b2c2730249c88ca92d82d")"));
	ASSERT_EQ(expr.groups().size(), 2);

	ASSERT_TRUE(expr.search(R"(W/"0815")"));
	ASSERT_EQ(expr.groups().size(), 2);
}

TEST(TestCase_Regex, TestEscape)
{
	auto expr = R"(\{%)";
	ASSERT_EQ(re::escape(R"({%)"), expr);

	expr = R"(%\})";
	ASSERT_EQ(re::escape(R"(%})"), expr);

	expr = R"(\{\{)";
	ASSERT_EQ(re::escape(R"({{)"), expr);

	expr = R"(\}\})";
	ASSERT_EQ(re::escape(R"(}})"), expr);

	expr = R"(\{#)";
	ASSERT_EQ(re::escape(R"({#)"), expr);

	expr = R"(#\})";
	ASSERT_EQ(re::escape(R"(#})"), expr);
}

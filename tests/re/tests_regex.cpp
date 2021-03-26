/**
 * re/tests_regex.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/re/regex.h"

using namespace xw;


class TestCase_Regex : public ::testing::Test
{
protected:
	re::Regex regex;

	void SetUp() override
	{
		this->regex = re::Regex(R"((?:W\/)?"[^"]*")");
	}
};

TEST_F(TestCase_Regex, match)
{
	ASSERT_TRUE(this->regex.match(R"("bfc13a64729c4290ef5b2c2730249c88ca92d82d")"));
}

TEST_F(TestCase_Regex, search)
{
	ASSERT_TRUE(this->regex.search(R"(W/"0815")"));
	ASSERT_EQ(this->regex.groups().size(), 1);
}

TEST_F(TestCase_Regex, groups)
{
	ASSERT_TRUE(this->regex.search(R"(W/"0815"W/"0821")"));
	auto groups = this->regex.groups();
	ASSERT_EQ(groups.size(), 2);
	ASSERT_EQ(groups[0], R"(W/"0815")");
	ASSERT_EQ(groups[1], R"(W/"0821")");
}

TEST_F(TestCase_Regex, group_Existent)
{
	ASSERT_TRUE(this->regex.search(R"(W/"0815")"));
	ASSERT_EQ(this->regex.group(0), R"(W/"0815")");
}

TEST_F(TestCase_Regex, group_NonExistent)
{
	ASSERT_TRUE(this->regex.search(R"(W/"0815")"));
	ASSERT_EQ(this->regex.group(1), "");
}

TEST_F(TestCase_Regex, str)
{
	ASSERT_EQ(this->regex.str(), R"((?:W\/)?"[^"]*")");
}

TEST(TestCase_escape, left_squared_bracket)
{
	auto expr = R"(\[)";
	ASSERT_EQ(re::escape(R"([)"), expr);
}

TEST(TestCase_escape, backslash)
{
	auto expr = R"(\\)";
	ASSERT_EQ(re::escape(R"(\)"), expr);
}

TEST(TestCase_escape, xor_)
{
	auto expr = R"(\^)";
	ASSERT_EQ(re::escape(R"(^)"), expr);
}

TEST(TestCase_escape, dollar)
{
	auto expr = R"(\$)";
	ASSERT_EQ(re::escape(R"($)"), expr);
}

TEST(TestCase_escape, dot)
{
	auto expr = R"(\.)";
	ASSERT_EQ(re::escape(R"(.)"), expr);
}

TEST(TestCase_escape, pipe)
{
	auto expr = R"(\|)";
	ASSERT_EQ(re::escape(R"(|)"), expr);
}

TEST(TestCase_escape, question_mark)
{
	auto expr = R"(\?)";
	ASSERT_EQ(re::escape(R"(?)"), expr);
}

TEST(TestCase_escape, star)
{
	auto expr = R"(\*)";
	ASSERT_EQ(re::escape(R"(*)"), expr);
}

TEST(TestCase_escape, plus)
{
	auto expr = R"(\+)";
	ASSERT_EQ(re::escape(R"(+)"), expr);
}

TEST(TestCase_escape, left_bracket)
{
	auto expr = R"(\()";
	ASSERT_EQ(re::escape(R"(()"), expr);
}

TEST(TestCase_escape, right_bracket)
{
	auto expr = R"(\))";
	ASSERT_EQ(re::escape(R"())"), expr);
}

TEST(TestCase_escape, left_brace)
{
	auto expr = R"(\{)";
	ASSERT_EQ(re::escape(R"({)"), expr);
}

TEST(TestCase_escape, right_brace)
{
	auto expr = R"(\})";
	ASSERT_EQ(re::escape(R"(})"), expr);
}

TEST(TestCase_escape, left_brace_with_no)
{
	auto expr = R"(\{#)";
	ASSERT_EQ(re::escape(R"({#)"), expr);
}

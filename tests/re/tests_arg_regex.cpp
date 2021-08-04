/**
 * re/tests_arg_regex.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/re/arg_regex.h"

using namespace xw;


class TestCase_ArgRegex : public ::testing::Test
{
protected:
	re::ArgRegex regex;

	void SetUp() override
	{
		this->regex = re::ArgRegex(R"(accounts/<id>(\d+)/picture/<name>(\w+\.jpeg))");
	}
};

TEST_F(TestCase_ArgRegex, match_True)
{
	ASSERT_TRUE(this->regex.match("accounts/1/picture/flower.jpeg"));
}

TEST_F(TestCase_ArgRegex, match_False)
{
	ASSERT_FALSE(this->regex.match("accounts/-1/picture/flower.jpeg"));
}

TEST_F(TestCase_ArgRegex, search_True)
{
	ASSERT_TRUE(this->regex.search("accounts/1/picture/flower.jpeg"));
}

TEST_F(TestCase_ArgRegex, search_False)
{
	ASSERT_FALSE(this->regex.search("accounts/-1/picture/flower.jpeg"));
}

TEST_F(TestCase_ArgRegex, args_Found)
{
	this->regex.search("accounts/1/picture/flower.jpeg");
	ASSERT_EQ(this->regex.args().size(), 2);
}

TEST_F(TestCase_ArgRegex, args_NotFound)
{
	this->regex.search("accounts/-1/picture/flower.jpeg");
	ASSERT_EQ(this->regex.args().size(), 0);
}

TEST_F(TestCase_ArgRegex, arg_Existent)
{
	this->regex.search("accounts/1/picture/flower.jpeg");
	ASSERT_EQ(this->regex.arg("id"), "1");
	ASSERT_EQ(this->regex.arg("name"), "flower.jpeg");
}

TEST_F(TestCase_ArgRegex, tuple_Existent)
{
	this->regex.search("accounts/1/picture/flower.jpeg");
	auto tuple = this->regex.tuple<int, std::string>();
	ASSERT_EQ(std::get<0>(tuple), 1);
	ASSERT_EQ(std::get<1>(tuple), "flower.jpeg");
}

TEST_F(TestCase_ArgRegex, tuple_ThrowsSizeMismatch)
{
	this->regex.search("accounts/1/picture/flower.jpeg");
	ASSERT_THROW(this->regex.tuple<int>(), ArgumentError);
}

TEST_F(TestCase_ArgRegex, arg_NonExistent)
{
	this->regex.search("accounts/1/picture/flower.jpeg");
	ASSERT_EQ(this->regex.arg("age"), "");
}

TEST_F(TestCase_ArgRegex, parts)
{
	auto parts = this->regex.parts();
	ASSERT_EQ(parts.size(), 2);
	ASSERT_EQ(parts[0], "accounts/");
	ASSERT_EQ(parts[1], "/picture/");
}

TEST_F(TestCase_ArgRegex, str)
{
	ASSERT_EQ(
		this->regex.str(), R"(accounts/<id>(\d+)/picture/<name>(\w+\.jpeg))"
	);
}

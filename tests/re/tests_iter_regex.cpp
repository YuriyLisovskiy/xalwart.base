/**
 * re/tests_iter_regex.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/exceptions.h"
#include "../../src/re/iter_regex.h"

using namespace xw;


class TestCase_IterRegex : public ::testing::Test
{
protected:
	re::IterRegex regex;

	void SetUp() override
	{
		this->regex = re::IterRegex(R"([A-Za-z]+)");
	}
};

TEST_F(TestCase_IterRegex, setup_IsInitialized)
{
	this->regex.setup("Some text");
	ASSERT_NO_THROW(this->regex.search_next());
}

TEST_F(TestCase_IterRegex, setup_IsNotInitialized)
{
	ASSERT_THROW(this->regex.search_next(), core::RuntimeError);
}

TEST_F(TestCase_IterRegex, search_next_Found)
{
	this->regex.setup("Some 100 text");
	ASSERT_TRUE(this->regex.search_next());
}

TEST_F(TestCase_IterRegex, search_next_NotFound)
{
	this->regex.setup("1-2992");
	ASSERT_FALSE(this->regex.search_next());
}

TEST_F(TestCase_IterRegex, groups_Found)
{
	this->regex.setup("Some 100 text");
	ASSERT_TRUE(this->regex.search_next());
	auto actual = this->regex.groups();
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ("Some", actual[0]);
	ASSERT_TRUE(this->regex.search_next());
	actual = this->regex.groups();
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ("text", actual[0]);
	ASSERT_FALSE(this->regex.search_next());
}

TEST_F(TestCase_IterRegex, groups_NotFound)
{
	this->regex.setup("43 , 100");
	this->regex.search_next();
	auto actual = this->regex.groups();
	ASSERT_EQ(0, actual.size());
}

TEST_F(TestCase_IterRegex, group_Found)
{
	this->regex.setup("Some 100 text");
	ASSERT_TRUE(this->regex.search_next());
	auto actual = this->regex.group(0);
	ASSERT_EQ("Some", actual);
}

TEST_F(TestCase_IterRegex, group_NotFound)
{
	this->regex.setup("43 , 100");
	this->regex.search_next();
	auto actual = this->regex.group(0);
	ASSERT_EQ("", actual);
}

TEST_F(TestCase_IterRegex, str)
{
	ASSERT_EQ("[A-Za-z]+", this->regex.str());
}

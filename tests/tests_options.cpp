/**
 * tests_options.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <map>

#include <gtest/gtest.h>

#include "../src/options.h"

using namespace xw;


class OptionsTestCase : public ::testing::Test
{
protected:
	Options options;

	void SetUp() override
	{
		this->options = {{
			{"user_id", "12345"},
			{"account_name", "some_name"}
		}};
	}
};

TEST_F(OptionsTestCase, ContainsTest)
{
	ASSERT_FALSE(this->options.contains("user_account_id"));
	ASSERT_TRUE(this->options.contains("account_name"));
}

TEST_F(OptionsTestCase, GetIntTest)
{
	ASSERT_EQ(this->options.get<int>("user_id"), 12345);
}

TEST_F(OptionsTestCase, GetNonIntTest)
{
	ASSERT_EQ(this->options.get<int>("account_name", -1), -1);
}

TEST_F(OptionsTestCase, GetIntTestReturnsDefault)
{
	ASSERT_EQ(this->options.get<int>("user", -1), -1);
}

TEST_F(OptionsTestCase, GetStringTest)
{
	ASSERT_EQ(this->options.get<std::string>("account_name"), "some_name");
	ASSERT_EQ(this->options.get<std::string>("user_id"), "12345");
}

TEST_F(OptionsTestCase, GetStringTestReturnsDefault)
{
	ASSERT_EQ(this->options.get<std::string>("account", "default value"), "default value");
}

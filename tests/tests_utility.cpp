/**
 * tests_utility.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/utility.h"

using namespace xw;


TEST(TestCase_utility, contains_FoundWithIterators)
{
	auto values = {1, 2, 3, 4, 5};
	ASSERT_TRUE(util::contains(4, values.begin(), values.end()));
}

TEST(TestCase_utility, contains_NotFoundWithIterators)
{
	auto values = {1, 2, 3, 4, 5};
	ASSERT_FALSE(util::contains(-6.5, values.begin(), values.end()));
}

TEST(TestCase_utility, contains_FoundWithInitializerList)
{
	ASSERT_TRUE(util::contains(4, {1, 2, 3, 4, 5}));
}

TEST(TestCase_utility, contains_NotFoundWithInitializerList)
{
	auto values = {1, 2, 3, 4, 5};
	ASSERT_FALSE(util::contains(256, values));
}

TEST(TestCase_utility, index_of_Found)
{
	auto values = {'h', 'e', 'l', 'l', 'o'};
	ASSERT_EQ(2, util::index_of('l', values.begin(), values.end()));
}

TEST(TestCase_utility, index_of_NotFound)
{
	auto values = {'h', 'e', 'l', 'l', 'o'};
	ASSERT_EQ(-1, util::index_of('Z', values.begin(), values.end()));
}

TEST(TestCase_utility, demangle_BuiltInType)
{
	std::string expected = "float";
	auto actual = util::demangle(typeid(float).name());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, demangle_CustomType)
{
	struct CustomType
	{
	};
	std::string expected = "TestCase_utility_demangle_CustomType_Test::TestBody()::CustomType";
	auto actual = util::demangle(typeid(CustomType).name());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_datetime_Ordinary)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	auto tz = std::make_shared<dt::Timezone>(
		dt::Timedelta(0, 0, 0 ,0 , 0, 2), "EET"
	);
	dt = dt.as_timezone(tz);
	std::string expected = "Fri, 15 Nov 2019 14:45:26 +0200";
	std::string actual = util::format_datetime(&dt);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_datetime_WithoutTimezone)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	std::string expected = "Fri, 15 Nov 2019 12:45:26 -0000";
	std::string actual = util::format_datetime(&dt);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_datetime_WithGmtTimezone)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	dt = dt.as_timezone(std::make_shared<dt::Timezone>(dt::Timezone::UTC));
	std::string expected = "Fri, 15 Nov 2019 12:45:26 GMT";
	std::string actual = util::format_datetime(&dt, true);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_date)
{
	time_t timestamp = 1617135792;
	std::string expected = "Tue, 30 Mar 2021 20:23:12 -0000";
	auto actual = util::format_date(timestamp);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_date_WithLocalTime)
{
	time_t timestamp = 1617135792;
	std::string expected = "Tue, 30 Mar 2021 20:23:12 +0000";
	auto actual = util::format_date(timestamp, true);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_date_WithGMT)
{
	time_t timestamp = 1617135792;
	std::string expected = "Tue, 30 Mar 2021 20:23:12 GMT";
	auto actual = util::format_date(timestamp, false, true);
	ASSERT_EQ(expected, actual);
}

/**
 * tests_utility.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "./benchmark.h"
#include "../src/utility.h"

using namespace xw;

TEST(TestCase_utility, format_datetime)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	dt = dt.as_timezone(std::make_shared<dt::Timezone>(
		dt::Timedelta(0, 0, 0 ,0 , 0, 2), "EET"
	));
	std::string expected = "Fri, 15 Nov 2019 14:45:26 +0200";
	std::string actual = utility::format_datetime(&dt);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_datetime_NoTimezone)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	std::string expected = "Fri, 15 Nov 2019 12:45:26 -0000";
	std::string actual = utility::format_datetime(&dt);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_utility, format_datetime_UseGmt)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	dt = dt.as_timezone(std::make_shared<dt::Timezone>(dt::Timezone::UTC));
	std::string expected = "Fri, 15 Nov 2019 12:45:26 GMT";
	std::string actual = utility::format_datetime(&dt, true);
	ASSERT_EQ(expected, actual);
}

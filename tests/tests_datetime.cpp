/**
 * tests_datetime.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/datetime.h"

using namespace xw;


TEST(Datetime_TestCase, _M_Assert_NotAborts)
{
	ASSERT_NO_THROW(dt::internal::_M_Assert("", true, "", 0, ""));
}

TEST(Datetime_TestCase, _mod)
{
	ASSERT_EQ(dt::internal::_mod(-1, 2), 1);
	ASSERT_EQ(dt::internal::_mod(2, -1), 0);
	ASSERT_EQ(dt::internal::_mod(-1, -2), -1);
	ASSERT_EQ(dt::internal::_mod(1, -2), -1);
	ASSERT_EQ(dt::internal::_mod(5, 3), 2);
	ASSERT_EQ(dt::internal::_mod(3, 5), 3);
}

TEST(Datetime_TestCase, _true_div)
{
	auto actual = dt::internal::_true_div(3, 2);
	ASSERT_EQ(actual, 1);

	actual = dt::internal::_true_div(5, 2);
	ASSERT_EQ(actual, 2);

	actual = dt::internal::_true_div(-5, 2);
	ASSERT_EQ(actual, -3);
}

TEST(Datetime_TestCase, _div_mod)
{
	auto actual = dt::internal::_div_mod(1, 1);
	ASSERT_EQ(actual.first, 1);
	ASSERT_EQ(actual.second, 0);

	actual = dt::internal::_div_mod(-2, 1);
	ASSERT_EQ(actual.first, -2);
	ASSERT_EQ(actual.second, 0);

	actual = dt::internal::_div_mod(-2, 1);
	ASSERT_EQ(actual.first, -2);
	ASSERT_EQ(actual.second, 0);

	actual = dt::internal::_div_mod(-1, 1);
	ASSERT_EQ(actual.first, -1);
	ASSERT_EQ(actual.second, 0);

	actual = dt::internal::_div_mod(1764, 789);
	ASSERT_EQ(actual.first, 2);
	ASSERT_EQ(actual.second, 186);

	actual = dt::internal::_div_mod(-1764, 789);
	ASSERT_EQ(actual.first, -3);
	ASSERT_EQ(actual.second, 603);

	actual = dt::internal::_div_mod(1764, -789);
	ASSERT_EQ(actual.first, -3);
	ASSERT_EQ(actual.second, -603);

	actual = dt::internal::_div_mod(-1764, -789);
	ASSERT_EQ(actual.first, 2);
	ASSERT_EQ(actual.second, -186);
}

TEST(Datetime_TestCase, _cmp)
{
	ASSERT_EQ(dt::internal::_cmp(1, 1), 0);
	ASSERT_EQ(dt::internal::_cmp(-1, 1), -1);
	ASSERT_EQ(dt::internal::_cmp(1, -1), 1);

	ASSERT_EQ(dt::internal::_cmp(1.0, 1.0), 0);
	ASSERT_EQ(dt::internal::_cmp(-1.0, 1.0), -1);
	ASSERT_EQ(dt::internal::_cmp(1.0, -1.0), 1);

	ASSERT_EQ(dt::internal::_cmp(std::string("hello"), std::string("hello")), 0);
	ASSERT_EQ(dt::internal::_cmp(std::string("aello"), std::string("hello")), -1);
	ASSERT_EQ(dt::internal::_cmp(std::string("hello"), std::string("aello")), 1);
}

TEST(Datetime_TestCase, _cmp_arr)
{
	int a[4] = {1, 3, 2, 4};
	int b[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::internal::_cmp_arr(a, b, 4), -1);

	int c[4] = {1, 7, 2, 4};
	int d[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::internal::_cmp_arr(c, d, 4), 1);

	int e[4] = {1, 7, 1, -5};
	int f[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::internal::_cmp_arr(e, f, 4), 0);
}

TEST(Datetime_TestCase, _is_leap)
{
	ASSERT_TRUE(dt::internal::_is_leap(2020));
	ASSERT_TRUE(dt::internal::_is_leap(1940));
	ASSERT_FALSE(dt::internal::_is_leap(2010));
	ASSERT_TRUE(dt::internal::_is_leap(1980));
	ASSERT_FALSE(dt::internal::_is_leap(1986));
	ASSERT_FALSE(dt::internal::_is_leap(1990));
	ASSERT_TRUE(dt::internal::_is_leap(1988));
	ASSERT_TRUE(dt::internal::_is_leap(16));
}

TEST(Datetime_TestCase, _days_before_year)
{
	ASSERT_EQ(dt::internal::_days_before_year(2000), 730119);
	ASSERT_EQ(dt::internal::_days_before_year(1656), 604476);
	ASSERT_EQ(dt::internal::_days_before_year(1799), 656706);
	ASSERT_EQ(dt::internal::_days_before_year(2020), 737424);
	ASSERT_EQ(dt::internal::_days_before_year(2077), 758244);
}

TEST(Datetime_TestCase, _days_in_month)
{
	ASSERT_EQ(dt::internal::_days_in_month(2000, 1), 31);
	ASSERT_EQ(dt::internal::_days_in_month(1656, 2), 29);
	ASSERT_EQ(dt::internal::_days_in_month(1658, 2), 28);
	ASSERT_EQ(dt::internal::_days_in_month(1799, 3), 31);
	ASSERT_EQ(dt::internal::_days_in_month(2020, 4), 30);
	ASSERT_EQ(dt::internal::_days_in_month(2077, 2), 28);
}

TEST(Datetime_TestCase, _days_before_month)
{
	ASSERT_EQ(dt::internal::_days_before_month(2000, 1), 0);
	ASSERT_EQ(dt::internal::_days_before_month(1656, 2), 31);
	ASSERT_EQ(dt::internal::_days_before_month(1658, 5), 120);
	ASSERT_EQ(dt::internal::_days_before_month(1799, 3), 59);
	ASSERT_EQ(dt::internal::_days_before_month(2020, 4), 91);
	ASSERT_EQ(dt::internal::_days_before_month(2077, 12), 334);
}

TEST(Datetime_TestCase, _ymd2ord)
{
	ASSERT_EQ(dt::internal::_ymd2ord(1970, 10, 11), 719446);
	ASSERT_EQ(dt::internal::_ymd2ord(2020, 10, 11), 737709);
	ASSERT_EQ(dt::internal::_ymd2ord(1970, 7, 1), 719344);
	ASSERT_EQ(dt::internal::_ymd2ord(1737, 7, 1), 634243);
	ASSERT_EQ(dt::internal::_ymd2ord(2077, 3, 16), 758319);
}

TEST(Datetime_TestCase, _DInY)
{
	ASSERT_EQ(dt::internal::_DI400Y, 146097);
	ASSERT_EQ(dt::internal::_DI100Y, 36524);
	ASSERT_EQ(dt::internal::_DI4Y, 1461);
}

TEST(Datetime_TestCase, _ord2ymd)
{
	auto expected = dt::internal::ymd{2221, 11, 9};
	auto actual = dt::internal::_ord2ymd(811151);
	ASSERT_EQ(expected.year, actual.year);
	ASSERT_EQ(expected.month, actual.month);
	ASSERT_EQ(expected.day, actual.day);

	expected = dt::internal::ymd{1948, 1, 25};
	actual = dt::internal::_ord2ymd(711151);
	ASSERT_EQ(expected.year, actual.year);
	ASSERT_EQ(expected.month, actual.month);
	ASSERT_EQ(expected.day, actual.day);
}

TEST(Datetime_TestCase, tm_tuple_Gmtime)
{
	time_t time = 1573821926;
	auto tm_ptr = std::gmtime(&time);
	dt::tm_tuple tt(tm_ptr);
	ASSERT_EQ(tt.tm_year, 2019);
	ASSERT_EQ(tt.tm_mon, 11);
	ASSERT_EQ(tt.tm_mday, 15);
	ASSERT_EQ(tt.tm_hour, 12);
	ASSERT_EQ(tt.tm_min, 45);
	ASSERT_EQ(tt.tm_sec, 26);
	ASSERT_EQ(tt.tm_wday, 4);
	ASSERT_EQ(tt.tm_yday, 319);
	ASSERT_EQ(tt.tm_isdst, 0);

	auto tm_struct = tt.as_tm();
	ASSERT_EQ(tm_struct.tm_year, 119);
	ASSERT_EQ(tm_struct.tm_mon, 10);
	ASSERT_EQ(tm_struct.tm_mday, 15);
	ASSERT_EQ(tm_struct.tm_hour, 12);
	ASSERT_EQ(tm_struct.tm_min, 45);
	ASSERT_EQ(tm_struct.tm_sec, 26);
	ASSERT_EQ(tm_struct.tm_wday, 5);
	ASSERT_EQ(tm_struct.tm_yday, 318);
	ASSERT_EQ(tm_struct.tm_isdst, 0);
}



TEST(DatetimeTestCase, StrftimeTest)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	dt = dt.as_timezone(std::make_shared<dt::Timezone>(
		dt::Timedelta(0, 0, 0 ,0 , 0, 2), "EET"
	));
	std::string expected = "Fri, 15 Nov 2019 14:45:26 EET";
	auto strf_time = dt.strftime("%a, %e %b %Y %T %Z");
	ASSERT_EQ(expected, strf_time);
}

TEST(DatetimeTestCase, TimestampTest)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26 GMT";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T %Z");
	double expected = 1573821926.0;
	double actual = dt.timestamp();
	ASSERT_EQ(expected, actual);

	str_dt = "Fri, 15 Nov 2019 12:45:26 EET";
	dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T %Z");
	ASSERT_EQ(expected, dt.timestamp());

	str_dt = "Fri, 15 Nov 2019 12:45:26 Y";
	dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T %Z");
	ASSERT_EQ(expected, dt.timestamp());

	str_dt = "Fri, 15 Nov 2019 12:45:26 AFT";
	dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T %Z");
	ASSERT_EQ(expected, dt.timestamp());

	str_dt = "Fri, 15 Nov 2019 12:45:26 IRST";
	dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T %Z");
	ASSERT_EQ(expected, dt.timestamp());
}

TEST(ModuleTestCase, TestContacts)
{
	ASSERT_EQ(dt::MIN_YEAR, 1);
	ASSERT_EQ(dt::MAX_YEAR, 9999);
}

TEST(ModuleTestCase, TestDivideAndRound)
{
	ASSERT_EQ(dt::internal::_divide_and_round(-10, -3), 3);
	ASSERT_EQ(dt::internal::_divide_and_round(5, -2), -2);

	// four cases: (2 signs of a) x (2 signs of b)
	ASSERT_EQ(dt::internal::_divide_and_round(7, 3), 2);
	ASSERT_EQ(dt::internal::_divide_and_round(-7, 3), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(7, -3), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(-7, -3), 2);

	// ties to even - eight cases:
	// (2 signs of a) x (2 signs of b) x (even / odd quotient)
	ASSERT_EQ(dt::internal::_divide_and_round(10, 4), 2);
	ASSERT_EQ(dt::internal::_divide_and_round(-10, 4), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(10, -4), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(-10, -4), 2);

	ASSERT_EQ(dt::internal::_divide_and_round(6, 4), 2);
	ASSERT_EQ(dt::internal::_divide_and_round(-6, 4), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(6, -4), -2);
	ASSERT_EQ(dt::internal::_divide_and_round(-6, -4), 2);
}

class FixedOffset : public dt::Timezone
{
private:
	dt::Timedelta _dst_offset;

public:
	FixedOffset(
		int offset, const std::string& name, int dst_offset = 42
	) : Timezone(dt::Timedelta(0, 0, 0, 0, offset), name)
	{
		this->_dst_offset = dt::Timedelta(0, 0, 0, 0, dst_offset);
	}

	std::shared_ptr<dt::Timedelta> dst(const dt::Datetime* dt) const override
	{
		return std::make_shared<dt::Timedelta>(this->_dst_offset);
	}
};

TEST(TimezoneTestCase, NormalTest)
{
	auto fo = FixedOffset(3, "Three");

	auto now = dt::Datetime::now();
	ASSERT_EQ(*fo.utc_offset(&now), dt::Timedelta(0, 0, 0, 0, 3));
	ASSERT_EQ(fo.tz_name(&now), std::string("Three"));
	ASSERT_EQ(*fo.dst(&now), dt::Timedelta(0, 0, 0, 0, 42));

	ASSERT_EQ(*fo.utc_offset(nullptr), dt::Timedelta(0, 0, 0, 0, 3));
	ASSERT_EQ(fo.tz_name(nullptr), std::string("Three"));
	ASSERT_EQ(*fo.dst(nullptr), dt::Timedelta(0, 0, 0, 0, 42));
}

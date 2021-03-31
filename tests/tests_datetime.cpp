/**
 * tests_datetime.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/datetime.h"

using namespace xw;


TEST(TestCase_dt, _M_Assert_NotAborts)
{
	ASSERT_NO_THROW(dt::_M_Assert("", true, "", 0, ""));
}

TEST(TestCase_dt, _mod)
{
	ASSERT_EQ(dt::_mod(-1, 2), 1);
	ASSERT_EQ(dt::_mod(2, -1), 0);
	ASSERT_EQ(dt::_mod(-1, -2), -1);
	ASSERT_EQ(dt::_mod(1, -2), -1);
	ASSERT_EQ(dt::_mod(5, 3), 2);
	ASSERT_EQ(dt::_mod(3, 5), 3);
}

TEST(TestCase_dt, _true_div)
{
	auto actual = dt::_true_div(3, 2);
	ASSERT_EQ(actual, 1);

	actual = dt::_true_div(5, 2);
	ASSERT_EQ(actual, 2);

	actual = dt::_true_div(-5, 2);
	ASSERT_EQ(actual, -3);
}

TEST(TestCase_dt, _div_mod)
{
	auto actual = dt::_div_mod(1, 1);
	ASSERT_EQ(actual.first, 1);
	ASSERT_EQ(actual.second, 0);

	actual = dt::_div_mod(-2, 1);
	ASSERT_EQ(actual.first, -2);
	ASSERT_EQ(actual.second, 0);

	actual = dt::_div_mod(-2, 1);
	ASSERT_EQ(actual.first, -2);
	ASSERT_EQ(actual.second, 0);

	actual = dt::_div_mod(-1, 1);
	ASSERT_EQ(actual.first, -1);
	ASSERT_EQ(actual.second, 0);

	actual = dt::_div_mod(1764, 789);
	ASSERT_EQ(actual.first, 2);
	ASSERT_EQ(actual.second, 186);

	actual = dt::_div_mod(-1764, 789);
	ASSERT_EQ(actual.first, -3);
	ASSERT_EQ(actual.second, 603);

	actual = dt::_div_mod(1764, -789);
	ASSERT_EQ(actual.first, -3);
	ASSERT_EQ(actual.second, -603);

	actual = dt::_div_mod(-1764, -789);
	ASSERT_EQ(actual.first, 2);
	ASSERT_EQ(actual.second, -186);
}

TEST(TestCase_dt, _cmp_val)
{
	ASSERT_EQ(dt::_cmp_val(1, 1), 0);
	ASSERT_EQ(dt::_cmp_val(-1, 1), -1);
	ASSERT_EQ(dt::_cmp_val(1, -1), 1);

	ASSERT_EQ(dt::_cmp_val(1.0, 1.0), 0);
	ASSERT_EQ(dt::_cmp_val(-1.0, 1.0), -1);
	ASSERT_EQ(dt::_cmp_val(1.0, -1.0), 1);

	ASSERT_EQ(dt::_cmp_val(std::string("hello"), std::string("hello")), 0);
	ASSERT_EQ(dt::_cmp_val(std::string("aello"), std::string("hello")), -1);
	ASSERT_EQ(dt::_cmp_val(std::string("hello"), std::string("aello")), 1);
}

TEST(TestCase_dt, _cmp_arr)
{
	int a[4] = {1, 3, 2, 4};
	int b[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::_cmp_arr(a, b, 4), -1);

	int c[4] = {1, 7, 2, 4};
	int d[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::_cmp_arr(c, d, 4), 1);

	int e[4] = {1, 7, 1, -5};
	int f[4] = {1, 7, 1, -5};
	ASSERT_EQ(dt::_cmp_arr(e, f, 4), 0);
}

TEST(TestCase_dt, _is_leap)
{
	ASSERT_TRUE(dt::_is_leap(2020));
	ASSERT_TRUE(dt::_is_leap(1940));
	ASSERT_FALSE(dt::_is_leap(2010));
	ASSERT_TRUE(dt::_is_leap(1980));
	ASSERT_FALSE(dt::_is_leap(1986));
	ASSERT_FALSE(dt::_is_leap(1990));
	ASSERT_TRUE(dt::_is_leap(1988));
	ASSERT_TRUE(dt::_is_leap(16));
}

TEST(TestCase_dt, _days_before_year)
{
	ASSERT_EQ(dt::_days_before_year(2000), 730119);
	ASSERT_EQ(dt::_days_before_year(1656), 604476);
	ASSERT_EQ(dt::_days_before_year(1799), 656706);
	ASSERT_EQ(dt::_days_before_year(2020), 737424);
	ASSERT_EQ(dt::_days_before_year(2077), 758244);
}

TEST(TestCase_dt, _days_in_month)
{
	ASSERT_EQ(dt::_days_in_month(2000, 1), 31);
	ASSERT_EQ(dt::_days_in_month(1656, 2), 29);
	ASSERT_EQ(dt::_days_in_month(1658, 2), 28);
	ASSERT_EQ(dt::_days_in_month(1799, 3), 31);
	ASSERT_EQ(dt::_days_in_month(2020, 4), 30);
	ASSERT_EQ(dt::_days_in_month(2077, 2), 28);
}

TEST(TestCase_dt, _days_before_month)
{
	ASSERT_EQ(dt::_days_before_month(2000, 1), 0);
	ASSERT_EQ(dt::_days_before_month(1656, 2), 31);
	ASSERT_EQ(dt::_days_before_month(1658, 5), 120);
	ASSERT_EQ(dt::_days_before_month(1799, 3), 59);
	ASSERT_EQ(dt::_days_before_month(2020, 4), 91);
	ASSERT_EQ(dt::_days_before_month(2077, 12), 334);
}

TEST(TestCase_dt, _ymd2ord)
{
	ASSERT_EQ(dt::_ymd2ord(1970, 10, 11), 719446);
	ASSERT_EQ(dt::_ymd2ord(2020, 10, 11), 737709);
	ASSERT_EQ(dt::_ymd2ord(1970, 7, 1), 719344);
	ASSERT_EQ(dt::_ymd2ord(1737, 7, 1), 634243);
	ASSERT_EQ(dt::_ymd2ord(2077, 3, 16), 758319);
}

TEST(TestCase_dt, _DInY)
{
	ASSERT_EQ(dt::_DI400Y, 146097);
	ASSERT_EQ(dt::_DI100Y, 36524);
	ASSERT_EQ(dt::_DI4Y, 1461);
}

TEST(TestCase_dt, _ord2ymd)
{
	auto expected = dt::ymd{2221, 11, 9};
	auto actual = dt::_ord2ymd(811151);
	ASSERT_EQ(expected.year, actual.year);
	ASSERT_EQ(expected.month, actual.month);
	ASSERT_EQ(expected.day, actual.day);

	expected = dt::ymd{1948, 1, 25};
	actual = dt::_ord2ymd(711151);
	ASSERT_EQ(expected.year, actual.year);
	ASSERT_EQ(expected.month, actual.month);
	ASSERT_EQ(expected.day, actual.day);
}

TEST(TestCase_dt, tm_tuple_Gmtime)
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

TEST(TestCase_datetime, strftime)
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

TEST(TestCase_datetime, strptime_WithTimestamp)
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

TEST(TestCase_dt, public_constants)
{
	ASSERT_EQ(dt::MIN_YEAR, 1);
	ASSERT_EQ(dt::MAX_YEAR, 9999);
}

TEST(TestCase_dt, _divide_and_round)
{
	ASSERT_EQ(dt::_divide_and_round(-10, -3), 3);
	ASSERT_EQ(dt::_divide_and_round(5, -2), -2);

	// four cases: (2 signs of a) x (2 signs of b)
	ASSERT_EQ(dt::_divide_and_round(7, 3), 2);
	ASSERT_EQ(dt::_divide_and_round(-7, 3), -2);
	ASSERT_EQ(dt::_divide_and_round(7, -3), -2);
	ASSERT_EQ(dt::_divide_and_round(-7, -3), 2);

	// ties to even - eight cases:
	// (2 signs of a) x (2 signs of b) x (even / odd quotient)
	ASSERT_EQ(dt::_divide_and_round(10, 4), 2);
	ASSERT_EQ(dt::_divide_and_round(-10, 4), -2);
	ASSERT_EQ(dt::_divide_and_round(10, -4), -2);
	ASSERT_EQ(dt::_divide_and_round(-10, -4), 2);

	ASSERT_EQ(dt::_divide_and_round(6, 4), 2);
	ASSERT_EQ(dt::_divide_and_round(-6, 4), -2);
	ASSERT_EQ(dt::_divide_and_round(6, -4), -2);
	ASSERT_EQ(dt::_divide_and_round(-6, -4), 2);
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

TEST(TestCase_timezone, test)
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

/**
 * tests_utility.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include <utility>

#include "./benchmark.h"
#include "../src/utility.h"

using namespace xw::core;


TEST(UtilityTestCase, StringToBytesAndViseVersa)
{
	std::string expected("hello, world!");
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<std::string>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UTF8StringToBytesAndViseVersa)
{
	xw::string expected("hello, world!");
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<xw::string>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, ShortInt_ToBytesAndViseVersa)
{
	short int expected = -5;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<short int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UnsignedShortInt_ToBytesAndViseVersa)
{
	unsigned short int expected = 5;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<unsigned short int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UnsignedInt_ToBytesAndViseVersa)
{
	unsigned int expected = 234567;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<unsigned int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, Int_ToBytesAndViseVersa)
{
	int expected = -754567;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, LongInt_ToBytesAndViseVersa)
{
	long int expected = -7654356789;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<long int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UnsignedLongInt_ToBytesAndViseVersa)
{
	unsigned long int expected = 6543456789;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<unsigned long int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, LongLongInt_ToBytesAndViseVersa)
{
	long long int expected = -98765432345678;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<long long int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UnsignedLongLongInt_ToBytesAndViseVersa)
{
	unsigned long long int expected = 765434567890;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<unsigned long long int>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, SignedChar_ToBytesAndViseVersa)
{
	signed char expected = 'z';
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<signed char>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, UnsignedChar_ToBytesAndViseVersa)
{
	unsigned char expected = 'k';
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<unsigned char>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, Float_ToBytesAndViseVersa)
{
	float expected = 1976.45f;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<float>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, Double_ToBytesAndViseVersa)
{
	double expected = 7654345678.7656789;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<double>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, LongDouble_ToBytesAndViseVersa)
{
	long double expected = 765434567890.76543234567;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<long double>(bytes);
	ASSERT_EQ(actual, expected);
}

TEST(UtilityTestCase, Wchar_T_ToBytesAndViseVersa)
{
	wchar_t expected = L'ñ';
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<wchar_t>(bytes);
	ASSERT_EQ(actual, expected);
}

class CustomType
{
private:
	int _val;
	xw::string _str;

public:
	CustomType() : _val(0), _str("")
	{
	}

	explicit CustomType(int val, xw::string str) : _val(val), _str(std::move(str))
	{
	}

	[[nodiscard]] int get_val() const
	{
		return this->_val;
	}
};

TEST(UtilityTestCase, CustomTypeToBytesAndViseVersa)
{
	auto expected = CustomType(100, "!🌍 olleH");
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<CustomType>(bytes);
	ASSERT_EQ(actual.get_val(), expected.get_val());
}

TEST(UtilityTestCase, format_datetime)
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

TEST(UtilityTestCase, format_datetime_NoTimezone)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	std::string expected = "Fri, 15 Nov 2019 12:45:26 -0000";
	std::string actual = utility::format_datetime(&dt);
	ASSERT_EQ(expected, actual);
}

TEST(UtilityTestCase, format_datetime_UseGmt)
{
	const char* str_dt = "Fri, 15 Nov 2019 12:45:26";
	auto dt = dt::Datetime::strptime(str_dt, "%a, %e %b %Y %T");
	dt = dt.as_timezone(std::make_shared<dt::Timezone>(dt::Timezone::UTC));
	std::string expected = "Fri, 15 Nov 2019 12:45:26 GMT";
	std::string actual = utility::format_datetime(&dt, true);
	ASSERT_EQ(expected, actual);
}

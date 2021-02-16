/**
 * tests_string.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/string_utils.h"

using namespace xw;


TEST(StrUtilsUrlSplitTypeTestCase, TestSuccess)
{
	std::string schemeActual, dataActual;
	str::url_split_type("http://example.com/file.html", schemeActual, dataActual);
	ASSERT_EQ(schemeActual, "http");
	ASSERT_EQ(dataActual, "//example.com/file.html");
}

TEST(StrUtilsUrlSplitTypeTestCase, TestMissingColon)
{
	std::string schemeActual, dataActual;
	str::url_split_type("http//example.com/file.html", schemeActual, dataActual);
	ASSERT_EQ(schemeActual, "");
	ASSERT_EQ(dataActual, "http//example.com/file.html");
}

TEST(StrUtilsUrlSplitTypeTestCase, TestSlashBeforeColon)
{
	std::string schemeActual, dataActual;
	str::url_split_type("http/://example.com/file.html", schemeActual, dataActual);
	ASSERT_EQ(schemeActual, "");
	ASSERT_EQ(dataActual, "http/://example.com/file.html");
}

TEST(StrUtilsUrlSplitTypeTestCase, TestEmptyInput)
{
	std::string schemeActual, dataActual;
	str::url_split_type("", schemeActual, dataActual);
	ASSERT_EQ(schemeActual, "");
	ASSERT_EQ(dataActual, "");
}


TEST(StrUtilsSplitTestCase, TestSplitByDefaultChar)
{
	std::string toSplit("Alphanumeric and printable shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", "printable", "shellcode"};
	auto actual = str::split(toSplit);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(StrUtilsSplitTestCase, TestSplit)
{
	std::string toSplit("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::split(toSplit, ':');
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(StrRSplitTestCase, TestRSplit)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric:and: printable ", " shellcode"};
	auto actual = str::rsplit(to_split, ':', 1);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}


TEST(StrUtilsJoinVectorTestCase, TestJoinStringVectorWithSpace)
{
	std::string expected = "Alphanumeric and printable shellcode";
	std::vector<std::string> strVec = {"Alphanumeric", "and", "printable", "shellcode"};
	ASSERT_EQ(str::join(strVec.cbegin(), strVec.cend(), " "), expected);
}

TEST(StrUtilsJoinVectorTestCase, TestJoinIntVectorWithComma)
{
	std::string expected = "{1, 2, 3, 4, 5, 6, 7, 8, 9, 10}";
	std::vector<int> intVec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	ASSERT_EQ("{" + str::join(intVec.cbegin(), intVec.cend(), ", ") + "}", expected);
}

TEST(StrUtilsJoinVectorTestCase, TestJoinCharVectorWithputSpace)
{
	std::string expected = "Alphanumeric";
	std::vector<char> intVec = {'A', 'l', 'p', 'h', 'a', 'n', 'u', 'm', 'e', 'r', 'i', 'c'};
	ASSERT_EQ(str::join(intVec.cbegin(), intVec.cend(), ""), expected);
}


TEST(StrUtilsLTrimTestCase, TestLeftTrimmingInPlace)
{
	std::string expected = "Hello, World   ";
	std::string actual = "       " + expected;
	str::ltrim(actual);
	ASSERT_EQ(actual, expected);

	expected = "Hello, World  - ---";
	actual = "------" + expected;
	str::ltrim(actual, "-");
	ASSERT_EQ(actual, expected);
}

TEST(StrUtilsRTrimTestCase, TestRightTrimmingInPlace)
{
	std::string expected = "      Hello, World";
	std::string actual = expected + "       ";
	str::rtrim(actual);
	ASSERT_EQ(actual, expected);

	expected = "--------Hello, World";
	actual = expected + "------";
	str::rtrim(actual, "-");
	ASSERT_EQ(actual, expected);
}

TEST(StrUtilsTrimTestCase, TestTrimmingInPlace)
{
	std::string expected = "Hello, World      --- - ---";
	std::string actual = "       " + expected + "      ";
	str::trim(actual);
	ASSERT_EQ(actual, expected);

	expected = "Hello, World";
	actual = "------" + expected + "----";
	str::trim(actual, "-");
	ASSERT_EQ(actual, expected);
}

TEST(StrUtilsLTrimTestCase, TestLeftTrimmingCopy)
{
	std::string expected = "Hello, World   ";
	ASSERT_EQ(str::ltrim("       " + expected), expected);

	expected = "Hello, World  - ---";
	ASSERT_EQ(str::ltrim("------" + expected, "-"), expected);
}

TEST(StrUtilsRTrimTestCase, TestRightTrimmingCopy)
{
	std::string expected = "      Hello, World";
	ASSERT_EQ(str::rtrim(expected + "       "), expected);

	expected = "--------Hello, World";
	ASSERT_EQ(str::rtrim(expected + "------", "-"), expected);
}

TEST(StrUtilsTrimTestCase, TestTrimmingCopy)
{
	std::string expected = "Hello, World      --- - ---";
	ASSERT_EQ(str::trim("       " + expected + "      "), expected);

	expected = "Hello, World";
	ASSERT_EQ(str::trim("------" + expected + "----", "-"), expected);
}


TEST(StrUpperTestCase, TestUpper)
{
	std::string expected = "HELLO, WORLD";
	std::string actual = str::upper("Hello, world");

	ASSERT_EQ(expected, actual);
}


TEST(StrLowerTestCase, TestLower)
{
	std::string expected = "hello, world";
	std::string actual = str::lower("HeLlO, WoRlD");

	ASSERT_EQ(expected, actual);
}

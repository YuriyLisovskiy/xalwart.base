/**
 * tests_string_utils.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/string_utils.h"

using namespace xw;


TEST(TestCase_string_utils, _normalize_exp_GreaterThan1)
{
	double input = 25.6;
	auto exponent = str::_normalize_exp(&input);
	ASSERT_EQ(input, 0.256);
	ASSERT_EQ(exponent, 2);
}

TEST(TestCase_string_utils, _normalize_exp_LessThanOneTenth)
{
	double input = 0.000256;
	auto exponent = str::_normalize_exp(&input);
	ASSERT_EQ(input, 0.256);
	ASSERT_EQ(exponent, -3);
}

struct TestCase_string_utils_custom_type
{
	std::string some_value;
};

TEST(TestCase_string_utils, join_AnyTypeLambda)
{
	std::initializer_list<TestCase_string_utils_custom_type> list = {{"some 1"}, {"some 2"}};
	std::string expected = "some 1 - some 2";
	auto actual = str::join(" - ", list.begin(), list.end(), [](const auto& val) -> auto {
		return val.some_value;
	});
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_AnyTypeLambdaEmptyList)
{
	std::initializer_list<int> list;
	auto actual = str::join("-", list.begin(), list.end(), [](const auto& num) -> auto {
		return std::to_string(num);
	});
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, join_AnyTypeLambdaWithInitializerList)
{
	std::string expected = "some 1 - some 2";
	auto actual = str::join<TestCase_string_utils_custom_type>(
		" - ", {{"some 1"}, {"some 2"}}, [](const auto& val) -> auto {
			return val.some_value;
		}
	);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_CStrings)
{
	auto list = {"one", "two", "three", "four"};
	std::string expected = "one, two, three, four";
	auto actual = str::join(", ", list.begin(), list.end());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_CStringsInitializerList)
{
	std::string expected = "one, two, three, four";
	auto actual = str::join<const char*>(", ", {"one", "two", "three", "four"});
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_CStringsEmptyList)
{
	std::initializer_list<const char*> list;
	auto actual = str::join(", ", list.begin(), list.end());
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, join_Strings)
{
	std::initializer_list<std::string> list = {"Alphanumeric", "and", "printable", "shellcode"};
	std::string expected = "Alphanumeric and printable shellcode";
	auto actual = str::join(" ", list.begin(), list.end());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_StringsInitializerList)
{
	std::string expected = "Alphanumeric and printable shellcode";
	auto actual = str::join<std::string>(" ", {"Alphanumeric", "and", "printable", "shellcode"});
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_StringsEmptyList)
{
	std::initializer_list<std::string> list;
	auto actual = str::join(", ", list.begin(), list.end());
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, join_Chars)
{
	auto list = {'A', 'l', 'p', 'h', 'a', 'n', 'u', 'm', 'e', 'r', 'i', 'c'};
	std::string expected = "Alphanumeric";
	auto actual = str::join("", list.begin(), list.end());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_CharsInitializerList)
{
	std::string expected = "Alphanumeric";
	auto actual = str::join("", {'A', 'l', 'p', 'h', 'a', 'n', 'u', 'm', 'e', 'r', 'i', 'c'});
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_Numeric)
{
	auto list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::string expected = "1, 2, 3, 4, 5, 6, 7, 8, 9, 10";
	auto actual = str::join(", ", list.begin(), list.end());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_NumericInitializerList)
{
	std::string expected = "1, 2, 3, 4, 5, 6, 7, 8, 9, 10";
	auto actual = str::join(", ", {1, 2, 3, 4, 5, 6, 7, 8, 9, 10});
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, join_NumericEmptyList)
{
	auto list = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	std::string expected = "1, 2, 3, 4, 5, 6, 7, 8, 9, 10";
	auto actual = str::join(", ", list.begin(), list.end());
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, url_split_type)
{
	std::string actual_scheme, actual_data;
	str::url_split_type("http://example.com/file.html", actual_scheme, actual_data);
	ASSERT_EQ(actual_scheme, "http");
	ASSERT_EQ(actual_data, "//example.com/file.html");
}

TEST(TestCase_string_utils, url_split_type_SchemeNotFound)
{
	std::string actual_scheme, actual_data;
	str::url_split_type("http//example.com/file.html", actual_scheme, actual_data);
	ASSERT_EQ(actual_scheme, "");
	ASSERT_EQ(actual_data, "http//example.com/file.html");
}

TEST(TestCase_string_utils, url_split_type_SchemeNotFoundSlashBeforeColon)
{
	std::string actual_scheme, actual_data;
	str::url_split_type("http/://example.com/file.html", actual_scheme, actual_data);
	ASSERT_EQ(actual_scheme, "");
	ASSERT_EQ(actual_data, "http/://example.com/file.html");
}

TEST(TestCase_string_utils, url_split_type_EmptyInput)
{
	std::string actual_scheme, actual_data;
	str::url_split_type("", actual_scheme, actual_data);
	ASSERT_EQ(actual_scheme, "");
	ASSERT_EQ(actual_data, "");
}

TEST(TestCase_string_utils, contains_True)
{
	ASSERT_TRUE(str::contains("Hello, World", ','));
}

TEST(TestCase_string_utils, contains_False)
{
	ASSERT_FALSE(str::contains("Hello, World", '|'));
}

TEST(TestCase_string_utils, lower)
{
	std::string expected = "hello, world!!1!!!111";
	auto actual = str::lower("HeLlO, WorlD!!1!!!111");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, upper)
{
	std::string expected = "HELLO, WORLD!!1!!!111$$$&";
	auto actual = str::upper("hello, WoRlD!!1!!!111$$$&");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, split_EmptyString)
{
	auto actual = str::split("");
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ("", actual[0]);
}

TEST(TestCase_string_utils, split_ToZeroParts)
{
	std::string value("Alphanumeric and printable shellcode");
	auto actual = str::split(value, ' ', 0);
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ(value, actual[0]);
}

TEST(TestCase_string_utils, split_WithLastSymbolAsDelimiter)
{
	std::string value("hello:");
	auto actual = str::split(value, ':');
	ASSERT_EQ(2, actual.size());
	ASSERT_EQ("hello", actual[0]);
	ASSERT_EQ("", actual[1]);
}

TEST(TestCase_string_utils, split_WithNonExistentDelimiter)
{
	std::string value("Alphanumeric and printable shellcode");
	auto actual = str::split(value, '~');
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ(value, actual[0]);
}

TEST(TestCase_string_utils, split_WithDefaultDelimiter)
{
	std::string value("Alphanumeric and printable shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", "printable", "shellcode"};
	auto actual = str::split(value);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, split_WithCustomDelimiter)
{
	std::string value("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::split(value, ':');
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, split_WithPositiveCount1)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and: printable : shellcode"};
	auto actual = str::split(to_split, ':', 1);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, split_WithPositiveCount)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable : shellcode"};
	auto actual = str::split(to_split, ':', 2);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, split_WithSameCountAsPartsNumber)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::split(to_split, ':', 4);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, split_WithPositiveCountGreaterThanActualParts)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::split(to_split, ':', 5);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, rsplit_EmptyString)
{
	auto actual = str::rsplit("");
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ("", actual[0]);
}

TEST(TestCase_string_utils, rsplit_ToZeroParts)
{
	std::string value("Alphanumeric and printable shellcode");
	auto actual = str::rsplit(value, ' ', 0);
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ(value, actual[0]);
}

TEST(TestCase_string_utils, rsplit_WithNonExistentDelimiter)
{
	std::string value("Alphanumeric and printable shellcode");
	auto actual = str::rsplit(value, '~');
	ASSERT_EQ(1, actual.size());
	ASSERT_EQ(value, actual[0]);
}

TEST(TestCase_string_utils, rsplit_WithDefaultDelimiter)
{
	std::string value("Alphanumeric and printable shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", "printable", "shellcode"};
	auto actual = str::rsplit(value);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, rsplit_WithCustomDelimiter)
{
	std::string value("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::rsplit(value, ':');
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, rsplit_WithPositiveCount1)
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

TEST(TestCase_string_utils, rsplit_WithPositiveCount)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric:and", " printable ", " shellcode"};
	auto actual = str::rsplit(to_split, ':', 2);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, rsplit_WithSameCountAsPartsNumber)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::rsplit(to_split, ':', 4);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, rsplit_WithPositiveCountGreaterThanActualParts)
{
	std::string to_split("Alphanumeric:and: printable : shellcode");
	std::vector<std::string> expected = {"Alphanumeric", "and", " printable ", " shellcode"};
	auto actual = str::rsplit(to_split, ':', 5);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_string_utils, ltrim_DefaultChars)
{
	std::string expected = "Hello, World   ";
	std::string actual = str::ltrim("       Hello, World   ");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, ltrim_CustomChars)
{
	std::string expected = "llo, World";
	std::string actual = str::ltrim("%%%Hello, World", "%eH");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, rtrim_DefaultChars)
{
	std::string expected = " -- Hello, World --";
	std::string actual = str::rtrim(" -- Hello, World -- ");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, rtrim_CustomChars)
{
	std::string expected = " -- Hello,";
	std::string actual = str::rtrim(" -- Hello, World -- ", " World-");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, trim_DefaultChars)
{
	std::string expected = "Hello, World";
	std::string actual = str::trim(" Hello, World          ");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, trim_CustomChars)
{
	std::string expected = ", World";
	std::string actual = str::trim(" -- Hello, World -- ", "-Hello ");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_string_utils, count_Found)
{
	std::string s = "Hello, World!";
	size_t expected = 3;
	auto actual = str::count(s, 'l');
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, count_NotFound)
{
	std::string s = "Hello, World!";
	size_t expected = 0;
	auto actual = str::count(s, 'w');
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_LeftOnly)
{
	std::string expected = ", World!";
	auto actual = str::cut_edges("Hello, World!", 5, 0, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_LeftOnlyCutAll)
{
	auto actual = str::cut_edges("Hello, World!", 13, 0, false);
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, cut_edges_LeftOnlyNotCutEdgesAreGreaterThanInput)
{
	std::string expected = "Hello, World!";
	auto actual = str::cut_edges("Hello, World!", 14, 0, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_RightOnly)
{
	std::string expected = "H";
	auto actual = str::cut_edges("Hello, World!", 0, 12, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_RightOnlyCutAll)
{
	auto actual = str::cut_edges("Hello, World!", 0, 13, false);
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, cut_edges_RightOnlyNotCutEdgesAreGreaterThanInput)
{
	std::string expected = "Hello, World!";
	auto actual = str::cut_edges("Hello, World!", 0, 14, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_Both)
{
	std::string expected = " lo, Wo  ";
	auto actual = str::cut_edges("Hel lo, Wo  rld!", 3, 4, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_BothWithTrim)
{
	std::string expected = "llo, Wo";
	auto actual = str::cut_edges("He llo, Wo  rld!", 3, 4, true);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_NotCutEdgesAreGreaterThanInput)
{
	std::string expected = "Hel lo, Wo  rld!";
	auto actual = str::cut_edges("Hel lo, Wo  rld!", 8, 9, false);
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, cut_edges_CutAll)
{
	auto actual = str::cut_edges("Hel lo, Wo  rld!", 7, 9, false);
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, cut_edges_CutEmptyString)
{
	auto actual = str::cut_edges("", 7, 9, false);
	ASSERT_EQ("", actual);
}

TEST(TestCase_string_utils, replace_OneSub)
{
	std::string expected = "Hello, Home!";
	auto actual = str::replace("Hello, World?", "World?", "Home!");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, replace_MultipleSubs)
{
	std::string expected = "He~|~~|~o, Wor~|~d!";
	auto actual = str::replace("Hello, World!", "l", "~|~");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, replace_SubsToEmpty)
{
	std::string expected = "Heo, Word!";
	auto actual = str::replace("Hello, World!", "l", "");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, replace_EmptySub)
{
	std::string expected = "Hello, World!";
	auto actual = str::replace("Hello, World!", "", "~");
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_string_utils, replace_EmptyString)
{
	auto actual = str::replace("", "1", "~");
	ASSERT_EQ("", actual);
}

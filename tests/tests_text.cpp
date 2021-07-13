/**
 * tests_text.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/text.h"

using namespace xw;


TEST(TestCase_text, smart_split_DoubleQuotes)
{
	std::string input = R"(This is "a person's" test.)";
	std::vector expected = {
		"This", "is", R"("a person's")", "test."
	};
	auto actual = text::smart_split(input);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(smart_split, smart_split_SingleQuotes)
{
	std::string input = R"(Another 'person\'s' test.)";
	std::vector expected = {
		"Another", R"('person\'s')", "test."
	};
	auto actual = text::smart_split(input);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(smart_split, smart_split_NestedDoubleQuotes)
{
	std::string input = R"(A "\"funky\" style" test.)";
	std::vector expected = {
		"A", R"("\"funky\" style")", "test."
	};
	auto actual = text::smart_split(input);
	ASSERT_EQ(expected.size(), actual.size());
	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

/**
 * tests/collections/tests_dict.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/collections/base_dictionary.h"

using namespace xw;


TEST(TestCase_Dictionary, TestRemove)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_FALSE(testDict.empty());
	testDict.remove(1);
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Dictionary, TestClear)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2}, {3, 4}
	});
	ASSERT_FALSE(testDict.empty());
	testDict.clear();
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Dictionary, TestSize)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_EQ(testDict.size(), 0);

	testDict = {{{1, 2}}};
	ASSERT_EQ(testDict.size(), 1);
}

TEST(TestCase_Dictionary, TestContainsTrue)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_TRUE(testDict.contains(1));
}

TEST(TestCase_Dictionary, TestContainsFalse)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_FALSE(testDict.contains(2));
}

TEST(TestCase_Dictionary, TestIsEmpty)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Dictionary, TestIsNotEmpty)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_FALSE(testDict.empty());
}

TEST(TestCase_Dictionary, TestBeginNotThrows)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_NO_THROW(testDict.begin());
}

TEST(TestCase_Dictionary, TestEndNotThrows)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_NO_THROW(testDict.end());
}

TEST(TestCase_Dictionary, TestRBeginNotThrows)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_NO_THROW(testDict.rbegin());
}

TEST(TestCase_Dictionary, TestREndNotThrows)
{
	collections::BaseDictionary<int, int> testDict;
	ASSERT_NO_THROW(testDict.rend());
}

TEST(TestCase_Dictionary, TestGetKeys)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2},
		{2, 3},
		{3, 4}
	});
	std::vector<int> expected = {1, 2, 3};
	auto actual = testDict.keys();

	ASSERT_EQ(expected.size(), actual.size());

	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_Dictionary, TestGetSize)
{
	collections::BaseDictionary<int, int> testDict(std::map<int, int>{
		{1, 2},
		{2, 3},
		{3, 4}
	});
	auto expected = 3;
	auto actual = testDict.size();

	ASSERT_EQ(expected, actual);
}

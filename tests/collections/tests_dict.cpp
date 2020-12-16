/**
 * tests/collections/tests_dict.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/collections/dict.h"

using namespace xw;


// Dict testing.
TEST(DictTestCase, TestGetItemExists)
{
	collections::Dict<int, int> testDict({
		{1, 2},
		{2, 3},
		{3, 4}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	ASSERT_EQ(testDict.get(2, 0), 3);
	ASSERT_EQ(testDict.get(3, 0), 4);
}

TEST(DictTestCase, TestGetItemNotExists)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(DictTestCase, TestSet)
{
	collections::Dict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

TEST(DictTestCase, TestRemove)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	testDict.remove(1);
	ASSERT_EQ(testDict.get(1, 0), 0);
}

TEST(DictTestCase, TestClear)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}, {3, 4}
	});
	ASSERT_FALSE(testDict.is_empty());
	testDict.clear();
	ASSERT_TRUE(testDict.is_empty());
}

TEST(DictTestCase, TestSize)
{
	collections::Dict<int, int> testDict;
	ASSERT_EQ(testDict.size(), 0);
	testDict.set(1, 2);
	ASSERT_EQ(testDict.size(), 1);
	testDict.set(2, 5);
	ASSERT_EQ(testDict.size(), 2);
}

TEST(DictTestCase, TestContains)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_TRUE(testDict.contains(1));
	ASSERT_FALSE(testDict.contains(2));
}

TEST(DictTestCase, TestIsEmpty)
{
	collections::Dict<int, int> testDict;
	ASSERT_TRUE(testDict.is_empty());
}

TEST(DictTestCase, TestIsNotEmpty)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_FALSE(testDict.is_empty());
}

TEST(DictTestCase, TestBeginNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.begin());
}

TEST(DictTestCase, TestEndNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.end());
}

TEST(DictTestCase, TestRBeginNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rbegin());
}

TEST(DictTestCase, TestREndNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rend());
}

TEST(DictTestCase, TestGetKeys)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
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

TEST(DictTestCase, TestGetSize)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2},
		{2, 3},
		{3, 4}
	});
	auto expected = 3;
	auto actual = testDict.size();

	ASSERT_EQ(expected, actual);
}

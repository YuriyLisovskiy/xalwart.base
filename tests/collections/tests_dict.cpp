/**
 * tests/collections/tests_dict.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/collections/dict.h"

using namespace xw;


// Dict testing.
TEST(TestCase_Dict, TestGetItemExists)
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

TEST(TestCase_Dict, TestGetItemNotExists)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(TestCase_Dict, TestSet)
{
	collections::Dict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

TEST(TestCase_Dict, TestRemove)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	testDict.remove(1);
	ASSERT_EQ(testDict.get(1, 0), 0);
}

TEST(TestCase_Dict, TestClear)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}, {3, 4}
	});
	ASSERT_FALSE(testDict.is_empty());
	testDict.clear();
	ASSERT_TRUE(testDict.is_empty());
}

TEST(TestCase_Dict, TestSize)
{
	collections::Dict<int, int> testDict;
	ASSERT_EQ(testDict.size(), 0);
	testDict.set(1, 2);
	ASSERT_EQ(testDict.size(), 1);
	testDict.set(2, 5);
	ASSERT_EQ(testDict.size(), 2);
}

TEST(TestCase_Dict, TestContains)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_TRUE(testDict.contains(1));
	ASSERT_FALSE(testDict.contains(2));
}

TEST(TestCase_Dict, TestIsEmpty)
{
	collections::Dict<int, int> testDict;
	ASSERT_TRUE(testDict.is_empty());
}

TEST(TestCase_Dict, TestIsNotEmpty)
{
	collections::Dict<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_FALSE(testDict.is_empty());
}

TEST(TestCase_Dict, TestBeginNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.begin());
}

TEST(TestCase_Dict, TestEndNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.end());
}

TEST(TestCase_Dict, TestRBeginNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rbegin());
}

TEST(TestCase_Dict, TestREndNotThrows)
{
	collections::Dict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rend());
}

TEST(TestCase_Dict, TestGetKeys)
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

TEST(TestCase_Dict, TestGetSize)
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

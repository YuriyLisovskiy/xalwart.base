/**
 * tests/collections/tests_multimap.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/collections/multimap.h"

using namespace xw;


TEST(TestCase_Multimap, TestRemove)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2}}
	});
	ASSERT_FALSE(testDict.empty());
	testDict.remove(1);
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Multimap, TestClear)
{
	collections::Multimap<int, int> testDict = {{
		{1, {2}}, {3, {4}}
	}};
	ASSERT_FALSE(testDict.empty());
	testDict.clear();
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Multimap, TestSize)
{
	collections::Multimap<int, int> testDict;
	ASSERT_EQ(testDict.size(), 0);

	testDict = {{{1, {2}}}};
	ASSERT_EQ(testDict.size(), 1);
}

TEST(TestCase_Multimap, TestContainsTrue)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2}}
	});
	ASSERT_TRUE(testDict.contains(1));
}

TEST(TestCase_Multimap, TestContainsFalse)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{{1, {2}}});
	ASSERT_FALSE(testDict.contains(2));
}

TEST(TestCase_Multimap, TestIsEmpty)
{
	collections::Multimap<int, int> testDict;
	ASSERT_TRUE(testDict.empty());
}

TEST(TestCase_Multimap, TestIsNotEmpty)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2}}
	});
	ASSERT_FALSE(testDict.empty());
}

TEST(TestCase_Multimap, TestBeginNotThrows)
{
	collections::Multimap<int, int> testDict;
	ASSERT_NO_THROW(testDict.begin());
}

TEST(TestCase_Multimap, TestEndNotThrows)
{
	collections::Multimap<int, int> testDict;
	ASSERT_NO_THROW(testDict.end());
}

TEST(TestCase_Multimap, TestRBeginNotThrows)
{
	collections::Multimap<int, int> testDict;
	ASSERT_NO_THROW(testDict.rbegin());
}

TEST(TestCase_Multimap, TestREndNotThrows)
{
	collections::Multimap<int, int> testDict;
	ASSERT_NO_THROW(testDict.rend());
}

TEST(TestCase_Multimap, TestGetKeys)
{
	collections::Multimap<int, int> testDict({
		{1, {2}},
		{2, {3}},
		{3, {4}}
	});
	std::vector<int> expected = {1, 2, 3};
	auto actual = testDict.keys();

	ASSERT_EQ(expected.size(), actual.size());

	for (size_t i = 0; i < expected.size(); i++)
	{
		ASSERT_EQ(expected[i], actual[i]);
	}
}

TEST(TestCase_Multimap, TestGetSize)
{
	collections::Multimap<int, int> testDict({
		{1, {2}},
		{2, {3}},
		{3, {4}}
	});
	auto expected = 3;
	auto actual = testDict.size();

	ASSERT_EQ(expected, actual);
}

template <typename T>
bool vectorsAreEqual(const std::vector<T>& left, const std::vector<T>& right)
{
	bool result = true;
	if (left.size() != right.size())
	{
		result = false;
	}
	else
	{
		for (size_t i = 0; i < left.size(); i++)
		{
			if (left[i] != right[i])
			{
				result = false;
				break;
			}
		}
	}
	return result;
}

TEST(TestCase_Multimap, TestGetItemExists)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
		{4, {5, 6, 7}},
		{7, {8, 9, 10}}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	ASSERT_EQ(testDict.get(4, 0), 5);
	ASSERT_EQ(testDict.get(7, 0), 8);
}

TEST(TestCase_Multimap, TestGetItemNotExists)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(TestCase_Multimap, TestSet)
{
	collections::Multimap<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

TEST(TestCase_Multimap, TestSetVector)
{
	collections::Multimap<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, std::vector<int>{5, 6, 7});
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_Multimap, TestAppendToNonExistent)
{
	collections::Multimap<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.add(3, 5);
	ASSERT_EQ(testDict.get(3), 5);
	testDict.add(3, 7);
	ASSERT_EQ(testDict.get(3), 5);
	testDict.add(3, 100);
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_Multimap, TestAppendToExistent)
{
	collections::Multimap<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3}}
	});
	ASSERT_TRUE(vectorsAreEqual(testDict.get_sequence(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.add(1, 5);
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.get_sequence(1, std::vector<int>{}), std::vector<int>{2, 3, 5}));
}

TEST(TestCase_Multimap, TestAppendVectorToNonExistent)
{
	collections::Multimap<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.add(3, {5, 6, 7});
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_Multimap, TestAppendVectorToExistent)
{
	collections::Multimap<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3}}}
	);
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.get_sequence(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.add(1, {5, 6, 7});
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.get_sequence(1, std::vector<int>{}), std::vector<int>{2, 3, 5, 6, 7}));
}


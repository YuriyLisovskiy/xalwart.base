/**
 * tests/collections/tests_multi_dict.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <map>

#include <gtest/gtest.h>

#include "../../src/collections/multi_dictionary.h"

using namespace xw;


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

TEST(TestCase_MultiDictionary, TestGetItemExists)
{
	collections::MultiDictionary<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
		{4, {5, 6, 7}},
		{7, {8, 9, 10}}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	ASSERT_EQ(testDict.get(4, 0), 5);
	ASSERT_EQ(testDict.get(7, 0), 8);
}

TEST(TestCase_MultiDictionary, TestGetItemNotExists)
{
	collections::MultiDictionary<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(TestCase_MultiDictionary, TestSet)
{
	collections::MultiDictionary<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

TEST(TestCase_MultiDictionary, TestSetVector)
{
	collections::MultiDictionary<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, std::vector<int>{5, 6, 7});
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_MultiDictionary, TestAppendToNonExistent)
{
	collections::MultiDictionary<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.add(3, 5);
	ASSERT_EQ(testDict.get(3), 5);
	testDict.add(3, 7);
	ASSERT_EQ(testDict.get(3), 5);
	testDict.add(3, 100);
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_MultiDictionary, TestAppendToExistent)
{
	collections::MultiDictionary<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3}}
	});
	ASSERT_TRUE(vectorsAreEqual(testDict.getlist(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.add(1, 5);
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.getlist(1, std::vector<int>{}), std::vector<int>{2, 3, 5}));
}

TEST(TestCase_MultiDictionary, TestAppendVectorToNonExistent)
{
	collections::MultiDictionary<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.add(3, {5, 6, 7});
	ASSERT_EQ(testDict.get(3), 5);
}

TEST(TestCase_MultiDictionary, TestAppendVectorToExistent)
{
	collections::MultiDictionary<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3}}}
	);
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.getlist(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.add(1, {5, 6, 7});
	ASSERT_EQ(testDict.get(1), 2);
	ASSERT_TRUE(vectorsAreEqual(testDict.getlist(1, std::vector<int>{}), std::vector<int>{2, 3, 5, 6, 7}));
}

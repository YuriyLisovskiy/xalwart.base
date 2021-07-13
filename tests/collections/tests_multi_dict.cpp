/**
 * tests/collections/tests_multi_dict.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <map>

#include <gtest/gtest.h>

#include "../../src/collections/multi_dict.h"

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

TEST(TestCase_MultiValueDict, TestGetItemExists)
{
	collections::MultiValueDict<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
		{4, {5, 6, 7}},
		{7, {8, 9, 10}}
	});
	ASSERT_EQ(testDict.get(1, 0), 4);
	ASSERT_EQ(testDict.get(4, 0), 7);
	ASSERT_EQ(testDict.get(7, 0), 10);
}

TEST(TestCase_MultiValueDict, TestGetItemNotExists)
{
	collections::MultiValueDict<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3, 4}},
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(TestCase_MultiValueDict, TestSet)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

TEST(TestCase_MultiValueDict, TestSetVector)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, std::vector<int>{5, 6, 7});
	ASSERT_EQ(testDict.get(3), 7);
}

TEST(TestCase_MultiValueDict, TestAppendToNonExistent)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.append(3, 5);
	ASSERT_EQ(testDict.get(3), 5);
	testDict.append(3, 7);
	ASSERT_EQ(testDict.get(3), 7);
	testDict.append(3, 100);
	ASSERT_EQ(testDict.get(3), 100);
}

TEST(TestCase_MultiValueDict, TestAppendToExistent)
{
	collections::MultiValueDict<int, int> testDict(std::map<int, std::vector<int>>{
		{1, {2, 3}}
	});
	ASSERT_TRUE(vectorsAreEqual(testDict.get(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.append(1, 5);
	ASSERT_EQ(testDict.get(1), 5);
	ASSERT_TRUE(vectorsAreEqual(testDict.get(1, std::vector<int>{}), std::vector<int>{2, 3, 5}));
}

TEST(TestCase_MultiValueDict, TestAppendVectorToNonExistent)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_EQ(testDict.get(3, {}), {});
	testDict.append(3, {5, 6, 7});
	ASSERT_EQ(testDict.get(3), 7);
}

TEST(TestCase_MultiValueDict, TestAppendVectorToExistent)
{
	collections::MultiValueDict<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3}}}
	);
	ASSERT_EQ(testDict.get(1), 3);
	ASSERT_TRUE(vectorsAreEqual(testDict.get(1, std::vector<int>{}), std::vector<int>{2, 3}));
	testDict.append(1, {5, 6, 7});
	ASSERT_EQ(testDict.get(1), 7);
	ASSERT_TRUE(vectorsAreEqual(testDict.get(1, std::vector<int>{}), std::vector<int>{2, 3, 5, 6, 7}));
}

TEST(TestCase_MultiValueDict, TestClear)
{
	collections::MultiValueDict<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3, 4}}}
	);
	ASSERT_FALSE(testDict.is_empty());
	testDict.clear();
	ASSERT_TRUE(testDict.is_empty());
}

TEST(TestCase_MultiValueDict, TestSize)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_EQ(testDict.size(), 0);
	testDict.append(1, {2, 3, 4});
	ASSERT_EQ(testDict.size(), 1);
	testDict.append(2, {5, 6, 7});
	ASSERT_EQ(testDict.size(), 2);
}

TEST(TestCase_MultiValueDict, TestRemove)
{
	collections::MultiValueDict<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3, 4}}}
	);
	ASSERT_EQ(testDict.get(1, 0), 4);
	testDict.remove(1);
	ASSERT_EQ(testDict.get(1, 0), 0);
}

TEST(TestCase_MultiValueDict, TestContains)
{
	collections::MultiValueDict<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3, 4}}}
	);
	ASSERT_TRUE(testDict.contains(1));
	ASSERT_FALSE(testDict.contains(2));
}

TEST(TestCase_MultiValueDict, TestIsEmpty)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_TRUE(testDict.is_empty());
}

TEST(TestCase_MultiValueDict, TestIsNotEmpty)
{
	collections::MultiValueDict<int, int> testDict(
		std::map<int, std::vector<int>>{{1, {2, 3, 4}}}
	);
	ASSERT_FALSE(testDict.is_empty());
}

TEST(TestCase_MultiValueDict, TestBeginNotThrows)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_NO_THROW(testDict.begin());
}

TEST(TestCase_MultiValueDict, TestEndNotThrows)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_NO_THROW(testDict.end());
}

TEST(TestCase_MultiValueDict, TestRBeginNotThrows)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rbegin());
}

TEST(TestCase_MultiValueDict, TestREndNotThrows)
{
	collections::MultiValueDict<int, int> testDict;
	ASSERT_NO_THROW(testDict.rend());
}

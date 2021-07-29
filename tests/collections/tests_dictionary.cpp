/**
 * tests/collections/tests_dict.cpp
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/collections/dictionary.h"

using namespace xw;


TEST(TestCase_Dictionary, TestGetItemExists)
{
	collections::Dictionary<int, int> testDict({
		{1, 2},
		{2, 3},
		{3, 4}
	});
	ASSERT_EQ(testDict.get(1, 0), 2);
	ASSERT_EQ(testDict.get(2, 0), 3);
	ASSERT_EQ(testDict.get(3, 0), 4);
}

TEST(TestCase_Dictionary, TestGetItemNotExists)
{
	collections::Dictionary<int, int> testDict(std::map<int, int>{
		{1, 2}
	});
	ASSERT_EQ(testDict.get(3, 0), 0);
}

TEST(TestCase_Dictionary, TestSet)
{
	collections::Dictionary<int, int> testDict;
	ASSERT_EQ(testDict.get(3, 0), 0);
	testDict.set(3, 5);
	ASSERT_EQ(testDict.get(3, 0), 5);
}

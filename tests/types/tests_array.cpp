/**
 * tests/types/tests_array.cpp
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 */

#include <vector>

#include <gtest/gtest.h>

#include "../../src/types/array.h"

using namespace xw;


TEST(ArrayTestCase, AssignTest)
{
	using Array = core::types::Array;
	using namespace core::types;

	Array null_arr;
	ASSERT_FALSE(null_arr);

	Array arr;
	arr = std::vector<int>{10, 2, 5};
	ASSERT_TRUE(arr);

	ASSERT_EQ(*(arr[0]->__cast__<Value<int>>()), 10);
	ASSERT_EQ(*(arr[1]->__cast__<Value<int>>()), 2);
	ASSERT_EQ(*(arr[2]->__cast__<Value<int>>()), 5);

	arr.push_back(10.501);
	arr.push_back(std::string("hello"));
	arr.push_back("c-string");

	ASSERT_EQ(*(arr[3]->__cast__<Value<double>>()), 10.501);
	ASSERT_EQ(*(arr[4]->__cast__<Value<std::string>>()), std::string("hello"));
	ASSERT_EQ(*(arr[5]->__cast__<Value<const char*>>()), "c-string");
}

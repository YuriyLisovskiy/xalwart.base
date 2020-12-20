/**
 * tests_utility.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/utility.h"

using namespace xw::core;

TEST(TestCase, IntToBytesAndViseVersa)
{
	int expected = 10;
	auto bytes = utility::serialize(expected);
	auto actual = utility::deserialize<int>(bytes);
	ASSERT_EQ(actual, expected);
	delete[] bytes;
}

/**
 * tests_lazy.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/lazy.h"

using namespace xw;


TEST(Lazy_TestCase, value_Get)
{
	auto lazy = Lazy<int>([]() -> int { return 10; });
	ASSERT_EQ(lazy.value(), 10);
}

TEST(Lazy_TestCase, value_Set)
{
	auto lazy = Lazy<int>([]() -> int { return 10; });
	ASSERT_EQ(lazy.value(), 10);

	lazy.value() = 7;
	ASSERT_EQ(lazy.value(), 7);
}

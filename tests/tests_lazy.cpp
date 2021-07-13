/**
 * tests_lazy.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/lazy.h"

using namespace xw;


TEST(TestCase_Lazy, value_Get)
{
	auto lazy = Lazy<int>([]() -> int { return 10; });
	ASSERT_EQ(lazy.get(), 10);
}

TEST(TestCase_Lazy, value_Set)
{
	auto lazy = Lazy<int>([]() -> int { return 10; });
	ASSERT_EQ(lazy.get(), 10);

	lazy.set(7);
	ASSERT_EQ(lazy.get(), 7);
}

/**
 * types/tests_utility.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/utility.h"

using namespace xw;


TEST(TestCase_utility, to_sequence)
{
	auto list = std::vector<types::string>{"one", "two", "three"};
	auto sequence = types::to_sequence(list.begin(), list.end());
	ASSERT_EQ(list.size(), sequence.size());

	sequence.look_through([list](auto idx, const auto* item) -> void
	{
		ASSERT_EQ(list.at(idx).__str__(), item->__str__());
	}, false);
}

TEST(TestCase_utility, to_sequence_Empty)
{
	auto list = std::vector<types::string>{};
	auto sequence = types::to_sequence(list.begin(), list.end());
	ASSERT_EQ(list.size(), sequence.size());
}

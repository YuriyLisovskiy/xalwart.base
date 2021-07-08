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

TEST(TestCase_utility, to_object_Array)
{
	auto container = std::array<types::_char, 3>{'a', 'b', 'c'};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{'a', 'b', 'c'}");
}

TEST(TestCase_utility, to_object_Vector)
{
	auto container = std::vector<types::_char>{'a', 'b', 'c'};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{'a', 'b', 'c'}");
}

TEST(TestCase_utility, to_object_Deque)
{
	auto container = std::deque<types::_char>{'a', 'b', 'c'};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{'a', 'b', 'c'}");
}

TEST(TestCase_utility, to_object_Forward_list)
{
	auto container = std::forward_list<types::_char>{'a', 'b', 'c'};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{'a', 'b', 'c'}");
}

TEST(TestCase_utility, to_object_List)
{
	auto container = std::list<types::_char>{'a', 'b', 'c'};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{'a', 'b', 'c'}");
}

TEST(TestCase_utility, to_object_StdMap)
{
	auto container = std::map<types::string, types::_int>{
		{"a", 14},
		{"b", 7},
		{"c", 0},
	};
	ASSERT_EQ(types::to_object(container).get()->__str__(), "{{\"a\", 14}, {\"b\", 7}, {\"c\", 0}}");
}

TEST(TestCase_utility, to_object_Map)
{
	auto container = types::map<types::string, types::_int>{
		{"a", 14},
		{"b", -7},
		{"c", 0},
	};
	ASSERT_EQ(types::to_object(container).get()->__str__(), R"({{"a", 14}, {"b", -7}, {"c", 0}})");
}

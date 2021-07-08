/**
 * types/tests_map.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/map.h"
#include "../../src/types/string.h"
#include "../../src/types/fundamental.h"

using namespace xw;


class TestCase_Map : public ::testing::Test
{
protected:
	types::Map<types::string, types::fundamental<int>> string_int_map;
	types::Map<types::fundamental<char>, types::fundamental<float>> empty_map;

	void SetUp() override
	{
		(*this->string_int_map).emplace("Hello", 10);
		(*this->string_int_map).emplace("14.7", 11);
	}
};

TEST_F(TestCase_Map, is_map_True)
{
	ASSERT_TRUE(this->string_int_map.is_map());
}

TEST_F(TestCase_Map, is_sequence_False)
{
	ASSERT_FALSE(this->string_int_map.is_sequence());
}

TEST_F(TestCase_Map, look_through)
{
	std::map<std::string, int> expected = {{"Hello", 10}, {"14.7", 11}};
	this->string_int_map.look_through([expected](size_t i, const obj::Object* key, const obj::Object* val)
	{
		auto s_key = key->__str__();
		ASSERT_TRUE(expected.contains(s_key));
		ASSERT_EQ(std::to_string(expected.at(s_key)), val->__str__());
	}, false);
}

TEST_F(TestCase_Map, look_through_Reversed)
{
	std::map<std::string, int> expected = {{"14.7", 11}, {"Hello", 10}};
	this->string_int_map.look_through([expected](size_t i, const obj::Object* key, const obj::Object* val)
	{
		auto s_key = key->__str__();
		ASSERT_TRUE(expected.contains(s_key));
		ASSERT_EQ(std::to_string(expected.at(s_key)), val->__str__());
	}, true);
}

TEST_F(TestCase_Map, empty_True)
{
	ASSERT_TRUE(this->empty_map.empty());
}

TEST_F(TestCase_Map, empty_False)
{
	ASSERT_FALSE(this->string_int_map.empty());
}

TEST_F(TestCase_Map, size)
{
	auto expected = 2;
	auto actual = this->string_int_map.size();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Map, operator_star)
{
	ASSERT_EQ((*this->string_int_map).size(), 2);
}

TEST_F(TestCase_Map, __cmp__EqualsTrue)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("World")}};
	types::map<types::string, types::string> map2{{types::string("Hello"), types::string("World")}};
	ASSERT_EQ(map1.__cmp__(&map2), 0);
}

TEST_F(TestCase_Map, __cmp__EqualsFalse)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("World")}};
	types::map<types::string, types::string> map2{{types::string("World"), types::string("Hello")}};
	ASSERT_NE(map1.__cmp__(&map2), 0);
}

TEST_F(TestCase_Map, __cmp__LessTrue)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("Home")}};
	types::map<types::string, types::string> map2{{types::string("Hello"), types::string("World")}};
	ASSERT_EQ(map1.__cmp__(&map2), -1);
}

TEST_F(TestCase_Map, __cmp__LessFalse)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("World")}};
	types::map<types::string, types::string> map2{{types::string("Hello"), types::string("World")}};
	ASSERT_NE(map1.__cmp__(&map2), -1);
}

TEST_F(TestCase_Map, __cmp__GreaterTrue)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("World")}};
	types::map<types::string, types::string> map2{{types::string("Hello"), types::string("Home")}};
	ASSERT_EQ(map1.__cmp__(&map2), 1);
}

TEST_F(TestCase_Map, __cmp__GreaterFalse)
{
	types::map<types::string, types::string> map1{{types::string("Hello"), types::string("World")}};
	types::map<types::string, types::string> map2{{types::string("Hello"), types::string("World")}};
	ASSERT_NE(map1.__cmp__(&map2), 1);
}

TEST_F(TestCase_Map, __cmp__ThrowsIncompatibleTypes)
{
	types::map<types::string, types::string> mp{{types::string("Hello"), types::string("World")}};
	types::fundamental<int> s2(256);
	ASSERT_THROW(auto _ = mp.__cmp__(&s2), TypeError);
}

TEST_F(TestCase_Map, __str__)
{
	std::string expected = R"({{"14.7", 11}, {"Hello", 10}})";
	auto actual = this->string_int_map.__str__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Map, __str__Empty)
{
	std::string expected = "{}";
	auto actual = this->empty_map.__str__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Map, __repr__)
{
	std::string expected = R"({{"14.7", 11}, {"Hello", 10}})";
	auto actual = this->string_int_map.__repr__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Map, __repr__Empty)
{
	std::string expected = "{}";
	auto actual = this->empty_map.__repr__();
	ASSERT_EQ(expected, actual);
}

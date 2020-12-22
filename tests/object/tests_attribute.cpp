/**
 * tests_attribute.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/utility.h"
#include "../../src/object/attribute.h"

using namespace xw::core;


TEST(Attribute_TestCase, GetInt)
{
	int val = 10;
	object::Attribute attribute([&val]() -> std::vector<char> {
		return utility::serialize(val);
	});
	ASSERT_EQ(utility::deserialize<int>(attribute.get()), val);
}

TEST(Attribute_TestCase, SetInt)
{
	int val = 1;
	object::Attribute attribute(
		[&val]() -> std::vector<char> {
			return utility::serialize(val);
		},
		[&val](const std::vector<char>& v) -> void {
			val = utility::deserialize<int>(v);
		}
	);
	ASSERT_EQ(utility::deserialize<int>(attribute.get()), 1);
	attribute.set(utility::serialize<int>(7));
	ASSERT_EQ(utility::deserialize<int>(attribute.get()), 7);
}

TEST(Attribute_TestCase, GetUTF8String)
{
	xw::string val = "hello";
	object::Attribute attribute([&val]() -> std::vector<char> {
		return utility::serialize(val);
	});
	auto bytes = attribute.get();
	ASSERT_EQ(utility::deserialize<xw::string>(bytes), val);
}

TEST(Attribute_TestCase, SetUTF8String)
{
	xw::string val = "hello";
	object::Attribute attribute(
		[&val]() -> std::vector<char> {
			return utility::serialize(val);
		},
		[&val](const std::vector<char>& v) -> void {
			val = utility::deserialize<xw::string>(v);
		}
	);
	ASSERT_EQ(utility::deserialize<xw::string>(attribute.get()), val);
	attribute.set(utility::serialize<xw::string>("world"));
	ASSERT_EQ(utility::deserialize<xw::string>(attribute.get()), xw::string("world"));
}

struct CustomStruct
{
	int field;

	CustomStruct() : field(0) {}
	explicit CustomStruct(int val) : field(val) {}
};

TEST(Attribute_TestCase, GetCustomStruct)
{
	CustomStruct custom(2020);
	object::Attribute attribute([&custom]() -> std::vector<char> {
		return utility::serialize(custom);
	});
	ASSERT_EQ(utility::deserialize<CustomStruct>(attribute.get()).field, custom.field);
}

TEST(Attribute_TestCase, SetCustomStruct)
{
	CustomStruct custom(2020);
	object::Attribute attribute(
		[&custom]() -> std::vector<char> {
			return utility::serialize(custom);
		},
		[&custom](const std::vector<char>& v) -> void {
			custom = utility::deserialize<CustomStruct>(v);
		}
	);
	ASSERT_EQ(utility::deserialize<CustomStruct>(attribute.get()).field, custom.field);
	CustomStruct another_custom(2077);
	attribute.set(utility::serialize(another_custom));
	ASSERT_EQ(utility::deserialize<CustomStruct>(attribute.get()).field, another_custom.field);
}

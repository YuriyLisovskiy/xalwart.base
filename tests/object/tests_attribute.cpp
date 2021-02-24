/**
 * tests_attribute.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/utility.h"
#include "../../src/object/attribute.h"
#include "../../src/types/fundamental.h"
#include "../../src/types/string.h"

using namespace xw;


TEST(Attribute_TestCase, GetInt)
{
	int val = 10;
	object::Attribute attribute([&val]() -> std::shared_ptr<object::Object> {
		return std::make_shared<types::Fundamental<int>>(val);
	});
	auto& expected = *(types::Fundamental<int>*)attribute.get().get();
	ASSERT_EQ(expected.get(), val);
}

TEST(Attribute_TestCase, SetInt)
{
	int val = 1;
	object::Attribute attribute(
		[&val]() -> std::shared_ptr<object::Object> {
			return std::make_shared<types::Fundamental<int>>(val);
		},
		[&val](const std::shared_ptr<object::Object>& v) -> void {
			val = (*(types::Fundamental<int>*)v.get()).get();
		}
	);
	auto& expected = *(types::Fundamental<int>*)attribute.get().get();
	ASSERT_EQ(expected.get(), 1);
	attribute.set(std::make_shared<types::Fundamental<int>>(7));

	expected = *(types::Fundamental<int>*)attribute.get().get();
	ASSERT_EQ(expected.get(), 7);
}

TEST(Attribute_TestCase, GetUTF8String)
{
	std::string val = "hello";
	object::Attribute attribute([&val]() -> std::shared_ptr<object::Object> {
		return std::make_shared<types::String>(val);
	});
	auto expected = (*(types::String*)attribute.get().get());
	ASSERT_EQ(*expected, val);
}

TEST(Attribute_TestCase, SetUTF8String)
{
	std::string val = "hello";
	object::Attribute attribute(
		[&val]() -> std::shared_ptr<object::Object> {
			return std::make_shared<types::String>(val);
		},
		[&val](const std::shared_ptr<object::Object>& v) -> void {
			val = *(*(types::String*)v.get());
		}
	);
	auto expected = (*(types::String*)attribute.get().get());
	ASSERT_EQ(*expected, val);
	attribute.set(std::make_shared<types::String>("world"));

	expected = (*(types::String*)attribute.get().get());
	ASSERT_EQ(*expected, std::string("world"));
}

struct CustomStruct : public object::Object
{
	int field;

	CustomStruct() : field(0) {}
	explicit CustomStruct(int val) : field(val) {}

	[[nodiscard]]
	short __cmp__(const Object* other) const override
	{
		return 0;
	}
};

TEST(Attribute_TestCase, GetCustomStruct)
{
	CustomStruct custom(2020);
	object::Attribute attribute([&custom]() -> std::shared_ptr<object::Object> {
		return std::make_shared<CustomStruct>(custom);
	});
	auto expected = (*(CustomStruct*)attribute.get().get());
	ASSERT_EQ(expected.field, custom.field);
}

TEST(Attribute_TestCase, SetCustomStruct)
{
	CustomStruct custom(2020);
	object::Attribute attribute(
		[&custom]() -> std::shared_ptr<object::Object> {
			return std::make_shared<CustomStruct>(custom);
		},
		[&custom](const std::shared_ptr<object::Object>& v) -> void {
			custom = (*(CustomStruct*)v.get());
		}
	);
	auto expected = (*(CustomStruct*)attribute.get().get());
	ASSERT_EQ(expected.field, custom.field);
	CustomStruct another_custom(2077);
	attribute.set(std::make_shared<CustomStruct>(another_custom));

	expected = (*(CustomStruct*)attribute.get().get());
	ASSERT_EQ(expected.field, another_custom.field);
}

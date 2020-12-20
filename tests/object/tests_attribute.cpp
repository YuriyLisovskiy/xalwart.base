/**
 * tests_attribute.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/object/attribute.h"

using namespace xw::core;


//TEST(Attribute_TestCase, GetInt)
//{
//	int val = 10;
//	object::Attribute attribute([val]() -> char* {
//		char* p;
//		std::memcpy((void*) p, (const void*) &val, sizeof(val));
//		return p;
//	});
//	ASSERT_EQ(attribute.get<int>(), val);
//}
//
//TEST(Attribute_TestCase, SetInt)
//{
//	int val = 1;
//	object::Attribute attribute(
//		[val]() -> char* {
//			return (char*)val;
//		},
//		[&val](char* v) -> void {
//			val = std::atoi(v);
//		}
//	);
//	ASSERT_EQ(attribute.get<int>(), 1);
//	attribute.set<int>(7);
//	ASSERT_EQ(attribute.get<int>(), 7);
//}

//TEST(Attribute_TestCase, GetString)
//{
//	std::string val = "hello";
//	object::Attribute attribute(&val);
//	ASSERT_EQ(attribute.get<std::string>(), val);
//}
//
//TEST(Attribute_TestCase, SetString)
//{
//	std::string val = "hello";
//	object::Attribute attribute(&val);
//	ASSERT_EQ(attribute.get<std::string>(), val);
//	attribute.set<std::string>("world");
//	ASSERT_EQ(attribute.get<std::string>(), "world");
//}

struct CustomStruct
{
	int field;

	CustomStruct() : field(0) {}
	explicit CustomStruct(int val) : field(val) {}
};

//TEST(Attribute_TestCase, GetCustomStruct)
//{
//	CustomStruct custom(2020);
//	object::Attribute attribute([custom]() -> char* {
//		char* p;
//		std::memcpy(p, (void*) &custom, sizeof(custom));
//		return p;
//	});
//	ASSERT_EQ(attribute.get<CustomStruct>().field, custom.field);
//}

//TEST(Attribute_TestCase, SetCustomStruct)
//{
//	CustomStruct custom(2020);
//	object::Attribute attribute(&custom);
//	ASSERT_EQ(attribute.get<CustomStruct>().field, custom.field);
//	CustomStruct another_custom(2077);
//	attribute.set(another_custom);
//	ASSERT_EQ(attribute.get<CustomStruct>().field, another_custom.field);
//}

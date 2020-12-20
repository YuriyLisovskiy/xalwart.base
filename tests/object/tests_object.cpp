/**
 * tests/object/tests_object.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/object/object.h"

using namespace xw;

//namespace test_namespace
//{
//	class EmptyObject : public core::object::Object
//	{
//	};
//}
//
//TEST(Object_TestCase, EmptyObjectTypeTest)
//{
//	auto obj = test_namespace::EmptyObject();
//	auto type = obj.__type__();
//
//	ASSERT_EQ(type.name(), "EmptyObject");
//	ASSERT_EQ(type.namespace_(), "test_namespace");
//}
//
//class TestObject : public core::object::Object
//{
//public:
//	 int integer;
//
//	explicit TestObject(int integer) : integer(integer)
//	{
//		this->__attrs__ = {
////			attr("integer", TestObject::integer),
//			{"integer", core::object::Attribute(&(TestObject::integer))}
//		};
//	}
//};
//
//TEST(Object_TestCase, get)
//{
//	auto obj = TestObject(100);
//	ASSERT_EQ(obj.__get_attr__<int>("integer"), 100);
//}

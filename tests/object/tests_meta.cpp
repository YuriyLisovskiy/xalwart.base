/**
 * tests/object/tests_meta.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/object/meta.h"
#include "../../src/object/object.h"

using namespace xw;


class CustomObject : public obj::Object
{
};

class TestCase_Type_CustomObjectWithoutNamespace : public ::testing::Test
{
protected:
	CustomObject object;
};

TEST_F(TestCase_Type_CustomObjectWithoutNamespace, name)
{
	ASSERT_EQ(this->object.__type__().name(), "CustomObject");
}

TEST_F(TestCase_Type_CustomObjectWithoutNamespace, namespace_)
{
	ASSERT_EQ(this->object.__type__().namespace_(), "");
}

TEST_F(TestCase_Type_CustomObjectWithoutNamespace, operator_equals_True)
{
	CustomObject other;
	ASSERT_TRUE(this->object.__type__() == other.__type__());
}

TEST_F(TestCase_Type_CustomObjectWithoutNamespace, ostream)
{
	auto expected = "<class 'CustomObject'>";

	std::stringstream ss;
	ss << this->object.__type__();
	auto actual = ss.str();

	ASSERT_EQ(expected, actual);
}

namespace some_ns::inner_ns
{
	class AnotherCustomObject : public obj::Object
	{
	};
}

class TestCase_Type_AnotherCustomObjectWithNamespace : public ::testing::Test
{
protected:
	some_ns::inner_ns::AnotherCustomObject object;
};

TEST_F(TestCase_Type_AnotherCustomObjectWithNamespace, name)
{
	ASSERT_EQ(this->object.__type__().name(), "AnotherCustomObject");
}

TEST_F(TestCase_Type_AnotherCustomObjectWithNamespace, namespace_)
{
	ASSERT_EQ(this->object.__type__().namespace_(), "some_ns::inner_ns");
}

TEST_F(TestCase_Type_AnotherCustomObjectWithNamespace, ostream)
{
	auto expected = "<class 'AnotherCustomObject'>";

	std::stringstream ss;
	ss << this->object.__type__();
	auto actual = ss.str();

	ASSERT_EQ(expected, actual);
}

TEST(TestCase_Type, operator_equals_False)
{
	CustomObject object1;
	some_ns::inner_ns::AnotherCustomObject object2;
	ASSERT_FALSE(object1.__type__() == object2.__type__());
}

TEST(TestCase_type_name, getObjectTypeNameWithoutNamespace)
{
	ASSERT_EQ(obj::meta::type_name<CustomObject>(), "CustomObject");
}

TEST(TestCase_type_name, getObjectTypeNameWithNamespace)
{
	ASSERT_EQ(
		obj::meta::type_name<some_ns::inner_ns::AnotherCustomObject>(),
		"some_ns::inner_ns::AnotherCustomObject"
	);
}

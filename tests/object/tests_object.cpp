/**
 * tests/object/tests_object.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/object/object.h"

using namespace xw;


class TestCase_Object : public ::testing::Test
{
protected:
	obj::Object object;
};

TEST_F(TestCase_Object, __get_attr__ThrowsAttributeError)
{
	ASSERT_THROW(
		auto _ = this->object.__get_attr__("some_attr"), AttributeError
	);
}

TEST_F(TestCase_Object, __set_attr__ThrowsAttributeError)
{
	ASSERT_THROW(
		this->object.__set_attr__("some_attr", (void*)10), AttributeError
	);
}

TEST_F(TestCase_Object, __has_attr__)
{
	ASSERT_FALSE(this->object.__has_attr__("some_attr"));
}

TEST_F(TestCase_Object, __type__)
{
	ASSERT_EQ(this->object.__type__().name(), "Object");
}

TEST_F(TestCase_Object, __str__)
{
	std::stringstream oss;
	oss << static_cast<const void*>(&this->object);
	auto expected = "<Object object at " + oss.str() + ">";
	auto actual = this->object.__str__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Object, __repr__)
{
	std::stringstream oss;
	oss << static_cast<const void*>(&this->object);
	auto expected = "'<Object object at " + oss.str() + ">'";
	auto actual = this->object.__repr__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Object, __cmp__ThrowsNotImplementedException)
{
	obj::Object other;
	ASSERT_THROW(
		auto _ = this->object.__cmp__(&other), NotImplementedException
	);
}

TEST_F(TestCase_Object, operator_bool_ThrowsNotImplementedException)
{
	ASSERT_THROW(auto _ = (bool) this->object, NotImplementedException);
}

TEST_F(TestCase_Object, operator_not_ThrowsNotImplementedException)
{
	ASSERT_THROW(auto _ = !this->object, NotImplementedException);
}

/**
 * types/tests_string.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/string.h"

using namespace xw;


TEST(TestCase_String, __str__)
{
	std::string expected = "Some string to check.";
	auto actual = types::String(expected).__str__();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_String, __repr__)
{
	std::string s = "Some string to check.";
	auto expected = "'" + s + "'";
	auto actual = types::String(s).__repr__();
	ASSERT_EQ(expected, actual);
}

TEST(TestCase_String, __cmp__True)
{
	types::String s1("One"), s2("One");
	ASSERT_EQ(s1.__cmp__(&s2), 0);
}

TEST(TestCase_String, __cmp__False)
{
	types::String s1("One"), s2("Two");
	ASSERT_NE(s1.__cmp__(&s2), 0);
}

TEST(TestCase_String, __cmp__ThrowsTypeError)
{
	types::String s1("One");;
	obj::Object o;
	ASSERT_THROW(auto _ = s1.__cmp__(&o), core::TypeError);
}

TEST(TestCase_String, operator_bool_True)
{
	auto s = types::String("Hello, World!");
	ASSERT_TRUE(s.operator bool());
}

TEST(TestCase_String, operator_bool_False)
{
	types::String s;
	ASSERT_FALSE(s.operator bool());
}

TEST(TestCase_String, operator_not_True)
{
	types::String s;
	ASSERT_TRUE(!s);
}

TEST(TestCase_String, operator_not_False)
{
	auto s = types::String("Hello, World!");
	ASSERT_FALSE(!s);
}

TEST(TestCase_String, operator_star)
{
	types::String s;
	ASSERT_EQ("", s.__str__());

	*s = "Hello";
	ASSERT_EQ("Hello", s.__str__());

	*s += " World";
	ASSERT_EQ("Hello World", s.__str__());
}

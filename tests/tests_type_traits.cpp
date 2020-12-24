/**
 * tests_type_traits.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <memory>

#include <gtest/gtest.h>

#include "../src/type_traits.h"

using namespace xw::core;


TEST(TypeTraits_TestCase, has_operator_bool_SharedPtrTrue)
{
	ASSERT_TRUE(has_operator_bool<std::shared_ptr<int>>::value);
}

TEST(TypeTraits_TestCase, has_operator_bool_IntFalse)
{
	ASSERT_FALSE(has_operator_bool<int>::value);
}

struct A
{
	explicit operator bool()
	{
		return false;
	}
};

TEST(TypeTraits_TestCase, has_operator_bool_True_CustomType)
{
	ASSERT_TRUE(has_operator_bool<A>::value);
}

class B
{
};

TEST(TypeTraits_TestCase, has_operator_bool_False_CustomType)
{
	ASSERT_FALSE(has_operator_bool<B>::value);
}

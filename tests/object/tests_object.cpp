/**
 * tests/object/tests_object.cpp
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/object/object.h"

using namespace xw;

namespace test_namespace
{
	class EmptyObject : public core::object::Object
	{
	};
}

TEST(ObjectTestsCase, EmptyObjectTypeTest)
{
	auto obj = test_namespace::EmptyObject();
	auto type = obj.__type__();

	ASSERT_EQ(type.name(), "EmptyObject");
	ASSERT_EQ(type.namespace_(), "test_namespace");
}

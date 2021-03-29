/**
 * tests_sys.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/sys.h"

using namespace xw;


TEST(TestCase_sys, _version_string)
{
	ASSERT_EQ("1.2.3", sys::_version_string(1, 2, 3));
}

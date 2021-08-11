/**
 * tests__def_.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/_def_.h"

using namespace xw;


TEST(TestCase_Version, less_True)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.5");
	ASSERT_TRUE(l_ver < r_ver);
}

TEST(TestCase_Version, less_False)
{
	Version l_ver("0.1.5");
	Version r_ver("0.1.0");
	ASSERT_FALSE(l_ver < r_ver);
}

TEST(TestCase_Version, less_or_equals_True)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.5");
	ASSERT_TRUE(l_ver <= r_ver);

	r_ver = Version("0.1.0");
	ASSERT_TRUE(l_ver <= r_ver);
}

TEST(TestCase_Version, less_or_equals_False)
{
	Version l_ver("0.1.5");
	Version r_ver("0.1.0");
	ASSERT_FALSE(l_ver <= r_ver);

	r_ver = Version("0.1.4");
	ASSERT_FALSE(l_ver <= r_ver);
}

TEST(TestCase_Version, greater_True)
{
	Version l_ver("0.1.5");
	Version r_ver("0.1.0");
	ASSERT_TRUE(l_ver > r_ver);
}

TEST(TestCase_Version, greater_False)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.5");
	ASSERT_FALSE(l_ver > r_ver);
}

TEST(TestCase_Version, greater_or_equals_True)
{
	Version l_ver("0.1.5");
	Version r_ver("0.1.0");
	ASSERT_TRUE(l_ver >= r_ver);

	r_ver = Version("0.1.0");
	ASSERT_TRUE(l_ver >= r_ver);
}

TEST(TestCase_Version, greater_or_equals_False)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.5");
	ASSERT_FALSE(l_ver >= r_ver);

	r_ver = Version("0.1.5");
	ASSERT_FALSE(l_ver >= r_ver);
}

TEST(TestCase_Version, equals_True)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.0");
	ASSERT_TRUE(l_ver == r_ver);
}

TEST(TestCase_Version, equals_False)
{
	Version l_ver("0.1.0");
	Version r_ver("0.2.0");
	ASSERT_FALSE(l_ver == r_ver);
}

TEST(TestCase_Version, not_equals_True)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.7");
	ASSERT_TRUE(l_ver != r_ver);

	l_ver = Version("0.1.7");
	r_ver = Version("0.1.0");
	ASSERT_TRUE(l_ver != r_ver);
}

TEST(TestCase_Version, not_equals_False)
{
	Version l_ver("0.1.0");
	Version r_ver("0.1.0");
	ASSERT_FALSE(l_ver != r_ver);
}

TEST(TestCase_Version, less_True_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_TRUE(l_ver < "0.1.5");
}

TEST(TestCase_Version, less_False_c_string)
{
	Version l_ver("0.1.5");
	ASSERT_FALSE(l_ver < "0.1.0");
}

TEST(TestCase_Version, less_or_equals_True_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_TRUE(l_ver <= "0.1.5");
	ASSERT_TRUE(l_ver <= "0.1.0");
}

TEST(TestCase_Version, less_or_equals_False_c_string)
{
	Version l_ver("0.1.5");
	ASSERT_FALSE(l_ver <= "0.1.0");
	ASSERT_FALSE(l_ver <= "0.1.4");
}

TEST(TestCase_Version, greater_True_c_string)
{
	Version l_ver("0.1.5");
	ASSERT_TRUE(l_ver > "0.1.0");
}

TEST(TestCase_Version, greater_False_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_FALSE(l_ver > "0.1.5");
}

TEST(TestCase_Version, greater_or_equals_True_c_string)
{
	Version l_ver("0.1.5");
	ASSERT_TRUE(l_ver >= "0.1.0");
	ASSERT_TRUE(l_ver >= "0.1.5");
}

TEST(TestCase_Version, greater_or_equals_False_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_FALSE(l_ver >= "0.1.1");
	ASSERT_FALSE(l_ver >= "0.1.5");
}

TEST(TestCase_Version, equals_True_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_TRUE(l_ver == "0.1.0");
}

TEST(TestCase_Version, equals_False_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_FALSE(l_ver == "0.2.0");
}

TEST(TestCase_Version, not_equals_True_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_TRUE(l_ver != "0.1.7");

	l_ver = Version("0.1.7");
	ASSERT_TRUE(l_ver != "0.1.0");
}

TEST(TestCase_Version, not_equals_False_c_string)
{
	Version l_ver("0.1.0");
	ASSERT_FALSE(l_ver != "0.1.0");
}

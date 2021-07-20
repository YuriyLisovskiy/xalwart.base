/**
 * tests__def_.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../src/_def_.h"

using namespace xw;


TEST(TestCase_version_t, less_True)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.5");
	ASSERT_TRUE(l_ver < r_ver);
}

TEST(TestCase_version_t, less_False)
{
	base::v::version_t l_ver("0.1.5");
	base::v::version_t r_ver("0.1.0");
	ASSERT_FALSE(l_ver < r_ver);
}

TEST(TestCase_version_t, less_or_equals_True)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.5");
	ASSERT_TRUE(l_ver <= r_ver);

	r_ver = base::v::version_t("0.1.0");
	ASSERT_TRUE(l_ver <= r_ver);
}

TEST(TestCase_version_t, less_or_equals_False)
{
	base::v::version_t l_ver("0.1.5");
	base::v::version_t r_ver("0.1.0");
	ASSERT_FALSE(l_ver <= r_ver);

	r_ver = base::v::version_t("0.1.4");
	ASSERT_FALSE(l_ver <= r_ver);
}

TEST(TestCase_version_t, greater_True)
{
	base::v::version_t l_ver("0.1.5");
	base::v::version_t r_ver("0.1.0");
	ASSERT_TRUE(l_ver > r_ver);
}

TEST(TestCase_version_t, greater_False)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.5");
	ASSERT_FALSE(l_ver > r_ver);
}

TEST(TestCase_version_t, greater_or_equals_True)
{
	base::v::version_t l_ver("0.1.5");
	base::v::version_t r_ver("0.1.0");
	ASSERT_TRUE(l_ver >= r_ver);

	r_ver = base::v::version_t("0.1.0");
	ASSERT_TRUE(l_ver >= r_ver);
}

TEST(TestCase_version_t, greater_or_equals_False)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.5");
	ASSERT_FALSE(l_ver >= r_ver);

	r_ver = base::v::version_t("0.1.5");
	ASSERT_FALSE(l_ver >= r_ver);
}

TEST(TestCase_version_t, equals_True)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.0");
	ASSERT_TRUE(l_ver == r_ver);
}

TEST(TestCase_version_t, equals_False)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.2.0");
	ASSERT_FALSE(l_ver == r_ver);
}

TEST(TestCase_version_t, not_equals_True)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.7");
	ASSERT_TRUE(l_ver != r_ver);

	l_ver = base::v::version_t("0.1.7");
	r_ver = base::v::version_t("0.1.0");
	ASSERT_TRUE(l_ver != r_ver);
}

TEST(TestCase_version_t, not_equals_False)
{
	base::v::version_t l_ver("0.1.0");
	base::v::version_t r_ver("0.1.0");
	ASSERT_FALSE(l_ver != r_ver);
}

TEST(TestCase_version_t, less_True_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_TRUE(l_ver < "0.1.5");
}

TEST(TestCase_version_t, less_False_c_string)
{
	base::v::version_t l_ver("0.1.5");
	ASSERT_FALSE(l_ver < "0.1.0");
}

TEST(TestCase_version_t, less_or_equals_True_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_TRUE(l_ver <= "0.1.5");
	ASSERT_TRUE(l_ver <= "0.1.0");
}

TEST(TestCase_version_t, less_or_equals_False_c_string)
{
	base::v::version_t l_ver("0.1.5");
	ASSERT_FALSE(l_ver <= "0.1.0");
	ASSERT_FALSE(l_ver <= "0.1.4");
}

TEST(TestCase_version_t, greater_True_c_string)
{
	base::v::version_t l_ver("0.1.5");
	ASSERT_TRUE(l_ver > "0.1.0");
}

TEST(TestCase_version_t, greater_False_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_FALSE(l_ver > "0.1.5");
}

TEST(TestCase_version_t, greater_or_equals_True_c_string)
{
	base::v::version_t l_ver("0.1.5");
	ASSERT_TRUE(l_ver >= "0.1.0");
	ASSERT_TRUE(l_ver >= "0.1.5");
}

TEST(TestCase_version_t, greater_or_equals_False_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_FALSE(l_ver >= "0.1.1");
	ASSERT_FALSE(l_ver >= "0.1.5");
}

TEST(TestCase_version_t, equals_True_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_TRUE(l_ver == "0.1.0");
}

TEST(TestCase_version_t, equals_False_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_FALSE(l_ver == "0.2.0");
}

TEST(TestCase_version_t, not_equals_True_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_TRUE(l_ver != "0.1.7");

	l_ver = base::v::version_t("0.1.7");
	ASSERT_TRUE(l_ver != "0.1.0");
}

TEST(TestCase_version_t, not_equals_False_c_string)
{
	base::v::version_t l_ver("0.1.0");
	ASSERT_FALSE(l_ver != "0.1.0");
}
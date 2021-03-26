/**
 * tests/net/tests_request_context.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/net/request_context.h"

using namespace xw;


class TestCase_RequestContext : public ::testing::Test
{
protected:
	net::RequestContext context;

	void SetUp() override
	{
		this->context.major_v = 1;
		this->context.minor_v = 2;
	}
};

TEST_F(TestCase_RequestContext, proto_v_eq_to_True)
{
	ASSERT_TRUE(this->context.proto_v_eq_to(1, 2));
}

TEST_F(TestCase_RequestContext, proto_v_eq_to_FalseGreater)
{
	ASSERT_FALSE(this->context.proto_v_eq_to(1, 3));
	ASSERT_FALSE(this->context.proto_v_eq_to(2, 0));
}

TEST_F(TestCase_RequestContext, proto_v_eq_to_FalseLess)
{
	ASSERT_FALSE(this->context.proto_v_eq_to(0, 9));
	ASSERT_FALSE(this->context.proto_v_eq_to(1, 1));
}

TEST_F(TestCase_RequestContext, proto_v_gte_TrueEquals)
{
	ASSERT_TRUE(this->context.proto_v_gte(1, 2));
}

TEST_F(TestCase_RequestContext, proto_v_gte_TrueGreater)
{
	ASSERT_TRUE(this->context.proto_v_gte(1, 1));
	ASSERT_TRUE(this->context.proto_v_gte(0, 9));
}

TEST_F(TestCase_RequestContext, proto_v_gte_FalseLess)
{
	ASSERT_FALSE(this->context.proto_v_gte(1, 3));
	ASSERT_FALSE(this->context.proto_v_gte(2, 0));
}

TEST_F(TestCase_RequestContext, proto_v_lte_TrueEquals)
{
	ASSERT_TRUE(this->context.proto_v_lte(1, 2));
}

TEST_F(TestCase_RequestContext, proto_v_lte_TrueLess)
{
	ASSERT_TRUE(this->context.proto_v_lte(1, 3));
	ASSERT_TRUE(this->context.proto_v_lte(2, 0));
}

TEST_F(TestCase_RequestContext, proto_v_lte_FalseGreater)
{
	ASSERT_FALSE(this->context.proto_v_lte(1, 1));
	ASSERT_FALSE(this->context.proto_v_lte(0, 9));
}

TEST_F(TestCase_RequestContext, proto_v_gt_True)
{
	ASSERT_TRUE(this->context.proto_v_gt(1, 1));
	ASSERT_TRUE(this->context.proto_v_gt(0, 9));
}

TEST_F(TestCase_RequestContext, proto_v_gt_FalseEquals)
{
	ASSERT_FALSE(this->context.proto_v_gt(1, 2));
}

TEST_F(TestCase_RequestContext, proto_v_gt_FalseLess)
{
	ASSERT_FALSE(this->context.proto_v_gt(1, 3));
	ASSERT_FALSE(this->context.proto_v_gt(2, 0));
}

TEST_F(TestCase_RequestContext, proto_v_lt_True)
{
	ASSERT_TRUE(this->context.proto_v_lt(1, 3));
	ASSERT_TRUE(this->context.proto_v_lt(2, 0));
}

TEST_F(TestCase_RequestContext, proto_v_lt_FalseEquals)
{
	ASSERT_FALSE(this->context.proto_v_lt(1, 2));
}

TEST_F(TestCase_RequestContext, proto_v_lt_FalseGreater)
{
	ASSERT_FALSE(this->context.proto_v_lt(0, 9));
	ASSERT_FALSE(this->context.proto_v_lt(1, 1));
}

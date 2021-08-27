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
		this->context.protocol_version = {1, 2};
	}
};

TEST_F(TestCase_RequestContext, proto_v_eq_to_True)
{
	ASSERT_TRUE((this->context.protocol_version == net::ProtocolVersion{1, 2}));
}

TEST_F(TestCase_RequestContext, proto_v_eq_to_FalseGreater)
{
	ASSERT_FALSE((this->context.protocol_version == net::ProtocolVersion{1, 3}));
	ASSERT_FALSE((this->context.protocol_version == net::ProtocolVersion{2, 0}));
}

TEST_F(TestCase_RequestContext, proto_v_eq_to_FalseLess)
{
	ASSERT_FALSE((this->context.protocol_version == net::ProtocolVersion{0, 9}));
	ASSERT_FALSE((this->context.protocol_version == net::ProtocolVersion{1, 1}));
}

TEST_F(TestCase_RequestContext, proto_v_gte_TrueEquals)
{
	ASSERT_TRUE((this->context.protocol_version >= net::ProtocolVersion{1, 2}));
}

TEST_F(TestCase_RequestContext, proto_v_gte_TrueGreater)
{
	ASSERT_TRUE((this->context.protocol_version >= net::ProtocolVersion{1, 1}));
	ASSERT_TRUE((this->context.protocol_version >= net::ProtocolVersion{0, 9}));
}

TEST_F(TestCase_RequestContext, proto_v_gte_FalseLess)
{
	ASSERT_FALSE((this->context.protocol_version >= net::ProtocolVersion{1, 3}));
	ASSERT_FALSE((this->context.protocol_version >= net::ProtocolVersion{2, 0}));
}

TEST_F(TestCase_RequestContext, proto_v_lte_TrueEquals)
{
	ASSERT_TRUE((this->context.protocol_version <= net::ProtocolVersion{1, 2}));
}

TEST_F(TestCase_RequestContext, proto_v_lte_TrueLess)
{
	ASSERT_TRUE((this->context.protocol_version <= net::ProtocolVersion{1, 3}));
	ASSERT_TRUE((this->context.protocol_version <= net::ProtocolVersion{2, 0}));
}

TEST_F(TestCase_RequestContext, proto_v_lte_FalseGreater)
{
	ASSERT_FALSE((this->context.protocol_version <= net::ProtocolVersion{1, 1}));
	ASSERT_FALSE((this->context.protocol_version <= net::ProtocolVersion{0, 9}));
}

TEST_F(TestCase_RequestContext, proto_v_gt_True)
{
	ASSERT_TRUE((this->context.protocol_version > net::ProtocolVersion{1, 1}));
	ASSERT_TRUE((this->context.protocol_version > net::ProtocolVersion{0, 9}));
}

TEST_F(TestCase_RequestContext, proto_v_gt_FalseEquals)
{
	ASSERT_FALSE((this->context.protocol_version > net::ProtocolVersion{1, 2}));
}

TEST_F(TestCase_RequestContext, proto_v_gt_FalseLess)
{
	ASSERT_FALSE((this->context.protocol_version > net::ProtocolVersion{1, 3}));
	ASSERT_FALSE((this->context.protocol_version > net::ProtocolVersion{2, 0}));
}

TEST_F(TestCase_RequestContext, proto_v_lt_True)
{
	ASSERT_TRUE((this->context.protocol_version < net::ProtocolVersion{1, 3}));
	ASSERT_TRUE((this->context.protocol_version < net::ProtocolVersion{2, 0}));
}

TEST_F(TestCase_RequestContext, proto_v_lt_FalseEquals)
{
	ASSERT_FALSE((this->context.protocol_version < net::ProtocolVersion{1, 2}));
}

TEST_F(TestCase_RequestContext, proto_v_lt_FalseGreater)
{
	ASSERT_FALSE((this->context.protocol_version < net::ProtocolVersion{0, 9}));
	ASSERT_FALSE((this->context.protocol_version < net::ProtocolVersion{1, 1}));
}

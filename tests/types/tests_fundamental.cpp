/**
 * types/tests_fundamental.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <sstream>

#include <gtest/gtest.h>

#include "../../src/types/fundamental.h"

using namespace xw;


TEST(TestCase_Fundamental_Int, Test_Get)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_EQ(int_obj.get(), 10);
}

TEST(TestCase_Fundamental_Int, Test_HoldsType_True)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_TRUE(int_obj.holds_type<int>());
}

TEST(TestCase_Fundamental_Int, Test_HoldsType_False)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_FALSE(int_obj.holds_type<long>());
}

TEST(TestCase_Fundamental_Int, Test_OperatorBool_True)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_TRUE(int_obj.operator bool());
}

TEST(TestCase_Fundamental_Int, Test_OperatorBool_False)
{
	auto int_obj = types::Fundamental<int>(0);
	ASSERT_FALSE(int_obj.operator bool());
}

TEST(TestCase_Fundamental_Int, Test___str__)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_EQ(int_obj.__str__(), "10");
}

TEST(TestCase_Fundamental_Int, Test___repr__)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_EQ(int_obj.__repr__(), "10");
}

TEST(TestCase_Fundamental_Int, Test_AssignmentOperator)
{
	auto int_obj = types::Fundamental<int>(10);
	auto int_obj_copy = int_obj;
	ASSERT_EQ(int_obj.get(), int_obj_copy.get());
}

TEST(TestCase_Fundamental_Int, Test_OperatorPlus)
{
	auto left = types::Fundamental<int>(10);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left + right).get(), 10 + 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMinus)
{
	auto left = types::Fundamental<int>(10);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left - right).get(), 10 - 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorUnaryPlus)
{
	auto value = types::Fundamental<int>(-10);
	ASSERT_EQ((+value).get(), -10);
}

TEST(TestCase_Fundamental_Int, Test_OperatorUnaryMinus)
{
	auto value = types::Fundamental<int>(10);
	ASSERT_EQ((-value).get(), -10);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMultiply)
{
	auto left = types::Fundamental<int>(7);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left * right).get(), 7 * 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorDivision)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left / right).get(), 11 / 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMod)
{
	auto left = types::Fundamental<int>(35);
	auto right = types::Fundamental<int>(11);
	ASSERT_EQ((left % right).get(), 35 % 11);
}

TEST(TestCase_Fundamental_Int, Test_OperatorEquals_True)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(11);
	ASSERT_TRUE(left == right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorEquals_False)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_FALSE(left == right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorNotEquals_False)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(11);
	ASSERT_FALSE(left != right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorNotEquals_True)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_TRUE(left != right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLess_True)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(12);
	ASSERT_TRUE(left < right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLess_False)
{
	auto left = types::Fundamental<int>(37);
	auto right = types::Fundamental<int>(35);
	ASSERT_FALSE(left < right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLessEq_True)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(11);
	ASSERT_TRUE(left <= right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLessEq_False)
{
	auto left = types::Fundamental<int>(37);
	auto right = types::Fundamental<int>(35);
	ASSERT_FALSE(left <= right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorGreater_True)
{
	auto left = types::Fundamental<int>(12);
	auto right = types::Fundamental<int>(11);
	ASSERT_TRUE(left > right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorGreater_False)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_FALSE(left > right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorGreaterEq_True)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(11);
	ASSERT_TRUE(left >= right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorGreaterEq_False)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_FALSE(left >= right);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseAnd)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left & right).get(), 11 & 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorNot_True)
{
	auto value = types::Fundamental<int>(0);
	ASSERT_TRUE(!value);
}

TEST(TestCase_Fundamental_Int, Test_OperatorNot_False)
{
	auto value = types::Fundamental<int>(11);
	ASSERT_FALSE(!value);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseOr)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left | right).get(), 11 | 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseNot)
{
	auto value = types::Fundamental<int>(35);
	ASSERT_EQ((~value).get(), ~35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseXor)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ((left ^ right).get(), 11 ^ 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLeftShiftIntegral)
{
	auto value = types::Fundamental<int>(11);
	auto ic = 5;
	ASSERT_EQ((value << ic).get(), 11 << 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLeftShift)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(5);
	ASSERT_EQ((left << right).get(), 11 << 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorRightShiftIntegral)
{
	auto value = types::Fundamental<int>(11);
	auto ic = 5;
	ASSERT_EQ((value >> ic).get(), 11 >> 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorRightShift)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(5);
	ASSERT_EQ((left >> right).get(), 11 >> 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorOstream)
{
	auto value = types::Fundamental<int>(11);
	std::stringstream ss;
	ss << value;
	ASSERT_EQ(ss.str(), "11");
}

TEST(TestCase_Fundamental_Int, Test_OperatorAddEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(left.get(), 11);
	left += right;
	ASSERT_EQ(left.get(), 11 + 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorAddEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	float right = 35.4f;

	ASSERT_EQ(left.get(), 11);
	left += right;

	int expected = 11;
	expected += right;

	ASSERT_EQ(left.get(), expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorStar)
{
	auto value = types::Fundamental<int>(11);
	ASSERT_EQ(*value, 11);
}

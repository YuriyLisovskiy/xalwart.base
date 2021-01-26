/**
 * types/tests_fundamental_int.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/fundamental.h"

using namespace xw;


TEST(TestCase_Fundamental_Int, Test_Get)
{
	auto int_obj = types::Fundamental<int>(10);
	ASSERT_EQ(*int_obj, 10);
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

TEST(TestCase_Fundamental_Int, Test_FitTo)
{
	auto value = types::Fundamental<float>(10.5f);
	ASSERT_EQ(*value, 10.5f);

	auto fitted_value = value.fit_to<unsigned long>();
	ASSERT_EQ(*fitted_value, 10);
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
	ASSERT_EQ(int_obj.__repr__(), "xw::types::Fundamental<int>{10}");
}

TEST(TestCase_Fundamental_Int, Test_AssignmentOperator)
{
	auto int_obj = types::Fundamental<int>(10);
	auto int_obj_copy = int_obj;
	ASSERT_EQ(*int_obj, *int_obj_copy);
}

TEST(TestCase_Fundamental_Int, Test_OperatorPlus)
{
	auto left = types::Fundamental<int>(10);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*(left + right), 10 + 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMinus)
{
	auto left = types::Fundamental<int>(10);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*(left - right), 10 - 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorUnaryPlus)
{
	auto value = types::Fundamental<int>(-10);
	ASSERT_EQ(*(+value), -10);
}

TEST(TestCase_Fundamental_Int, Test_OperatorUnaryMinus)
{
	auto value = types::Fundamental<int>(10);
	ASSERT_EQ(*-value, -10);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMultiply)
{
	auto left = types::Fundamental<int>(7);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*(left * right), 7 * 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorDivision)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*(left / right), 11 / 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMod)
{
	auto left = types::Fundamental<int>(35);
	auto right = types::Fundamental<int>(11);
	ASSERT_EQ(*(left % right), 35 % 11);
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
	ASSERT_EQ(*(left & right), 11 & 35);
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
	ASSERT_EQ(*(left | right), 11 | 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseNot)
{
	auto value = types::Fundamental<int>(35);
	ASSERT_EQ(*~value, ~35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseXor)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*(left ^ right), 11 ^ 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLeftShiftIntegral)
{
	auto value = types::Fundamental<int>(11);
	auto ic = 5;
	ASSERT_EQ(*(value << ic), 11 << 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorLeftShift)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(5);
	ASSERT_EQ(*(left << right), 11 << 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorRightShiftIntegral)
{
	auto value = types::Fundamental<int>(11);
	auto ic = 5;
	ASSERT_EQ(*(value >> ic), 11 >> 5);
}

TEST(TestCase_Fundamental_Int, Test_OperatorRightShift)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(5);
	ASSERT_EQ(*(left >> right), 11 >> 5);
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
	ASSERT_EQ(*left, 11);
	left += right;
	ASSERT_EQ(*left, 11 + 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorAddEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	float right = 35.4f;

	ASSERT_EQ(*left, 11);
	left += right;

	int expected = 11;
	expected += right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorSubEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left -= right;
	ASSERT_EQ(*left, 11 - 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorSubEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	float right = 35.4f;

	ASSERT_EQ(*left, 11);
	left -= right;

	int expected = 11;
	expected -= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMulEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left *= right;
	ASSERT_EQ(*left, 11 * 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorMulEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	float right = 35.4f;

	ASSERT_EQ(*left, 11);
	left *= right;

	int expected = 11;
	expected *= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorDivEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left /= right;
	ASSERT_EQ(*left, 11 / 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorDivEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	float right = 35.4f;

	ASSERT_EQ(*left, 11);
	left /= right;

	int expected = 11;
	expected /= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorModEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left %= right;
	ASSERT_EQ(*left, 11 % 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorModEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	long long right = 7;

	ASSERT_EQ(*left, 11);
	left %= right;

	int expected = 11;
	expected %= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseAndEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left &= right;
	ASSERT_EQ(*left, 11 & 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseAndEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	signed right = 35;

	ASSERT_EQ(*left, 11);
	left &= right;

	int expected = 11;
	expected &= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseOrEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(35);
	ASSERT_EQ(*left, 11);
	left |= right;
	ASSERT_EQ(*left, 11 | 35);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseOrEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	unsigned right = 35;

	ASSERT_EQ(*left, 11);
	left |= right;

	int expected = 11;
	expected |= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseXorEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(4);
	ASSERT_EQ(*left, 11);
	left ^= right;
	ASSERT_EQ(*left, 11 ^ 4);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseXorEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	short right = 4;

	ASSERT_EQ(*left, 11);
	left ^= right;

	int expected = 11;
	expected ^= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseLeftShiftEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(3);
	ASSERT_EQ(*left, 11);
	left <<= right;
	ASSERT_EQ(*left, 11 << 3);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseLeftShiftEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	char right = 'c';

	ASSERT_EQ(*left, 11);
	left <<= right;

	int expected = 11;
	expected <<= right;

	ASSERT_EQ(*left, expected);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseRightShiftEq)
{
	auto left = types::Fundamental<int>(11);
	auto right = types::Fundamental<int>(2);
	ASSERT_EQ(*left, 11);
	left >>= right;
	ASSERT_EQ(*left, 11 >> 2);
}

TEST(TestCase_Fundamental_Int, Test_OperatorBitwiseRightShiftEqFundamental)
{
	auto left = types::Fundamental<int>(11);
	long right = 2;

	ASSERT_EQ(*left, 11);
	left >>= right;

	int expected = 11;
	expected >>= right;

	ASSERT_EQ(*left, expected);
}

/**
 * types/tests_fundamental.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/fundamental.h"

using namespace xw;

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_ShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto short_int_value2 = std::make_shared<types::Fundamental<short int>>(69);
	auto actual = short_int_value1->__cmp__(short_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_ShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto short_int_value2 = std::make_shared<types::Fundamental<short int>>(68);
	auto actual = short_int_value1->__cmp__(short_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_ShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto short_int_value2 = std::make_shared<types::Fundamental<short int>>(68);
	auto actual = short_int_value1->__cmp__(short_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_UnsignedShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto actual = short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_UnsignedShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_UnsignedShortInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Int)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(69);
	auto actual = short_int_value1->__cmp__(int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Int)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = short_int_value1->__cmp__(int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Int)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = short_int_value1->__cmp__(int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_UnsignedInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto actual = short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_UnsignedInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_UnsignedInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_LongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(69);
	auto actual = short_int_value1->__cmp__(long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_LongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = short_int_value1->__cmp__(long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_LongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = short_int_value1->__cmp__(long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_UnsignedLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_UnsignedLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_UnsignedLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_LongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_LongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_LongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_UnsignedLongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_UnsignedLongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_UnsignedLongLongInt)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_SignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = short_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_SignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = short_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_SignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = short_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_UnsignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_UnsignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_UnsignedChar)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Wchar_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Wchar_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Wchar_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Char8_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = short_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Char8_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = short_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Char8_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = short_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Char16_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = short_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Char16_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = short_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Char16_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = short_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Char32_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = short_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Char32_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = short_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Char32_T)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = short_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Float)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = short_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Float)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = short_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Float)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = short_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_Double)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = short_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_Double)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = short_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_Double)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = short_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Less_LongDouble)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = short_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Equals_LongDouble)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = short_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_ShortInt_Greater_LongDouble)
{
	auto short_int_value1 = std::make_shared<types::Fundamental<short int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = short_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_UnsignedShortInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_UnsignedShortInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_UnsignedShortInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto unsigned_short_int_value2 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_short_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Int)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Int)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Int)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_UnsignedInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_UnsignedInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_UnsignedInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_LongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_LongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_LongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_UnsignedLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_UnsignedLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_UnsignedLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_LongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_LongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_LongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_UnsignedLongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_UnsignedLongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_UnsignedLongLongInt)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_SignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_SignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_SignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_UnsignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_UnsignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_UnsignedChar)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Wchar_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Wchar_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Wchar_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Char8_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Char8_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Char8_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Char16_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Char16_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Char16_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Char32_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Char32_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Char32_T)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Float)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Float)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Float)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_Double)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_Double)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_Double)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Less_LongDouble)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = unsigned_short_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Equals_LongDouble)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedShortInt_Greater_LongDouble)
{
	auto unsigned_short_int_value1 = std::make_shared<types::Fundamental<unsigned short int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_short_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Int)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(69);
	auto actual = int_value1->__cmp__(int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Int)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = int_value1->__cmp__(int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Int)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto int_value2 = std::make_shared<types::Fundamental<int>>(68);
	auto actual = int_value1->__cmp__(int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_UnsignedInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto actual = int_value1->__cmp__(unsigned_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_UnsignedInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_UnsignedInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_LongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(69);
	auto actual = int_value1->__cmp__(long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_LongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = int_value1->__cmp__(long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_LongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = int_value1->__cmp__(long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_UnsignedLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_UnsignedLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_UnsignedLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_LongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_LongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_LongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_UnsignedLongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_UnsignedLongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_UnsignedLongLongInt)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_SignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_SignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_SignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_UnsignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_UnsignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_UnsignedChar)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Wchar_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Wchar_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Wchar_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Char8_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Char8_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Char8_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Char16_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Char16_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Char16_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Char32_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Char32_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Char32_T)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Float)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Float)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Float)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_Double)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_Double)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_Double)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Less_LongDouble)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Equals_LongDouble)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_Int_Greater_LongDouble)
{
	auto int_value1 = std::make_shared<types::Fundamental<int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_UnsignedInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto actual = unsigned_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_UnsignedInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_UnsignedInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto unsigned_int_value2 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_LongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(69);
	auto actual = unsigned_int_value1->__cmp__(long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_LongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_LongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_UnsignedLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_UnsignedLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_UnsignedLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_LongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = unsigned_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_LongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_LongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_UnsignedLongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_UnsignedLongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_UnsignedLongLongInt)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_SignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = unsigned_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_SignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_SignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_UnsignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = unsigned_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_UnsignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_UnsignedChar)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Wchar_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = unsigned_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Wchar_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Wchar_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Char8_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = unsigned_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Char8_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Char8_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Char16_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = unsigned_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Char16_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Char16_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Char32_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = unsigned_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Char32_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Char32_T)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Float)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = unsigned_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Float)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Float)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_Double)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = unsigned_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_Double)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_Double)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Less_LongDouble)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = unsigned_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Equals_LongDouble)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedInt_Greater_LongDouble)
{
	auto unsigned_int_value1 = std::make_shared<types::Fundamental<unsigned int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_LongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(69);
	auto actual = long_int_value1->__cmp__(long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_LongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = long_int_value1->__cmp__(long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_LongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto long_int_value2 = std::make_shared<types::Fundamental<long int>>(68);
	auto actual = long_int_value1->__cmp__(long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_UnsignedLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_UnsignedLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_UnsignedLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_LongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_LongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_LongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_UnsignedLongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_UnsignedLongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_UnsignedLongLongInt)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_SignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = long_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_SignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_SignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_UnsignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_UnsignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_UnsignedChar)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Wchar_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Wchar_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Wchar_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Char8_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = long_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Char8_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Char8_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Char16_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = long_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Char16_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Char16_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Char32_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = long_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Char32_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Char32_T)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Float)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = long_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Float)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = long_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Float)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = long_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_Double)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = long_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_Double)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = long_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_Double)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = long_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Less_LongDouble)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = long_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Equals_LongDouble)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = long_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongInt_Greater_LongDouble)
{
	auto long_int_value1 = std::make_shared<types::Fundamental<long int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = long_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_UnsignedLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_UnsignedLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_UnsignedLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto unsigned_long_int_value2 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_LongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_LongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_LongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_UnsignedLongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_UnsignedLongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_UnsignedLongLongInt)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_SignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_SignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_SignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_UnsignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_UnsignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_UnsignedChar)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Wchar_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Wchar_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Wchar_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Char8_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Char8_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Char8_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Char16_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Char16_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Char16_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Char32_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Char32_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Char32_T)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Float)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Float)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Float)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_Double)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_Double)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_Double)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Less_LongDouble)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = unsigned_long_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Equals_LongDouble)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongInt_Greater_LongDouble)
{
	auto unsigned_long_int_value1 = std::make_shared<types::Fundamental<unsigned long int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_LongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(69);
	auto actual = long_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_LongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = long_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_LongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto long_long_int_value2 = std::make_shared<types::Fundamental<long long int>>(68);
	auto actual = long_long_int_value1->__cmp__(long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_UnsignedLongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_UnsignedLongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_UnsignedLongLongInt)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_SignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_SignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_SignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_UnsignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_UnsignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_UnsignedChar)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Wchar_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Wchar_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Wchar_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Char8_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Char8_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Char8_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Char16_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Char16_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Char16_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Char32_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Char32_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Char32_T)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Float)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = long_long_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Float)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = long_long_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Float)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = long_long_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_Double)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = long_long_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_Double)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = long_long_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_Double)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = long_long_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Less_LongDouble)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Equals_LongDouble)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_LongLongInt_Greater_LongDouble)
{
	auto long_long_int_value1 = std::make_shared<types::Fundamental<long long int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_UnsignedLongLongInt)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_UnsignedLongLongInt)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_UnsignedLongLongInt)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto unsigned_long_long_int_value2 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_long_long_int_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_SignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_SignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_SignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_UnsignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_UnsignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_UnsignedChar)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Wchar_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Wchar_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Wchar_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Char8_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Char8_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Char8_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Char16_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Char16_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Char16_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Char32_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Char32_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Char32_T)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Float)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Float)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Float)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_Double)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_Double)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_Double)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Less_LongDouble)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = unsigned_long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Equals_LongDouble)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_UnsignedLongLongInt_Greater_LongDouble)
{
	auto unsigned_long_long_int_value1 = std::make_shared<types::Fundamental<unsigned long long int>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = unsigned_long_long_int_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_SignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(69);
	auto actual = signed_char_value1->__cmp__(signed_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_SignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = signed_char_value1->__cmp__(signed_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_SignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto signed_char_value2 = std::make_shared<types::Fundamental<signed char>>(68);
	auto actual = signed_char_value1->__cmp__(signed_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_UnsignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(69);
	auto actual = signed_char_value1->__cmp__(unsigned_char_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_UnsignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = signed_char_value1->__cmp__(unsigned_char_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_UnsignedChar)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto unsigned_char_value2 = std::make_shared<types::Fundamental<unsigned char>>(68);
	auto actual = signed_char_value1->__cmp__(unsigned_char_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Wchar_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(69);
	auto actual = signed_char_value1->__cmp__(wchar_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Wchar_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = signed_char_value1->__cmp__(wchar_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Wchar_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto wchar_t_value2 = std::make_shared<types::Fundamental<wchar_t>>(68);
	auto actual = signed_char_value1->__cmp__(wchar_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Char8_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(69);
	auto actual = signed_char_value1->__cmp__(char8_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Char8_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = signed_char_value1->__cmp__(char8_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Char8_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto char8_t_value2 = std::make_shared<types::Fundamental<char8_t>>(68);
	auto actual = signed_char_value1->__cmp__(char8_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Char16_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(69);
	auto actual = signed_char_value1->__cmp__(char16_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Char16_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = signed_char_value1->__cmp__(char16_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Char16_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto char16_t_value2 = std::make_shared<types::Fundamental<char16_t>>(68);
	auto actual = signed_char_value1->__cmp__(char16_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Char32_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(69);
	auto actual = signed_char_value1->__cmp__(char32_t_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Char32_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = signed_char_value1->__cmp__(char32_t_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Char32_T)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto char32_t_value2 = std::make_shared<types::Fundamental<char32_t>>(68);
	auto actual = signed_char_value1->__cmp__(char32_t_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Float)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(69);
	auto actual = signed_char_value1->__cmp__(float_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Float)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = signed_char_value1->__cmp__(float_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Float)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto float_value2 = std::make_shared<types::Fundamental<float>>(68);
	auto actual = signed_char_value1->__cmp__(float_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_Double)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(69);
	auto actual = signed_char_value1->__cmp__(double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_Double)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = signed_char_value1->__cmp__(double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_Double)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto double_value2 = std::make_shared<types::Fundamental<double>>(68);
	auto actual = signed_char_value1->__cmp__(double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Less_LongDouble)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(69);
	auto actual = signed_char_value1->__cmp__(long_double_value2.get());
	short expected = -1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Equals_LongDouble)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(68);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = signed_char_value1->__cmp__(long_double_value2.get());
	short expected = 0;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Cmp_SignedChar_Greater_LongDouble)
{
	auto signed_char_value1 = std::make_shared<types::Fundamental<signed char>>(69);
	auto long_double_value2 = std::make_shared<types::Fundamental<long double>>(68);
	auto actual = signed_char_value1->__cmp__(long_double_value2.get());
	short expected = 1;
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Bool)
{
	auto value = types::Fundamental<bool>(true);
	auto actual = value.__str__();
	auto expected = std::string("true");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_ShortInt)
{
	auto value = types::Fundamental<short int>(-34);
	auto actual = value.__str__();
	auto expected = std::string("-34");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_UnsignedShortInt)
{
	auto value = types::Fundamental<unsigned short int>(22);
	auto actual = value.__str__();
	auto expected = std::string("22");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Int)
{
	auto value = types::Fundamental<int>(-9876);
	auto actual = value.__str__();
	auto expected = std::string("-9876");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_UnsignedInt)
{
	auto value = types::Fundamental<unsigned int>(977);
	auto actual = value.__str__();
	auto expected = std::string("977");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_LongInt)
{
	auto value = types::Fundamental<long int>(-8765434567);
	auto actual = value.__str__();
	auto expected = std::string("-8765434567");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_UnsignedLongInt)
{
	auto value = types::Fundamental<unsigned long int>(34567898765);
	auto actual = value.__str__();
	auto expected = std::string("34567898765");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_LongLongInt)
{
	auto value = types::Fundamental<long long int>(-876565623456745);
	auto actual = value.__str__();
	auto expected = std::string("-876565623456745");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_UnsignedLongLongInt)
{
	auto value = types::Fundamental<unsigned long long int>(4567454567);
	auto actual = value.__str__();
	auto expected = std::string("4567454567");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_SignedChar)
{
	auto value = types::Fundamental<signed char>('h');
	auto actual = value.__str__();
	auto expected = std::string("h");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_UnsignedChar)
{
	auto value = types::Fundamental<unsigned char>('z');
	auto actual = value.__str__();
	auto expected = std::string("z");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Wchar_T)
{
	auto value = types::Fundamental<wchar_t>(234);
	auto actual = value.__str__();
	auto expected = std::string("234");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Char8_T)
{
	auto value = types::Fundamental<char8_t>(68);
	auto actual = value.__str__();
	auto expected = std::string("68");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Char16_T)
{
	auto value = types::Fundamental<char16_t>(222);
	auto actual = value.__str__();
	auto expected = std::string("222");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Char32_T)
{
	auto value = types::Fundamental<char32_t>(333);
	auto actual = value.__str__();
	auto expected = std::string("333");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Float)
{
	auto value = types::Fundamental<float>(34567.0f);
	auto actual = value.__str__();
	auto expected = std::string("34567.0");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_Double)
{
	auto value = types::Fundamental<double>(34567.35);
	auto actual = value.__str__();
	auto expected = std::string("34567.349999");
	ASSERT_EQ(actual, expected);
}

TEST(TestCase_Fundamental, Test_Str_LongDouble)
{
	auto value = types::Fundamental<long double>(345784567.00000);
	auto actual = value.__str__();
	auto expected = std::string("345784567.0");
	ASSERT_EQ(actual, expected);
}

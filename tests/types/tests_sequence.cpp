/**
 * types/tests_sequence.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/sequence.h"
#include "../../src/types/string.h"
#include "../../src/types/fundamental.h"

using namespace xw;


class TestCase_Sequence : public ::testing::Test
{
protected:
	types::Sequence<types::string> string_sequence;
	types::Sequence<types::fundamental<float>> empty_sequence;

	void SetUp() override
	{
		(*this->string_sequence).emplace_back("Hello");
		(*this->string_sequence).emplace_back("14.7");
	}
};

TEST_F(TestCase_Sequence, is_sequence_True)
{
	ASSERT_TRUE(this->string_sequence.is_sequence());
}

TEST_F(TestCase_Sequence, is_map_False)
{
	ASSERT_FALSE(this->string_sequence.is_map());
}

TEST_F(TestCase_Sequence, look_through)
{
	std::vector expected = {"Hello", "14.7"};
	this->string_sequence.look_through([expected](size_t i, const obj::Object* val)
	{
		ASSERT_EQ(expected[i], val->__str__());
	}, false);
}

TEST_F(TestCase_Sequence, look_through_Reversed)
{
	std::vector expected = {"14.7", "Hello"};
	this->string_sequence.look_through([expected](size_t i, const obj::Object* val)
	{
		ASSERT_EQ(expected[i], val->__str__());
	}, true);
}

TEST_F(TestCase_Sequence, empty_True)
{
	ASSERT_TRUE(this->empty_sequence.empty());
}

TEST_F(TestCase_Sequence, empty_False)
{
	ASSERT_FALSE(this->string_sequence.empty());
}

TEST_F(TestCase_Sequence, size)
{
	auto expected = 2;
	auto actual = this->string_sequence.size();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Sequence, operator_star)
{
	ASSERT_EQ((*this->string_sequence).size(), 2);
}

TEST_F(TestCase_Sequence, __cmp__EqualsTrue)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::sequence<types::string> seq2{types::string("Hello"), types::string("World")};
	ASSERT_EQ(seq1.__cmp__(&seq2), 0);
}

TEST_F(TestCase_Sequence, __cmp__EqualsFalse)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::sequence<types::string> seq2{types::string("World"), types::string("Hello")};
	ASSERT_NE(seq1.__cmp__(&seq2), 0);
}

TEST_F(TestCase_Sequence, __cmp__LessTrue)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("Home")};
	types::sequence<types::string> seq2{types::string("Hello"), types::string("World")};
	ASSERT_EQ(seq1.__cmp__(&seq2), -1);
}

TEST_F(TestCase_Sequence, __cmp__LessFalse)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::sequence<types::string> seq2{types::string("Hello"), types::string("World")};
	ASSERT_NE(seq1.__cmp__(&seq2), -1);
}

TEST_F(TestCase_Sequence, __cmp__GreaterTrue)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::sequence<types::string> seq2{types::string("Hello"), types::string("Home")};
	ASSERT_EQ(seq1.__cmp__(&seq2), 1);
}

TEST_F(TestCase_Sequence, __cmp__GreaterFalse)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::sequence<types::string> seq2{types::string("Hello"), types::string("World")};
	ASSERT_NE(seq1.__cmp__(&seq2), 1);
}

TEST_F(TestCase_Sequence, __cmp__ThrowsIncompatibleTypes)
{
	types::sequence<types::string> seq1{types::string("Hello"), types::string("World")};
	types::fundamental<int> s2(256);
	ASSERT_THROW(auto _ = seq1.__cmp__(&s2), TypeError);
}

TEST_F(TestCase_Sequence, __str__)
{
	std::string expected = "{Hello, 14.7}";
	auto actual = this->string_sequence.__str__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Sequence, __str__Empty)
{
	std::string expected = "{}";
	auto actual = this->empty_sequence.__str__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Sequence, __repr__)
{
	std::string expected = "{'Hello', '14.7'}";
	auto actual = this->string_sequence.__repr__();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_Sequence, __repr__Empty)
{
	std::string expected = "{}";
	auto actual = this->empty_sequence.__repr__();
	ASSERT_EQ(expected, actual);
}

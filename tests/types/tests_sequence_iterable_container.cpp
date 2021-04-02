/**
 * types/tests_sequence_iterable_container.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/iterable.h"
#include "../../src/types/string.h"
#include "../../src/types/fundamental.h"

using namespace xw;


class TestCase_SequenceIterableContainer : public ::testing::Test
{
protected:
	types::SequenceIterableContainer<std::vector<std::shared_ptr<obj::Object>>> sequence;
	types::SequenceIterableContainer<std::vector<std::shared_ptr<obj::Object>>> empty_sequence;

	void SetUp() override
	{
		this->sequence.value().push_back(std::make_shared<types::String>("Hello"));
		this->sequence.value().push_back(std::make_shared<types::Fundamental<float>>(14.7f));
	}
};

TEST_F(TestCase_SequenceIterableContainer, look_through)
{
	std::vector expected = {"Hello", "14.7"};
	this->sequence.look_through([expected](size_t i, const std::shared_ptr<obj::Object>& val)
	{
		ASSERT_EQ(expected[i], val->__str__());
	}, false);
}

TEST_F(TestCase_SequenceIterableContainer, look_through_Reversed)
{
	std::vector expected = {"14.7", "Hello"};
	this->sequence.look_through([expected](size_t i, const std::shared_ptr<obj::Object>& val)
	{
		ASSERT_EQ(expected[i], val->__str__());
	}, true);
}

TEST_F(TestCase_SequenceIterableContainer, empty_True)
{
	ASSERT_TRUE(this->empty_sequence.empty());
}

TEST_F(TestCase_SequenceIterableContainer, empty_False)
{
	ASSERT_FALSE(this->sequence.empty());
}

TEST_F(TestCase_SequenceIterableContainer, size)
{
	auto expected = 2;
	auto actual = this->sequence.size();
	ASSERT_EQ(expected, actual);
}

TEST_F(TestCase_SequenceIterableContainer, value)
{
	ASSERT_EQ(this->sequence.value().size(), 2);
}

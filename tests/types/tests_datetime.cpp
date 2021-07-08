/**
 * types/tests_datetime.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include <gtest/gtest.h>

#include "../../src/types/datetime.h"

using namespace xw;


class TestCase_Datetime : public ::testing::Test
{
protected:
	dt::Datetime now;
	types::Date date;
	types::Time time;
	types::Datetime datetime;

	void SetUp() override
	{
		this->now = dt::Datetime::now(std::make_shared<dt::Timezone>(dt::Timezone::UTC));
		this->date = types::Date(this->now.date());
		this->time = types::Time(this->now.time());
		this->datetime = types::Datetime(this->now);
	}
};

TEST_F(TestCase_Datetime, __str__Date)
{
	ASSERT_EQ(this->now.date().str(), this->date.__str__());
}

TEST_F(TestCase_Datetime, __repr__Date)
{
	ASSERT_EQ("\"" + this->now.date().str() + "\"", this->date.__repr__());
}

TEST_F(TestCase_Datetime, __cmp__Date_less)
{
	auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_EQ(this->date.__cmp__(&other), -1);
}

TEST_F(TestCase_Datetime, __cmp__Date_eq)
{
	auto other = types::Date(this->now.date());
	ASSERT_EQ(this->date.__cmp__(&other), 0);
}

TEST_F(TestCase_Datetime, __cmp__Date_greater)
{
	auto other = types::Date(this->now.date() - dt::Timedelta(1));
	ASSERT_EQ(this->date.__cmp__(&other), 1);
}

TEST_F(TestCase_Datetime, operator_bool_Date)
{
	ASSERT_TRUE((bool)this->date);
}

TEST_F(TestCase_Datetime, operator_not_Date)
{
	ASSERT_FALSE(!this->date);
}

TEST_F(TestCase_Datetime, operator_equals_Date_True)
{
	const auto other = types::Date(this->now.date());
	ASSERT_TRUE(this->date == other);
}

TEST_F(TestCase_Datetime, operator_equals_Date_False)
{
	const auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_FALSE(this->date == other);
}

TEST_F(TestCase_Datetime, operator_not_equals_Date_True)
{
	const auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_TRUE(this->date != other);
}

TEST_F(TestCase_Datetime, operator_not_equals_Date_False)
{
	const auto other = types::Date(this->now.date());
	ASSERT_FALSE(this->date != other);
}

TEST_F(TestCase_Datetime, operator_less_Date_True)
{
	const auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_TRUE(this->date < other);
}

TEST_F(TestCase_Datetime, operator_less_Date_False)
{
	const auto other = types::Date(this->now.date());
	ASSERT_FALSE(this->date < other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Date_True)
{
	auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_TRUE(this->date <= other);

	other = types::Date(this->now.date());
	ASSERT_TRUE(this->date <= other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Date_False)
{
	const auto other = types::Date(this->now.date() - dt::Timedelta(1));
	ASSERT_FALSE(this->date <= other);
}

TEST_F(TestCase_Datetime, operator_greater_Date_True)
{
	const auto other = types::Date(this->now.date() - dt::Timedelta(1));
	ASSERT_TRUE(this->date > other);
}

TEST_F(TestCase_Datetime, operator_greater_Date_False)
{
	const auto other = types::Date(this->now.date());
	ASSERT_FALSE(this->date > other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Date_True)
{
	auto other = types::Date(this->now.date() - dt::Timedelta(1));
	ASSERT_TRUE(this->date >= other);

	other = types::Date(this->now.date());
	ASSERT_TRUE(this->date >= other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Date_False)
{
	const auto other = types::Date(this->now.date() + dt::Timedelta(1));
	ASSERT_FALSE(this->date >= other);
}

TEST_F(TestCase_Datetime, __str__Time)
{
	ASSERT_EQ(this->now.time().str(), this->time.__str__());
}

TEST_F(TestCase_Datetime, __repr__Time)
{
	ASSERT_EQ("\"" + this->now.time().str() + "\"", this->time.__repr__());
}

TEST_F(TestCase_Datetime, __cmp__Time_less)
{
	auto t = this->now.time();
	if (t.hour() != 23)
	{
		auto other = types::Time(
			dt::Time(t.hour() + 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_EQ(this->time.__cmp__(&other), -1);
	}
}

TEST_F(TestCase_Datetime, __cmp__Time_eq)
{
	auto t = this->now.time();
	auto other = types::Time(this->now.time());
	ASSERT_EQ(this->time.__cmp__(&other), 0);
}

TEST_F(TestCase_Datetime, __cmp__Time_greater)
{
	auto t = this->now.time();
	if (t.hour() != 0)
	{
		auto other = types::Time(
			dt::Time(t.hour() - 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_EQ(this->time.__cmp__(&other), 1);
	}
}

TEST_F(TestCase_Datetime, operator_bool_Time)
{
	ASSERT_TRUE((bool)this->time);
}

TEST_F(TestCase_Datetime, operator_not_Time)
{
	ASSERT_FALSE(!this->time);
}

TEST_F(TestCase_Datetime, operator_equals_Time_True)
{
	auto other = types::Time(this->now.time());
	ASSERT_TRUE(this->time == other);
}

TEST_F(TestCase_Datetime, operator_equals_Time_False)
{
	auto t = this->now.time();
	if (t.hour() != 0)
	{
		auto other = types::Time(
			dt::Time(t.hour() - 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_FALSE(this->time == other);
	}
}

TEST_F(TestCase_Datetime, operator_not_equals_Time_True)
{
	auto t = this->now.time();
	if (t.hour() != 23)
	{
		auto other = types::Time(
			dt::Time(t.hour() + 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_TRUE(this->time != other);
	}
}

TEST_F(TestCase_Datetime, operator_not_equals_Time_False)
{
	const auto other = types::Time(this->now.time());
	ASSERT_FALSE(this->time != other);
}

TEST_F(TestCase_Datetime, operator_less_Time_True)
{
	auto t = this->now.time();
	if (t.hour() != 23)
	{
		auto other = types::Time(
			dt::Time(t.hour() + 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_TRUE(this->time < other);
	}
}

TEST_F(TestCase_Datetime, operator_less_Time_False)
{
	const auto other = types::Time(this->now.time());
	ASSERT_FALSE(this->time < other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Time_True)
{
	auto t = this->now.time();
	if (t.hour() != 23)
	{
		auto other = types::Time(
			dt::Time(t.hour() + 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_TRUE(this->time <= other);
	}

	auto other = types::Time(this->now.time());
	ASSERT_TRUE(this->time <= other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Time_False)
{
	auto t = this->now.time();
	if (t.hour() != 0)
	{
		auto other = types::Time(
			dt::Time(t.hour() - 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_FALSE(this->time <= other);
	}
}

TEST_F(TestCase_Datetime, operator_greater_Time_True)
{
	auto t = this->now.time();
	if (t.hour() != 0)
	{
		auto other = types::Time(
			dt::Time(t.hour() - 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_TRUE(this->time > other);
	}
}

TEST_F(TestCase_Datetime, operator_greater_Time_False)
{
	const auto other = types::Time(this->now.time());
	ASSERT_FALSE(this->time > other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Time_True)
{
	auto t = this->now.time();
	if (t.hour() != 0)
	{
		auto other = types::Time(
			dt::Time(t.hour() - 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_TRUE(this->time >= other);
	}

	auto other = types::Time(this->now.time());
	ASSERT_TRUE(this->time >= other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Time_False)
{
	auto t = this->now.time();
	if (t.hour() != 23)
	{
		auto other = types::Time(
			dt::Time(t.hour() + 1, t.minute(), t.second(), t.microsecond(), nullptr, t.fold())
		);
		ASSERT_FALSE(this->time >= other);
	}
}

TEST_F(TestCase_Datetime, __str__Datetime)
{
	ASSERT_EQ(this->now.str(), this->datetime.__str__());
}

TEST_F(TestCase_Datetime, __repr__Datetime)
{
	ASSERT_EQ("\"" + this->now.str() + "\"", this->datetime.__repr__());
}

TEST_F(TestCase_Datetime, __cmp__Datetime_less)
{
	auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_EQ(this->datetime.__cmp__(&other), -1);
}

TEST_F(TestCase_Datetime, __cmp__Datetime_eq)
{
	auto other = types::Datetime(this->now);
	ASSERT_EQ(this->datetime.__cmp__(&other), 0);
}

TEST_F(TestCase_Datetime, __cmp__Datetime_greater)
{
	auto other = types::Datetime(this->now - dt::Timedelta(1));
	ASSERT_EQ(this->datetime.__cmp__(&other), 1);
}

TEST_F(TestCase_Datetime, operator_bool_Datetime)
{
	ASSERT_TRUE((bool)this->datetime);
}

TEST_F(TestCase_Datetime, operator_not_Datetime)
{
	ASSERT_FALSE(!this->datetime);
}

TEST_F(TestCase_Datetime, operator_equals_Datetime_True)
{
	const auto other = types::Datetime(this->now);
	ASSERT_TRUE(this->datetime == other);
}

TEST_F(TestCase_Datetime, operator_equals_Datetime_False)
{
	const auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_FALSE(this->datetime == other);
}

TEST_F(TestCase_Datetime, operator_not_equals_Datetime_True)
{
	const auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_TRUE(this->datetime != other);
}

TEST_F(TestCase_Datetime, operator_not_equals_Datetime_False)
{
	const auto other = types::Datetime(this->now);
	ASSERT_FALSE(this->datetime != other);
}

TEST_F(TestCase_Datetime, operator_less_Datetime_True)
{
	const auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_TRUE(this->datetime < other);
}

TEST_F(TestCase_Datetime, operator_less_Datetime_False)
{
	const auto other = types::Datetime(this->now);
	ASSERT_FALSE(this->datetime < other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Datetime_True)
{
	auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_TRUE(this->datetime <= other);

	other = types::Datetime(this->now);
	ASSERT_TRUE(this->datetime <= other);
}

TEST_F(TestCase_Datetime, operator_less_or_equals_Datetime_False)
{
	const auto other = types::Datetime(this->now - dt::Timedelta(1));
	ASSERT_FALSE(this->datetime <= other);
}

TEST_F(TestCase_Datetime, operator_greater_Datetime_True)
{
	const auto other = types::Datetime(this->now - dt::Timedelta(1));
	ASSERT_TRUE(this->datetime > other);
}

TEST_F(TestCase_Datetime, operator_greater_Datetime_False)
{
	const auto other = types::Datetime(this->now);
	ASSERT_FALSE(this->datetime > other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Datetime_True)
{
	auto other = types::Datetime(this->now - dt::Timedelta(1));
	ASSERT_TRUE(this->datetime >= other);

	other = types::Datetime(this->now);
	ASSERT_TRUE(this->datetime >= other);
}

TEST_F(TestCase_Datetime, operator_greater_or_equals_Datetime_False)
{
	const auto other = types::Datetime(this->now + dt::Timedelta(1));
	ASSERT_FALSE(this->datetime >= other);
}

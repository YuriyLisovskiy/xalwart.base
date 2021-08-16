/**
 * types/datetime.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrappers for `dt::Date`, `dt::Time` and `dt::Datetime`
 * for rendering in templates.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../datetime.h"
#include "../object/object.h"


__TYPES_BEGIN__

template <typename T>
concept date_time_type = std::is_same_v<T, dt::Date> ||
	std::is_same_v<T, dt::Time> ||
	std::is_same_v<T, dt::Datetime>;

template <date_time_type DateTimeT>
class DatetimeBaseImplementation : public obj::Object
{
protected:
	std::string format;
	DateTimeT value;

public:

	// Default constructor.
	DatetimeBaseImplementation() = default;

	// Constructs Date from `DateTimeT`
	inline explicit DatetimeBaseImplementation(DateTimeT v) : value(std::move(v))
	{
	}

	// Constructs Date from `DateTimeT` and string format.
	inline DatetimeBaseImplementation(DateTimeT v, std::string format) :
		value(std::move(v)), format(std::move(format))
	{
	}

	// Returns an internal `DateTimeT` value as string.
	[[nodiscard]]
	inline std::string __str__() const override
	{
		return this->format.empty() ? this->value.str() : this->value.strftime(format);
	}

	// Returns an internal `DateTimeT` value wrapped to quotes.
	[[nodiscard]]
	inline std::string __repr__() const override
	{
		return "\"" + this->__str__() + "\"";
	}

	// Compares two objects.
	//
	// Throws `TypeError` if `other` is not `DateTimeT` object.
	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const DatetimeBaseImplementation<DateTimeT>*>(other))
		{
			if (this->value < other_v->value)
			{
				return -1;
			}

			return this->value == other_v->value ? 0 : 1;
		}

		throw TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() +
			"' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	// Returns `true` by default.
	inline explicit operator bool () const override
	{
		return true;
	}

	// Returns `false` by default.
	inline bool operator! () const override
	{
		return false;
	}

	// Returns an address to internal `dt::Date` object.
	inline dt::Date& operator* ()
	{
		return this->value;
	}

	// Operator equals.
	inline bool operator== (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value == other.value;
	}

	// Operator not equals.
	inline bool operator!= (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value != other.value;
	}

	// Operator less.
	inline bool operator< (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value < other.value;
	}

	// Operator less or equals.
	inline bool operator<= (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value <= other.value;
	}

	// Operator greater.
	inline bool operator> (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value > other.value;
	}

	// Operator greater or equals.
	inline bool operator>= (const DatetimeBaseImplementation<DateTimeT>& other) const
	{
		return this->value >= other.value;
	}
};

class Date final : public DatetimeBaseImplementation<dt::Date>
{
public:

	// Default constructor.
	Date() = default;

	// Constructs Date from `dt::Date`
	inline explicit Date(const dt::Date& date) : DatetimeBaseImplementation<dt::Date>(date)
	{
	}

	// Constructs Date from `dt::Date` and string format.
	inline Date(const dt::Date& date, const std::string& format) :
		DatetimeBaseImplementation<dt::Date>(date, format)
	{
	}
};

class Time final : public DatetimeBaseImplementation<dt::Time>
{
public:

	// Default constructor.
	Time() = default;

	// Constructs Time from `dt::Time`
	inline explicit Time(const dt::Time& time) : DatetimeBaseImplementation<dt::Time>(time)
	{
	}

	// Constructs Time from `dt::Time` and string format.
	inline Time(const dt::Time& time, const std::string& format) :
		DatetimeBaseImplementation<dt::Time>(time, format)
	{
	}
};

class Datetime final : public DatetimeBaseImplementation<dt::Datetime>
{
public:

	// Default constructor.
	Datetime() = default;

	// Constructs Datetime from `dt::Datetime`.
	inline Datetime(const dt::Datetime& datetime) : DatetimeBaseImplementation<dt::Datetime>(datetime)
	{
	}

	// Constructs Datetime from `dt::Datetime` and string format.
	inline Datetime(const dt::Datetime& datetime, const std::string& format) :
		DatetimeBaseImplementation<dt::Datetime>(datetime, format)
	{
	}
};

using date = Date;
using time = Time;
using datetime = Datetime;

__TYPES_END__

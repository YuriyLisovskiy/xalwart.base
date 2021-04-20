/**
 * utility.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Core utilities.
 */

#pragma once

// C++ libraries.
#include <cstring>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./datetime.h"
#include "./exceptions.h"


__UTILITY_BEGIN__

// Checks if sequence contains item or not.
//
// `begin`: iterator to the beginning of the sequence.
// `end`: iterator to the end of the sequence.
// `item`: item to check.
//
// Returns `true` if sequence contains item, `false` otherwise.
// Returns `false` if the range is empty.
template <typename ItemT, typename IteratorT>
inline bool contains(const ItemT& item, IteratorT begin, IteratorT end)
{
	return std::any_of(begin, end, [item](const auto& o) -> bool {
		return o == item;
	});
}

// Checks if initializer list contains item or not.
//
// `item`: item to check.
// `sequence`: initializer list of items where to search for.
//
// Returns `true` if sequence contains item, `false` otherwise.
// Returns `false` if the range is empty.
template <typename ItemT>
bool contains(const ItemT& item, const std::initializer_list<ItemT>& sequence)
{
	return contains(item, sequence.begin(), sequence.end());
}

// Searches for index of item in given range.
//
// `begin`: iterator to the beginning of the sequence.
// `end`: iterator to the end of the sequence.
// `item`: item to search.
//
// Returns non-negative `long` integer if the range contains `item`,
// `-1` otherwise.
template <typename ItemT, typename IteratorT>
inline long index_of(const ItemT& item, IteratorT begin, IteratorT end)
{
	auto it = std::find(begin, end, item);
	if (it == end)
	{
		return -1;
	}

	return std::distance(begin, it);
}

// Converts type name to full name.
//
// `name`: result of 'typeid(...).name()' call.
//
// Returns full name.
extern std::string demangle(const char* name);

// Turn a datetime into a date string as specified in RFC 2822.
//
// If usegmt is True, dt must be an aware datetime with an offset of zero.  In
// this case 'GMT' will be rendered instead of the normal +0000 required by
// RFC2822.  This is to support HTTP headers involving date stamps.
//
// `dt`: pointer to datetime object.
// `use_gmt`: indicates whether to use GMT or not.
//
// Returns formatted datetime as `std::string`.
extern std::string format_datetime(
	const dt::Datetime* dt, bool use_gmt = false
);

// Returns a date string as specified by RFC 2822, e.g.:
//
// Fri, 09 Nov 2001 01:08:47 -0000
//
// Optional timeval if given is a floating point time value as accepted by
// gmtime() and localtime(), otherwise the current time is used.
//
// Optional localtime is a flag that when True, interprets timeval, and
// returns a date relative to the local timezone instead of UTC, properly
// taking daylight savings time into account.
//
// Optional argument usegmt means that the timezone is written out as
// an ascii string, not numeric one (so "GMT" instead of "+0000"). This
// is needed for HTTP, and is only used when localtime==false.
//
// `time_val`: time structure to format.
// `local_time`: indicates whether `time_val` is local time or not.
// `use_gmt`: indicates whether to use GMT or not.
//
// Returns formatted datetime as `std::string`.
extern std::string format_date(
	time_t time_val, bool local_time = false, bool use_gmt = false
);

// Formats datetime from 'dt::time_tuple' and zone name as specified by RFC 2822, e.g.:
//
// Fri, 09 Nov 2001 01:08:47 -0000
//
// `time_tuple`: datetime struct to format.
// `zone`: time zone name.
//
// Returns formatted datetime as `std::string`.
extern std::string _format_timetuple_and_zone(
	dt::tm_tuple* time_tuple, const std::string& zone
);

template <typename T>
T* require_non_null(T* p, const char* message)
{
	if (p == nullptr)
	{
		throw NullPointerException(message, _ERROR_DETAILS_);
	}

	return p;
}

template <typename T>
T* require_non_null(T* p)
{
	return require_non_null<T>(
		p, ("pointer to object of type '" + demangle(typeid(T).name()) + "' is nullptr").c_str()
	);
}

__UTILITY_END__

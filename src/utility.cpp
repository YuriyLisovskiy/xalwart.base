/**
 * utility.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./utility.h"

// C++ libraries.
#include <cassert>

#ifdef _MSC_VER
#include <stdexcept>
#else
#include <cxxabi.h>
#endif

// Base libraries.
#include "./string_utils.h"


__UTILITY_BEGIN__

// Statuses:
// 0 - operation succeeded
// 1 - a memory allocation failure occurred
// 2 - mangled_name is not a valid name under the C++ ABI mangling rules
// 3 - one of the arguments is invalid
std::string demangle(const char* name)
{
#ifdef _MSC_VER
	return str::ltrim(name, "class");
#else
	int status = -4;
	std::unique_ptr<char, void(*)(void*)> res {
		abi::__cxa_demangle(name, nullptr, nullptr, &status),
		std::free
	};

	return status == 0 ? res.get() : name;
#endif
}

std::string format_datetime(const dt::Datetime* dt, bool use_gmt)
{
	assert(dt != nullptr);
	auto now = dt->time_tuple();
	std::string zone;
	if (use_gmt)
	{
		if (!dt->tz_info() || *dt->tz_info() != dt::Timezone::UTC)
		{
			throw std::invalid_argument("use_gmt option requires a UTC datetime");
		}

		zone = "GMT";
	}
	else if (!dt->tz_info())
	{
		zone = "-0000";
	}
	else
	{
		zone = dt->strftime("%z");
	}

	return _format_timetuple_and_zone(&now, zone);
}

std::string format_date(time_t time_val, bool local_time, bool use_gmt)
{
	// Note: we cannot use strftime() because that honors the locale and RFC
	// 2822 requires that day and month names be the English abbreviations.
	if (!time_val)
	{
		time_val = dt::_time();
	}

	std::shared_ptr<dt::Datetime> dt;
	if (local_time || use_gmt)
	{
		dt = std::make_shared<dt::Datetime>(
			dt::Datetime::from_timestamp(time_val, std::make_shared<dt::Timezone>(dt::Timezone::UTC))
		);
	}
	else
	{
		dt = std::make_shared<dt::Datetime>(dt::Datetime::utc_from_timestamp(time_val));
	}

	if (local_time)
	{
		*dt = dt->as_timezone();
		use_gmt = false;
	}

	return format_datetime(dt.get(), use_gmt);
}

std::string _format_timetuple_and_zone(dt::tm_tuple* time_tuple, const std::string& zone)
{
	return dt::_DAY_NAMES[time_tuple->tm_wday+1] + ", " +
		dt::_lf(time_tuple->tm_mday) + " " +
		dt::_MONTH_NAMES[time_tuple->tm_mon] + " " +
		dt::_lf(time_tuple->tm_year, 4) + " " +
		dt::_lf(time_tuple->tm_hour) + ":" +
		dt::_lf(time_tuple->tm_min) + ":" +
		dt::_lf(time_tuple->tm_sec) + " " +
		zone;
}

__UTILITY_END__

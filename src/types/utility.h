/**
 * types/utility.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Types utilities.
 */

#pragma once

// C++ libraries
#include <deque>
#include <list>
#include <forward_list>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../utility.h"
#include "./fundamental.h"
#include "./string.h"
#include "./datetime.h"
#include "./sequence.h"
#include "./map.h"


__TYPES_BEGIN__

// Converts any iterable container to 'xw::types::Sequence'.
template <object_based_iterator IteratorT>
Sequence<iterator_v_type<IteratorT>> to_sequence(IteratorT begin, IteratorT end)
{
	using T = iterator_v_type<IteratorT>;
	Sequence<T> result;
	*result = std::list<T>(begin, end);
	return result;
}

// Converts fundamentals, 'std::string', 'const char*', 'xw::dt::Date',
// 'xw::dt::Time', 'xw::dt::Datetime' or 'xw::obj::Object'-based instances
// to 'std::shared_ptr<const xw::obj::Object>'.
template <typename T>
std::shared_ptr<const obj::Object> to_object(const T& value)
{
	if constexpr (std::is_fundamental_v<T>)
	{
		return std::make_shared<Fundamental<T>>(value);
	}
	else if constexpr (std::is_same_v<T, std::string> || std::is_same_v<T, const char*>)
	{
		return std::make_shared<types::String>(value);
	}
	else if constexpr (std::is_same_v<T, dt::Date>)
	{
		return std::make_shared<Date>(value);
	}
	else if constexpr (std::is_same_v<T, dt::Time>)
	{
		return std::make_shared<Time>(value);
	}
	else if constexpr (std::is_same_v<T, dt::Datetime>)
	{
		return std::make_shared<Datetime>(value);
	}
	else if constexpr (std::is_base_of_v<obj::Object, T>)
	{
		return std::make_shared<T>(value);
	}

	throw TypeError(
		"unable to convert value, '" + util::demangle(typeid(T).name()) + "' type is not supported",
		_ERROR_DETAILS_
	);
}

// Converts 'std::array' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T, std::size_t Nm>
std::shared_ptr<const obj::Object> to_object(const std::array<T, Nm>& v)
{
	return std::make_shared<Sequence<T>>(to_sequence(v.begin(), v.end()));
}

// Converts 'std::vector' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T>
std::shared_ptr<const obj::Object> to_object(const std::vector<T>& v)
{
	return std::make_shared<Sequence<T>>(to_sequence(v.begin(), v.end()));
}

// Converts 'std::deque' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T>
std::shared_ptr<const obj::Object> to_object(const std::deque<T>& v)
{
	return std::make_shared<Sequence<T>>(to_sequence(v.begin(), v.end()));
}

// Converts 'std::forward_list' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T>
std::shared_ptr<const obj::Object> to_object(const std::forward_list<T>& v)
{
	return std::make_shared<Sequence<T>>(to_sequence(v.begin(), v.end()));
}

// Converts 'std::list' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T>
std::shared_ptr<const obj::Object> to_object(const std::list<T>& v)
{
	return std::make_shared<Sequence<T>>(to_sequence(v.begin(), v.end()));
}

// Converts 'xw::types::Sequence' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type T>
std::shared_ptr<const obj::Object> to_object(const Sequence<T>& v)
{
	return std::make_shared<Sequence<T>>(v);
}

// Converts 'std::map' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type KeyT, object_based_type ValT>
std::shared_ptr<const obj::Object> to_object(const std::map<KeyT, ValT>& v)
{
	return std::make_shared<Map<KeyT, ValT>>(v);
}

// Converts 'xw::types::Map' to 'std::shared_ptr<const xw::obj::Object>'
template <object_based_type KeyT, object_based_type ValT>
std::shared_ptr<const obj::Object> to_object(const Map<KeyT, ValT>& v)
{
	return std::make_shared<Map<KeyT, ValT>>(v);
}

__TYPES_END__

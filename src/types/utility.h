/**
 * types/utility.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Types utilities.
 */

#pragma once

// C++ libraries.
// TODO

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../utility.h"
#include "./fundamental.h"
#include "./string.h"
#include "./datetime.h"
#include "./sequence.h"
//#include "./map.h"


__TYPES_BEGIN__

template <object_based_iterator_type_c IteratorT>
Sequence<iterator_v_type<IteratorT>> to_sequence(IteratorT begin, IteratorT end)
{
	using T = iterator_v_type<IteratorT>;
	Sequence<T> result;
	*result = std::list<T>(begin, end);
	return result;
}

// TESTME: to_object
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

// TODO add `to_object` function for `Sequence` and `Map`.

__TYPES_END__

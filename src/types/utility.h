/**
 * types/utility.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <type_traits>

// Module definitions.
#include "./_def_.h"


__TYPES_BEGIN__

template <typename Base, typename Derived>
constexpr bool is_base_of()
{
	if constexpr (std::is_pointer<Base>::value && std::is_pointer<Derived>::value)
	{
		using T1 = typename std::remove_pointer<Base>::type;
		using T2 = typename std::remove_pointer<Derived>::type;
		return std::is_base_of<T1, T2>::value;
	}

	if constexpr (std::is_pointer<Base>::value )
	{
		using T1 = typename std::remove_pointer<Base>::type;
		return std::is_base_of<T1, Derived>::value;
	}

	if constexpr (std::is_pointer<Derived>::value)
	{
		using T2 = typename std::remove_pointer<Derived>::type;
		return std::is_base_of<Base, T2>::value;
	}

	return std::is_base_of<Base, Derived>::value;
}

template <typename Derived, typename Base>
constexpr bool is_base_of(const Base&)
{
	return is_base_of<Base, Derived>();
}

template <typename LeftT, typename RightT>
constexpr bool is_instance(const RightT& value)
{
	if constexpr (std::is_pointer<RightT>::value)
	{
		using T = typename std::remove_pointer<RightT>::type;
		return std::is_same<LeftT, T>::value || std::is_base_of<LeftT, T>::value;
	}

	return std::is_same<LeftT, RightT>::value || std::is_base_of<LeftT, RightT>::value;
}

__TYPES_END__

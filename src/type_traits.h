/**
 * type_traits.h
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


__CORE_BEGIN__

template <typename T, class = void>
struct has_operator_bool: std::false_type{};

template <typename T>
struct has_operator_bool<T, std::void_t<decltype(std::declval<T>().operator bool())>> : std::true_type{};

__CORE_END__

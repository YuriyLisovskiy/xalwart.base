/**
 * str.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__MAIN_NAMESPACE_BEGIN__

using string = std::string;

template<size_t N>
struct fixed_string
{
	char value[N + 1]{};
	size_t length = N;

	constexpr fixed_string(char const* s)
	{
		for (size_t i = 0; i < N; i++)
		{
			this->value[i] = s[i];
		}
	}

	constexpr explicit operator char const* () const
	{
		return this->value;
	}
};

template<size_t N>
fixed_string(char const (&)[N]) -> fixed_string<N - 1>;

__MAIN_NAMESPACE_END__

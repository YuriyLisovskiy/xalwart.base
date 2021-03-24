/**
 * string_utils.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Purpose: utility functions to simplify work with string.
 */

#pragma once

// C++ libraries.
#include <vector>
#include <string>
#include <functional>

// Module definitions.
#include "./_def_.h"


__STR_BEGIN__

// Normalizes value to exponent.
//
// `val`: pointer to value to normalize.
extern int _normalize_exp(double* val);

// Joins list of items using lambda function to convert
// item to std::string.
template <typename IterBegin, typename IterEnd>
std::string join(
	IterBegin begin, IterEnd end,
	const char* delimiter,
	const std::function<std::string(
		const typename std::iterator_traits<IterBegin>::value_type&
	)>& func
)
{
	std::string result;
	for (auto it = begin; it != end; it++)
	{
		result += func(*it);
		if (std::next(it) != end)
		{
			result += delimiter;
		}
	}

	return result;
}

template <typename T>
concept str_or_char_iterator_type =
	std::is_same_v<std::string, typename std::iterator_traits<T>::value_type> ||
	std::is_same_v<const char*, typename std::iterator_traits<T>::value_type> ||
	std::is_same_v<char, typename std::iterator_traits<T>::value_type>;

// Joins list of std::string or const char* items.
template <str_or_char_iterator_type IteratorT>
std::string join(IteratorT begin, IteratorT end, const char* delimiter)
{
	std::string result;
	for (str_or_char_iterator_type auto it = begin; it != end; it++)
	{
		result += *it;
		if (std::next(it) != end)
		{
			result += delimiter;
		}
	}

	return result;
}

template <typename T>
concept numeric_iterator_type =
	std::is_fundamental_v<typename std::iterator_traits<T>::value_type> &&
	!std::is_same_v<char, typename std::iterator_traits<T>::value_type>;

// Joins list of numeric items.
template <numeric_iterator_type IteratorT>
std::string join(IteratorT begin, IteratorT end, const char* delimiter)
{
	std::string result;
	for (numeric_iterator_type auto it = begin; it != end; it++)
	{
		result += std::to_string(*it);
		if (std::next(it) != end)
		{
			result += delimiter;
		}
	}

	return result;
}

// url_split_type("type:opaqueString", typeOut, opaqueStringOut) --> "type", "opaqueString".
//
// `url`: url to analyze.
// `scheme`: type output result.
// `data`: opaque string output result.
extern void url_split_type(const std::string& url, std::string& scheme, std::string& data);

// Checks if string contains char.
//
// `s`: string to analyze.
// `chr`: symbol to search for in given string
inline bool contains(const std::string& s, char chr)
{
	return s.find(chr) != std::string::npos;
}

// Converts all uppercase letters to lowercase.
//
// `s`: string with uppercase letters.
extern std::string lower(const std::string& s);

// Converts all lowercase letters to uppercase.
//
// `s`: string with lowercase letters.
extern std::string upper(const std::string& s);

// Splits the string to a vector of strings relatively for the character.
//
// `str`: string to split.
// `delimiter`: delimiter where to split string.
extern std::vector<std::string> split(const std::string& str, char delimiter=' ');

// Splits the string to a vector of strings with n length starting from right.
//
// `str`: string to split.
// `delimiter`: delimiter where to split string.
extern std::vector<std::string> rsplit(const std::string& str, char delimiter=' ', size_t n=-1);

// Splits the string to a std::pair of strings starting from left.
//
// `str`: string to split.
// `delimiter`: delimiter where to split string.
extern std::pair<std::string, std::string> lsplit_one(const std::string& str, char delimiter=' ');

// Trims left part of string in-place.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern void ltrim(std::string& s, const std::string& to_trim=" ");

// Trims left part of string and returns a copy of trimmed string.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern std::string ltrim(const std::string& s, const std::string& to_trim=" ");

// Trims right part of string in-place.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern void rtrim(std::string& s, const std::string& to_trim=" ");

// Trims right part of string and returns a copy of trimmed string.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern std::string rtrim(const std::string& s, const std::string& to_trim=" ");

// Trims both left and right parts of string in-place.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern void trim(std::string& s, const std::string& to_trim=" ");

// Trims both left and right parts of string and returns a copy of trimmed string.
//
// `s`: string to trim.
// `to_trim`: string to be trimmed.
extern std::string trim(const std::string& s, const std::string& to_trim=" ");

// Calculates number of entries of char `ch` in string `str`.
extern size_t count(const std::string& src, char ch);

// Cuts `left_n` chars from the left side of string `s` and `right_n` chars
// from the right side of the string. Additionally trims whitespace if needed.
extern std::string cut_edges(
	const std::string& s, size_t left_n, size_t right_n, bool trim_whitespace=true
);

// Replaces `old_sub` strings with `new_sub` in `src` string.
extern std::string replace(
	const std::string& src,
	const std::string& old_sub,
	const std::string& new_sub
);

extern std::string make_text_list(
	const std::vector<std::string>& list, const std::string& last
);

// Carries out a fixed conversion of a double value to a string, with a precision of 5 decimal digits.
// Values with absolute values less than 0.000001 are rounded to 0.0
// Note: this blindly assumes that the buffer will be large enough to hold the largest possible result.
// The largest value we expect is an IEEE 754 double precision real, with maximum magnitude of approximately
// e+308. The C standard requires an implementation to allow a single conversion to produce up to 512
// characters, so that's what we really expect as the buffer size.
extern std::string ftoa_fixed(double value);

// Converts double value to scientific number in string form.
//
// `value`: value to convert.
extern std::string ftoa_sci(double value);

__STR_END__

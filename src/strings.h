/**
 * strings.h
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 *
 * Purpose: utility functions to simplify work with string.
 */

#pragma once

// C++ libraries.
#include <vector>
#include <sstream>

// Module definitions.
#include "./_def_.h"


__STR_BEGIN__

/// Joins std::vector of values separated by given delimiter.
///
/// @tparam _Container: type of given container.
/// @param begin: constant iterator's pointer to the beginning of container.
/// @param end: constant iterator's pointer to the end of container.
/// @param delimiter: values' separator.
/// @return	joined string.
template <typename _Iterator>
std::string join(
	_Iterator begin,
	_Iterator end,
	const std::string& delimiter
)
{
	std::ostringstream oss;
	for (auto it = begin; it != end; it++)
	{
		oss << *it;
		if (std::next(it) != end)
		{
			oss << delimiter;
		}
	}

	return oss.str();
}

/// url_split_type("type:opaqueString", typeOut, opaqueStringOut) --> "type", "opaqueString".
///
/// @param url: url to analyze.
/// @param scheme: type output result.
/// @param data: opaque string output result.
extern void url_split_type(const std::string& url, std::string& scheme, std::string& data);

/// Checks if string contains char.
///
/// @param _str: string to analyze.
/// @param _char: symbol to search for in given string
/// @return true if symbol is found, otherwise returns false.
extern bool contains(const std::string& _str, char _char);

/// Converts all uppercase letters to lowercase.
///
/// @param _str: string with uppercase letters.
/// @return converted string.
extern std::string lower(const std::string& _str);

/// Converts all lowercase letters to uppercase.
///
/// @param _str: string with lowercase letters.
/// @return converted string.
extern std::string upper(const std::string& _str);

/// Splits the string to a vector of strings relatively for the character.
///
/// @param str: string to split.
/// @param delimiter: delimiter where to split string.
/// @return std::vector of strings.
extern std::vector<std::string> split(const std::string& str, char delimiter = ' ');

/// Splits the string to a vector of strings with n length starting from right.
///
/// @param str: string to split.
/// @param delimiter: delimiter where to split string.
/// @return std::vector of strings.
extern std::vector<std::string> rsplit(const std::string& str, char delimiter = ' ', size_t n = -1);

/// Checks if string starts with some string prefix.
///
/// @param src: string to check.
/// @param prefix: possible string beginning.
/// @return true if string starts with given prefix, otherwise returns false.
extern bool starts_with(const std::string& src, const std::string& prefix);

/// Checks if string ends with some string suffix.
///
/// @param src: string to check.
/// @param suffix: possible string ending.
/// @return true if string ends with given suffix, otherwise returns false.
extern bool ends_with(const std::string& src, const std::string& suffix);

/// Trims left part of string in-place.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern void ltrim(std::string& s, const std::string& to_trim = " ");

/// Trims left part of string and returns a copy of trimmed string.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern std::string ltrim(const std::string& s, const std::string& to_trim = " ");

/// Trims right part of string in-place.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern void rtrim(std::string& s, const std::string& to_trim = " ");

/// Trims right part of string and returns a copy of trimmed string.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern std::string rtrim(const std::string& s, const std::string& to_trim = " ");

/// Trims both left and right parts of string in-place.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern void trim(std::string& s, const std::string& to_trim = " ");

/// Trims both left and right parts of string and returns a copy of trimmed string.
///
/// @param s: string to trim.
/// @param to_trim: string to be trimmed.
extern std::string trim(const std::string& s, const std::string& to_trim = " ");

extern size_t count(const std::string& src, char ch);

extern std::string cut_edges(
	const std::string& s, size_t left, size_t right, bool trim_whitespace = true
);

extern std::string replace(
	const std::string& src,
	const std::string& old_sub,
	const std::string& new_sub
);

extern std::string make_text_list(
	const std::vector<std::string>& list, const std::string& last
);

/// Carries out a fixed conversion of a double value to a string, with a precision of 5 decimal digits.
/// Values with absolute values less than 0.000001 are rounded to 0.0
/// Note: this blindly assumes that the buffer will be large enough to hold the largest possible result.
/// The largest value we expect is an IEEE 754 double precision real, with maximum magnitude of approximately
/// e+308. The C standard requires an implementation to allow a single conversion to produce up to 512
/// characters, so that's what we really expect as the buffer size.
extern std::string ftoa_fixed(double value);

/// Converts double value to scientific number in string form.
///
/// @param value: value to convert
/// @return	std::string representation of converted value.
extern std::string ftoa_sci(double value);

__STR_END__


__STR_INTERNAL_BEGIN__

/// Normalizes value to exponent.
///
/// @param val: pointer to value to normalize.
/// @return normalized value as int.
extern int normalize_exp(double* val);

__STR_INTERNAL_END__

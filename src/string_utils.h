/**
 * string_utils.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Utility functions to simplify work with string.
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
//
// Returns exponent value and updates input value.
//
// Example:
//
// case 1: input value is 25.6, the `val` will
// become 0.256 and an exponent will be 2.
//
// case 2: input value is 0.000256, the `val` will
// become 0.256 and an exponent will be -3.
extern int _normalize_exp(double* val);

// Joins list of items using lambda function to convert
// item to std::string.
//
// `delimiter`: string to insert between items.
// `begin`, 'end': range to join.
// `func`: lambda function which converts item to `std::string`.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <typename IterBegin, typename IterEnd>
inline std::string join(
	const char* delimiter, IterBegin begin, IterEnd end,
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

// Joins list of items using lambda function to convert
// item to std::string.
//
// `delimiter`: string to insert between items.
// `list': an initializer list of values.
// `func`: lambda function which converts item to `std::string`.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <typename T>
inline std::string join(
	const char* delimiter, const std::initializer_list<T>& list, const std::function<std::string(const T&)>& func
)
{
	return join(delimiter, list.begin(), list.end(), func);
}

template <typename T>
concept str_or_char_type =
	std::is_same_v<std::string, T> || std::is_same_v<const char*, T> || std::is_same_v<char, T>;

template <typename T>
concept str_or_char_iterator =
	std::is_same_v<std::string, typename std::iterator_traits<T>::value_type> ||
	std::is_same_v<const char*, typename std::iterator_traits<T>::value_type> ||
	std::is_same_v<char, typename std::iterator_traits<T>::value_type>;

// Joins list of std::string or const char* items.
//
// `begin`, 'end': range to join.
// `delimiter`: string to insert between items.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <str_or_char_iterator IteratorT>
inline std::string join(const char* delimiter, IteratorT begin, IteratorT end)
{
	std::string result;
	for (str_or_char_iterator auto it = begin; it != end; it++)
	{
		result += *it;
		if (std::next(it) != end)
		{
			result += delimiter;
		}
	}

	return result;
}

// Joins list of std::string, const char* or char items.
//
// `list` an initializer list to join.
// `delimiter`: string to insert between items.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <str_or_char_type T>
inline std::string join(const char* delimiter, const std::initializer_list<T>& list)
{
	return join(delimiter, list.begin(), list.end());
}

template <typename T>
concept numeric_type = std::is_fundamental_v<T> && !std::is_same_v<char, T>;

template <typename T>
concept numeric_iterator =
	std::is_fundamental_v<typename std::iterator_traits<T>::value_type> &&
	!std::is_same_v<char, typename std::iterator_traits<T>::value_type>;

// Joins list of numeric items.
//
// `begin`, 'end': range to join.
// `delimiter`: string to insert between items.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <numeric_iterator IteratorT>
inline std::string join(const char* delimiter, IteratorT begin, IteratorT end)
{
	std::string result;
	for (numeric_iterator auto it = begin; it != end; it++)
	{
		result += std::to_string(*it);
		if (std::next(it) != end)
		{
			result += delimiter;
		}
	}

	return result;
}

// Joins list of numeric items.
//
// `list': an initializer list to join.
// `delimiter`: string to insert between items.
//
// Returns string with joined items. If range is empty, returns empty
// string.
template <numeric_type T>
inline std::string join(const char* delimiter, const std::initializer_list<T>& list)
{
	return join(delimiter, list.begin(), list.end());
}

// url_split_type("type:opaque_string", type_out, opaque_string_out) --> "type", "opaque_string".
//
// `url`: url to analyze.
// `scheme`: type output result.
// `data`: opaque string output result.
//
// If input url is empty the result scheme and data will be empty.
extern void url_split_type(const std::string& url, std::string& scheme, std::string& data);

// Checks if string contains char.
//
// `s`: string to analyze.
// `chr`: symbol to search for in given string
//
// Returns `true` if char is present in string, `false` otherwise.
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
// The algorithm starts to look through from the left side of the string.
//
// `s`: string to split.
// `delimiter`: delimiter where to split string.
// `n`: number of parts to split to.
//
// Returns vector with parts of string. If `n` is negative, the algorithm
// will ignore split counter. If input string is empty or `n` is equal to
// zero, returns vector of size 1 with input string. Otherwise the function
// returns `n + 1` parts of input string or `n` if `n` equals to or greater
// than actual found parts.
extern std::vector<std::string> split(const std::string& s, char delimiter=' ', long n=-1);

// Splits the string to vector of strings starting from right.
//
// `s`: string to split.
// `delimiter`: delimiter where to split string.
// `n`: number of parts to split to.
//
// Returns vector with parts of string. If `n` is negative, returns the result
// of `std::split(s, delimiter)` call. If input string is empty or `n` is equal to
// zero, returns empty vector.
extern std::vector<std::string> rsplit(const std::string& s, char delimiter=' ', long n=-1);

// Trims left part of string.
//
// `s`: string to trim.
// `c`: char to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string ltrim(const std::string& s, char c=' ');

// Trims right part of string.
//
// `s`: string to trim.
// `c`: char to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string rtrim(const std::string& s, char c=' ');

// Trims both left and right parts of string.
//
// `s`: string to trim.
// `c`: char to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string trim(const std::string& s, char c=' ');

// Trims left part of string.
//
// `s`: string to trim.
// `chars`: string to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string ltrim(const std::string& s, const std::string& chars);

// Trims right part of string.
//
// `s`: string to trim.
// `chars`: string to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string rtrim(const std::string& s, const std::string& chars);

// Trims both left and right parts of string.
//
// `s`: string to trim.
// `chars`: string to be trimmed.
//
// Returns a copy of trimmed string.
extern std::string trim(const std::string& s, const std::string& chars);

// Calculates number of entries of char `ch` in string `str`.
//
// `src`: input string to count from.
// `ch`: symbol to count it's occurrences.
//
// Returns non-negative integer.
extern size_t count(const std::string& s, char ch);

// Cuts chars from the left side of input string and chars
// from the right side of the string. Additionally trims
// whitespace if needed.
//
// `src`: string to cut.
// `left_n`: left edge.
// `right_n`: right edge.
// `trim_whitespace`: indicates whether to trim whitespaces or not.
extern std::string cut_edges(std::string s, size_t left_n, size_t right_n, bool trim_whitespace=true);

// Replaces old substring with new substring.
//
// `src`: input string.
// `old_sub`: old substring to remove.
// `new_sub`: new substring to insert.
//
// If `old_sub` is empty, returns string without changes.
extern std::string replace(std::string src, const std::string& old_sub, const std::string& new_sub);

// Creates text from input vector of strings.
//
// `list`: vector of strings.
// `last`: string to insert before the last item of input sequence.
//
// If input sequence is empty, returns empty string. If the size
// of sequence is 1, returns the first item. Otherwise returns
// first `n - 1` items concatenated with `last` string and the
// last item of the sequence.
// Example: 'one, two and three'.
extern std::string make_text_list(const std::vector<std::string>& list, const std::string& last);

__STR_END__

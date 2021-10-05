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
#include <locale>
#include <codecvt>
#include <algorithm>
#include <concepts>

// Module definitions.
#include "./_def_.h"


__STR_BEGIN__

static constexpr size_t npos = -1;

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

// TESTME: string_to_wstring
// TODO: docs for 'string_to_wstring'
inline std::wstring string_to_wstring(const std::string& s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.from_bytes(s);
}

// TESTME: wstring_to_string
// TODO: docs for 'wstring_to_string'
inline std::string wstring_to_string(const std::wstring& s)
{
	std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
	return converter.to_bytes(s);
}

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

// Converts all uppercase letters to lowercase in `std::string`.
//
// `s`: string with uppercase letters.
inline std::string to_lower(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](auto c) -> auto { return std::tolower(c); });
	return s;
}

// Converts all uppercase letters to lowercase in `std::wstring`.
//
// `s`: string with uppercase letters.
inline std::wstring to_lower(std::wstring s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](auto c) -> auto { return std::tolower(c); });
	return s;
}

// Converts all lowercase letters to uppercase in `std::string`.
//
// `s`: string with lowercase letters.
inline std::string to_upper(std::string s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](auto c) -> auto { return std::toupper(c); });
	return s;
}

// Converts all lowercase letters to uppercase in `std::wstring`.
//
// `s`: string with lowercase letters.
inline std::wstring to_upper(std::wstring s)
{
	std::transform(s.begin(), s.end(), s.begin(), [](auto c) -> auto { return std::toupper(c); });
	return s;
}

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
extern std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter=' ', long n=-1);

// Do the same as the above but with `std::string`.
inline std::vector<std::string> split(const std::string& s, char delimiter=' ', long n=-1)
{
	auto wstring_result = split(string_to_wstring(s), delimiter, n);
	std::vector<std::string> result;
	std::transform(
		wstring_result.begin(), wstring_result.end(), std::back_inserter(result),
		[](const std::wstring& s) -> std::string { return wstring_to_string(s); }
	);
	return result;
}

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

// Trims both left and right parts of `std::wstring`.
//
// `s`: string to trim.
// `c`: char to be trimmed.
//
// Returns a copy of trimmed string.
extern std::wstring trim(const std::wstring& s, wchar_t c=' ');

// Trims both left and right parts of `std::string`.
//
// `s`: string to trim.
// `c`: char to be trimmed.
//
// Returns a copy of trimmed string.
inline std::string trim(const std::string& s, char c=' ')
{
	return wstring_to_string(trim(string_to_wstring(s), c));
}

// Trims both left and right parts of `std::string`.
//
// `s`: string to trim.
// `chars`: string to be trimmed.
//
// Returns a copy of trimmed string.
extern std::wstring trim(const std::wstring& s, const std::wstring& chars);

// Trims both left and right parts of `std::wstring`.
//
// `s`: string to trim.
// `chars`: string to be trimmed.
//
// Returns a copy of trimmed string.
inline std::string trim(const std::string& s, const std::string& chars)
{
	return wstring_to_string(trim(string_to_wstring(s), string_to_wstring(chars)));
}

// TESTME: trim_left_func
// TODO: docs for 'trim_left_func'
extern std::wstring trim_left_func(const std::wstring& s, const std::function<bool(wchar_t)>& func);

// TESTME: trim_left_func
// TODO: docs for 'trim_left_func'
inline std::string trim_left_func(const std::string& s, const std::function<bool(char)>& func)
{
	return wstring_to_string(trim_left_func(string_to_wstring(s), func));
}

// TESTME: trim_func
// TODO: docs for 'trim_func'
extern std::wstring trim_func(const std::wstring& s, const std::function<bool(wchar_t)>& func);

// TESTME: trim_func
// TODO: docs for 'trim_func'
inline std::string trim_func(const std::string& s, const std::function<bool(char)>& func)
{
	return wstring_to_string(trim_func(string_to_wstring(s), func));
}

// Cut chars from the left side of input string and chars
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

// TESTME: find_if
// TODO: docs for 'find_if'
template <typename IteratorType>
inline size_t find_if(
	IteratorType first, IteratorType last, const std::function<bool(iterator_v_type<IteratorType>)>& func
)
{
	size_t position = 0;
	while (first != last)
	{
		if (func(*first++))
		{
			return position;
		}

		position++;
	}

	return npos;
}

// TESTME: is_end_position
// TODO: docs for 'is_end_position'
constexpr inline bool is_end_position(size_t position)
{
	return position == npos;
}

// TESTME: equal_fold
// TODO: docs for 'equal_fold'
extern bool equal_fold(std::string s, std::string t);

__STR_END__

/**
 * string_utils.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./string_utils.h"

#include <utility>


__STR_BEGIN__

int _normalize_exp(double* val)
{
	int exponent = 0;
	double value = *val;
	while (value >= 1.0)
	{
		value /= 10.0;
		++exponent;
	}

	while (value < 0.1)
	{
		value *= 10.0;
		--exponent;
	}

	*val = value;
	return exponent;
}

void url_split_type(const std::string& url, std::string& scheme, std::string& data)
{
	bool _break = false, colon_found = false;
	auto it = url.begin();
	while (it != url.end() && !_break)
	{
		switch (*it)
		{
			case '/':
				_break = true;
				break;
			case ':':
				colon_found = true;
				_break = true;
				break;
			default:
				scheme += *it;
				break;
		}

		it++;
	}

	if (!scheme.empty() && colon_found)
	{
		data = std::string(it, url.end());
	}
	else
	{
		scheme = "";
		data = url;
	}
}

std::string lower(const std::string& s)
{
	std::string res(s);
	std::transform(res.begin(), res.end(), res.begin(), [](auto c) -> auto {
		return std::tolower(c);
	});
	return res;
}

std::string upper(const std::string& s)
{
	std::string res(s);
	std::transform(res.begin(), res.end(), res.begin(), [](auto c) -> auto {
		return std::toupper(c);
	});
	return res;
}

std::vector<std::string> split(const std::string& s, char delimiter, long n)
{
	bool count_splits = true;
	if (n < 0)
	{
		count_splits = false;
	}

	if (s.empty() || n == 0)
	{
		return {s};
	}

	auto size = s.size();
	std::vector<std::string> result;
	std::string current;
	size_t counter = 0;
	size_t i;
	for (i = 0; i < size && (!count_splits || counter < n); i++)
	{
		if (s[i] == delimiter)
		{
			result.push_back(current);
			current.clear();
			counter++;
		}
		else
		{
			current += s[i];
		}
	}

	if (!current.empty())
	{
		result.push_back(current);
	}
	else if (i < size)
	{
		result.push_back(s.substr(i));
	}

	return result;
}

std::vector<std::string> rsplit(const std::string& s, char delimiter, long n)
{
	if (s.empty() || n == 0)
	{
		return {s};
	}

	auto rs = s;
	std::reverse(rs.begin(), rs.end());
	auto result = split(rs, delimiter, n);
	auto begin = result.begin();
	auto end = result.end();
	while (true)
	{
		if (begin == end)
		{
			break;
		}
		else if (begin == --end)
		{
			std::reverse(begin->begin(), begin->end());
			break;
		}
		else
		{
			std::reverse(begin->begin(), begin->end());
			std::reverse(end->begin(), end->end());
			std::iter_swap(begin, end);
			++begin;
		}
	}

	return result;
}

std::string ltrim(std::string s, const std::string& chars)
{
	size_t pos = 0;
	size_t n = s.size();
	while (pos < n && chars.find(s[pos]) != std::string::npos)
	{
		pos++;
//		s.erase(s.begin(), s.begin() + chars.size());
	}

	return s.substr(pos);
}

std::string rtrim(std::string s, const std::string& chars)
{
	size_t pos = s.size() - 1;
	while (pos >= 0 && chars.find(s[pos]) != std::string::npos)
	{
		pos--;
//		s.erase(s.begin(), s.begin() + chars.size());
	}

	return s.substr(0, pos + 1);
}

std::string trim(std::string s, const std::string& chars)
{
	return rtrim(std::move(ltrim(std::move(s), chars)), chars);
}

size_t count(const std::string& src, char ch)
{
	size_t res = 0;
	for (const auto& c : src)
	{
		if (c == ch)
		{
			res++;
		}
	}

	return res;
}

std::string cut_edges(
	const std::string& src, size_t left_n, size_t right_n, bool trim_whitespace
)
{
	std::string copy = src;
	if (src.size() >= left_n + right_n)
	{
		if (left_n)
		{
			copy.erase(0, left_n);
		}

		if (right_n)
		{
			copy.erase(copy.size() - right_n);
		}
	}

	if (trim_whitespace)
	{
		copy = trim(copy);
	}

	return copy;
}

void replace(
	std::string& src, const std::string& old_sub, const std::string& new_sub
)
{
	size_t index = 0;
	while (true)
	{
		index = src.find(old_sub, index);
		if (index == std::string::npos)
		{
			break;
		}

		src.replace(index, old_sub.size(), new_sub);
		index += new_sub.size();
	}
}

std::string replace(
	const std::string& src, const std::string& old_sub, const std::string& new_sub
)
{
	std::string copy = src;
	replace(copy, old_sub, new_sub);
	return copy;
}

std::string make_text_list(
	const std::vector<std::string>& list, const std::string& last
)
{
	if (list.empty())
	{
		return "";
	}

	if (list.size() == 1)
	{
		return list[0];
	}

	return join(", ", list.begin(), list.end() - 1) + " " + last + " " + *list.end();
}

std::string ftoa_fixed(double value)
{
	if (value == 0.0)
	{
		return "0";
	}

	std::string result;
	if (value < 0.0)
	{
		result += '-';
		value = -value;
	}

	int exponent = _normalize_exp(&value);
	int places = 0;
	static const int width = 4;

	while (exponent > 0)
	{
		int digit = value * 10;
		result += std::to_string(digit) + '0';
		value = value * 10 - digit;
		++places;
		--exponent;
	}

	if (places == 0)
	{
		result += '0';
	}

	result += '.';
	while (exponent < 0 && places < width)
	{
		result += '0';
		--exponent;
		++places;
	}

	while (places < width)
	{
		int digit = value * 10.0;
		result += std::to_string(digit) + '0';
		value = value * 10.0 - digit;
		++places;
	}

	return result;
}

std::string ftoa_sci(double value)
{
	if (value == 0.0)
	{
		return "0";
	}

	std::string result;
	if (value < 0.0)
	{
		result += '-';
		value = -value;
	}

	static const int width = 4;
	int exponent = _normalize_exp(&value);
	int digit = value * 10.0;
	result += std::to_string(digit) + '0';
	value = value * 10.0 - digit;
	--exponent;

	result += '.';
	for (int i = 0; i < width; i++)
	{
		digit = value * 10.0;
		result += std::to_string(digit) + '0';
		value = value * 10.0 - digit;
	}

	return result + 'e' + std::to_string(exponent);
}

__STR_END__

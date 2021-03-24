/**
 * string_utils.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./string_utils.h"


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
	std::transform(
		res.begin(),
		res.end(),
		res.begin(),
		[](unsigned char c){ return std::tolower(c); }
	);
	return res;
}

std::string upper(const std::string& s)
{
	std::string res(s);
	std::transform(
		res.begin(),
		res.end(),
		res.begin(),
		[](unsigned char c){ return std::toupper(c); }
	);
	return res;
}

std::vector<std::string> split(const std::string& str, char delimiter)
{
	std::vector<std::string> result;
	if (str.empty())
	{
		return result;
	}

	std::string current;
	for (const char& _char : str)
	{
		if (_char == delimiter)
		{
			result.push_back(current);
			current.clear();
		}
		else
		{
			current += _char;
		}
	}

	result.push_back(current);
	return result;
}

std::vector<std::string> rsplit(const std::string& str, char delimiter, size_t n)
{
	if (n < 0)
	{
		return split(str, delimiter);
	}

	long str_last_pos = (long)str.size() - 1;
	if (str_last_pos == -1)
	{
		return {};
	}

	std::vector<std::string> result;
	std::string current;
	size_t split_count = 0;
	long int i;
	for (i = str_last_pos; i >= 0 && split_count < n; i--)
	{
		if (str[i] == delimiter)
		{
			std::reverse(current.begin(), current.end());
			result.insert(result.begin(), current);
			current.clear();
			split_count++;
		}
		else
		{
			current += str[i];
		}
	}

	if (result.empty())
	{
		std::reverse(current.begin(), current.end());
		result.insert(result.begin(), current);
	}
	else
	{
		result.insert(result.begin(), str.substr(0, i + 1));
	}

	return result;
}

std::pair<std::string, std::string> lsplit_one(const std::string& s, char delimiter)
{
	std::pair<std::string, std::string> result;
	size_t len = s.size();
	for (size_t i = 0; i < len; i++)
	{
		auto ch = s[i];
		if (ch == delimiter)
		{
			if (i + 1 < len)
			{
				result.second = std::string(s.begin() + i + 1, s.end());
			}

			break;
		}
		else
		{
			result.first += ch;
		}
	}

	return result;
}

void ltrim(std::string& s, const std::string& to_trim)
{
	while (s.starts_with(to_trim))
	{
		s.erase(s.begin(), s.begin() + to_trim.size());
	}
}

std::string ltrim(const std::string& s, const std::string& to_trim)
{
	std::string copy = s;
	ltrim(copy, to_trim);
	return copy;
}

void rtrim(std::string& s, const std::string& to_trim)
{
	while (s.ends_with(to_trim))
	{
		s.erase(s.end() - to_trim.size(), s.end());
	}
}

std::string rtrim(const std::string& s, const std::string& to_trim)
{
	std::string copy = s;
	rtrim(copy, to_trim);
	return copy;
}

void trim(std::string& s, const std::string& to_trim)
{
	ltrim(s, to_trim);
	rtrim(s, to_trim);
}

std::string trim(const std::string& s, const std::string& to_trim)
{
	std::string copy = s;
	trim(copy, to_trim);
	return copy;
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
	const std::string& s, size_t left_n, size_t right_n, bool trim_whitespace
)
{
	std::string copy = s;
	if (s.size() >= left_n + right_n)
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
		trim(copy);
	}

	return copy;
}

std::string replace(
	const std::string& src, const std::string& old_sub, const std::string& new_sub
)
{
	std::string copy = src;
	size_t index = 0;
	while (true)
	{
		index = src.find(old_sub, index);
		if (index == std::string::npos)
		{
			break;
		}

		copy.replace(index, old_sub.size(), new_sub);
		index += new_sub.size();
	}

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

	return join(list.begin(), list.end() - 1, ", ") + " " + last + " " + *list.end();
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

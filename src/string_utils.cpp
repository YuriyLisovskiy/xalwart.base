/**
 * string_utils.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./string_utils.h"

// C++ libraries.
#ifdef _MSC_VER
#include <algorithm>
#endif

// Base libraries.
#include "./unicode/letter.h"


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

std::vector<std::wstring> split(const std::wstring& s, wchar_t delimiter, long n)
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
	std::vector<std::wstring> result;
	std::wstring current;
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

	if (i < size)
	{
		result.push_back(s.substr(i));
	}
	else
	{
		result.push_back(current);
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

std::string ltrim(const std::string& s, char c)
{
	size_t pos = 0;
	size_t n = s.size();
	while (pos < n && s.at(pos) == c)
	{
		pos++;
	}

	return s.substr(pos);
}

std::string rtrim(const std::string& s, char c)
{
	long long pos = (long long)s.size() - 1;
	while (pos >= 0 && s.at(pos) == c)
	{
		pos--;
	}

	return s.substr(0, pos + 1);
}

std::string ltrim(const std::string& s, const std::string& chars)
{
	size_t pos = 0;
	size_t n = s.size();
	while (pos < n && chars.find(s[pos]) != std::string::npos)
	{
		pos++;
	}

	return s.substr(pos);
}

std::string rtrim(const std::string& s, const std::string& chars)
{
	long long pos = (long long)s.size() - 1;
	while (pos >= 0 && chars.find(s[pos]) != std::string::npos)
	{
		pos--;
	}

	return s.substr(0, pos + 1);
}

std::wstring trim(const std::wstring& s, wchar_t c)
{
	size_t l_pos = 0;
	size_t n = s.size();
	while (l_pos < n && s.at(l_pos) == c)
	{
		l_pos++;
	}

	long long r_pos = (long long)n - 1;
	while (r_pos >= 0 && s.at(r_pos) == c)
	{
		r_pos--;
	}

	return s.substr(l_pos, r_pos - l_pos + 1);
}

std::wstring trim(const std::wstring& s, const std::wstring& chars)
{
	size_t l_pos = 0;
	size_t n = s.size();
	while (l_pos < n && chars.find(s[l_pos]) != std::wstring::npos)
	{
		l_pos++;
	}

	long long r_pos = (long long)n - 1;
	while (r_pos >= 0 && chars.find(s[r_pos]) != std::wstring::npos)
	{
		r_pos--;
	}

	return s.substr(l_pos, r_pos - l_pos + 1);
}

std::wstring trim_left_func(const std::wstring& s, const std::function<bool(wchar_t)>& func)
{
	size_t pos = 0;
	size_t n = s.size();
	while (pos < n && func(s[pos]))
	{
		pos++;
	}

	return s.substr(pos);
}

std::wstring trim_func(const std::wstring& s, const std::function<bool(wchar_t)>& func)
{
	size_t l_pos = 0;
	size_t n = s.size();
	while (l_pos < n && func(s[l_pos]))
	{
		l_pos++;
	}

	long long r_pos = (long long)n - 1;
	while (r_pos >= 0 && func(s[r_pos]))
	{
		r_pos--;
	}

	return s.substr(l_pos, r_pos - l_pos + 1);
}

std::string cut_edges(std::string s, size_t left_n, size_t right_n, bool trim_whitespace)
{
	if (s.size() >= left_n + right_n)
	{
		if (left_n)
		{
			s.erase(0, left_n);
		}

		if (right_n)
		{
			s.erase(s.size() - right_n);
		}
	}

	if (trim_whitespace)
	{
		s = trim(s);
	}

	return s;
}

std::string replace(std::string src, const std::string& old_sub, const std::string& new_sub)
{
	if (src.empty() || old_sub.empty())
	{
		return src;
	}

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

	return src;
}

std::string make_text_list(const std::vector<std::string>& list, const std::string& last)
{
	if (list.empty())
	{
		return "";
	}

	if (list.size() == 1)
	{
		return list[0];
	}

	return join(", ", list.begin(), list.end() - 1) + " " + last + " " + *(list.end() - 1);
}

bool equal_fold(std::wstring s, std::wstring t)
{
	while (!s.empty() && !t.empty())
	{
		// Extract first byte from each string.
		wchar_t sr, tr;
		if (s[0] < unicode::BYTE_SELF)
		{
			sr = s[0];
			s = s.substr(1);
		}
		else
		{
			// r, size := utf8.DecodeRuneInString(s)
			// sr, s = r, s[size:]
		}

		if (t[0] < unicode::BYTE_SELF)
		{
			tr = t[0];
			t = t.substr(1);
		}
		else
		{
			// r, size := utf8.DecodeRuneInString(t)
			// tr, t = r, t[size:]
		}

		// If they match, keep going; if not, return false.

		// Easy case.
		if (tr == sr)
		{
			continue;
		}

		// Make sr < tr to simplify what follows.
		if (tr < sr)
		{
			std::swap(tr, sr);
		}

		// Fast check for ASCII.
		if (tr < unicode::BYTE_SELF)
		{
			// ASCII only, sr/tr must be upper/lower case
			if ('A' <= sr && sr <= 'Z' && tr == sr + 'a' - 'A')
			{
				continue;
			}

			return false;
		}

		// General case; `simple_fold(x)` returns the next equivalent byte > x
		// or wraps around to smaller values.
		auto r = unicode::simple_fold(sr);
		while (r != sr && r < tr)
		{
			r = unicode::simple_fold(sr);
		}

		if (r == tr)
		{
			continue;
		}

		return false;
	}

	// One string is empty. Are both?
	return s == t;
}

__STR_END__

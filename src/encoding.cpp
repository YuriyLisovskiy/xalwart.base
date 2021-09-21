/**
 * encoding.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./encoding.h"

// C++ libraries.
#include <sstream>

// Base libraries.
#include "./exceptions.h"
#include "./string_utils.h"
#include "./unicode/tables.h"


__ENCODING_BEGIN__

inline constexpr const char* HEX_DIGITS = "0123456789ABCDEF";

// The maximum size table for linear search for non-Latin1 symbol.
inline constexpr const size_t LINEAR_MAX = 18;

bool _is16(const std::vector<unicode::Range16>& ranges, uint16_t r)
{
	if (ranges.size() <= LINEAR_MAX || r <= unicode::MAX_LATIN_1)
	{
		for (const auto& range : ranges)
		{
			if (r < range.lo)
			{
				return false;
			}

			if (r <= range.hi)
			{
				return range.stride == 1 || (r - range.lo) % range.stride == 0;
			}
		}

		return false;
	}

	// binary search over ranges
	size_t lo = 0;
	auto hi = ranges.size();
	while (lo < hi)
	{
		auto m = lo + (hi - lo) / 2;
		auto range = ranges[m];
		if (range.lo <= r && r <= range.hi)
		{
			return range.stride == 1 || (r - range.lo) % range.stride == 0;
		}

		if (r < range.lo)
		{
			hi = m;
		}
		else
		{
			lo = m + 1;
		}
	}

	return false;
}

bool _is32(const std::vector<unicode::Range32>& ranges, uint32_t r)
{
	if (ranges.size() <= LINEAR_MAX)
	{
		for (const auto& range : ranges)
		{
			if (r < range.lo)
			{
				return false;
			}

			if (r <= range.hi)
			{
				return range.stride == 1 || (r - range.lo) % range.stride == 0;
			}
		}

		return false;
	}

	// binary search over ranges
	size_t lo = 0;
	auto hi = ranges.size();
	while (lo < hi)
	{
		auto m = lo + (hi - lo) / 2;
		auto range = ranges[m];
		if (range.lo <= r && r <= range.hi)
		{
			return range.stride == 1 || (r - range.lo) % range.stride == 0;
		}

		if (r < range.lo)
		{
			hi = m;
		}
		else
		{
			lo = m + 1;
		}
	}

	return false;
}

bool _is_excluding_latin(const unicode::RangeTable& range_table, wchar_t c)
{
	auto r16 = range_table.r16;
	auto offset = range_table.latin_offset;

	// Compare as uint32 to correctly handle negative values.
	if (r16.size() > offset && c <= r16[r16.size() - 1].hi)
	{
		return _is16({r16.begin() + offset, r16.end()}, (uint16_t)c);
	}

	if (!range_table.r32.empty() && c >= range_table.r32[0].lo)
	{
		return _is32(range_table.r32, (uint32_t)c);
	}

	return false;
}

bool is_space(unsigned char c)
{
	if (c <= unicode::MAX_LATIN_1)
	{
		switch (c)
		{
			case '\t':
			case '\n':
			case '\v':
			case '\f':
			case '\r':
			case ' ':
			case 0x85:
			case 0xA0:
				return true;
			default:
				return false;
		}
	}

	return _is_excluding_latin(unicode::WHITE_SPACE, c);
}

bool is_hex(unsigned char c)
{
	if ('0' <= c && c <= '9')
	{
		return true;
	}

	if ('a' <= c && c <= 'f')
	{
		return true;
	}

	if ('A' <= c && c <= 'F')
	{
		return true;
	}

	return false;
}

unsigned char unhex(unsigned char c)
{
	if ('0' <= c && c <= '9')
	{
		return (unsigned char)(c - '0');
	}

	if ('a' <= c && c <= 'f')
	{
		return (unsigned char)(c - 'a' + 10);
	}

	if ('A' <= c && c <= 'F')
	{
		return (unsigned char)(c - 'A' + 10);
	}

	return 0;
}

void escape_char(std::ostringstream& stream, char c, const std::string& safe)
{
	if ((c >= '0' && c <= '9') ||
	    (c >= 'a' && c <= 'z') ||
	    (c >= 'A' && c <= 'Z') ||
	    c == '-' || c == '_' || c == '.' || c == '!' || c == '~' ||
	    c == '*' || c == '\'' || c == '(' || c == ')' || safe.find(c) != -1)
	{
		stream << c;
	}
	else
	{
		stream << '%';
		stream << HEX_DIGITS[(c & 0xF0) >> 4];
		stream << HEX_DIGITS[(c & 0x0F) ];
	}
}

std::string quote(const std::string& s, const std::string& safe)
{
	std::ostringstream oss;
	for (const auto& c : s)
	{
		escape_char(oss, c, safe);
	}

	return oss.str();
}

std::string encode_ascii(const std::string& s, Mode mode)
{
	std::string res;
	auto sz = s.size();
	for (size_t i = 0; i < sz; i++)
	{
		auto c = (unsigned char)s[i];
		if (c > 127)
		{
			switch (mode)
			{
				case Mode::Strict:
					throw EncodingError(
						"'ascii' codec can't encode character in position " + std::to_string(i) +
						": ordinal not in range [0;127]",
						_ERROR_DETAILS_
					);
				case Mode::Ignore:
					continue;
				case Mode::Replace:
					res += '?';
					continue;
			}
		}

		res += c;
	}

	return res;
}

std::string encode_iso_8859_1(const std::string& s, Mode mode)
{
	if (s.empty())
	{
		return s;
	}

	std::string out;
	auto in = s.begin();
	unsigned int codepoint;
	while (*in != 0)
	{
		auto ch = static_cast<unsigned char>(*in);
		if (ch <= 0x7f)
		{
			codepoint = ch;
		}
		else if (ch <= 0xbf)
		{
			codepoint = (codepoint << 6) | (ch & 0x3f);
		}
		else if (ch <= 0xdf)
		{
			codepoint = ch & 0x1f;
		}
		else if (ch <= 0xef)
		{
			codepoint = ch & 0x0f;
		}
		else
		{
			codepoint = ch & 0x07;
		}

		++in;
		if (((*in & 0xc0) != 0x80) && (codepoint <= 0x10ffff))
		{
			if (codepoint <= 255)
			{
				out.append(1, static_cast<char>(codepoint));
			}
			else
			{
				switch (mode)
				{
					case Mode::Strict:
						throw EncodingError(
							"'iso_8859_1' codec can't encode character: ordinal not in range [0;255]",
							_ERROR_DETAILS_
						);
					case Mode::Ignore:
						break;
					case Mode::Replace:
						out += '?';
						break;
				}
			}
		}
	}

	return out;
}

std::string encode_utf_8(const std::string& s, Mode /* mode */)
{
	// !IMPORTANT!
	// Check if it is not required to encode the string on Windows.
	return s;
}

std::string encode(const std::string& s, Encoding enc, Mode mode)
{
	std::string result;
	switch (enc)
	{
		case Encoding::ASCII:
			result = encode_ascii(s, mode);
			break;
		case Encoding::Latin_1:
		case Encoding::ISO_8859_1:
			result = encode_iso_8859_1(s, mode);
			break;
		case Encoding::Utf_8:
			result = encode_utf_8(s, mode);
			break;
		default:
			throw EncodingError("unknown encoding", _ERROR_DETAILS_);
	}

	return result;
}

std::tuple<std::wstring, bool> decode2231(const std::wstring& s)
{
	auto sv = str::split(s, '\'', 3);
	if (sv.size() != 3)
	{
		return {L"", false};
	}

	// TODO: ignoring lang in sv[1] for now. If anybody needs it we'll
	//  need to decide how to expose it in the API. But I'm not sure
	//  anybody uses it in practice.
	auto charset = str::to_lower(sv[0]);
	if (charset.empty())
	{
		return {L"", false};
	}

	if (charset != L"us-ascii" && charset != L"utf-8")
	{
		// TODO: unsupported encoding
		return {L"", false};
	}

	auto unescaped_string = percent_hex_unescape(str::wstring_to_string(sv[2]));
	return {str::string_to_wstring(unescaped_string), true};
}

std::string percent_hex_unescape(std::string s)
{
	// Count %, check that they're well-formed.
	size_t percents = 0;
	for (size_t i = 0; i < s.size();)
	{
		if (s[i] != '%')
		{
			i++;
			continue;
		}

		percents++;
		if (i + 2 >= s.size() || !is_hex(s[i + 1]) || !is_hex(s[i + 2]))
		{
			s = s.substr(i);
			if (s.size() > 3)
			{
				s = s.substr(0, 3);
			}

			throw ValueError("mime: bogus characters after %: " + s, _ERROR_DETAILS_);
		}

		i += 3;
	}

	if (percents == 0)
	{
		return s;
	}

	std::string result;
	size_t j = 0;
	auto s_size = s.size();
	for (size_t i = 0; i < s_size;)
	{
		switch (s[i]) {
			case '%':
				result[j] = unhex(s[i + 1] << 4 | unhex(s[i + 2]));
				j++;
				i += 3;
				break;
			default:
				result[j] = s[i];
				j++;
				i++;
				break;
		}
	}

	return result;
}

__ENCODING_END__

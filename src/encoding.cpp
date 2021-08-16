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


__ENCODING_BEGIN__

inline constexpr const char* HEX_DIGITS = "0123456789ABCDEF";

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

__ENCODING_END__

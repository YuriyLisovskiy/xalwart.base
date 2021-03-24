/**
 * encoding.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./encoding.h"

// C++ libraries.
#include <iomanip>
#include <sstream>

// Core libraries.
#include "./exceptions.h"


__ENCODING_BEGIN__

// Converts character to percent-encoded character and writes it to stream.
//
// `safe`: string which contains chars that must not be converted. If char 'c'
// is in this sequence, it will be written to stream without converting.
//
// RFC 3986 section 2.2 Reserved Characters: ! * ' ( ) ; : @ & = + $ , / ? # [ ]
// RFC 3986 section 2.3 Unreserved Characters: ALPHA NUMERIC - _ . ~
void _escape_char(std::ostringstream& stream, char c, const std::string& safe="")
{
	if (std::isalnum((unsigned char) c) || c == '-' || c == '_' || c == '.' || c == '~' || safe.find(c) != -1)
	{
		stream << c;
	}
	else
	{
		stream << std::uppercase;
		stream << '%' << std::setw(2) << int((unsigned char) c);
		stream << std::nouppercase;
	}
}

std::string encode_url(const std::string& url)
{
	enum url_state_enum
	{
		s_scheme,
		s_slash_after_scheme,
		s_host,
		s_path,
		s_query,
		s_fragment

	} state = url_state_enum::s_scheme;

	std::ostringstream oss;
	oss.fill('0');
	oss << std::hex;
	for (const char& c : url)
	{
		switch (state)
		{
			case url_state_enum::s_scheme:
				if (c == '/')
				{
					state = url_state_enum::s_slash_after_scheme;
				}

				oss << c;
				break;
			case url_state_enum::s_slash_after_scheme:
				if (c == '/')
				{
					state = url_state_enum::s_host;
				}

				oss << c;
				break;
			case url_state_enum::s_host:
				if (c == '/')
				{
					state = url_state_enum::s_path;
				}

				oss << c;
				break;
			case url_state_enum::s_path:
				if (c == '?')
				{
					oss << c;
					state = url_state_enum::s_query;
				}
				else
				{
					_escape_char(oss, c, "/");
				}
				break;
			case url_state_enum::s_query:
				if (c == '#')
				{
					oss << c;
					state = url_state_enum::s_fragment;
				}
				else
				{
					_escape_char(oss, c, "&=");
				}
				break;
			case url_state_enum::s_fragment:
				_escape_char(oss, c);
				break;
		}
	}

	return oss.str();
}

std::string quote(const std::string& s, const std::string& safe)
{
	std::ostringstream oss;
	oss.fill('0');
	oss << std::hex;
	for (const auto& _char : s)
	{
		_escape_char(oss, _char, safe);
	}

	return oss.str();
}

std::string encode(const std::string& s, encoding enc, Mode mode)
{
	std::string result;
	switch (enc)
	{
		case ascii:
			result = encode_ascii(s, mode);
			break;
		case latin_1:
		case iso_8859_1:
			result = encode_iso_8859_1(s, mode);
			break;
		case utf_8:
			result = encode_utf_8(s, mode);
			break;
		default:
			throw core::EncodingError("unknown encoding", _ERROR_DETAILS_);
	}

	return result;
}

std::string encode_ascii(const std::string& s, Mode mode)
{
	std::string res;
	for (size_t i = 0; i < s.size(); i++)
	{
		auto _char = static_cast<unsigned char>(s[i]);
		switch (mode)
		{
			case Mode::STRICT:
				if (_char > 127)
				{
					throw core::EncodingError(
						"'ascii' codec can't encode character in position " + std::to_string(i) + ": ordinal not in range [0;127]",
						_ERROR_DETAILS_
					);
				}
				break;
			case Mode::IGNORE:
				continue;
			case Mode::REPLACE:
				res += '?';
				continue;
		}

		res += _char;
	}

	return res;
}

std::string encode_iso_8859_1(const std::string& s, Mode mode)
{
	std::string out;
	out.reserve(s.length());
	std::transform(
		s.cbegin(),
		s.cend(),
		std::back_inserter(out),
		[mode](const wchar_t c) {
			switch (mode)
			{
				case Mode::STRICT:
					if (c > 255)
					{
						throw core::EncodingError(
							"'iso_8859_1' codec can't encode character: ordinal not in range [0;255]",
							_ERROR_DETAILS_
						);
					}
					break;
				case Mode::IGNORE:
					return L's';
				case Mode::REPLACE:
					return L'?';
			}

			return c;
		}
	);

	return out;
}

std::string encode_utf_8(const std::string& s, Mode mode)
{
	// TODO: encode_utf_8(const xw::string& str, Mode mode)
	return s;
}

__ENCODING_END__

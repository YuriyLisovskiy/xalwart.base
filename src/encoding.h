/**
 * encoding.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Encoding/decoding utilities for string.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__ENCODING_BEGIN__

// Converts character to percent-encoded character and writes it to stream.
//
// `safe`: string which contains chars that must not be converted. If char 'c'
// is in this sequence, it will be written to stream without converting.
//
// RFC 3986 section 2.2 Reserved Characters: ! * ' ( ) ; : @ & = + $ , / ? # [ ]
// RFC 3986 section 2.3 Unreserved Characters: ALPHA NUMERIC - _ . ~
//
// `stream`: target stream.
// `c`: char to write.
// `safe`: characters which should be ignored.
extern void _escape_char(std::ostringstream& stream, char c, const std::string& safe="");

// Encodes url using percent-encoding.
extern std::string encode_url(const std::string& url);

// Encodes string to hex.
//
// `s`: input string.
// `safe`: characters which should be ignored.
extern std::string quote(const std::string& s, const std::string& safe="");

// Supported encodings.
enum encoding
{
	ascii, latin_1, iso_8859_1, utf_8
};

// Supported modes.
enum Mode
{
	STRICT, // throw EncodingError if string violates encoding rules;
	IGNORE, // remove offending symbols from string;
	REPLACE // replace offending symbols by question mark ('?').
};

// Encode string using given encoding and mode.
//
// `s`: string to encode.
// `enc`: target encoding.
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode(const std::string& s, encoding enc, Mode mode=Mode::STRICT);

// Encodes string to ASCII string.
//
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode_ascii(const std::string& s, Mode mode);

// latin-1 encoding.
//
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode_iso_8859_1(const std::string& s, Mode mode);

// Encodes string to UTF-8 string.
//
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode_utf_8(const std::string& s, Mode mode);

__ENCODING_END__

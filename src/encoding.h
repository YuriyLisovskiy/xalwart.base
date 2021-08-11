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
// Reserved Characters: ; : @ & = + $ , / ? # [ ]
// Unreserved Characters: ALPHA NUMERIC - _ . ! ~ * ' ( )
//
// `stream`: target stream.
// `c`: char to write.
// `safe`: characters which should be ignored.
extern void _escape_char(std::ostringstream& stream, char c, const std::string& safe="");

// Encodes string to hex using `_escape_char(...)`.
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

// Encodes string to ASCII string.
//
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode_ascii(const std::string& s, Mode mode);

// latin-1 encoding.
//
// !IMPORTANT!
// Characters from `0x7F` to `0xA0` are not tested!
//
// `s`: string to encode.
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

// Encode string using given encoding and mode.
//
// `s`: string to encode.
// `enc`: target encoding.
// `mode`: target mode.
//
// Returns encoded copy input string.
extern std::string encode(const std::string& s, encoding enc, Mode mode=Mode::STRICT);

__ENCODING_END__

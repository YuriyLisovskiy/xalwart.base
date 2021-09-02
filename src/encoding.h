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
#include <vector>
#include <tuple>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./unicode/_def_.h"


__ENCODING_BEGIN__

// TESTME: _is16
// Reports whether r is in the sorted vector of 16-bit ranges.
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
extern bool _is16(const std::vector<unicode::Range16>& ranges, uint16_t r);

// TESTME: _is32
// Reports whether r is in the sorted slice of 32-bit ranges.
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
extern bool _is32(const std::vector<unicode::Range32>& ranges, uint32_t r);

// TESTME: _is_excluding_latin
//
// The original implementation is in Golang 1.15.8: unicode/letter.go
extern bool _is_excluding_latin(const unicode::RangeTable& range_table, wchar_t c);

// TESTME: is_space
// Reports whether the wchar_t is a space character as defined
// by Unicode's White Space property; in the Latin-1 space
// this is
//	'\t', '\n', '\v', '\f', '\r', ' ', U+0085 (NEL), U+00A0 (NBSP).
//
// The original implementation is in Golang 1.15.8: unicode/graphic.go
bool is_space(wchar_t c);

// TESTME: is_hex
extern bool is_hex(char c);

// TESTME: unhex
extern char unhex(char c);

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
extern void escape_char(std::ostringstream& stream, char c, const std::string& safe="");

// Encodes string to hex using `escape_char(...)`.
//
// `s`: input string.
// `safe`: characters which should be ignored.
extern std::string quote(const std::string& s, const std::string& safe="");

// Supported encodings.
enum class Encoding
{
	ASCII, Latin_1, ISO_8859_1, Utf_8
};

// Supported modes.
enum class Mode
{
	Strict, // throw EncodingError if string violates encoding rules;
	Ignore, // remove offending symbols from string;
	Replace // replace offending symbols by question mark ('?').
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
extern std::string encode(const std::string& s, Encoding enc, Mode mode=Mode::Strict);

// TESTME: decode2231
// TODO: docs for 'decode2231'
//
// The original implementation is in Golang 1.15.8: mime/mediatype.go
extern std::tuple<std::wstring, bool> decode2231(const std::wstring& s);

// TESTME: percent_hex_unescape
// TODO: docs for 'percent_hex_unescape'
//
// The original implementation is in Golang 1.15.8: mime/mediatype.go
extern std::string percent_hex_unescape(std::string s);

__ENCODING_END__

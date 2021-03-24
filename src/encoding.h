/**
 * encoding.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Purpose: encoding/decoding of string.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__ENCODING_BEGIN__

// Encodes url using percent-encoding.
extern std::string encode_url(const std::string& url);

extern std::string quote(const std::string& s, const std::string& safe="");

enum encoding
{
	ascii, latin_1, iso_8859_1, utf_8
};

enum Mode
{
	STRICT, IGNORE, REPLACE
};

// TODO: add more encodings.
// Encode string to given encoding.
//
// Available encodings:
//  - ascii
//  - latin_1 (iso_8859_1)
//
// Modes:
//  - strict: throws EncodingError if string violates encoding rules;
//  - ignore: removes offending symbols from string;
//  - replace: replaces offending symbols by question mark ('?').
extern std::string encode(const std::string& s, encoding enc, Mode mode=Mode::STRICT);

// Encodes string to ASCII string.
extern std::string encode_ascii(const std::string& s, Mode mode);

// latin-1 encoding.
extern std::string encode_iso_8859_1(const std::string& s, Mode mode);

// Encodes string to UTF-8 string.
extern std::string encode_utf_8(const std::string& s, Mode mode);

__ENCODING_END__

/**
 * unicode/utf8.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * UTF-8 basic utilities.
 *
 * Implementation is based on Golang 1.15.8: unicode/utf8/utf8.go
 */

#pragma once

// C++ libraries.
#include <string>
#include <tuple>

// Module definitions.
#include "./_def_.h"


__UNICODE_UTF8_BEGIN__

// 'decode_symbol' unpacks the first UTF-8 encoding in 'string' and returns
// unsigned character and its width in bytes. If 'string' is empty it returns
// \0 character and 0 as a size.
// Otherwise, if the encoding is invalid, it throws 'EncodingError'.
std::tuple<uint32_t, size_t> decode_symbol(const std::string& s);

__UNICODE_UTF8_END__

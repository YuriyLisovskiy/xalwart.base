/**
 * net/utility.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Common net utilities.
 */

#pragma once

// C++ libraries.
#include <string>
#include <map>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../io.h"


__NET_BEGIN__

// TESTME: parse_headers
/** Parses only RFC2822 headers from a stream.
 *
 * \param result contains collected header values
 * \param reader stream to read from
 * \param max_header_length maximum header's size before throwing `LineTooLongError`
 * \param max_headers_count maximum headers count before throwing `TooMuchHeadersError`
 *
 * \throw `LineTooLongError`, `TooMuchHeadersError`.
 *
 * \return total bytes read count.
 */
extern size_t parse_headers(
	std::map<std::string, std::string>& result, io::IReader* reader,
	size_t max_header_length,
	size_t max_headers_count
);

__NET_END__

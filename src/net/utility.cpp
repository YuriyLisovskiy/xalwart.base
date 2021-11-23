/**
 * encoding.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./utility.h"

// Base libraries.
#include "../exceptions.h"
#include "../string_utils.h"
#include "../encoding.h"


__NET_BEGIN__

size_t parse_headers(
	std::map<std::string, std::string>& result, io::IReader* reader,
	size_t max_header_length,
	size_t max_headers_count
)
{
	const short HEADER_KEY = 0, HEADER_VALUE = 1;
	size_t total_bytes_read = 0;
	std::string header_line;
	while (reader->read_line(header_line))
	{
		total_bytes_read += header_line.size();
		if (header_line.size() > max_header_length)
		{
			throw LineTooLongError(
				"The header contains a value that exceeds " + std::to_string(max_header_length) + " bytes",
				_ERROR_DETAILS_
			);
		}

		header_line = str::rtrim(header_line, "\r\n");
		auto full_header = str::split(
			encoding::encode_iso_8859_1(header_line, encoding::Mode::Strict), ':', 1
		);
		if (result.size() > max_headers_count)
		{
			throw TooMuchHeadersError(
				"Headers count exceeds " + std::to_string(max_headers_count), _ERROR_DETAILS_
			);
		}

		if (header_line.empty() || header_line == "\r\n" || header_line == "\n")
		{
			break;
		}

		if (full_header.size() == 1)
		{
			full_header.emplace_back("");
		}

		full_header[HEADER_VALUE] = str::ltrim(full_header[HEADER_VALUE]);
		result.insert(std::make_pair(full_header[HEADER_KEY], full_header[HEADER_VALUE]));
	}

	return total_bytes_read;
}

__NET_END__

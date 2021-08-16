/**
 * net/request_context.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Data transfer object of request between server and main application.
 */

#pragma once

// C++ libraries.
#include <functional>
#include <string>
#include <map>

// Module definitions.
#include "./_def_.h"


__NET_BEGIN__

struct RequestContext
{
	// Major part of http protocol version.
	size_t major_v{};

	// Minor part of http protocol version.
	size_t minor_v{};

	// Request's path.
	std::string path;

	// Contains request's query.
	// If field is empty-string, request has not query.
	std::string query;

	// Hold http request's method type.
	std::string method;

	// Indicates whether request's connection is keep alive or not.
	bool keep_alive{};

	// Contains body of http request.
	std::string content;

	// Accumulates request's headers.
	std::map<std::string, std::string> headers;

	// Contains the size of request's content.
	unsigned long long content_size{};

	// Contains the size of request's chunk as std::string.
	// Used only for chunked requests.
	std::string chunk_str;

	// Contains the size of request's chunk.
	// Used only for chunked requests.
	unsigned long long chunk_size{};

	// Indicates whether request is chunked or not.
	bool chunked{};

	std::function<bool(const char* data, size_t n)> write;

	// Checks if current protocol major and minor versions are
	// the same as provided.
	[[nodiscard]]
	inline bool proto_v_eq_to(short major, short minor) const
	{
		return this->major_v == major && this->minor_v == minor;
	}

	// Checks if current protocol major and minor versions are greater
	// than or equal to provided.
	[[nodiscard]]
	inline bool proto_v_gte(short major, short minor) const
	{
		return this->proto_v_eq_to(major, minor) || this->proto_v_gt(major, minor);
	}

	// Checks if current protocol major and minor versions are less
	// than or equal to provided.
	[[nodiscard]]
	inline bool proto_v_lte(short major, short minor) const
	{
		return this->proto_v_eq_to(major, minor) || this->proto_v_lt(major, minor);
	}

	// Checks if current protocol major and minor versions are greater
	// than provided.
	[[nodiscard]]
	inline bool proto_v_gt(short major, short minor) const
	{
		return this->major_v > major || (!(major > this->major_v) && this->minor_v > minor);
	}

	// Checks if current protocol major and minor versions are less
	// than provided.
	[[nodiscard]]
	inline bool proto_v_lt(short major, short minor) const
	{
		return this->major_v < major || (!(major < this->major_v) && this->minor_v < minor);
	}
};

// Function type that handles the request.
typedef std::function<uint(RequestContext*, const std::map<std::string, std::string>&)> HandlerFunc;

__NET_END__

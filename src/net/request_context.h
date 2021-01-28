/**
 * net/request_context.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <map>
#include <functional>
#include <string>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../collections/dict.h"


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
	collections::Dict<std::string, std::string> headers;

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

	[[nodiscard]]
	bool proto_v_eq(short major, short minor) const;

	[[nodiscard]]
	bool proto_v_gte(short major, short minor) const;

	[[nodiscard]]
	bool proto_v_lte(short major, short minor) const;

	[[nodiscard]]
	bool proto_v_gt(short major, short minor) const;

	[[nodiscard]]
	bool proto_v_lt(short major, short minor) const;
};

typedef std::function<uint(
	RequestContext*, collections::Dict<std::string, std::string>
)> HandlerFunc;

__NET_END__

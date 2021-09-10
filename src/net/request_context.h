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
#include <memory>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../io.h"


__NET_BEGIN__

struct ProtocolVersion
{
	size_t major{};
	size_t minor{};

	inline bool operator== (const ProtocolVersion& other) const
	{
		return this->major == other.major && this->minor == other.minor;
	}

	inline bool operator> (const ProtocolVersion& other) const
	{
		return this->major > other.major || (other.major <= this->major && this->minor > other.minor);
	}

	inline bool operator>= (const ProtocolVersion& other) const
	{
		return *this > other || *this == other;
	}

	inline bool operator< (const ProtocolVersion& other) const
	{
		return this->major < other.major || (other.major >= this->major && this->minor < other.minor);
	}

	inline bool operator<= (const ProtocolVersion& other) const
	{
		return *this < other || *this == other;
	}
};

struct RequestContext
{
	ProtocolVersion protocol_version;

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
	std::shared_ptr<io::ILimitedBufferedStream> body;

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

	std::shared_ptr<io::IWriter> response_writer;
};

__NET_END__

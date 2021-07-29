/**
 * net/abc.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Abstract base classes for `net` module.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./request_context.h"
#include "../collections/dictionary.h"


__NET_ABC_BEGIN__

// Base class (interface) for server implementation.
class IServer
{
public:
	virtual void setup_handler(net::HandlerFunc handler) = 0;

	// Binds socket.
	virtual void bind(const std::string& address, uint16_t port) = 0;

	// Listens the socket.
	virtual void listen(const std::string& startup_message) = 0;

	// Shutdowns and closes server socket.
	virtual void close() = 0;

	// Returns server's environment variables.
	[[nodiscard]]
	virtual collections::Dictionary<std::string, std::string> environ() const = 0;

protected:

	// Initializes environment variables of the server.
	virtual void init_environ() = 0;
};

__NET_ABC_END__

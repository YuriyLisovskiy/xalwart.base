/**
 * net/abc.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Abstract base classes for 'net' module.
 */

#pragma once

// C++ libraries.
#include <string>
#include <map>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./request_context.h"


__NET_ABC_BEGIN__

// Base class (interface) for server implementation.
class Server
{
public:
	// Binds socket.
	virtual void bind(const std::string& address, uint16_t port) = 0;

	// Listens bound socket.
	virtual void listen(const std::string& startup_message) = 0;

	// Shutdowns and closes server socket.
	virtual void close() = 0;

	// Returns server's environment variables.
	[[nodiscard]]
	virtual std::map<std::string, std::string> get_environment() const = 0;

	// Mark server development if it is not production-ready.
	// This will notify user not to use it for production.
	[[nodiscard]]
	virtual bool is_development() const = 0;

protected:

	// Initializes environment variables of the server.
	virtual void initialize_environment() = 0;
};

__NET_ABC_END__

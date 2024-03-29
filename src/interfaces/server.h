/**
 * interfaces/server.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Interfaces related to server.
 */

#pragma once

// C++ libraries.
#include <string>
#include <map>

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "../net/request_context.h"


__SERVER_BEGIN__

// Base class (interface) for server implementation.
class IServer
{
public:
	virtual ~IServer() = default;

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

__SERVER_END__

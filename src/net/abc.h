/**
 * net/abc.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: abstract base classes for net module.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./request_context.h"
#include "../collections/dict.h"


__NET_BEGIN__

class IServer
{
public:
	virtual void setup_handler(net::HandlerFunc handler) = 0;

	// Bind socket.
	virtual void bind(const std::string& address, uint16_t port) = 0;

	// Listen the socket.
	virtual void listen(const std::string& startup_message) = 0;

	// Shutdown and close server socket.
	virtual void close() = 0;

	[[nodiscard]]
	virtual collections::Dict<std::string, std::string> environ() const = 0;

protected:
	virtual void init_environ() = 0;
};

__NET_END__

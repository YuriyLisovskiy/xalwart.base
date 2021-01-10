/**
 * server.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./collections/dict.h"


__CORE_BEGIN__

class IServer
{
public:
	// Bind socket.
	virtual void bind(const std::string& address, uint16_t port) = 0;

	// Listen the socket.
	virtual void listen(const std::string& startup_message) = 0;

	// Shutdown and close server socket.
	virtual void close() = 0;

	// Send all bytes.
	virtual core::Error send(int sock, const char* data) = 0;

	// Write n bytes from data array.
	virtual core::Error write(int sock, const char* data, size_t n) = 0;

	virtual void init_environ() = 0;

	[[nodiscard]]
	virtual collections::Dict<std::string, std::string> environ() const = 0;
};

__CORE_END__

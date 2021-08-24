/**
 * io.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__IO_BEGIN__

class IReader
{
public:
	/**
	 * Reads all bytes from stream before `\r\n` sequence.
	 *
	 * \return `true` if there are more bytes to read, `false` otherwise.
	 */
	virtual bool read_line(std::string& buffer) = 0;

	/**
	 * Reads all bytes from stream.
	 *
	 * \return `true` if there are more bytes to read, `false` otherwise.
	 */
	virtual bool read_all(std::string& buffer) = 0;

	/**
	 * Closes the stream.
	 *
	 * \return `true` if the operation is successful, `false` otherwise.
	 */
	virtual bool close_reader() = 0;
};

class IWriter
{
public:
	/**
	 * Writes `count` bytes to stream.
	 *
	 * \return `true` if the operation is successful, `false` otherwise.
	 */
	virtual bool write(const char* buffer, ssize_t count) = 0;

	/**
	 * Closes the stream.
	 *
	 * \return `true` if the operation is successful, `false` otherwise.
	 */
	virtual bool close_writer() = 0;
};

__IO_END__

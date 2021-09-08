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
	virtual ssize_t read_line(std::string& buffer) = 0;

	/**
	 * Reads `max_count` or less bytes from stream.
	 *
	 * \return `true` if there are more bytes to read, `false` otherwise.
	 */
	virtual ssize_t read(std::string& buffer, size_t max_count) = 0;

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
	virtual ssize_t write(const char* buffer, size_t count) = 0;

	/**
	 * Closes the stream.
	 *
	 * \return `true` if the operation is successful, `false` otherwise.
	 */
	virtual bool close_writer() = 0;
};

// TODO: docs for 'ILimiter'
class ILimiter
{
public:
	/**
	 * Negative limit means that reader has no limit.
	 */
	virtual void set_limit(ssize_t limit) = 0;

	[[nodiscard]]
	virtual ssize_t limit() const = 0;
};

// TODO: docs for 'IBuffer'
class IBuffer
{
public:
	virtual ssize_t peek(std::string& buffer, size_t max_count) = 0;

	[[nodiscard]]
	virtual ssize_t buffered() const = 0;
};

// TODO: docs for 'IBufferedReader'
class IBufferedReader : public IReader, public IBuffer
{
};

// TODO: docs for 'ILimitedBufferedReader'
class ILimitedBufferedReader : public IBufferedReader, public ILimiter
{
};

// TODO: docs for 'ILimitedBufferedStream'
class ILimitedBufferedStream : public ILimitedBufferedReader, public IWriter
{
};

__IO_END__

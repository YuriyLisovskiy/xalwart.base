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
	virtual ssize_t write(const char* buffer, ssize_t count) = 0;

	/**
	 * Closes the stream.
	 *
	 * \return `true` if the operation is successful, `false` otherwise.
	 */
	virtual bool close_writer() = 0;
};

// TODO: docs for 'IBufferedReader'
class IBufferedReader : public io::IReader
{
public:
	virtual ssize_t peek(std::string& buffer, ssize_t max_count) = 0;

	[[nodiscard]]
	virtual ssize_t buffered() const = 0;
};

class IStream : public IReader, public IWriter
{
public:

	/**
	 * Closes input and output streams.
	 *
	 * \return `true` if both operations are successful, `false` otherwise.
	 */
	inline virtual bool close()
	{
		return this->close_reader() && this->close_writer();
	}
};

class IBufferedStream : public IBufferedReader, public IWriter
{
public:

	/**
	 * Closes input and output streams.
	 *
	 * \return `true` if both operations are successful, `false` otherwise.
	 */
	inline virtual bool close()
	{
		return this->close_reader() && this->close_writer();
	}
};

__IO_END__

/**
 * error.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Error class for lightweight exception-like handling.
 */

#pragma once

// C++ libraries.
#include <ostream>
#include <string>

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

// Supported error types.
enum error_type
{
	None = 0,
	HttpError = 1,

	// HttpError-based exceptions.
	EntityTooLargeError = 2,
	FileDoesNotExistError = 3,
	PermissionDenied = 4,
	NotFound = 5,
	InternalServerError = 6,
	RequestTimeout = 7,
	SuspiciousOperation = 8,

	// SuspiciousOperation-based exceptions.
	DisallowedHost = 9,
	DisallowedRedirect = 10
};

// Returns string representation of error type.
// If error type is not known, returns "Unknown".
//
// `et`: error type object to convert.
extern std::string to_string(error_type et);

// Error representation.
struct Error
{
	// Error type.
	error_type type = None;

	// Line number where error was occurred.
	int line = 0;

	// Function name where error was occurred.
	std::string func;

	// File name where error was occurred.
	std::string file;

	// Error message.
	std::string msg;

	inline Error(
		error_type type, std::string msg, int line, const char* func, const char* file
	) : type(type), msg(std::move(msg)), line(line), func(func), file(file)
	{
	}

	// Constructs error with empty line, function and file names.
	inline explicit Error(error_type type, const std::string& msg) : Error(type, msg, 0, "", "")
	{
	}

	// Constructs `None` error.
	inline Error() : Error(None, "", 0, "", "")
	{
	}

	// Returns `None` error.
	inline static Error none()
	{
		return Error();
	}

	// Returns `true` if error type is not `None`, `false` otherwise.
	inline explicit operator bool() const
	{
		return this->type != None;
	}

	// Returns `true` if error type not `None`, `false` otherwise.
	inline bool operator !() const
	{
		return this->type == None;
	}

	// Returns error message and it's type as `std::string`.
	[[nodiscard]]
	inline std::string get_message() const
	{
		return to_string(this->type) + ": " + this->msg;
	}
};

__CORE_END__

// Writes `error_type` object to stream.
inline std::ostream& operator<<(std::ostream& os, const xw::core::error_type& type)
{
	return os << to_string(type);
}

// Formats and writes `Error` object to stream.
inline std::ostream& operator<<(std::ostream& os, const xw::core::Error& err)
{
	return os << "\nFile \"" << err.file << "\", line " << err.line << ", in " << err.func << '\n' << err.msg;
}

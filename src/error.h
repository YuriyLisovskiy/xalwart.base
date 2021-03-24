/**
 * error.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: error holder for lightweight exception-like handling.
 */

#pragma once

// C++ libraries.
#include <ostream>
#include <string>

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

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
extern std::string to_string(error_type et);

struct Error
{
	error_type type = None;
	int line = 0;
	std::string func;
	std::string file;
	std::string msg;

	inline Error(
		error_type type, std::string msg, int line, const char* func, const char* file
	) : type(type), msg(std::move(msg)), line(line), func(func), file(file)
	{
	}

	inline explicit Error(error_type type, const std::string& msg) : Error(type, msg, 0, "", "")
	{
	}

	inline Error() : Error(None, "", 0, "", "")
	{
	}

	inline static Error none()
	{
		return Error();
	}

	inline explicit operator bool() const
	{
		return this->type != None;
	}

	inline bool operator !() const
	{
		return this->type == None;
	}

	[[nodiscard]]
	inline std::string get_message() const
	{
		return to_string(this->type) + ": " + this->msg;
	}
};

__CORE_END__

inline std::ostream& operator<<(std::ostream& os, const xw::core::error_type& type)
{
	return os << to_string(type);
}

inline std::ostream& operator<<(std::ostream& os, const xw::core::Error& err)
{
	return os << "\nFile \"" << err.file << "\", line " << err.line << ", in " << err.func << '\n' << err.msg;
}

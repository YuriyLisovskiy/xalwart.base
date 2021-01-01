/**
 * error.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <ostream>
#include <string>

// Module definitions.
#include "./_def_.h"


__CORE_INTERNAL_BEGIN__

const short ERROR_T_HTTP_LOWER = 2;
const short ERROR_T_HTTP_UPPER = 7;

const short ERROR_T_SO_LOWER = 8;
const short ERROR_T_SO_UPPER = 9;

__CORE_INTERNAL_END__

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
	SuspiciousOperation = 7,

	// SuspiciousOperation-based exceptions.
	DisallowedHost = 8,
	DisallowedRedirect = 9
};

extern std::string to_string(error_type et);

struct Error
{
	error_type type{};
	int line = 0;
	const char* func = "";
	const char* file = "";
	const char* msg = "";

	Error(
		error_type type, const char* msg, int line, const char* func, const char* file
	);

	Error(
		error_type type, const std::string& msg, int line, const char* func, const char* file
	);

	explicit Error(error_type type, const char* msg);

	explicit Error(error_type type, const std::string& msg);

	Error();

	static Error none();

	explicit operator bool() const;

	std::string get_message() const;
};

__CORE_END__

std::ostream& operator<<(std::ostream& os, const xw::core::error_type& type);

std::ostream& operator<<(std::ostream& os, const xw::core::Error& err);

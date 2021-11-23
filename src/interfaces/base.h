/**
 * interfaces/base.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Interfaces for 'base' library.
 */

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "../exceptions.h"
#include "../vendor/nlohmann/json.h"


__MAIN_NAMESPACE_BEGIN__

// TODO: docs for 'ILogger'
class ILogger
{
public:
	enum class Color
	{
		Default,
		Black,
		Red,
		Green,
		Yellow,
		Blue,
		Magenta,
		Cyan,
		White,
		BoldBlack,
		BoldRed,
		BoldGreen,
		BoldYellow,
		BoldBlue,
		BoldMagenta,
		BoldCyan,
		BoldWhite,
	};

	virtual void enable_colors() = 0;
	virtual void disable_colors() = 0;

	virtual ~ILogger() = default;

	// Logs given text, line, function name and file name with 'info' logging level.
	virtual void info(const std::string& msg, int line, const char* function, const char* file) const = 0;

	// Logs given text with 'info' logging level.
	virtual void info(const std::string& msg) const = 0;

	// Logs given text, line, function name and file name with 'debug' logging level.
	virtual void debug(const std::string& msg, int line, const char* function, const char* file) const = 0;

	// Logs given text with 'debug' logging level.
	virtual void debug(const std::string& msg) const = 0;

	// Logs given text, line, function name and file name with 'warning' logging level.
	virtual void warning(const std::string& msg, int line, const char* function, const char* file) const = 0;

	// Logs given text with 'warning' logging level.
	virtual void warning(const std::string& msg) const = 0;

	// Logs given text, line, function name and file name with 'error' logging level.
	virtual void error(const std::string& msg, int line, const char* function, const char* file) const = 0;

	// Logs given text with 'error' logging level.
	virtual void error(const std::string& msg) const = 0;

	// Logs given text, line, function name and file name with 'trace' logging level.
	virtual void trace(const std::string& msg, int line, const char* function, const char* file) const = 0;

	// Logs given text with 'trace' logging level.
	virtual void trace(const std::string& msg) const = 0;

	virtual void print(const std::string& msg, Color colour, char end) const = 0;
	virtual void print(const std::string& msg, Color colour) const = 0;
	virtual void print(const std::string& msg) const = 0;

	// Logs exception with 'info' logging level.
	virtual void info(const BaseException& exc) const = 0;

	// Logs exception with 'debug' logging level.
	virtual void debug(const BaseException& exc) const = 0;

	// Logs exception with 'warning' logging level.
	virtual void warning(const BaseException& exc) const = 0;

	// Logs exception with 'error' logging level.
	virtual void error(const BaseException& exc) const = 0;
};

// TODO: docs for 'StringSerializable'
class IStringSerializable
{
public:
	[[nodiscard]]
	virtual std::string to_string() const = 0;
};

// TODO: docs for 'JsonSerializable'
class IJsonSerializable
{
public:
	[[nodiscard]]
	virtual nlohmann::json to_json() const = 0;
};

__MAIN_NAMESPACE_END__

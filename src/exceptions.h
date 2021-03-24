/**
 * exceptions.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * 	- BaseException - main exception class
 *
 * Exception-based exceptions:
 *	- AttributeError
 *	- ArgumentError
 *	- BadSignature
 *	- CommandError
 *	- DictError
 *	- EncodingError
 *	- FileError
 *	- ImproperlyConfigured
 *	- InterruptException
 *	- ParseError
 *	- RuntimeError
 *	- NotImplementedException
 *	- NullPointerException
 *	- SocketError
 *	- TypeError
 *	- ValueError
 *
 * DictError-based exceptions:
 *	- MultiPartParserError
 *	- MultiValueDictError
*/

#pragma once

// C++ libraries.
#include <string>

// Module definitions.
#include "./_def_.h"


__CORE_BEGIN__

class BaseException : public std::exception
{
protected:
	std::string _exception_type;
	std::string _message;
	int _line;
	const char* _function;
	const char* _file;

	// Use only when initializing of a derived exception!
	BaseException(const char* message, int line, const char* function, const char* file, const char* type);

public:
	BaseException(const char* message, int line, const char* function, const char* file);
	~BaseException() noexcept override = default;

	[[nodiscard]] const char* what() const noexcept override;
	[[nodiscard]] virtual int line() const noexcept;
	[[nodiscard]] virtual const char* function() const noexcept;
	[[nodiscard]] virtual const char* file() const noexcept;
	[[nodiscard]] virtual std::string get_message() const noexcept;
};

DEF_EXCEPTION_WITH_BASE(AttributeError, BaseException, "attribute error");
DEF_EXCEPTION_WITH_BASE(ArgumentError, BaseException, "argument error");
DEF_EXCEPTION_WITH_BASE(BadSignature, BaseException, "bad signature error");
DEF_EXCEPTION_WITH_BASE(CommandError, BaseException, "command error");
DEF_EXCEPTION_WITH_BASE(DictError, BaseException, "dict error");

// Redirect to scheme not in allowed list.
DEF_EXCEPTION_WITH_BASE(EncodingError, BaseException, "encoding error");
DEF_EXCEPTION_WITH_BASE(FileError, BaseException, "file error");
DEF_EXCEPTION_WITH_BASE(ImproperlyConfigured, BaseException, "improperly configured");

class InterruptException : public BaseException
{
protected:
	// Use only when initializing of a derived exception!
	InterruptException(
		const char* message, int line, const char* function, const char* file, const char* type
	);

	static void handle_signal(int sig);
public:
	explicit InterruptException(
		const char* message, int line = 0, const char* function = "", const char* file = ""
	);
	explicit InterruptException(
		const std::string& message, int line = 0, const char* function = "", const char* file = ""
	);
	static void initialize();
};

DEF_EXCEPTION_WITH_BASE(ParseError, BaseException, "parse error");
DEF_EXCEPTION_WITH_BASE(RuntimeError, BaseException, "runtime error");
DEF_EXCEPTION_WITH_BASE(MultiPartParserError, ParseError, "multipart parser error");
DEF_EXCEPTION_WITH_BASE(MultiValueDictError, DictError, "multi-value dict error");
DEF_EXCEPTION_WITH_BASE(NotImplementedException, BaseException, "not implemented");
DEF_EXCEPTION_WITH_BASE(NullPointerException, BaseException, "null pointer exception");

class SocketError : public BaseException
{
private:
	int _errno;

protected:
	SocketError(
		int err_no, const char* message, int line, const char* function, const char* file, const char* type
	);

public:
	explicit SocketError(
		int err_no, const char* message, int line = 0, const char* function = "", const char* file = ""
	);

	explicit SocketError(
		int err_no, const std::string& message, int line = 0, const char* function = "", const char* file = ""
	);

	[[nodiscard]]
	int err_no() const;
};

DEF_EXCEPTION_WITH_BASE(ValueError, BaseException, "value error");
DEF_EXCEPTION_WITH_BASE(TypeError, BaseException, "type error");

__CORE_END__

/**
 * exceptions.h
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
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
//	std::string _full_message;
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


DEF_EXCEPTION_WITH_BASE(AttributeError, BaseException, "Attribute Error");
DEF_EXCEPTION_WITH_BASE(ArgumentError, BaseException, "Argument Error");
DEF_EXCEPTION_WITH_BASE(BadSignature, BaseException, "Bad Signature Error");
DEF_EXCEPTION_WITH_BASE(CommandError, BaseException, "Command Error");
DEF_EXCEPTION_WITH_BASE(DictError, BaseException, "Dict Error");

// Redirect to scheme not in allowed list.
DEF_EXCEPTION_WITH_BASE(EncodingError, BaseException, "Encoding Error");
DEF_EXCEPTION_WITH_BASE(FileError, BaseException, "File Error");
DEF_EXCEPTION_WITH_BASE(ImproperlyConfigured, BaseException, "Improperly Configured");

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

DEF_EXCEPTION_WITH_BASE(ParseError, BaseException, "Parse Error");
DEF_EXCEPTION_WITH_BASE(RuntimeError, BaseException, "Runtime Error");
DEF_EXCEPTION_WITH_BASE(MultiPartParserError, ParseError, "Multipart Parser Error");
DEF_EXCEPTION_WITH_BASE(MultiValueDictError, DictError, "Multi-Value Dict Error");
DEF_EXCEPTION_WITH_BASE(NotImplementedException, BaseException, "Not Implemented");
DEF_EXCEPTION_WITH_BASE(NullPointerException, BaseException, "Null Pointer Exception");
DEF_EXCEPTION_WITH_BASE(SocketError, BaseException, "Socket Error");
DEF_EXCEPTION_WITH_BASE(ValueError, BaseException, "Value Error");
DEF_EXCEPTION_WITH_BASE(TypeError, BaseException, "Type Error");

__CORE_END__

/**
 * exceptions.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * 	- BaseException - main exception class
 *
 * List of exceptions:
 *	- AttributeError
 *	- ArgumentError
 *	- BadSignature
 *	- CommandError
 *	- EncodingError
 *	- EscapeError
 *	- FileError
 *	- ImproperlyConfigured
 *	- InterruptException
 *	- KeyError
 *	- ParseError
 *	- RuntimeError
 *	- MultiPartParserError
 *	- NotImplementedException
 *	- NullPointerException
 *	- SocketError
 *	- TypeError
 *	- ValueError
*/

#pragma once

// C++ libraries.
#include <string>


namespace xw
{
// Base exception which is used in framework.
// Used to build new exception types.
class BaseException : public std::exception
{
protected:

	// Holds exception type name.
	std::string _exception_type;

	// Error message.
	std::string _message;

	// Line where an exception was generated.
	int _line;

	// Function name where an exception was generated.
	const char* _function;

	// File name where an exception was generated.
	const char* _file;

	// Use only for initializing in derived exception's constructor!
	inline BaseException(const char* message, int line, const char* function, const char* file, const char* type)
		: _message(message), _line(line), _function(function), _file(file), _exception_type(type)
	{
	}

public:

	// Initializes exception with type name.
	inline BaseException(const char* message, int line, const char* function, const char* file)
		: BaseException(message, line, function, file, "xw::BaseException")
	{
	}

	// Default destructor.
	~BaseException() noexcept override = default;

	// Returns error message as `const char*`.
	[[nodiscard]]
	inline const char* what() const noexcept override
	{
		return this->_message.c_str();
	}

	// Returns line where an exception was generated.
	[[nodiscard]]
	virtual inline int line() const noexcept
	{
		return this->_line;
	}

	// Returns function name where an exception was generated.
	[[nodiscard]]
	virtual inline const char* function() const noexcept
	{
		return this->_function;
	}

	// Returns file name where an exception was generated.
	[[nodiscard]]
	virtual inline const char* file() const noexcept
	{
		return this->_file;
	}

	// Returns error message with exception type as `std::string`.
	[[nodiscard]]
	virtual inline std::string get_message() const noexcept
	{
		return this->_exception_type + ": " + this->_message;
	}
};

// Declares exception's class with given base.
#define DEF_EXCEPTION_WITH_BASE(name, base, default_message, additional_namespace_name)\
class name : public base\
{\
protected:\
	name(\
		const char* message, int line, const char* function, const char* file, const char* type\
	)\
		: base(message, line, function, file, type)\
	{\
	}\
\
public:\
	explicit name(\
		const char* message = default_message,\
		int line=0, const char* function="", const char* file=""\
	) : name(\
		message, line, function, file, ("xw::" + std::string(additional_namespace_name) + std::string(#name)).c_str() \
	)\
	{\
	}\
\
	explicit name(\
		const std::string& message = default_message,\
		int line=0, const char* function="", const char* file=""\
	)\
		: name(message.c_str(), line, function, file)\
	{\
	}\
}

DEF_EXCEPTION_WITH_BASE(AttributeError, BaseException, "attribute error", "");
DEF_EXCEPTION_WITH_BASE(ArgumentError, BaseException, "argument error", "");
DEF_EXCEPTION_WITH_BASE(BadSignature, BaseException, "bad signature error", "");
DEF_EXCEPTION_WITH_BASE(CommandError, BaseException, "command error", "");

// Redirect to scheme not in allowed list.
DEF_EXCEPTION_WITH_BASE(EncodingError, BaseException, "encoding error", "");
DEF_EXCEPTION_WITH_BASE(EscapeError, BaseException, "escape error", "");
DEF_EXCEPTION_WITH_BASE(FileError, BaseException, "file error", "");
DEF_EXCEPTION_WITH_BASE(ImproperlyConfigured, BaseException, "improperly configured", "");

// Used for handling execution interrupts.
class InterruptException : public BaseException
{
protected:
	// Use only when initializing of a derived exception!
	inline InterruptException(
		const char* message, int line, const char* function, const char* file, const char* type
	) : BaseException(message, line, function, file, type)
	{
	}

	// Throws interrupt exception with signal number.
	static inline void handle_signal(int sig)
	{
		throw InterruptException("execution is interrupted with signal " + std::to_string(sig));
	}

public:
	inline explicit InterruptException(
		const char* message, int line=0, const char* function="", const char* file=""
	) : InterruptException(message, line, function, file, "xw::InterruptException")
	{
	}

	inline explicit InterruptException(
		const std::string& message, int line=0, const char* function="", const char* file=""
	) : InterruptException(message.c_str(), line, function, file)
	{
	}

	// Initializes interruption signals which should be handled.
	static void initialize();
};

DEF_EXCEPTION_WITH_BASE(KeyError, BaseException, "key error", "");
DEF_EXCEPTION_WITH_BASE(RuntimeError, BaseException, "runtime error", "");
DEF_EXCEPTION_WITH_BASE(NotImplementedException, BaseException, "not implemented", "");
DEF_EXCEPTION_WITH_BASE(NullPointerException, BaseException, "null pointer exception", "");
DEF_EXCEPTION_WITH_BASE(ValueError, BaseException, "value error", "");
DEF_EXCEPTION_WITH_BASE(TypeError, BaseException, "type error", "");
DEF_EXCEPTION_WITH_BASE(IOError, BaseException, "io error", "");
DEF_EXCEPTION_WITH_BASE(ReaderError, IOError, "reader error", "");
DEF_EXCEPTION_WITH_BASE(WriterError, IOError, "writer error", "");
DEF_EXCEPTION_WITH_BASE(ServerError, BaseException, "server error", "");
DEF_EXCEPTION_WITH_BASE(ParseError, ServerError, "parse error", "");
DEF_EXCEPTION_WITH_BASE(EntityTooLargeError, ServerError, "entity too large  error", "");
DEF_EXCEPTION_WITH_BASE(EoF, BaseException, "EOF", "");
DEF_EXCEPTION_WITH_BASE(UnexpectedEoF, EoF, "unexpected EOF", "");

// TESTME: LineTooLongError
// TODO: docs for 'LineTooLongError'
class LineTooLongError : public ParseError
{
protected:
	inline LineTooLongError(
		const char* message, int line, const char* function, const char* file, const char* type
	) : ParseError(message, line, function, file, type)
	{
	}

public:
	inline explicit LineTooLongError(
		const std::string& message, int line=0, const char* function="", const char* file=""
	) : LineTooLongError(message.c_str(), line, function, file, "xw::LineTooLongError")
	{
	}
};

// TESTME: TooMuchHeadersError
// TODO: docs for 'TooMuchHeadersError'
class TooMuchHeadersError : public ParseError
{
protected:
	inline TooMuchHeadersError(
		const char* message, int line, const char* function, const char* file, const char* type
	) : ParseError(message, line, function, file, type)
	{
	}

public:
	inline explicit TooMuchHeadersError(
		const std::string& message, int line=0, const char* function="", const char* file=""
	) : TooMuchHeadersError(message.c_str(), line, function, file, "xw::TooMuchHeadersError")
	{
	}
};

} // namespace xw

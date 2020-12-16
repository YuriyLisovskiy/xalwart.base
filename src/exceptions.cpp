/**
 * exceptions.cpp
 *
 * Copyright (c) 2019-2020 Yuriy Lisovskiy
 */

#include "./exceptions.h"

// C++ libraries.
#include <csignal>


__CORE_BEGIN__

// BaseException
BaseException::BaseException(const char* message, int line, const char* function, const char* file, const char* exceptionType)
	: _message(message), _line(line), _function(function), _file(file), _exception_type(exceptionType)
{
}

BaseException::BaseException(const char* message, int line, const char* function, const char* file)
	: BaseException(message, line, function, file, "BaseException")
{
}

const char* BaseException::what() const noexcept
{
	return this->_message.c_str();
}

int BaseException::line() const noexcept
{
	return this->_line;
}

const char* BaseException::function() const noexcept
{
	return this->_function;
}

const char* BaseException::file() const noexcept
{
	return this->_file;
}

std::string BaseException::get_message() const noexcept
{
	return this->_exception_type + ": " + this->_message;
}

// InterruptException
InterruptException::InterruptException(
	const char* message, int line, const char* function, const char* file, const char* type
) : BaseException(message, line, function, file, type)
{
}

InterruptException::InterruptException(const char* message, int line, const char* function, const char* file)
	: InterruptException(message, line, function, file, "InterruptException")
{
}

InterruptException::InterruptException(
	const std::string& message, int line, const char *function, const char *file
) : InterruptException(message.c_str(), line, function, file)
{
}

void InterruptException::handle_signal(int sig)
{
	throw InterruptException("execution is interrupted with signal " + std::to_string(sig));
}

void InterruptException::initialize()
{
#if defined(_WIN32) || defined(_WIN64)
	signal(SIGINT, &InterruptException::handle_signal);
	signal(SIGTERM, &InterruptException::handle_signal);
#elif defined(__unix__) || defined(__linux__)
	struct sigaction sig_int_handler{};
	sig_int_handler.sa_handler = InterruptException::handle_signal;
	sigemptyset(&sig_int_handler.sa_mask);
	sig_int_handler.sa_flags = 0;
	sigaction(SIGINT, &sig_int_handler, nullptr);
	sigaction(SIGTERM, &sig_int_handler, nullptr);
//	sigaction(SIGKILL, &sig_int_handler, nullptr);
#else
#error Library is not supported on this platform
#endif
}

__CORE_END__

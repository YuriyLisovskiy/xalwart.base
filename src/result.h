/**
 * result.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * The result of the returned value from function or error.
 * It is a lightweight exception-like handling mechanism.
 */

#pragma once

#include <iostream>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./error.h"


__CORE_BEGIN__

template <typename T>
concept result_type = std::is_default_constructible_v<T> && !std::is_pointer_v<T>;

// TESTME: Result
template <result_type ValueT>
class Result final
{
private:

	// Bounds of http error family.
	const short ERROR_T_HTTP_LOWER = 2;
	const short ERROR_T_HTTP_UPPER = 8;

	// Bounds of suspicious operation error family.
	const short ERROR_T_SO_LOWER = 9;
	const short ERROR_T_SO_UPPER = 10;

private:

	// Returns `true` if the expected error is the same as
	// base or current error type, `false` otherwise.
	[[nodiscard]]
	inline bool _check_base(error_type base, error_type expected) const
	{
		return expected == base || this->err.type == expected;
	}

	// Returns `true` if the expected error is the same as base,
	// super-base or current error type, `false` otherwise.
	[[nodiscard]]
	inline bool _check_nested(error_type super_base, error_type base, error_type expected) const
	{
		return expected == super_base || this->_check_base(base, expected);
	}

public:

	// Holds an error of the result.
	Error err{};

	// Holds a value of the result.
	ValueT value{};

	// Indicates whether result is null or not.
	bool is_nullptr = false;

	// Default constructor.
	Result() = default;

	// Constructs the result with given value.
	inline explicit Result(ValueT data) : value(data)
	{
	}

	// Constructs the result with given error.
	inline explicit Result(const Error& err) : err(err)
	{
	}

	// Copy constructor.
	// If `other` is null then neither error nor value
	// will be copied. If other holds error, then only
	// error will be copied, otherwise copies `value`.
	inline Result(const Result& other)
	{
		if (this != &other)
		{
			this->is_nullptr = other.is_nullptr;
			if (!this->is_nullptr)
			{
				if (other.err)
				{
					this->err = other.err;
				}
				else
				{
					this->value = other.value;
				}
			}
		}
	}

	// Copy-assignment operator.
	// Acts the same way as copy-constructor.
	inline Result& operator= (const Result& other)
	{
		if (this != &other)
		{
			this->is_nullptr = other.is_nullptr;
			if (!this->is_nullptr)
			{
				if (other.err)
				{
					this->err = other.err;
				}
				else
				{
					this->value = other.value;
				}
			}
		}

		return *this;
	}

	// Returns `true` if result is not null, `false` otherwise.
	inline explicit operator bool () const
	{
		return !this->is_nullptr;
	}

	// Checks if error was generated.
	//
	// `expected`: error which is expected to be generated.
	//
	// Returns `true` if the expected error is generated,
	// `false` otherwise.
	[[nodiscard]]
	inline bool catch_(error_type expected = HttpError) const
	{
		// Process SuspiciousOperation-based errors
		if (this->err.type >= ERROR_T_SO_LOWER && this->err.type <= ERROR_T_SO_UPPER)
		{
			return this->err.type != None && this->_check_nested(
				HttpError, SuspiciousOperation, expected
			);
		}
		// Process HttpError-based errors
		else if (this->err.type >= ERROR_T_HTTP_LOWER && this->err.type <= ERROR_T_HTTP_UPPER)
		{
			return this->err.type != None && this->_check_base(HttpError, expected);
		}

		return this->err.type != None && expected == HttpError;
	}

	// Creates a new result with the same error as initial
	// object.
	template <typename NewT>
	inline Result<NewT> forward()
	{
		auto result = Result<NewT>();
		result.err = this->err;
		return result;
	}

	// Creates null result without value and error.
	inline static Result<ValueT> null()
	{
		Result<ValueT> null_result;
		null_result.is_nullptr = true;
		return null_result;
	}
};

// Creates result with error.
//
// `msg`: error message.
//
// Returns `Result<ValueT>` object with given message
// and error type.
template <error_type err_type, typename ValueT>
Result<ValueT> raise(const std::string& msg)
{
	return Result<ValueT>(Error(err_type, msg.c_str(), 0, "", ""));
}

// Creates result with error.
//
// `msg`: error message.
// `line`: line where an error occurred.
// `func`: function where an error occurred.
// `file`: file where an error occurred.
//
// Returns `Result<ValueT>` object with given message, line,
// function name, file name and error type.
template <error_type err_type, typename ValueT>
Result<ValueT> raise(const std::string& msg, int line, const char* func, const char* file)
{
	return Result<ValueT>(Error(err_type, msg.c_str(), line, func, file));
}

__CORE_END__

/**
 * result.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: holds the result of the returned value from function
 *  or error. It is a lightweight exception-like handling mechanism.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./error.h"


__CORE_BEGIN__

template <typename T>
concept result_type = std::is_default_constructible_v<T> && !std::is_pointer_v<T>;

template <result_type ValueT>
class Result final
{
private:
	const short ERROR_T_HTTP_LOWER = 2;
	const short ERROR_T_HTTP_UPPER = 8;

	const short ERROR_T_SO_LOWER = 9;
	const short ERROR_T_SO_UPPER = 10;

private:
	[[nodiscard]]
	inline bool _check_base(error_type base, error_type expected) const
	{
		return expected == base || this->err.type == expected;
	}

	[[nodiscard]]
	inline bool _check_nested(error_type super_base, error_type base, error_type expected) const
	{
		return expected == super_base || this->_check_base(base, expected);
	}

public:
	Error err{};
	ValueT value{};
	bool is_nullptr = false;

	Result() = default;

	inline explicit Result(ValueT data) : value(data)
	{
	}

	inline explicit Result(const Error& err) : err(err)
	{
	}

	inline explicit Result(std::nullptr_t) : is_nullptr(true)
	{
	}

	inline explicit operator bool () const
	{
		return !this->is_nullptr;
	}

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

	template<typename NewType>
	inline Result<NewType> forward()
	{
		auto result = Result<NewType>();
		result.err = this->err;
		return result;
	}

	inline static Result<ValueT> null()
	{
		return Result<ValueT>(nullptr);
	}
};

template <error_type err_type, typename ValueT>
Result<ValueT> raise(const std::string& msg)
{
	return Result<ValueT>(Error(err_type, msg.c_str(), 0, "", ""));
}

template <error_type err_type, typename ValueT>
Result<ValueT> raise(const std::string& msg, int line, const char* func, const char* file)
{
	return Result<ValueT>(Error(err_type, msg.c_str(), line, func, file));
}

__CORE_END__

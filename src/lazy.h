/**
 * lazy.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Lazy initialization.
 */

#pragma once

// C++ libraries.
#include <functional>

// Module definitions.
#include "./_def_.h"


__MAIN_NAMESPACE_BEGIN__

template <typename T, typename ...Args>
class Lazy final
{
private:

	// Holds a value to be lazy initialized.
	T _value{};

	// Indicates whether value is already initialized
	// or not.
	bool _loaded = false;

	// Lazy function for value initialization.
	std::function<T(Args...)> _initializer = nullptr;

public:
	Lazy() = default;

	// Constructs initializer.
	//
	// `lambda`: initializer of value.
	//
	// Throws `std::runtime_error` if lambda is null.
	inline Lazy(std::function<T(Args...)> lambda) : _initializer(std::move(lambda))
	{
		if (!this->_initializer)
		{
			throw std::runtime_error(
				"lambda function for lazy initialization is required but not set"
			);
		}
	}

	// Initializes value if it was not done yet and
	// returns an address to initialized value.
	inline T& get(Args&& ...args)
	{
		if (!this->_loaded && this->_initializer)
		{
			this->_value = this->_initializer(std::forward<Args>(args)...);
			this->_loaded = true;
		}

		return this->_value;
	}

	// Returns value if it was initializer or the result of
	// initializer call.
	inline T get(Args&& ...args) const
	{
		if (!this->_loaded && this->_initializer)
		{
			return this->_initializer(std::forward<Args>(args)...);
		}

		return this->_value;
	}
};

template <typename LazyT, typename T>
concept lazy_type = std::is_same_v<LazyT, Lazy<T>>;

__MAIN_NAMESPACE_END__

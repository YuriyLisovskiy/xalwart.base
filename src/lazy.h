/**
 * lazy.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: class for lazy initialization.
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
	T _value{};
	bool _loaded = false;
	const std::function<T(Args...)> _initializer = nullptr;

public:
	Lazy() = default;

	inline Lazy(std::function<T(Args...)> lambda) : _initializer(std::move(lambda))
	{
		if (!this->_initializer)
		{
			throw std::runtime_error(
				"lambda function for lazy initialization is required but not set"
			);
		}
	}

	Lazy& operator= (Lazy&& other)
	{
		if (this != &other)
		{
			this->_loaded = other._loaded;
			this->_initializer = std::move(other._initializer);
			if (this->_loaded)
			{
				this->_value = std::move(other._value);
			}
		}

		return *this;
	}

	inline T& value(Args&& ...args)
	{
		if (!this->_loaded && this->_initializer)
		{
			this->_value = this->_initializer(std::forward<Args>(args)...);
			this->_loaded = true;
		}

		return this->_value;
	}
};

__MAIN_NAMESPACE_END__

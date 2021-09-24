/**
 * options.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrapper for Contains keyword-arguments based on 'std::map'.
 * Can be used for functions with optional arguments of built-in types.
 */

#pragma once

// C++ libraries.
#include <map>
#include <string>
#include <exception>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./utility.h"


__MAIN_NAMESPACE_BEGIN__

// TODO: docs for 'Options'
class Options final
{
private:
	std::map<std::string, std::string> _map;

public:
	Options() = default;

	inline Options(std::map<std::string, std::string> src) : _map(std::move(src))
	{
	}

	// Gets value by key and converts it to type T.
	// See util::as function in the 'utility.h' file for
	// what types are supported.
	template <typename T>
	inline T get(const std::string& key, T _default={}) const
	{
		if (this->contains(key))
		{
			try
			{
				return util::as<T>((const char*)this->_map.at(key).c_str());
			}
			catch (const std::invalid_argument&)
			{
			}
			catch (const std::range_error&)
			{
			}
		}

		return _default;
	}

	inline void set(const std::string& key, const std::string& value)
	{
		this->_map[key] = value;
	}

	[[nodiscard]]
	inline bool contains(const std::string& key) const
	{
		return this->_map.contains(key);
	}
};

__MAIN_NAMESPACE_END__

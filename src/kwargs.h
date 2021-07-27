/**
 * kwargs.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Contains keyword-arguments based on 'std::map'.
 * Mostly used for virtual functions with variable arguments
 * count.
 */

#pragma once

// C++ libraries.
#include <map>
#include <string>
#include <iostream>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./utility.h"


__MAIN_NAMESPACE_BEGIN__

class Kwargs final
{
private:
	std::map<std::string, std::string> _map;

public:
	Kwargs() = default;

	inline explicit Kwargs(std::map<std::string, std::string> src) : _map(std::move(src))
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
		return this->_map.find(key) != this->_map.end();
	}
};

__MAIN_NAMESPACE_END__

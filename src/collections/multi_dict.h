/**
 * collections/multi_dict.h
 *
 * Copyright (c) 2019 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Template container based on collections::Dict with additional
 * 	methods (extended collections::Dict). Main difference is that
 * 	MultiValueDict can contain multiple values in one key.
 */

#pragma once

// C++ libraries.
#include <initializer_list>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./dict.h"


__COLLECTIONS_BEGIN__

template <typename _Key, typename _Val>
class MultiValueDict : public Dict<_Key, std::vector<_Val>>
{
public:

	/// Constructs empty multi-value dictionary.
	MultiValueDict() : Dict<_Key, std::vector<_Val>>()
	{
	}

	/// Constructs MultiValueDict instance from std::map.
	explicit MultiValueDict(const std::map<_Key, std::vector<_Val>>& src_map)
		: Dict<_Key, std::vector<_Val>>(src_map)
	{
	}

	/// Returns first value from vector by key if it exists, otherwise returns _default.
	///
	/// @param key: dict key which holds std::vector of values.
	/// @param _default: a default value to be returned if key does not exist.
	/// @return first value of std::vector by given key.
	_Val get(_Key key, _Val _default = _Val())
	{
		if (this->contains(key))
		{
			std::vector<_Val> vec = this->_map[key];
			if (vec.size() > 0)
			{
				return vec.at(vec.size() - 1);
			}
		}

		return _default;
	}

	/// Returns vector of values by key if it exists, otherwise returns _default vector.
	///
	/// @param key: dict key which holds std::vector of values.
	/// @param _default: a default vector of values to be returned if key does not exist.
	/// @return std::vector of values by given key.
	std::vector<_Val> get(_Key key, std::vector<_Val> _default) const override
	{
		if (this->contains(key))
		{
			return this->_map.at(key);
		}

		return _default;
	}

	/// Sets new vector of values by given key if instance is mutable.
	///
	/// @param key: new key or existing key.
	/// @param value: new value to construct std::vector.
	void set(_Key key, _Val value)
	{
		this->_map[key] = std::vector<_Val>{value};
	}

	/// Sets new vector of values by given key.
	///
	/// @param key: new key or existing key.
	/// @param value: new std::vector.
	void set(_Key key, std::vector<_Val> value) override
	{
		this->_map[key] = value;
	}

	/// Appends new value by given key.
	///	If key does not exist, creates new key-value pair.
	///
	/// @param key: new key or existing key.
	/// @param value: new value to append to std::vector.
	void append(_Key key, _Val val)
	{
		if (this->contains(key))
		{
			this->_map[key].push_back(val);
		}
		else
		{
			this->set(key, val);
		}
	}

	/// Appends new vector of values by given key.
	///	If key does not exist, creates new key-value pair.
	///
	/// @param key: new key or existing key.
	/// @param value: new std::vector of values to append to std::vector.
	void append(_Key key, std::vector<_Val> vec)
	{
		if (this->contains(key))
		{
			for (const auto& item : vec)
			{
				this->_map[key].push_back(item);
			}
		}
		else
		{
			this->set(key, vec);
		}
	}
};

__COLLECTIONS_END__

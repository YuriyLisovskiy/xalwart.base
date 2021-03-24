/**
 * collections/multi_dict.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Template container based on `collections::Dict` with additional
 * 	methods (extended `collections::Dict`). Main difference is that
 * 	MultiValueDict can contain multiple values in one key.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./dict.h"


__COLLECTIONS_BEGIN__

template <typename _Key, typename _Val>
class MultiValueDict : public Dict<_Key, std::vector<_Val>>
{
public:

	// Constructs empty multi-value dictionary.
	MultiValueDict() : Dict<_Key, std::vector<_Val>>()
	{
	}

	// Constructs `MultiValueDict` instance from `std::map`.
	explicit MultiValueDict(const std::map<_Key, std::vector<_Val>>& src_map)
		: Dict<_Key, std::vector<_Val>>(src_map)
	{
	}

	// Returns first value from vector by key if it exists, otherwise returns _default.
	//
	// `key`: dict key which holds `std::vector` of values.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns first value of `std::vector` by given key.
	inline _Val get(_Key key, _Val _default = _Val())
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

	// Returns vector of values by key if it exists, otherwise returns `_default` vector.
	//
	// `key`: dict key which holds std::vector of values.
	// `_default`: a default vector of values to be returned if key does not exist.
	//
	// Returns `std::vector` of values by given key.
	inline std::vector<_Val> get(_Key key, std::vector<_Val> _default) const override
	{
		if (this->contains(key))
		{
			return this->_map.at(key);
		}

		return _default;
	}

	// Sets new vector of values by given key if instance is mutable.
	//
	// `key`: new key or existing key.
	// `value`: new value to construct `std::vector`.
	inline void set(_Key key, _Val value)
	{
		this->_map[key] = std::vector<_Val>{value};
	}

	// Sets new vector of values by given key.
	//
	// `key`: new key or existing key.
	// `value`: new `std::vector`.
	inline void set(_Key key, std::vector<_Val> value) override
	{
		this->_map[key] = value;
	}

	// Appends new value by given key.
	// If key does not exist, creates new key-value pair.
	//
	// `key`: new key or existing key.
	// `value`: new value to append to `std::vector`.
	inline void append(_Key key, _Val val)
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

	// Appends new vector of values by given key.
	// If key does not exist, creates new key-value pair.
	//
	// `key`: new key or existing key.
	// `value`: new `std::vector` of values to append to `std::vector`.
	inline void append(_Key key, std::vector<_Val> vec)
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

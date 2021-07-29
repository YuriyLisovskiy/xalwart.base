/**
 * collections/multi_dict.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Template container based on 'BaseDictionary' with additional
 * get/set methods. Main difference from 'Dictionary' is that
 * 'MultiDictionary' can contain multiple values by one key.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./base_dictionary.h"


__COLLECTIONS_BEGIN__

template <typename KeyT, typename ValT>
class MultiDictionary : public BaseDictionary<KeyT, std::vector<ValT>>
{
public:

	// Constructs empty multi-value dictionary.
	MultiDictionary() : BaseDictionary<KeyT, std::vector<ValT>>()
	{
	}

	// Constructs `MultiValueDict` instance from `std::map`.
	explicit MultiDictionary(const std::map<KeyT, std::vector<ValT>>& src_map) :
		BaseDictionary<KeyT, std::vector<ValT>>(src_map)
	{
	}

	// Returns first value from vector by key if it exists, `_default` otherwise.
	//
	// `key`: dict key which holds `std::vector` of values.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns first value of `std::vector` by given key.
	inline ValT get(KeyT key, ValT _default=ValT{}) const
	{
		if (this->contains(key))
		{
			const auto& vec = this->_map.at(key);
			if (vec.size() > 0)
			{
				return vec.at(0);
			}
		}

		return _default;
	}

	// Returns vector of values by key if it exists, `_default` vector otherwise.
	//
	// `key`: dict key which holds std::vector of values.
	// `_default`: a default vector of values to be returned if key does not exist.
	//
	// Returns `std::vector` of values by given key.
	inline std::vector<ValT> getlist(KeyT key, std::vector<ValT> _default=std::vector<ValT>{}) const
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
	inline void set(KeyT key, ValT value)
	{
		this->_map.insert(std::make_pair(key, std::vector<ValT>{value}));
	}

	// Sets new vector of values by given key.
	//
	// `key`: new key or existing key.
	// `value`: new `std::vector`.
	inline void set(KeyT key, std::vector<ValT> value)
	{
		this->_map.insert(std::make_pair(key, value));
	}

	// Appends new value by given key.
	// If key does not exist, creates new key-value pair.
	//
	// `key`: new key or existing key.
	// `value`: new value to append to `std::vector`.
	inline void add(KeyT key, ValT val)
	{
		if (this->contains(key))
		{
			this->_map.at(key).push_back(val);
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
	inline void add(KeyT key, std::vector<ValT> vec)
	{
		if (this->contains(key))
		{
			for (const auto& item : vec)
			{
				this->_map.at(key).push_back(item);
			}
		}
		else
		{
			this->set(key, vec);
		}
	}
};

__COLLECTIONS_END__

/**
 * collections/dictionary.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Template container based on `BaseDictionary<KeyT, ValueT>`
 * with get/set methods.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./base_dictionary.h"


__COLLECTIONS_BEGIN__

template <typename KeyT, typename ValueT>
class Dictionary : public BaseDictionary<KeyT, ValueT>
{
public:
	// Constructs an empty dictionary.
	Dictionary() = default;

	// Constructs `Dict` instance from `std::map`.
	Dictionary(const std::map<KeyT, ValueT>& src_map) : BaseDictionary<KeyT, ValueT>(src_map)
	{
	}

	// Returns value by key if it exists, otherwise returns `_default`.
	//
	// `key`: dict key which holds some value.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns value by given key.
	virtual inline ValueT get(KeyT key, ValueT _default=ValueT{}) const
	{
		if (this->contains(key))
		{
			return this->_map.at(key);
		}

		return _default;
	}

	// Sets new value by given key.
	//
	// `key`: new key or existing key.
	// `value`: new value.
	virtual inline void set(KeyT key, ValueT value)
	{
		this->_map.insert(std::make_pair(key, value));
	}
};

__COLLECTIONS_END__

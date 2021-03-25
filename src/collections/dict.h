/**
 * collections/dict.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Template container based on `std::map` with additional methods.
 */

#pragma once

// C++ libraries.
#include <map>
#include <vector>

// Module definitions.
#include "./_def_.h"


__COLLECTIONS_BEGIN__

template <typename KeyT, typename ValT>
class Dict
{
protected:
	// An actual container.
	std::map<KeyT, ValT> _map;

public:
	typedef typename std::map<KeyT, ValT>::iterator iterator;
	typedef typename std::map<KeyT, ValT>::reverse_iterator reverse_iterator;

	typedef typename std::map<KeyT, ValT>::const_iterator const_iterator;
	typedef typename std::map<KeyT, ValT>::const_reverse_iterator const_reverse_iterator;

	// Constructs empty dictionary.
	Dict() = default;

	// Constructs `Dict` instance from `std::map`.
	explicit Dict(const std::map<KeyT, ValT>& src_map)
	{
		this->_map = src_map;
	}

	// Returns value by key if it exists, otherwise returns `_default`.
	//
	// `key`: dict key which holds some value.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns value by given key.
	virtual inline ValT get(KeyT key, ValT _default = ValT()) const
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
	virtual inline void set(KeyT key, ValT value)
	{
		this->_map[key] = value;
	}

	// Removes value from dictionary by it's key.
	//
	// `key`: key to be removed.
	virtual inline void remove(KeyT key)
	{
		if (this->contains(key))
		{
			this->_map.erase(key);
		}
	}

	// Removes all values from dictionary.
	inline void clear()
	{
		this->_map.clear();
	}

	// Returns dictionary's current size.
	inline size_t size() const
	{
		return this->_map.size();
	}

	// Checks if dictionary contains value by given key.
	//
	// `key`: key to check.
	//
	// Returns `true` if value exists, `false` otherwise.
	virtual inline bool contains(KeyT key) const
	{
		return this->_map.find(key) != this->_map.end();
	}

	// Checks if dictionary is empty.
	//
	// Returns `true` if dict is empty, `false` otherwise.
	bool inline is_empty() const
	{
		return this->_map.empty();
	}

	// Returns all keys which dictionary contains as `std::vector`.
	virtual inline std::vector<KeyT> keys() const
	{
		std::vector<KeyT> keys;
		for (auto it = this->begin(); it != this->end(); it++)
		{
			keys.push_back(it->first);
		}

		return keys;
	}

	// Returns begin iterator.
	inline iterator begin() noexcept
	{
		return this->_map.begin();
	}

	// Returns constant begin iterator.
	inline const_iterator begin() const noexcept
	{
		return this->_map.begin();
	}

	// Returns end iterator.
	inline iterator end() noexcept
	{
		return this->_map.end();
	}

	// Returns constant end iterator.
	inline const_iterator end() const noexcept
	{
		return this->_map.end();
	}

	// Returns reversed begin iterator.
	inline reverse_iterator rbegin() noexcept
	{
		return this->_map.rbegin();
	}

	// Returns constant reversed begin iterator.
	inline const_reverse_iterator rbegin() const noexcept
	{
		return this->_map.rbegin();
	}

	// Returns reversed end iterator.
	inline reverse_iterator rend() noexcept
	{
		return this->_map.rend();
	}

	// Returns constant reversed end iterator.
	inline const_reverse_iterator rend() const noexcept
	{
		return this->_map.rend();
	}

	// Returns an address to value by key.
	inline ValT& operator[] (const KeyT& key)
	{
		return this->_map[key];
	}
};

__COLLECTIONS_END__

/**
 * collections/dict.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Template container based on `std::map` with additional
 * 	methods (extended `std::map`).
 */

#pragma once

// C++ libraries.
#include <map>
#include <vector>

// Module definitions.
#include "./_def_.h"


__COLLECTIONS_BEGIN__

template <typename _Key, typename _Val>
class Dict
{
protected:
	// An actual container.
	std::map<_Key, _Val> _map;

public:
	typedef typename std::map<_Key, _Val>::iterator iterator;
	typedef typename std::map<_Key, _Val>::reverse_iterator reverse_iterator;

	typedef typename std::map<_Key, _Val>::const_iterator const_iterator;
	typedef typename std::map<_Key, _Val>::const_reverse_iterator const_reverse_iterator;

	// Constructs empty dictionary.
	Dict() = default;

	// Constructs Dict instance from `std::map`.
	explicit Dict(const std::map<_Key, _Val>& src_map)
	{
		this->_map = src_map;
	}

	// Returns value by key if it exists, otherwise returns _default.
	//
	// `key`: dict key which holds some value.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns value by given key.
	virtual inline _Val get(_Key key, _Val _default = _Val()) const
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
	virtual inline void set(_Key key, _Val value)
	{
		this->_map[key] = value;
	}

	// Removes value from dict by it's key.
	//
	// `key`: key to be removed.
	virtual inline void remove(_Key key)
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
	// Returns true if value exists, otherwise returns false.
	virtual inline bool contains(_Key key) const
	{
		return this->_map.find(key) != this->_map.end();
	}

	// Checks if dictionary is empty.
	//
	// Returns true if dict is empty, otherwise returns false.
	bool inline is_empty() const
	{
		return this->_map.empty();
	}

	// Returns all keys which dictionary contains as `std::vector`.
	virtual inline std::vector<_Key> keys() const
	{
		std::vector<_Key> keys;
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

	inline _Val& operator[] (const _Key& key)
	{
		return this->_map[key];
	}
};

__COLLECTIONS_END__

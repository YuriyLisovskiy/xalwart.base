/**
 * collections/base.h
 *
 * Copyright (c) 2019, 2021 Yuriy Lisovskiy
 *
 * Base dictionary container based on `std::map`.
 * Get/set methods must be implemented in child containers.
 */

#pragma once

// C++ libraries.
#include <map>
#include <vector>

// Module definitions.
#include "./_def_.h"


__COLLECTIONS_BEGIN__

template <typename KeyT, typename ValT>
class BaseDictionary
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
	BaseDictionary() = default;

	// Constructs `Dict` instance from `std::map`.
	BaseDictionary(const std::map<KeyT, ValT>& src_map)
	{
		this->_map = src_map;
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
	[[nodiscard]]
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
	[[nodiscard]]
	bool inline empty() const
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
};

__COLLECTIONS_END__

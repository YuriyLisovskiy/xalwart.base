/**
 * collections/multimap.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrapper for `std::map` that maps key to sequence of
 * values with extra functionality for convenient use.
 */

#pragma once

// C++ libraries.
#include <map>
#include <vector>
#include <algorithm>

// Module definitions.
#include "./_def_.h"


__COLLECTIONS_BEGIN__

// TODO: docs for 'Multimap<typename KeyType, typename ValueType>'
template <typename KeyType, typename ValueType>
class Multimap
{
protected:
	using ValueIterable = std::vector<ValueType>;
	using MapType = std::map<KeyType, ValueIterable>;
	MapType _map;

public:
	typedef typename std::map<KeyType, ValueIterable>::iterator iterator;
	typedef typename std::map<KeyType, ValueIterable>::reverse_iterator reverse_iterator;

	typedef typename std::map<KeyType, ValueIterable>::const_iterator const_iterator;
	typedef typename std::map<KeyType, ValueIterable>::const_reverse_iterator const_reverse_iterator;

	Multimap() = default;

	inline Multimap(const MapType& source) : _map(source)
	{
	}

	inline Multimap(MapType&& source) : _map(std::move(source))
	{
	}

	inline Multimap(const Multimap& other)
	{
		if (this != &other)
		{
			this->_map = other._map;
		}
	}

	inline Multimap(Multimap&& other)
	{
		if (this != &other)
		{
			this->_map = std::move(other._map);
		}
	}

	inline Multimap& operator= (const Multimap& other)
	{
		if (this != &other)
		{
			this->_map = other._map;
		}

		return *this;
	}

	inline Multimap& operator= (Multimap&& other) noexcept
	{
		if (this != &other)
		{
			this->_map = std::move(other._map);
		}

		return *this;
	}

	// Returns first value from vector by key if it exists, `_default` otherwise.
	//
	// `key`: dict key which holds `std::vector` of values.
	// `_default`: a default value to be returned if key does not exist.
	//
	// Returns first value of `ValueIterable` by given key.
	inline ValueType get(KeyType key, const ValueType& _default={}) const
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
	inline ValueIterable get_sequence(KeyType key, const ValueIterable& _default={}) const
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
	inline void set(KeyType key, const ValueType& value)
	{
		if (this->contains(key))
		{
			this->_map[key] = ValueIterable{value};
		}
		else
		{
			this->_map.insert(std::make_pair(std::move(key), ValueIterable{value}));
		}
	}

	// Sets new vector of values by given key.
	//
	// `key`: new key or existing key.
	// `value`: new `std::vector`.
	inline void set(KeyType key, ValueIterable value)
	{
		if (this->contains(key))
		{
			this->_map[key] = std::move(value);
		}
		else
		{
			this->_map.insert(std::make_pair(std::move(key), std::move(value)));
		}
	}

	// Appends new value by given key.
	// If key does not exist, creates new key-value pair.
	//
	// `key`: new key or existing key.
	// `value`: new value to append to `std::vector`.
	inline void add(KeyType key, const ValueType& value)
	{
		if (this->contains(key))
		{
			this->_map.at(key).push_back(value);
		}
		else
		{
			this->set(key, value);
		}
	}

	// Appends new vector of values by given key.
	// If key does not exist, creates new key-value pair.
	//
	// `key`: new key or existing key.
	// `value`: new `std::vector` of values to append to `std::vector`.
	inline void add(KeyType key, const ValueIterable& value)
	{
		if (this->contains(key))
		{
			for (const auto& item : value)
			{
				this->_map.at(key).push_back(item);
			}
		}
		else
		{
			this->set(std::move(key), value);
		}
	}

	// Removes value from dictionary by it's key.
	//
	// `key`: key to be removed.
	virtual inline void remove(const KeyType& key)
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
	virtual inline bool contains(const KeyType& key) const
	{
		return this->_map.contains(key);
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
	virtual inline std::vector<KeyType> keys() const
	{
		std::vector<KeyType> keys;

		// TODO: its better to use std::transform, but it causes SIGINT (issue #20)
		for (const auto& pair : this->_map)
		{
			keys.push_back(pair.first);
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

	// Returns constant begin iterator.
	inline const_iterator cbegin() const noexcept
	{
		return this->_map.cbegin();
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

	// Returns constant end iterator.
	inline const_iterator cend() const noexcept
	{
		return this->_map.cend();
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

template <typename KeyType, typename ValueType>
using multimap = Multimap<KeyType, ValueType>;

__COLLECTIONS_END__

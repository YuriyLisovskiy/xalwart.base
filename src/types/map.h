/**
 * types/map.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrapper for map containers based on `std::map` for rendering in templates.
 */

#pragma once

// C++ libraries.
#include <map>

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "./abstract.h"


__TYPES_BEGIN__

template <object_based_type KeyT, object_based_type ValueT>
class Map : public obj::Object, public MapContainer
{
public:
	typedef KeyT key_type;
	typedef ValueT value_type;

	typedef std::map<key_type, value_type> container_type;

protected:
	container_type container;

protected:

	// Aggregates container values to string.
	// Used for `__str__()` and `__repr__()` methods.
	[[nodiscard]]
	virtual inline std::string aggregate(
		const std::string& separator, const std::function<std::string(const obj::Object*, const obj::Object*)>& func
	) const
	{
		auto begin = this->container.begin();
		auto end = this->container.end();
		std::string res;
		if (begin == end)
		{
			return res;
		}

		auto last_iteration = end;
		last_iteration--;
		for (auto it = begin; it != end; it++)
		{
			res += func(&it->first, &it->second);
			if (it != last_iteration)
			{
				res += separator;
			}
		}

		return res;
	}

public:
	// Default constructor.
	inline explicit Map() = default;

	// Constructs Sequence from container.
	inline explicit Map(container_type value) : container(std::move(value))
	{
	}

	// Constructs Sequence from initializer list.
	inline Map(std::initializer_list<std::pair<const key_type , value_type>> mp)
	{
		this->container = std::move(mp);
	}

	// Loops through map container using iterators.
	//
	// `begin`, `end`: iterators of the container.
	// `func`: function which handles an item and it's index.
	template <typename IteratorT>
	inline void look_through(
		IteratorT begin, IteratorT end, const std::function<void(size_t, const obj::Object*, const obj::Object*)>& func
	) const
	{
		size_t i = 0;
		for (auto it = begin; it != end; it++)
		{
			func(i++, &it->first, &it->second);
		}
	}

	// Iterates through map container in given direction.
	//
	// `func`: function which handles key, value and index.
	// `reversed`: iteration direction option.
	inline void look_through(
		const std::function<void(size_t, const obj::Object*, const obj::Object*)>& func, bool reversed
	) const override
	{
		if (reversed)
		{
			this->look_through(this->container.rbegin(), this->container.rend(), func);
		}
		else
		{
			this->look_through(this->container.begin(), this->container.end(), func);
		}
	}

	// Returns `true` if container is empty, `false` otherwise.
	[[nodiscard]]
	bool empty() const override
	{
		return this->container.empty();
	}

	// Returns the size of the container.
	[[nodiscard]]
	inline size_t size() const override
	{
		return this->container.size();
	}

	// Returns address to internal container.
	inline container_type& operator* ()
	{
		return this->container;
	}

	// Compares two sequential containers with the same type
	// of value.
	//
	// Throws `TypeError` if `other` has different type.
	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const Map<KeyT, ValueT>*>(other))
		{
			if (this->container == other_v->container)
			{
				return 0;
			}

			return this->container > other_v->container ? 1 : -1;
		}

		throw TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() +
			"' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	// Returns string representation of the container.
	[[nodiscard]]
	inline std::string __str__() const override
	{
		return "{" + this->aggregate(
			", ", [](const obj::Object* key, const obj::Object* value) -> std::string
			{
				return "{" + (key ? key->__repr__() : "nullptr") + ", " + (value ? value->__repr__() : "nullptr") + "}";
			}
		) + "}";
	}

	// Returns string representation of the container using
	// __repr__() method of container's values.
	[[nodiscard]]
	inline std::string __repr__() const override
	{
		return "{" + this->aggregate(
			", ", [](const obj::Object* key, const obj::Object* value) -> std::string
			{
				return "{" + (key ? key->__repr__() : "'nullptr'") + ", " + (value ? value->__repr__() : "'nullptr'") + "}";
			}
		) + "}";
	}
};

template <typename KeyT, typename ValueT>
using map = Map<KeyT, ValueT>;

__TYPES_END__

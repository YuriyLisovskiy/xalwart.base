/**
 * types/sequence.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrapper for sequential containers based on std::list for rendering in templates.
 */

#pragma once

// C++ libraries.
#include <list>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./iterable.h"


__TYPES_BEGIN__

template <object_based_type ValueT>
class Sequence : public obj::Object, public SequenceContainer
{
public:
	typedef ValueT value_type;
	typedef std::list<value_type> container_type;

protected:
	container_type container;

protected:
	[[nodiscard]]
	virtual inline std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const obj::Object*)>& func
	) const
	{
		std::string res;
		auto last_iteration = std::prev(this->container.end(), 1);
		for (auto it = this->container.begin(); it != this->container.end(); it++)
		{
			res += func(&(*it));
			if (it != last_iteration)
			{
				res += separator;
			}
		}

		return res;
	}

public:

	// Default constructor.
	inline explicit Sequence() = default;

	// Constructs Sequence from container.
	inline explicit Sequence(container_type value) : container(std::move(value))
	{
	}

	// Constructs Sequence from initializer list.
	inline explicit Sequence(std::initializer_list<value_type> list)
	{
		this->container = std::move(list);
	}

	// Iterates through sequential container using iterators.
	//
	// `begin`, `end`: iterators of the container.
	// `func`: function which handles an item and it's index.
	template <typename IteratorT>
	inline void look_through(
		IteratorT begin, IteratorT end,
		const std::function<void(size_t, const obj::Object*)>& func
	) const
	{
		size_t i = 0;
		for (auto it = begin; it != end; it++)
		{
			func(i++, &(*it));
		}
	}

	// Iterates through sequential container in given direction.
	//
	// `func`: function which handles an item and it's index.
	// `reversed`: iteration direction option.
	inline void look_through(
		const std::function<void(size_t, const obj::Object*)>& func, bool reversed
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
	// Throws `core::TypeError` if `other` has different type.
	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const Sequence<value_type>*>(other))
		{
			if (this->container == other_v->container)
			{
				return 0;
			}

			return this->container > other_v->container ? 1 : -1;
		}

		throw core::TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	// Returns string representation of the container.
	[[nodiscard]]
	inline std::string __str__() const override
	{
		return "{" + this->aggregate(
			", ",
			[](const obj::Object* item) -> std::string { return item->__str__(); }
		) + "}";
	}

	// Returns string representation of the container with
	// it's type name.
	//
	// Used for debugging.
	[[nodiscard]]
	inline std::string __repr__() const override
	{
		auto type = this->__type__();
		return type.namespace_() + "::" + type.name() + "{" + this->aggregate(
			", ",
			[](const obj::Object* item) -> std::string { return item->__repr__(); }
		) + "}";
	}
};

template <typename T>
using sequence = Sequence<T>;

__TYPES_END__

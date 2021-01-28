/**
 * types/iterable.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <algorithm>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../exceptions.h"
#include "../object/object.h"
#include "../types/string.h"


__TYPES_BEGIN__

template <typename ContainerT>
concept ContainerType = (
	std::is_same_v<typename ContainerT::value_type, std::shared_ptr<object::Object>>
);

class Iterable
{
public:
	[[nodiscard]]
	virtual std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const std::shared_ptr<object::Object>&)>& func
	) const = 0;
};

template <ContainerType ContainerT>
class IterableContainer : public object::Object, public Iterable
{
protected:
	ContainerT internal_value;

public:
	typedef typename ContainerT::value_type value_type;

	typedef std::allocator<value_type> allocator_type;

	typedef value_type& reference;
	typedef const value_type& const_reference;

	typedef typename std::allocator_traits<allocator_type>::pointer pointer;
	typedef typename std::allocator_traits<allocator_type>::const_pointer const_pointer;

	typedef typename ContainerT::iterator iterator;
	typedef typename ContainerT::const_iterator const_iterator;

	typedef typename std::reverse_iterator<iterator> reverse_iterator;
	typedef typename std::reverse_iterator<const_iterator> const_reverse_iterator;

	typedef typename std::iterator_traits<iterator>::difference_type difference_type;
	typedef typename ContainerT::size_type size_type;

public:
	inline explicit IterableContainer() = default;

	inline explicit IterableContainer(ContainerT value) : internal_value(std::move(value))
	{
	}

	inline ContainerT& value()
	{
		return this->internal_value;
	}

	[[nodiscard]]
	inline std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const std::shared_ptr<object::Object>&)>& func
	) const override
	{
		std::string res;
		for (auto it = this->internal_value.begin(); it != this->internal_value.end(); it++)
		{
			res += func(*it);
			if (it < this->internal_value.end() - 1)
			{
				res += separator;
			}
		}

		return res;
	}

	inline void reverse()
	{
		std::reverse(this->internal_value.begin(), this->internal_value.end());
	}

	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const IterableContainer<ContainerT>*>(other))
		{
			if (this->internal_value == other_v->internal_value)
			{
				return 0;
			}

			return this->internal_value > other_v->internal_value ? 1 : -1;
		}

		throw core::TypeError(
			"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and '" + other->__type__().name() + "'",
			_ERROR_DETAILS_
		);
	}

	[[nodiscard]]
	inline std::string __str__() const override
	{
		return "{" + this->aggregate(
			", ",
			[](const value_type& item) -> std::string { return item->__str__(); }
		) + "}";
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		return "xw::types::Vector{" + this->aggregate(
			", ",
			[](const value_type& item) -> std::string { return item->__repr__(); }
		) + "}";
	}
};

__TYPES_END__

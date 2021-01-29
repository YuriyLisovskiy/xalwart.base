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


__TYPES_BEGIN__

class Iterable
{
public:
	[[nodiscard]]
	virtual std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const std::shared_ptr<object::Object>&)>& func
	) const = 0;

	virtual std::shared_ptr<object::Object>& at(size_t i) = 0;

	[[nodiscard]]
	virtual const std::shared_ptr<object::Object>& at(size_t i) const = 0;

	virtual void reverse() = 0;

	[[nodiscard]]
	virtual size_t size() const = 0;

	// Sequence containers.
	[[nodiscard]]
	inline virtual constexpr bool is_array() const
	{
		return false;
	}

	[[nodiscard]]
	inline virtual constexpr bool is_vector() const
	{
		return false;
	}

	[[nodiscard]]
	inline virtual constexpr bool is_dequeue() const
	{
		return false;
	}

	[[nodiscard]]
	inline virtual constexpr bool is_forward_list() const
	{
		return false;
	}

	[[nodiscard]]
	inline virtual constexpr bool is_list() const
	{
		return false;
	}

	[[nodiscard]]
	inline virtual constexpr bool is_sequence() const
	{
		return this->is_array() || this->is_vector() ||
			this->is_dequeue() || this->is_forward_list() || this->is_list();
	};

	// Associative containers.
	[[nodiscard]]
	inline virtual constexpr bool is_map() const
	{
		return false;
	}
};

template <class ContainerT>
class IterableContainer : public object::Object, public Iterable
{
protected:
	ContainerT internal_value;

public:
	typedef typename ContainerT::value_type value_type;

	typedef typename ContainerT::allocator_type allocator_type;

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

	inline reference at(size_t i) override
	{
		return this->at(i);
	}

	[[nodiscard]]
	inline const_reference at(size_t i) const override
	{
		return this->at(i);
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

	inline void reverse() override
	{
		std::reverse(this->internal_value.begin(), this->internal_value.end());
	}

	[[nodiscard]]
	inline size_t size() const override
	{
		this->internal_value.size();
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

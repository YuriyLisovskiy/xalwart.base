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
	virtual void reverse() = 0;

	[[nodiscard]]
	virtual size_t size() const = 0;

	[[nodiscard]]
	virtual std::shared_ptr<object::Object> at(size_t i) const = 0;

	[[nodiscard]]
	inline virtual bool is_sequence() const
	{
		return false;
	};

	[[nodiscard]]
	inline virtual bool is_map() const
	{
		return false;
	}
};

// Requirements for derived class:
//
//  ContainerT::value_type must be std::shared_ptr<object::Object>
//
//  Methods:
//  - const std::shared_ptr<object::Object>& at(size_t i) const     - (otherwise, override it from this class)
//  - ContainerT::iterator begin()
//  - ContainerT::iterator end()
template <class ContainerT>
class SequenceIterable : public object::Object, public Iterable
{
protected:
	ContainerT internal_value;

public:
	inline explicit SequenceIterable() = default;

	inline explicit SequenceIterable(ContainerT value) : internal_value(std::move(value))
	{
	}

	[[nodiscard]]
	inline std::shared_ptr<object::Object> at(size_t i) const override
	{
		return this->internal_value.at(i);
	}

	[[nodiscard]]
	inline bool is_sequence() const override
	{
		return true;
	};

	inline ContainerT& value()
	{
		return this->internal_value;
	}

	[[nodiscard]]
	inline std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const std::shared_ptr<object::Object>&)>& func
	) const
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
		return this->internal_value.size();
	}

	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const SequenceIterable<ContainerT>*>(other))
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
			[](const std::shared_ptr<object::Object>& item) -> std::string { return item->__str__(); }
		) + "}";
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		auto type = this->__type__();
		return type.namespace_() + "::" + type.name() + "{" + this->aggregate(
			", ",
			[](const std::shared_ptr<object::Object>& item) -> std::string { return item->__repr__(); }
		) + "}";
	}
};

class MapIterable : public Iterable
{
	// TODO: MapIterable
};

template <typename T>
concept ObjectPointerType = std::is_base_of_v<object::Object, T>;

__TYPES_END__

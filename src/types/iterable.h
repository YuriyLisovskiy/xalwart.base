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
	virtual size_t size() const = 0;

	[[nodiscard]]
	virtual bool empty() const = 0;

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

class SequenceIterable : public Iterable
{
public:
	[[nodiscard]]
	inline bool is_sequence() const final
	{
		return true;
	};

	virtual void look_through(
		const std::function<void(size_t, const std::shared_ptr<obj::Object>&)>& func,
		bool reversed
	) const = 0;
};

// Requirements for derived class:
//
//  - ContainerT::value_type must be std::shared_ptr<object::Object>
//  - Override 'void look_through(...)' method or implement:
//      - ContainerT::iterator begin()
//      - ContainerT::iterator end()
template <class ContainerT>
class SequenceIterableContainer : public obj::Object, public SequenceIterable
{
protected:
	ContainerT internal_value;

protected:
	[[nodiscard]]
	virtual inline std::string aggregate(
		const std::string& separator,
		const std::function<std::string(const std::shared_ptr<obj::Object>&)>& func
	) const
	{
		std::string res;
		auto last_iteration = this->internal_value.end() - 1;
		for (auto it = this->internal_value.begin(); it != this->internal_value.end(); it++)
		{
			res += func(*it);
			if (it != last_iteration)
			{
				res += separator;
			}
		}

		return res;
	}

public:
	inline explicit SequenceIterableContainer() = default;

	inline explicit SequenceIterableContainer(ContainerT value) : internal_value(std::move(value))
	{
	}

	inline void look_through(
		const std::function<void(size_t, const std::shared_ptr<obj::Object>&)>& func,
		bool reversed
	) const override
	{
		size_t i = 0;
		if (reversed)
		{
			auto begin = this->internal_value.rbegin();
			auto end = this->internal_value.rend();
			for (auto it = begin; it != end; it++)
			{
				func(i++, *it);
			}
		}
		else
		{
			auto begin = this->internal_value.begin();
			auto end = this->internal_value.end();
			for (auto it = begin; it != end; it++)
			{
				func(i++, *it);
			}
		}
	}

	[[nodiscard]]
	bool empty() const override
	{
		return this->internal_value.empty();
	}

	[[nodiscard]]
	inline size_t size() const override
	{
		return this->internal_value.size();
	}

	inline ContainerT& value()
	{
		return this->internal_value;
	}

	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const SequenceIterableContainer<ContainerT>*>(other))
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
			[](const std::shared_ptr<obj::Object>& item) -> std::string { return item->__str__(); }
		) + "}";
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		auto type = this->__type__();
		return type.namespace_() + "::" + type.name() + "{" + this->aggregate(
			", ",
			[](const std::shared_ptr<obj::Object>& item) -> std::string { return item->__repr__(); }
		) + "}";
	}
};

class MapIterable : public Iterable
{
public:
	[[nodiscard]]
	inline bool is_map() const final
	{
		return true;
	};

	virtual void look_through(const std::function<void(
		size_t, const std::pair<std::shared_ptr<obj::Object>, std::shared_ptr<obj::Object>>&
	)>& func, bool reversed) const = 0;
};

// Requirements for derived class:
//
//  - ContainerT::value_type must be std::shared_ptr<object::Object>
//  - Override 'void look_through(...)' method or implement:
//      - ContainerT::iterator begin()
//      - ContainerT::iterator end()
template <class ContainerT>
class MapIterableContainer : public obj::Object, public MapIterable
{
protected:
	ContainerT internal_value;

protected:
	[[nodiscard]]
	virtual inline std::string aggregate(
		const std::string& separator,
		const std::function<std::string(
			const std::pair<std::shared_ptr<obj::Object>, std::shared_ptr<obj::Object>>&
		)>& func
	) const
	{
		std::string res;
		auto last_iteration = this->internal_value.end();
		last_iteration--;
		for (auto it = this->internal_value.begin(); it != this->internal_value.end(); it++)
		{
			res += func(*it);
			if (it != last_iteration)
			{
				res += separator;
			}
		}

		return res;
	}

public:
	inline explicit MapIterableContainer() = default;

	inline explicit MapIterableContainer(ContainerT value) : internal_value(std::move(value))
	{
	}

	inline void look_through(const std::function<void(
		size_t, const std::pair<std::shared_ptr<obj::Object>, std::shared_ptr<obj::Object>>&
	)>& func, bool reversed) const override
	{
		size_t i = 0;
		if (reversed)
		{
			auto begin = this->internal_value.rbegin();
			auto end = this->internal_value.rend();
			for (auto it = begin; it != end; it++)
			{
				func(i++, *it);
			}
		}
		else
		{
			auto begin = this->internal_value.begin();
			auto end = this->internal_value.end();
			for (auto it = begin; it != end; it++)
			{
				func(i++, *it);
			}
		}
	}

	[[nodiscard]]
	bool empty() const override
	{
		return this->internal_value.empty();
	}

	[[nodiscard]]
	inline size_t size() const override
	{
		return this->internal_value.size();
	}

	inline ContainerT& value()
	{
		return this->internal_value;
	}

	[[nodiscard]]
	inline short __cmp__(const Object* other) const override
	{
		if (auto other_v = dynamic_cast<const MapIterableContainer<ContainerT>*>(other))
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
			", ", [](
				const std::pair<std::shared_ptr<obj::Object>, std::shared_ptr<obj::Object>>& pair
			) -> std::string { return "{" + pair.first->__str__() + ", " + pair.second->__str__() + "}"; }
		) + "}";
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		auto type = this->__type__();
		return type.namespace_() + "::" + type.name() + "{" + this->aggregate(
			", ", [](
				const std::pair<std::shared_ptr<obj::Object>, std::shared_ptr<obj::Object>>& pair
			) -> std::string { return "{" + pair.first->__repr__() + ", " + pair.second->__repr__() + "}"; }
		) + "}";
	}
};

template <typename T>
concept ObjectBasedType = std::is_base_of_v<obj::Object, T>;

__TYPES_END__

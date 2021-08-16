/**
 * types/iterable.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Abstract base classes for `types` module.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Base libraries.
#include "../object/object.h"


__TYPES_ABC_BEGIN__

// Base class for iterable container.
class Iterable
{
public:
	[[nodiscard]]
	virtual size_t size() const = 0;

	[[nodiscard]]
	virtual bool empty() const = 0;

	// Returns `false` by default.
	[[nodiscard]]
	inline virtual bool is_sequence() const
	{
		return false;
	};

	// Returns `false` by default.
	[[nodiscard]]
	inline virtual bool is_map() const
	{
		return false;
	}
};

// Base class for sequential containers.
class SequenceContainer : public Iterable
{
public:

	// Marks than the container is sequential.
	[[nodiscard]]
	inline bool is_sequence() const final
	{
		return true;
	};

	// Used for sequential iterating over container's values.
	//
	// `func`: function with two parameters:
	//     - first: index
	//     - second: value
	// `reversed`: sets the direction of iterating.
	virtual void look_through(
		const std::function<void(size_t, const obj::Object*)>& func, bool reversed
	) const = 0;
};

// Base class for map containers.
class MapContainer : public Iterable
{
public:

	// Marks than the container is map.
	[[nodiscard]]
	inline bool is_map() const final
	{
		return true;
	};

	// Used for iterating over container's values.
	//
	// `func`: function with three parameters:
	//     - first: index
	//     - second: key
	//     - third: value
	// `reversed`: sets the direction of iterating.
	virtual void look_through(
		const std::function<void(size_t, const obj::Object*, const obj::Object*)>& func, bool reversed
	) const = 0;
};

__TYPES_ABC_END__


__TYPES_BEGIN__

template <typename T>
concept object_based_type = std::is_base_of_v<obj::Object, T>;

template <typename T>
concept object_based_iterator = std::is_base_of_v<obj::Object, iterator_v_type<T>>;

__TYPES_END__

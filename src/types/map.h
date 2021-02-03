/**
 * types/map.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <map>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./iterable.h"


__TYPES_BEGIN__

template <ObjectPointerType KeyT, ObjectPointerType ValueT>
class Map : public MapIterableContainer<std::map<std::shared_ptr<KeyT>, std::shared_ptr<ValueT>>>
{
public:
	inline explicit Map() = default;

	inline explicit Map(std::map<std::shared_ptr<KeyT>, std::shared_ptr<ValueT>> value)
		: MapIterableContainer<std::map<std::shared_ptr<KeyT>, std::shared_ptr<ValueT>>>(std::move(value))
	{
	}
};

__TYPES_END__

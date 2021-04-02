/**
 * types/vector.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <vector>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./iterable.h"


__TYPES_BEGIN__

// TODO: improve functionality.
// TODO: docs
// TESTME: Vector
template <object_based_type T = obj::Object>
class Vector : public SequenceIterableContainer<std::vector<std::shared_ptr<T>>>
{
public:
	inline explicit Vector() = default;

	inline explicit Vector(std::vector<std::shared_ptr<T>> value)
		: SequenceIterableContainer<std::vector<std::shared_ptr<T>>>(std::move(value))
	{
	}
};

__TYPES_END__

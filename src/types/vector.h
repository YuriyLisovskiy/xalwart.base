/**
 * types/vector.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./iterable.h"


__TYPES_BEGIN__

class Vector : public IterableContainer<std::vector<std::shared_ptr<object::Object>>>
{
public:
	inline explicit Vector() = default;

	inline explicit Vector(
		std::vector<std::shared_ptr<object::Object>> value
	) : IterableContainer<std::vector<std::shared_ptr<object::Object>>>(std::move(value))
	{
	}
};

__TYPES_END__

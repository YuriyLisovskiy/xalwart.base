/**
 * abc.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Abstract base classes for main module.
 */

#pragma once

// Module definitions.
#include "./_def_.h"


__ABC_BEGIN__

class IStringSerializable
{
public:
	[[nodiscard]]
	std::string to_string() const = 0;
};

__ABC_END__

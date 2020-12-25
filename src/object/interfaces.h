/**
 * object/interfaces.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: contains useful interfaces for inheritance.
 */

#pragma once

// Module definitions.
#include "./_def_.h"


__OBJECT_BEGIN__

class ICloneable
{
private:
	ICloneable(const ICloneable&) = default;
	ICloneable& operator=(const ICloneable&) = default;

public:
	ICloneable() = default;
	virtual ICloneable* clone() = 0;
};

__OBJECT_END__

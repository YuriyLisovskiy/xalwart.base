/**
 * types/string.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./string.h"

// Core libraries.
#include "../exceptions.h"


__TYPES_BEGIN__

short String::__cmp__(const Object* other) const
{
	if (auto other_v = dynamic_cast<const String*>(other))
	{
		if (this->value < other_v->value)
		{
			return -1;
		}

		return this->value == other_v->value ? 0 : 1;
	}

	throw core::TypeError(
		"'__cmp__' not supported between instances of '" + this->__type__().name() + "' and '" + other->__type__().name() + "'",
		_ERROR_DETAILS_
	);
}

String::operator bool() const
{
	return !this->value.empty();
}

bool String::operator! () const
{
	return this->value.empty();
}

__TYPES_END__

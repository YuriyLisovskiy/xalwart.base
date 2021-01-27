/**
 * types/string.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./string.h"

// C++ libraries.
// TODO

// Framework libraries.
// TODO


__TYPES_BEGIN__

short String::__cmp__(const Object* other) const
{
	// TODO:
	return 0;
}

String::operator bool() const
{
	return !this->internal_value.empty();
}

bool String::operator! () const
{
	return this->internal_value.empty();
}

__TYPES_END__

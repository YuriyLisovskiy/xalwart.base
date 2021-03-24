/**
 * object/object.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./object.h"

// Core libraries.
#include "../exceptions.h"


__OBJ_BEGIN__

std::shared_ptr<Object> Object::__get_attr__(const char* attr_name)
{
	throw core::NotImplementedException(
		"'" + this->__type__().name() + "::__get_attr__(const char*)' is not implemented",
		_ERROR_DETAILS_
	);
}

void Object::__set_attr__(const char* attr_name, const void* data)
{
	throw core::NotImplementedException(
		"'" + this->__type__().name() + "::__set_attr__(const char*, const void*)' is not implemented",
		_ERROR_DETAILS_
	);
}

bool Object::__has_attr__(const char* attr_name) const
{
	throw core::NotImplementedException(
		"'" + this->__type__().name() + "::__has_attr__(const char*)' is not implemented",
		_ERROR_DETAILS_
	);
}

Object::operator bool() const
{
	throw core::NotImplementedException(
		"'" + this->__type__().name() + "::operator bool() const' is not implemented",
		_ERROR_DETAILS_
	);
}

__OBJ_END__

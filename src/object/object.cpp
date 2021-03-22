/**
 * object/object.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./object.h"

// C++ libraries.
#include <sstream>

// Core libraries.
#include "../exceptions.h"


__OBJECT_BEGIN__

Object::Object()
{
	std::stringstream oss;
	oss << static_cast<const void*>(this);
	this->_object_address = oss.str();
}

std::shared_ptr<Object> Object::__get_attr__(const char* attr_name)
{
	if (this->__has_attr__(attr_name))
	{
		return this->__attrs__.at(attr_name).get();
	}

	throw core::AttributeError(
		"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'"
	);
}

void Object::__set_attr__(const char* attr_name, const void* data)
{
	if (this->__has_attr__(attr_name))
	{
		this->__attrs__[attr_name].set(data);
	}
	else
	{
		throw core::AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'"
		);
	}
}

Type Object::__type__() const
{
	return Type(*this);
}

std::string Object::__str__() const
{
	return "<" + this->__type__().name() + " object at " + this->_object_address + ">";
}

std::string Object::__repr__() const
{
	return this->__str__();
}

Object::operator bool() const
{
	return !this->__attrs__.empty();
}

bool Object::operator! () const
{
	return this->__attrs__.empty();
}

__OBJECT_END__

/**
 * object/attribute.cpp
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 */

#include "./attribute.h"


__OBJECT_BEGIN__

Attribute::Attribute(getter_t getter) : _getter(std::move(getter))
{
}

Attribute::Attribute(setter_t setter) : _setter(std::move(setter))
{
}

Attribute::Attribute(getter_t getter, setter_t setter)
	: _getter(std::move(getter)), _setter(std::move(setter))
{
}

std::shared_ptr<Object> Attribute::get() const
{
	if (this->_getter)
	{
		return this->_getter();
	}

	throw std::runtime_error("unable to get attribute value: logic is not provided");
}

void Attribute::set(const std::shared_ptr<Object>& data)
{
	if (!this->_setter)
	{
		throw std::runtime_error("unable to set attribute value: logic is not provided");
	}

	this->_setter(data);
}

__OBJECT_END__

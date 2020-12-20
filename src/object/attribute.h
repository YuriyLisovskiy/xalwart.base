/**
 * object/attribute.h
 *
 * Copyright (c) 2020 Yuriy Lisovskiy
 *
 * Purpose: holds address to a variable/class field and allows get and set it's value.
 */

#pragma once

#include <functional>
#include <exception>

// Module definitions.
#include "./_def_.h"


__OBJECT_BEGIN__

class Object;

class Attribute
{
public:
	typedef std::function<char*()> getter_t;
	typedef std::function<void(char*)> setter_t;

private:
	getter_t _getter;
	setter_t _setter;

public:
	Attribute() = default;

	explicit Attribute(getter_t getter)
	{
		this->_getter = getter;
	}

	explicit Attribute(setter_t setter)
	{
		this->_setter = setter;
	}

	explicit Attribute(getter_t getter, setter_t setter)
	{
		this->_getter = getter;
		this->_setter = setter;
	}

	[[nodiscard]] char* get() const
	{
		if (this->_getter)
		{
			return this->_getter();
		}

		throw std::runtime_error("unable to get attribute value: logic is not provided");
	}

	void set(char* val)
	{
		if (this->_setter)
		{
			this->_setter(val);
		}
		else
		{
			throw std::runtime_error("unable to set attribute value: logic is not provided");
		}
	}
};

__OBJECT_END__

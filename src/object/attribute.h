/**
 * object/attribute.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose: holds address to a variable/class field and allows get and set it's value.
 */

#pragma once

#include <functional>
#include <exception>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../utility.h"


__OBJECT_BEGIN__

class Object;

class Attribute
{
public:
	typedef std::function<std::shared_ptr<Object>()> getter_t;
	typedef std::function<void(const void*)> setter_t;

private:
	getter_t _getter;
	setter_t _setter;

public:
	Attribute() = default;
	explicit Attribute(getter_t getter);
	explicit Attribute(setter_t setter);
	explicit Attribute(getter_t getter, setter_t setter);

	[[nodiscard]]
	std::shared_ptr<Object> get() const;

	void set(const void* val);
};

__OBJECT_END__

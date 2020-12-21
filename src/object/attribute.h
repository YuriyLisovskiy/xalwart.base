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

// Core libraries.
#include "../utility.h"


__OBJECT_BEGIN__

class Attribute
{
public:
	typedef std::function<const std::vector<char>()> getter_t;
	typedef std::function<void(const std::vector<char>&)> setter_t;

private:
	getter_t _getter;
	setter_t _setter;

public:
	Attribute() = default;
	explicit Attribute(getter_t getter);
	explicit Attribute(setter_t setter);
	explicit Attribute(getter_t getter, setter_t setter);

	[[nodiscard]] std::vector<char> get() const;
	void set(const std::vector<char>& val);

//	template<typename ObjT>
//	[[nodiscard]] ObjT get() const
//	{
//		if (this->_getter)
//		{
//			return utility::deserialize<ObjT>(this->_getter().data());
//		}
//
//		throw std::runtime_error("unable to get attribute value: logic is not provided");
//	}
//
//	template<typename ObjT>
//	void set(ObjT val)
//	{
//		if (!this->_setter)
//		{
//			throw std::runtime_error("unable to set attribute value: logic is not provided");
//		}
//
//		this->_setter(utility::serialize(val).data());
//	}
};

__OBJECT_END__

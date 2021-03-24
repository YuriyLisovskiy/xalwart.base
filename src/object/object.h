/**
 * object/object.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Purpose:
 * 	Main parent for all derived classes which need to be rendered
 * 	or for some other purposes.
 */

#pragma once

// C++ libraries.
#include <sstream>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./meta.h"
#include "../exceptions.h"


__OBJ_BEGIN__

class Object
{
public:
	Object() = default;

	virtual ~Object() = default;

	// Returns `attr_name` attribute value of the object.
	//
	// Throws `core::AttributeError` by default.
	[[nodiscard]]
	virtual inline std::shared_ptr<Object> __get_attr__(const char* attr_name)
	{
		throw core::AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'",
			_ERROR_DETAILS_
		);
	}

	// Sets a new value to `attr_name` attribute.
	//
	// Throws `core::AttributeError` by default.
	virtual inline void __set_attr__(const char* attr_name, const void* data)
	{
		throw core::AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'",
			_ERROR_DETAILS_
		);
	}

	// Checks whether object has attribute with `attr_name` or not.
	//
	// Returns `false` by default.
	[[nodiscard]]
	virtual inline bool __has_attr__(const char* attr_name) const
	{
		return false;
	}

	// Returns basic meta information about the object.
	[[nodiscard]]
	inline meta::Type __type__() const
	{
		return meta::Type(*this);
	}

	// Default string representation of an object.
	[[nodiscard]]
	virtual inline std::string __str__() const
	{
		std::stringstream oss;
		oss << static_cast<const void*>(this);
		return "<" + this->__type__().name() + " object at " + oss.str() + ">";
	}

	// Used for debugging. By default returns '__str__()'.
	[[nodiscard]]
	virtual inline std::string __repr__() const
	{
		return this->__str__();
	}

	// Returns 0 if objects are equal, -1 if 'this' is less
	// than 'other' otherwise returns 1.
	//
	// Must be overwritten.
	[[nodiscard]]
	virtual short __cmp__(const Object* other) const = 0;

	// Returns boolean representation of the object.
	// Used in logical comparisons.
	//
	// Throws core::NotImplementedException by default.
	explicit virtual operator bool () const
	{
		throw core::NotImplementedException(
			"'" + this->__type__().name() + "::operator bool() const' is not implemented",
			_ERROR_DETAILS_
		);
	}

	// Negates and returns the result of `operator bool()`
	// by default.
	virtual inline bool operator! () const
	{
		return !this->operator bool();
	}
};

__OBJ_END__

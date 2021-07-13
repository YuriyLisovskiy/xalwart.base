/**
 * object/object.h
 *
 * Copyright (c) 2020-2021 Yuriy Lisovskiy
 *
 * Main parent for all derived classes which need to be rendered
 * or for some other purposes.
 */

#pragma once

// C++ libraries.
#include <sstream>

// Module definitions.
#include "./_def_.h"

// Base libraries.
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
	// Throws `AttributeError` by default.
	[[nodiscard]]
	virtual inline std::shared_ptr<const Object> __get_attr__(const char* attr_name) const
	{
		throw AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'",
			_ERROR_DETAILS_
		);
	}

	// Sets a new value to attribute.
	//
	// `attr_name`: name of an attribute to set.
	// `data`: pointer to data which should be set.
	//
	// Throws `AttributeError` by default.
	virtual inline void __set_attr__(const char* attr_name, const void* data)
	{
		throw AttributeError(
			"'" + this->__type__().name() + "' object has no attribute '" + std::string(attr_name) + "'",
			_ERROR_DETAILS_
		);
	}

	// Checks whether object has attribute or not.
	//
	// `attr_name`: name of an attribute to check.
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

	// Used for debugging. By default returns '__str__()' with
	// single quotes.
	[[nodiscard]]
	virtual inline std::string __repr__() const
	{
		return "'" + this->__str__() + "'";
	}

	// Returns 0 if objects are equal, -1 if 'this' is less
	// than 'other' otherwise returns 1.
	//
	// Throws NotImplementedException by default.
	[[nodiscard]]
	virtual inline short __cmp__(const Object* other) const
	{
		throw NotImplementedException(
			"Object of type '" + this->__type__().name() + "' does not support comparison",
			_ERROR_DETAILS_
		);
	}

	// Returns boolean representation of the object.
	// Used in logical comparisons.
	//
	// Throws NotImplementedException by default.
	explicit virtual operator bool () const
	{
		throw NotImplementedException(
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

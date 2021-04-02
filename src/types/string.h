/**
 * types/string.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Wrapper for `std::string` type for rendering it in templates.
 */

#pragma once

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../object/object.h"


__TYPES_BEGIN__

class String final : public obj::Object
{
protected:
	std::string value;

public:
	String() = default;

	inline explicit String(std::string s) : value(std::move(s))
	{
	}

	// Returns an internal string value.
	[[nodiscard]]
	inline std::string __str__() const override
	{
		return this->value;
	}

	// Returns an internal string value wrapped th quotes.
	[[nodiscard]]
	inline std::string __repr__() const override
	{
		return "'" + this->value + "'";
	}

	// Compares two objects.
	//
	// Throws `core::TypeError` if `other` is not `String`-type object.
	[[nodiscard]]
	short __cmp__(const Object* other) const override;

	// Returns `true` if internal string is not empty, `false` otherwise.
	inline explicit operator bool () const override
	{
		return !this->value.empty();
	}

	// Returns `true` if internal string is empty, `false` otherwise.
	inline bool operator! () const override
	{
		return this->value.empty();
	}

	// Returns an address to internal string.
	inline std::string& operator* ()
	{
		return this->value;
	}
};

typedef String string;

__TYPES_END__

/**
 * types/string.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <string_view>
#include <utility>

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
	inline explicit String(std::string s) : value(std::move(s))
	{
	}

	[[nodiscard]]
	inline std::string __str__() const override
	{
		return this->value;
	}

	[[nodiscard]]
	inline std::string __repr__() const override
	{
		return "'" + this->value + "'";
	}

	[[nodiscard]]
	short __cmp__(const Object* other) const override;

	explicit operator bool () const override;

	bool operator! () const override;

	inline std::string& operator* ()
	{
		return this->value;
	}
};

__TYPES_END__

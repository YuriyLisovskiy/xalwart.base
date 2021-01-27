/**
 * types/string.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Purpose: TODO
 */

#pragma once

// C++ libraries.
#include <iostream>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "../object/object.h"


__TYPES_BEGIN__

class String final : public object::Object
{
protected:
	xw::string internal_value;

public:
	inline explicit String(xw::string s) : internal_value(std::move(s))
	{
	}

	inline explicit String(xw::string&& s) : internal_value(std::forward<xw::string>(s))
	{
	}

	[[nodiscard]]
	inline xw::string get() const
	{
		return this->internal_value;
	}

	[[nodiscard]]
	inline xw::string __str__() const override
	{
		return this->internal_value;
	}

	[[nodiscard]]
	xw::string __repr__() const override
	{
		std::cout << std::string("sss");
		return "xw::types::String{" + this->internal_value + "}";
	}

	[[nodiscard]]
	short __cmp__(const Object* other) const override;

	explicit operator bool () const override;

	bool operator! () const override;
};

__TYPES_END__

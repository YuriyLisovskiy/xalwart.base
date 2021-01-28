/**
 * html.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./html.h"

// C++ libraries.
// TODO

// Core libraries.
#include "./string_utils.h"


__HTML_BEGIN__

std::string escape(const std::string& s, bool quote)
{
	auto escaped = s;
	str::replace(escaped, "&", "&amp;");    // Must be done first!
	str::replace(escaped, "<", "&lt;");
	str::replace(escaped, ">", "&gt;");
	if (quote)
	{
		str::replace(escaped, "\"", "&quot;");
		str::replace(escaped, "'", "&#x27;");
	}

	return escaped;
}

__HTML_END__

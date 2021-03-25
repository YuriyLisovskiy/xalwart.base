/**
 * html.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./html.h"

// Core libraries.
#include "./string_utils.h"


__HTML_BEGIN__

std::string escape(const std::string& input, bool quote)
{
	auto escaped = input;
	str::replace(escaped, "&", "&amp;"); // Must be done first!
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

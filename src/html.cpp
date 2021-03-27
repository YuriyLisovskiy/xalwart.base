/**
 * html.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./html.h"

// Core libraries.
#include "./string_utils.h"


__HTML_BEGIN__

std::string escape(std::string input, bool quote)
{
	str::replace(input, "&", "&amp;"); // Must be done first!
	str::replace(input, "<", "&lt;");
	str::replace(input, ">", "&gt;");
	if (quote)
	{
		str::replace(input, "\"", "&quot;");
		str::replace(input, "'", "&#x27;");
	}

	return input;
}

__HTML_END__

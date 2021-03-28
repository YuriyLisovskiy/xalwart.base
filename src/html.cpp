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
	input = str::replace(input, "&", "&amp;"); // Must be done first!
	input = str::replace(
		str::replace(input, "<", "&lt;"), ">", "&gt;"
	);
	if (quote)
	{
		input = str::replace(
			str::replace(input, "\"", "&quot;"), "'", "&#x27;"
		);
	}

	return input;
}

__HTML_END__

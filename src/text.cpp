/**
 * text.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./text.h"

// C++ libraries.
// TODO

// Framework libraries.
// TODO


__TEXT_BEGIN__

std::vector<std::string> smart_split(const std::string& text)
{
	auto smart_split_regex = SMART_SPLIT_REGEX;
	std::vector<std::string> result;
	smart_split_regex.setup(text);
	while (smart_split_regex.search_next())
	{
		result.push_back(smart_split_regex.group(0));
	}

	return result;
}

__TEXT_END__

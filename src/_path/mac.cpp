/**
 * _path/mac.cpp
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 */

#include "./mac.h"

#if defined(__mac__)

// C++ libraries.
#include <filesystem>


__PATH_BEGIN__

std::pair<std::string, std::string> split(const std::string& s)
{
	char colon = ':';
	if (s.find(colon) == std::string::npos)
	{
		return {"", s};
	}

	ssize_t col = 0;
	auto s_size = (ssize_t)s.size();
	for (ssize_t i = 0; i < s_size; i++)
	{
		if (s[i] == colon)
		{
			col = i + 1;
		}
	}

	auto p = s.substr(0, col - 1);
	auto file = s.substr(col);
	if (p.find(colon) != std::string::npos)
	{
		p = p + colon;
	}

	return {p, file};
}

std::string cwd()
{
	return std::filesystem::current_path();
}

__PATH_END__

#endif // __mac__

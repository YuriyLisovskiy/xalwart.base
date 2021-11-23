/**
 * _path/posix.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./posix.h"

#if defined(__linux__) || defined(__mac__)

// Base libraries.
#include "../string_utils.h"


__PATH_BEGIN__

std::string _basename(const std::string& p)
{
	size_t pos = p.rfind(path::path_sep);
	return p.substr(pos == std::string::npos ? 0 : pos + 1);
}

std::string _dirname(const std::string& p)
{
	size_t pos = p.rfind(path::path_sep);
	auto i = pos == std::string::npos ? 0 : pos + 1;
	auto head = p.substr(0, i);
	if (!head.empty() && head != std::string(head.size(), path::path_sep))
	{
		head = str::rtrim(head, path::path_sep);
	}

	return head;
}

__PATH_END__

#endif // __linux__ || __mac__

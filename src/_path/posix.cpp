/**
 * _path/posix.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./posix.h"

#ifdef __unix__

// C++ libraries.
#include <filesystem>
#include <unistd.h>

// Base libraries.
#include "../string_utils.h"
#include "../exceptions.h"


__PATH_BEGIN__

bool exists(const std::string& p)
{
	return access(p.c_str(), 0) == 0;
}

std::string basename(const std::string& p)
{
	size_t pos = p.rfind(path::path_sep);
	return p.substr(pos == std::string::npos ? 0 : pos + 1);
}

std::string dirname(const std::string& p)
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

std::string cwd()
{
	return std::filesystem::current_path();
}

__PATH_END__

#endif // __unix__

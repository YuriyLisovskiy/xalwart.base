/**
 * _path/posix.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./posix.h"

#ifdef __unix__

// C++ libraries.
#include <fstream>
#include <filesystem>
#include <unistd.h>

// Core libraries.
#include "../string_utils.h"
#include "../exceptions.h"


__PATH_BEGIN__

bool exists(const std::string& p)
{
	return access(p.c_str(), 0) == 0;
}

std::string basename(const std::string& p)
{
	size_t pos = p.rfind(path::sep);
	return p.substr(pos == std::string::npos ? 0 : pos + 1);
}

std::string dirname(const std::string& p)
{
	size_t pos = p.rfind(path::sep);
	auto i = pos == std::string::npos ? 0 : pos + 1;
	auto head = p.substr(0, i);
	if (!head.empty() && head != std::string(head.size(), path::sep))
	{
		head = str::rtrim(head, path::sep);
	}

	return head;
}

size_t get_size(const std::string& p)
{
	std::ifstream ifs(p, std::ifstream::ate | std::ifstream::binary);
	if (!ifs.is_open())
	{
		throw core::FileError("can not access file '" + p + "'", _ERROR_DETAILS_);
	}

	size_t result = ifs.tellg();
	ifs.close();
	return result;
}

std::string cwd()
{
	return std::filesystem::current_path();
}

__PATH_END__

#endif // __unix__
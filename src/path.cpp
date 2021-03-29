/**
 * path.cpp
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 */

#include "./path.h"

// C++ libraries.
#include <fstream>
#include <filesystem>

#if defined(_WIN32) || defined(_WIN64)
#include <io.h>
#include <direct.h>
#define access _access_s
#define getcwd _getcwd
#else
#include <unistd.h>
#endif

#ifdef _MSC_VER
#include <algorithm>
#endif

// Core libraries.
#include "./string_utils.h"
#include "./exceptions.h"


__PATH_BEGIN__

void _split_text(
	const std::string& full_path,
	char separator,
	char alt_separator,
	char ext_separator,
	std::string& root_out,
	std::string& ext_out
)
{
	root_out = full_path;
	ext_out = "";
	long sep_idx = full_path.rfind(separator);
	if (sep_idx == std::string::npos)
	{
		sep_idx = -1;
	}

	if (alt_separator != '\0')
	{
		long altsep_idx = full_path.rfind(alt_separator);
		if (altsep_idx == std::string::npos)
		{
			altsep_idx = -1;
		}

		sep_idx = std::max(sep_idx, altsep_idx);
	}

	long dot_idx = full_path.rfind(ext_separator);
	if (dot_idx == std::string::npos)
	{
		dot_idx = -1;
	}

	if (dot_idx > sep_idx)
	{
		// skip all leading dots
		size_t file_name_idx = sep_idx + 1;
		while (file_name_idx < dot_idx)
		{
			if (full_path.at(file_name_idx) != ext_separator)
			{
				root_out = full_path.substr(0, dot_idx);
				ext_out = full_path.substr(dot_idx);
				break;
			}

			file_name_idx++;
		}
	}
}

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
	if (!exists(p))
	{
		throw core::FileError("file '" + p + "' does not exist", _ERROR_DETAILS_);
	}

	std::ifstream ifs(p, std::ifstream::ate | std::ifstream::binary);
	size_t result = ifs.tellg();
	ifs.close();
	return result;
}

std::string join(const std::string& left, const std::string& right)
{
	auto new_left = str::rtrim(left, "/");
	return (new_left.empty() ? "." : new_left) + "/" + str::ltrim(right, "/");
}

std::string join(const std::vector<std::string>& paths)
{
	size_t size = paths.size();
	if (size == 0)
	{
		return "./";
	}

	if (size == 1)
	{
		return paths[0];
	}

	std::string result = str::rtrim(paths[0], "/");
	if (result.empty())
	{
		result = ".";
	}

	for (size_t i = 1; i < size - 1; i++)
	{
		auto part = str::trim(paths[i], "/");
		result += part.empty() ? "" : "/" + part;
	}

	auto part = str::ltrim(paths[size - 1], "/");
	result += part.empty() ? "" : "/" + part;

	return result == "." ? "./" : result;
}

std::string cwd()
{
	return std::filesystem::current_path();
}

bool is_absolute(const std::string& p)
{
#if defined(_WIN32) || defined(_WIN64)
	auto pos = p.find(':');
	if (pos != std::string::npos)
	{
		if (p.size() > pos + 1)
		{
			return p.substr(pos + 1)[0] == '\\';
		}

		return true;
	}
#else
	if (!p.empty())
	{
		return p[0] == '/';
	}
#endif

	return false;
}

__PATH_END__

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
	char sep,
	char altsep,
	char extsep,
	std::string& root_out,
	std::string& ext_out
)
{
	root_out = full_path;
	ext_out = "";
	size_t sep_idx = full_path.rfind(sep);
	if (altsep != '\0')
	{
		size_t altsep_idx = full_path.rfind(altsep);
		sep_idx = std::max(sep_idx, altsep_idx);
	}

	size_t dot_idx = full_path.rfind(extsep);
	if (dot_idx > sep_idx)
	{
		// skip all leading dots
		size_t file_name_idx = sep_idx + 1;
		while (file_name_idx < dot_idx)
		{
			if (full_path.at(file_name_idx) != extsep)
			{
				root_out = full_path.substr(0, dot_idx);
				ext_out = full_path.substr(dot_idx);
				break;
			}

			file_name_idx++;
		}
	}
}

bool exists(const std::string& path)
{
	return access(path.c_str(), 0) == 0;
}

std::string dirname(const std::string& path)
{
	size_t pos = path.rfind('/');
	if (pos == std::string::npos)
	{
		return "";
	}

	auto result = std::string(path.begin(), path.begin() + pos + 1);
	if (result.size() > 1)
	{
		result = str::rtrim(result, "/");
		while (result.ends_with("/."))
		{
			result = str::rtrim(str::rtrim(result, "."), "/");
		}
	}

	return result;
}

std::string basename(const std::string& path)
{
	size_t pos = path.rfind('/');
	if (pos == std::string::npos)
	{
		pos = 0;
	}
	else
	{
		pos += 1;
	}

	return str::rtrim(std::string(path.begin() + pos, path.end()), "/");
}

size_t get_size(const std::string& path)
{
	if (!exists(path))
	{
		throw core::FileError("file '" + path + "' does not exist", _ERROR_DETAILS_);
	}

	std::ifstream ifs(path, std::ifstream::ate | std::ifstream::binary);
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

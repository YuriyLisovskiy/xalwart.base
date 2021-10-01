/**
 * _path/posix.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Path utilities for Posix.
 */

#pragma once

#include "../sys.h"

#ifdef __unix__

// C++ libraries.
#include <string>
#include <vector>

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "./generic.h"


__PATH_BEGIN__

inline const char current_dir = '.';
inline const char* parent_dir = "..";
inline const char ext_sep = '.';
inline const char path_sep ='/';
inline const char path_list_sep = ':';
inline const char* def_path = "/bin:/usr/bin";
inline const char alt_sep = '\0';
inline const char* dev_null = "/dev/null";

// `p`: path to check.
//
// Returns `true` if path exists, `false` otherwise.
extern bool exists(const std::string& p);

// `p`: path to analyze.
//
// Returns the final component of a path name.
extern std::string basename(const std::string& p);

// `p`: path to analyze.
//
// Returns the directory component of a path name.
extern std::string dirname(const std::string& p);

template <typename... PartT>
void _join(std::string& out, const std::string& b, const PartT&... p)
{
	if (b.starts_with(path::path_sep))
	{
		out = b;
	}
	else if (out.empty() || out.ends_with(path::path_sep))
	{
		out += b;
	}
	else
	{
		out += std::string(1, path::path_sep) + b;
	}

	if constexpr (sizeof...(p) > 0)
	{
		_join(out, p...);
	}
}

// Join two or more pathname components, inserting 'path::sep'
// as needed. If any component is an absolute path, all previous path
// components will be discarded. An empty last part will result in a path
// that ends with a separator.
//
// `a`: first part of path.
// `p`: arguments pack of another parts.
template <typename... PartT>
std::string join(const std::string& a, const PartT&... p)
{
	std::string result_path = a;
	if constexpr (sizeof...(p) > 0)
	{
		_join(result_path, p...);
	}

	return result_path;
}

// Returns current working directory.
extern std::string cwd();

// Test whether a path is absolute.
//
// `p`: path to check.
//
// Returns `true` if path is absolute, `false` otherwise.
inline bool is_absolute(const std::string& p)
{
	return p.starts_with(path::path_sep);
}

__PATH_END__

#endif // __unix__

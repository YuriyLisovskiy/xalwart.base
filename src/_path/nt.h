/**
 * _path/nt.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Path utilities for WindowsNT/Windows95.
 */

#pragma once

#include "../sys.h"

#if defined(__windows__)

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "../string_utils.h"
#include "./generic.h"


__PATH_BEGIN__

inline const char current_dir = '.';
inline const char* parent_dir = "..";
inline const char ext_sep = '.';
inline const char path_sep = '\\';
inline const char path_list_sep = ';';
inline const char alt_sep = '/';
inline const char* def_path = ".;C:\\bin";
inline const char* dev_null = "nul";

// Split a path in head (everything up to the last '/') and tail (the
// rest). After the trailing '/' is stripped, the invariant
// join(head, tail) == p holds.
// The resulting head won't end in '/' unless it is the root.
extern std::pair<std::string, std::string> split(const std::string& p);

// `p`: path to check.
//
// Returns `true` if path exists, `false` otherwise.
extern bool exists(const std::string& p);

// `p`: path to analyze.
//
// Returns the final component of a path name.
inline std::string basename(const std::string& p)
{
	return split(p).second;
}

// `p`: path to analyze.
//
// Returns the directory component of a path name.
inline std::string dirname(const std::string& p)
{
	return split(p).first;
}

// Split a path in a drive specification (a drive letter followed by a
// colon) and the path specification.
// It is always true that drive_spec + path_spec == p
extern std::pair<std::string, std::string> split_drive(const std::string& p);

template <typename... PartT>
void _join(
	std::string& result_drive, std::string& result_path,
	const std::string& seps, const std::string& b, const PartT&... p
)
{
	auto [p_drive, p_path] = split_drive(b);
	if (!p_path.empty() && str::contains(seps, p_path[0]))
	{
		// Second path is absolute
		if (!p_drive.empty() || result_drive.empty())
		{
			result_drive = p_drive;
		}

		result_path = p_path;
		if constexpr (sizeof...(p) > 0)
		{
			_join(result_drive, result_path, seps, p...);
		}

		return;
	}
	else if (!p_drive.empty() && p_drive != result_drive)
	{
		if (str::to_lower(p_drive) != str::to_lower(result_drive))
		{
			// Different drives => ignore the first path entirely
			result_drive = p_drive;
			result_path = p_path;
			if constexpr (sizeof...(p) > 0)
			{
				_join(result_drive, result_path, seps, p...);
			}

			return;
		}

		// Same drive in different case
		result_drive = p_drive;
	}

	// Second path is relative to the first
	if (!result_path.empty() && !str::contains(seps, *result_path.end()))
	{
		result_path = result_path + path_sep;
	}

	result_path = result_path + p_path;
	if constexpr (sizeof...(p) > 0)
	{
		_join(result_drive, result_path, seps, p...);
	}
}

// Join two or more pathname components, inserting 'path::path_sep'
// as needed. If any component is an absolute path, all previous path
// components will be discarded. An empty last part will result in a path
// that ends with a separator.
//
// `a`: first part of path.
// `p`: arguments pack of another parts.
template <typename... PartT>
std::string join(const std::string& a, const PartT&... p)
{
	std::string seps = "\\/";
	char colon = ':';
	auto [result_drive, result_path] = split_drive(a);
	if constexpr (sizeof...(p) > 0)
	{
		_join(result_drive, result_path, seps, p...);
	}

	// add separator between UNC and non-absolute path
	if (
		!result_path.empty() && !str::contains(seps, result_path[0]) &&
		!result_drive.empty() && *result_drive.end() != colon
	)
	{
		return result_drive + path_sep + result_path;
	}

	return result_drive + result_path;
}

// Returns current working directory.
extern std::string cwd();

// Test whether a path is absolute.
//
// `p`: path to check.
//
// For Windows it is absolute if it starts with a slash or backslash (current
// volume), or if a pathname after the volume-letter-and-colon or UNC-resource
// starts with a slash or backslash.
extern bool is_absolute(const std::string& p);

__PATH_END__

#endif // __windows__

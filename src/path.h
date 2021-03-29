/**
 * path.h
 *
 * Copyright (c) 2019-2021 Yuriy Lisovskiy
 *
 * Utilities for working with path.
 */

#pragma once

// C++ libraries.
#include <string>
#include <vector>

// Module definitions.
#include "./_def_.h"

// Core libraries.
#include "./os.h"


__PATH_BEGIN__

inline const char current_dir = '.';
inline const char* parent_dir = "..";
inline const char ext_sep = '.';

#if defined(__windows__)

inline const char sep = '\\';
inline const char path_sep = ';';
inline const char* def_path = ".;C:\\bin";
inline const char alt_sep = '/';
inline const char* dev_null = "nul";

#elif defined(__unix__)

inline const char sep ='/';
inline const char path_sep = ':';
inline const char* def_path = "/bin:/usr/bin";
inline const char alt_sep = '\0';
inline const char* dev_null = "/dev/null";

#endif

// Split a path in root and extension.
// The extension is everything starting at the last dot in the last
// pathname component; the root is everything before that.
// It is always true that root + ext == p.
//
// Generic implementation of splitext, to be parametrized with
// the separators.
extern void _split_text(
	const std::string& full_path,
	char separator,
	char alt_separator,
	char ext_separator,
	std::string& root_out,
	std::string& ext_out
);

// Split a path in root and extension.
// The extension is everything starting at the last dot in the last
// pathname component; the root is everything before that.
// It is always true that `root + ext == p`.
inline void split_text(const std::string& full_path, std::string& root_out, std::string& ext_out)
{
	_split_text(full_path, path::sep, path::alt_sep, path::ext_sep, root_out, ext_out);
}

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

// `p`: path to access.
//
// Returns file size in bytes.
extern size_t get_size(const std::string& p);

template <typename... PartT>
void _join(std::string& out, const std::string& b, const PartT&... p)
{
	if (b.starts_with(path::sep))
	{
		out = b;
	}
	else if (out.empty() || out.ends_with(path::sep))
	{
		out += b;
	}
	else
	{
		out += std::string(1, path::sep) + b;
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
	return p.starts_with(path::sep);
}

__PATH_END__

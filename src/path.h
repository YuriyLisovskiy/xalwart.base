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


__PATH_BEGIN__

// TESTME: _split_text
// Split a path in root and extension.
// The extension is everything starting at the last dot in the last
// pathname component; the root is everything before that.
// It is always true that root + ext == p.
//
// Generic implementation of splitext, to be parametrized with
// the separators.
extern void _split_text(
	const std::string& full_path,
	char sep,
	char altsep,
	char extsep,
	std::string& root_out,
	std::string& ext_out
);

// TESTME: split_text
// Split a path in root and extension.
// The extension is everything starting at the last dot in the last
// pathname component; the root is everything before that.
// It is always true that `root + ext == p`.
inline void split_text(const std::string& full_path, std::string& root_out, std::string& ext_out)
{
	_split_text(full_path, '/', '\0', '.', root_out, ext_out);
}

// TESTME: exists
// `path`: path to check.
//
// Returns `true` if path exists, `false` otherwise.
extern bool exists(const std::string& path);

// TESTME: dirname
// `path`: path to analyze.
//
// Returns base directory name from given path.
extern std::string dirname(const std::string& path);

// TESTME: basename
// `path`: path to analyze.
//
// Returns file name from given path.
extern std::string basename(const std::string& path);

// TESTME: get_size
// `path`: path to access.
//
// Returns file size in bytes.
extern size_t get_size(const std::string& path);

// TESTME: join(left, right)
// Joins two strings to single path.
//
// `left`: left path part.
// `right`: right path part.
extern std::string join(const std::string& left, const std::string& right);

// TESTME: join(vector)
// Joins vector of strings to single path.
//
// `paths`: vector of path parts.
extern std::string join(const std::vector<std::string>& paths);

// Returns current working directory.
extern std::string cwd();

// TESTME: is_absolute
// Checks if path is absolute or not.
//
// `p`: path to check.
//
// Returns `true` if path is absolute, `false` otherwise.
extern bool is_absolute(const std::string& p);

__PATH_END__

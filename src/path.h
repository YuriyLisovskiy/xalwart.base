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

// TESTME: get_size
// `p`: path to access.
//
// Returns file size in bytes.
extern size_t get_size(const std::string& p);

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

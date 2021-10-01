/**
 * _path/mac.h
 *
 * Copyright (c) 2021 Yuriy Lisovskiy
 *
 * Pathname and path-related operations for the Macintosh.
 */

#pragma once

#include "../sys.h"

#if defined(__mac__)

// Module definitions.
#include "../_def_.h"

// Base libraries.
#include "./generic.h"


__PATH_BEGIN__

inline const char current_dir = ':';
inline const char* parent_dir = "::";
inline const char ext_sep = '.';
inline const char path_sep = ':';
inline const char path_list_sep = '\n';
inline const char* def_path = ":";
inline const char alt_sep = '\0';
inline const char* dev_null = "Dev:Null";

inline bool exists(const std::string& p)
{
	struct stat buffer{};
	return (stat(p.c_str(), &buffer) == 0);
}

// Split a pathname into two parts: the directory leading up to the final
// bit, and the basename (the filename, without colons, in that directory).
// The result (s, t) is such that join(s, t) yields the original argument.
extern std::pair<std::string, std::string> split(const std::string& p);

inline std::string basename(const std::string& p)
{
	return split(p).second;
}

inline std::string dirname(const std::string& p)
{
	return split(p).first;
}

// TODO: implement 'void _join(std::string& out, const std::string& b, const PartT&... p)'
template <typename... PartT>
inline void _join(std::string& out, const std::string& b, const PartT&... p)
{
	// TODO:
}

// TODO: implement 'std::string join(const std::string& a, const PartT&... p)'
template <typename... PartT>
inline std::string join(const std::string& a, const PartT&... p)
{
	// TODO:
	return "";
}

// Returns current working directory.
extern std::string cwd();

// Return true if a path is absolute.
// On the Mac, relative paths begin with a colon,
// but as a special case, paths with no colons at all are also relative.
// Anything else is absolute (the string up to the first colon is the
// volume name).
inline bool is_absolute(const std::string& p)
{
	char colon = ':';
	return !p.empty() && p.front() != colon && p.find(colon) != std::string::npos;
}

__PATH_END__

#endif // __mac__

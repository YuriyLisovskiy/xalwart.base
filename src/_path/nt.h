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


__PATH_BEGIN__

inline const char current_dir = '.';
inline const char* parent_dir = "..";
inline const char ext_sep = '.';
inline const char sep = '\\';
inline const char path_sep = ';';
inline const char alt_sep = '/';
inline const char* def_path = ".;C:\\bin";
inline const char* dev_null = "nul";

// TODO: implement 'void split_text(const std::string& full_path, std::string& root_out, std::string& ext_out)'
// TODO: implement 'bool exists(const std::string& p)'
// TODO: implement 'std::string basename(const std::string& p)'
// TODO: implement 'std::string dirname(const std::string& p)'
// TODO: implement 'void _join(std::string& out, const std::string& b, const PartT&... p)'
// TODO: implement 'std::string join(const std::string& a, const PartT&... p)'
// TODO: implement 'bool is_absolute(const std::string& p)'

__PATH_END__

#endif // __windows__
